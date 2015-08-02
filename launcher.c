#define _WIN32_WINNT 0x0601
#define WIN32_LEAN_AND_MEAN
#define PSAPI_VERSION 1
#include <windows.h>
#include <objbase.h>
#include <propvarutil.h>
#include <shobjidl.h>
#include <shellapi.h>
#include <propsys.h>
#include <propkey.h>
#include <processthreadsapi.h>
#include <psapi.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <wchar.h>

#include "macros.h"

static void ShowError(const char* desc, const char* err, const long code) {
	char msg[1024];

	sprintf(msg, "%s. Reason: %s (0x%lx)", desc, err, code);
	MessageBox(NULL, msg, "Launcher error", MB_ICONEXCLAMATION | MB_OK);
}

static void ShowLastError(const char* desc) {
	DWORD code;
	char* err;

	code = GetLastError();
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&err, 0, NULL);
	ShowError(desc, err, code);
	LocalFree(err);
}


PROCESS_INFORMATION StartChild(const wchar_t* cmdline) {
	STARTUPINFOW si;
	PROCESS_INFORMATION pi;
	DWORD code;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	SetLastError(0);
	code = CreateProcessW(NULL, (wchar_t*)cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	if (code == 0) {
		ShowLastError("Could not start the shell");
		return pi;
	}

	return pi;
}

static int SetEnv(const char* msystem) {
	int code;
	char* env;
	const char* err;
	const char prefix[] = "MSYSTEM=";

	env = (char*)alloca(strlen(prefix) + strlen(msystem) + 1);
	strcpy(env, prefix);
	strcat(env, msystem);
	code = putenv(env);
	if (code != 0) {
		err = strerror(errno);
		ShowError("Could not set MSYSTEM", err, errno);
		return 0;
	}

	return 1;
}

struct handle_data {
	unsigned long process_id;
	HWND best_handle;
};


BOOL is_main_window(HWND handle)
{
	return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}


BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam)
{
	struct handle_data* data = (struct handle_data*)lParam;
	unsigned long process_id = 0;
	GetWindowThreadProcessId(handle, &process_id);
	if (data->process_id != process_id || !is_main_window(handle)) {
		return TRUE;
	}
	data->best_handle = handle;
	return FALSE;
}

HWND find_main_window(unsigned long process_id)
{
	struct handle_data data;
	data.process_id = process_id;
	data.best_handle = 0;
	EnumWindows(enum_windows_callback, (LPARAM)&data);
	return data.best_handle;
}



HRESULT SetAppUserModelProperty(IPropertyStore* store, const PROPERTYKEY* key, LPCWSTR value) {
	PROPVARIANT propVariant;
	HRESULT hr;

	propVariant.vt = VT_LPWSTR;
	hr = SHStrDupW(value, &propVariant.pwszVal);
	if (FAILED(hr)) {
		return hr;
	}

	hr = store->lpVtbl->SetValue(store, key, &propVariant);
	if (FAILED(hr)) {
		return hr;
	}

	return 0;
}


int main(int argc, char* argv[]) {
	PROCESS_INFORMATION child;
	DWORD code;
	int res;
	HWND window;
	IPropertyStore* store;
	HRESULT hr;
	size_t buflen;
	wchar_t* buf;
	wchar_t msysdir[PATH_MAX], exepath[PATH_MAX];
	int delay = 10;

	UNUSED(argc);
	UNUSED(argv);

	code = GetModuleFileNameW(NULL, exepath, sizeof(exepath) / sizeof(exepath[0]));
	if (code == 0) {
		ShowLastError("Could not determine executable path");
		return __LINE__;
	}

	while (wcschr(exepath, L'\\') != NULL) {
		wcschr(exepath, L'\\')[0] = L'/';
	}
	wcscpy(msysdir, exepath);
	if (wcsrchr(msysdir, L'/') != NULL) {
		wcsrchr(msysdir, L'/')[0] = L'\0';
	}
	buflen = wcslen(msysdir) + 1000;
	buf = (wchar_t*)alloca(buflen * sizeof(wchar_t));

	code = SetEnv(STRINGIFY_A(MSYSTEM));
	if (code == 0) {
		return __LINE__;
	}

	res = swprintf(buf, buflen, L"%s/usr/bin/mintty.exe -i '%s' /usr/bin/bash --login -i", msysdir, exepath);
	if (res < 0) {
		return __LINE__;
	}

	child = StartChild(buf);
	if (child.hProcess == NULL) {
		return __LINE__;
	}

	while (true) {
		Sleep(delay);
		window = find_main_window(GetProcessId(child.hProcess));
		if (!window) {
			delay *= 2;
			if (delay > 60000) {
				return __LINE__;
			}
			continue;
		}

		hr = SHGetPropertyStoreForWindow(window, &IID_IPropertyStore, (void**)&store);
		if (FAILED(hr)) {
			return __LINE__;
		}

		hr = SetAppUserModelProperty(store, &PKEY_AppUserModel_ID, L"MSYS2.Shell." STRINGIFY_W(MSYSTEM) L".7");
		if (FAILED(hr)) {
			return __LINE__;
		}

		hr = SetAppUserModelProperty(store, &PKEY_AppUserModel_RelaunchDisplayNameResource, L"MSYS2 " STRINGIFY_W(MSYSTEM) L" shell");
		if (FAILED(hr)) {
			return __LINE__;
		}

		hr = SetAppUserModelProperty(store, &PKEY_AppUserModel_RelaunchCommand, exepath);
		if (FAILED(hr)) {
			return __LINE__;
		}

		hr = SetAppUserModelProperty(store, &PKEY_AppUserModel_RelaunchIconResource, exepath);
		if (FAILED(hr)) {
			return __LINE__;
		}

		hr = store->lpVtbl->Commit(store);
		if (FAILED(hr)) {
			return __LINE__;
		}

		store->lpVtbl->Release(store);
		store = NULL;
		break;
	}

	return 0;
}
