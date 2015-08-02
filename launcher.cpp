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
#include <stdio.h>
#include <string>

#include "pathtools.h"

#define UNUSED(x) ((void)(x))
#define STRINGIFY_A_(x) #x
#define STRINGIFY_W_(x) L ## #x
#define STRINGIFY_A(x) STRINGIFY_A_(x)
#define STRINGIFY_W(x) STRINGIFY_W_(x)

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


PROCESS_INFORMATION StartChild(const char* cmdline) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD code;
	
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	SetLastError(0);
	code = CreateProcess(NULL, (char*)cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	if (code == 0) {
		ShowLastError(cmdline);
		// ShowLastError("Could not start console");
		return pi;
	}
	
	return pi;
}

static int SetEnv(const char* msystem) {
	int code;
	char* env;
	const char* err;
	const char prefix[] = "MSYSTEM=";
	
	env = (char*)malloc(strlen(prefix) + strlen(msystem) + 1);
	if (env == NULL) {
		ShowError("Could not allocate memory", "", errno);
		return 0;
	}
	
	strcpy(env, prefix);
	strcat(env, msystem);
	
	code = putenv(env);
	if (code != 0) {
		err = strerror(errno);
		ShowError("Could not set MSYSTEM", err, errno);
		free(env);
		return 0;
	}
	
	free(env);
	
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



HRESULT SetAppUserModelProperty(IPropertyStore* store, const PROPERTYKEY key, LPCWSTR value) {
	PROPVARIANT propVariant;
	HRESULT hr;
	
	hr = InitPropVariantFromString(value, &propVariant);
	if (FAILED(hr)) {
		return hr;
	}
	
	hr = store->SetValue(key, propVariant);
	if (FAILED(hr)) {
		return hr;
	}
	
	return 0;
}


int main(int argc, char* argv[]) {
	PROCESS_INFORMATION child;
	DWORD code;
	HWND window;
	IPropertyStore* store;
	HRESULT hr;
	char* cmdline;
	const char cmd[] = "/usr/bin/mintty.exe -i /msys2.ico /usr/bin/bash --login -i";
	char msysdirA[PATH_MAX];
	wchar_t msysdirW[PATH_MAX];
	
	UNUSED(argc);
	UNUSED(argv);
	
	get_executable_path(argv[0], msysdirA, sizeof(msysdirA) / sizeof(msysdirA[0]));
	if (strrchr(msysdirA, '/') != NULL) {
		strrchr(msysdirA, '/')[1] = '\0';
	}
	mbstowcs(msysdirW, msysdirA, sizeof(msysdirW) / sizeof(msysdirW[0]));
	
	cmdline = (char*)malloc(strlen(msysdirA) + strlen(cmd) + 1);
	strcpy(cmdline, msysdirA);
	strcat(cmdline, cmd);
	
	code = SetEnv(STRINGIFY_A(MSYSTEM));
	if (code == 0) {
		return __LINE__;
	}
	
	child = StartChild(cmdline);
	if (child.hProcess == NULL) {
		return __LINE__;
	}
	
	while (true) {
		Sleep(100);
		window = find_main_window(GetProcessId(child.hProcess));
		if (!window) {
			continue;
		}
		
		hr = SHGetPropertyStoreForWindow(window, IID_PPV_ARGS(&store));
		if (FAILED(hr)) {
			return __LINE__;
		}
		
		hr = SetAppUserModelProperty(store, PKEY_AppUserModel_ID, L"MSYS2.Shell." STRINGIFY_W(MSYSTEM) L".0");
		if (FAILED(hr)) {
			return __LINE__;
		}
		
		hr = SetAppUserModelProperty(store, PKEY_AppUserModel_RelaunchCommand, (std::wstring(msysdirW) + (L"/" STRINGIFY_W(EXENAME))).c_str());
		if (FAILED(hr)) {
			return __LINE__;
		}
		
		hr = SetAppUserModelProperty(store, PKEY_AppUserModel_RelaunchDisplayNameResource, L"MSYS2 " STRINGIFY_W(MSYSTEM) L" shell");
		if (FAILED(hr)) {
			return __LINE__;
		}
		
		hr = SetAppUserModelProperty(store, PKEY_AppUserModel_RelaunchIconResource, (std::wstring(msysdirW) + L"/msys2.ico").c_str());
		if (FAILED(hr)) {
			return __LINE__;
		}
		
		hr = store->Commit();
		if (FAILED(hr)) {
			return __LINE__;
		}
		
		store->Release();
		store = NULL;
		break;
	}
	
	return 0;
}
