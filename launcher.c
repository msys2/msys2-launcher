#define _UNICODE
#define _WIN32_WINNT 0x0601
#define WIN32_LEAN_AND_MEAN
#define PSAPI_VERSION 1
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <wchar.h>

#include "macros.h"

// if any of the properties change, it's best to use a brand new AppID
#define APPID_REVISION 8

static void ShowError(const wchar_t* desc, const wchar_t* err, const long code) {
	wchar_t msg[1024];

	swprintf(msg, 1024, L"%s. Reason: %s (0x%lx)", desc, err, code);
	MessageBox(NULL, msg, L"Launcher error", MB_ICONEXCLAMATION | MB_OK);
}

static void ShowLastError(const wchar_t* desc) {
	DWORD code;
	wchar_t* err;

	code = GetLastError();
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&err, 0, NULL);
	ShowError(desc, err, code);
	LocalFree(err);
}

static void ShowErrno(const wchar_t* desc) {
	wchar_t* err;

	err = _wcserror(errno);
	ShowError(desc, err, errno);
}

PROCESS_INFORMATION StartChild(wchar_t* cmdline) {
	STARTUPINFOW si;
	PROCESS_INFORMATION pi;
	DWORD code;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	SetLastError(0);
	code = CreateProcess(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	if (code == 0) {
		ShowLastError(L"Could not start the shell");
		ShowError(L"The command was", cmdline, 0);
		return pi;
	}

	return pi;
}

static int SetEnv(const char* msystem) {
	int code;
	char* env;
	const char prefix[] = "MSYSTEM=";

	env = (char*)alloca(strlen(prefix) + strlen(msystem) + 1);
	strcpy(env, prefix);
	strcat(env, msystem);
	code = putenv(env);
	if (code != 0) {
		ShowErrno(L"Could not set MSYSTEM");
		return 0;
	}

	return 1;
}

int wmain(int argc, wchar_t* argv[]) {
	PROCESS_INFORMATION child;
	DWORD code;
	int res;
	size_t buflen;
	wchar_t* buf;
	wchar_t* args;
	wchar_t msysdir[PATH_MAX], exepath[PATH_MAX];

	UNUSED(argc);
	UNUSED(argv);

	code = GetModuleFileName(NULL, exepath, sizeof(exepath) / sizeof(exepath[0]));
	if (code == 0) {
		ShowLastError(L"Could not determine executable path");
		return __LINE__;
	}

	while (wcschr(exepath, L'\\') != NULL) {
		wcschr(exepath, L'\\')[0] = L'/';
	}
	wcscpy(msysdir, exepath);
	if (wcsrchr(msysdir, L'/') != NULL) {
		wcsrchr(msysdir, L'/')[0] = L'\0';
	}

	code = SetEnv(STRINGIFY_A(MSYSTEM));
	if (code == 0) {
		return __LINE__;
	}

	// can break, but hopefully won't for most use cases
	args = GetCommandLine();
	if (args[0] == '"') {
		args++;
	}
	args += wcslen(argv[0]);
	if (args[0] == '"') {
		args++;
	}

	res = -1;
	buf = NULL;
	buflen = 1024;
	while (res < 0 && buflen < 8192) {
		buf = (wchar_t*)realloc(buf, buflen * sizeof(wchar_t));
		if (buf == NULL) {
			ShowError(L"Could not allocate memory", L"", 0);
			return __LINE__;
		}
		res = swprintf(buf, buflen, L"%s/usr/bin/mintty.exe -i '%s' -o 'AppLaunchCmd=%s' -o 'AppID=MSYS2.Shell.%s.%d' -o 'AppName=MSYS2 %s Shell' --store-taskbar-properties -- /usr/bin/bash --login %s %s", msysdir, exepath, exepath, STRINGIFY_W(MSYSTEM), APPID_REVISION, STRINGIFY_W(MSYSTEM), argc == 1 ? L"-i" : L"-c '$0 \"$@\"'", args);
		buflen *= 2;
	}
	if (res < 0) {
		ShowErrno(L"Could not write to buffer");
		return __LINE__;
	}

	child = StartChild(buf);
	if (child.hProcess == NULL) {
		return __LINE__;
	}

	free(buf);
	buf = NULL;

	return 0;
}
