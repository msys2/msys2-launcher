#define __USE_MINGW_ANSI_STDIO 1
#define _UNICODE
#define _WIN32_WINNT 0x0601
#define WIN32_LEAN_AND_MEAN
#define PSAPI_VERSION 1
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <wchar.h>
int _CRT_glob = 0;

#include "macros.h"

// if any of the properties change, it's best to use a brand new AppID
#define APPID_REVISION 9

static void ShowError(const wchar_t* desc, const wchar_t* err, const long code) {
	wchar_t msg[1024];

	swprintf(msg, 1024, L"%ls. Reason: %ls (0x%lx)", desc, err, code);
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

// adapted from http://www.partow.net/programming/hashfunctions/index.html
// MIT licensed
static unsigned int APHash(const wchar_t* str, size_t length) {
	unsigned int hash = 0xAAAAAAAA;
	size_t i = 0;

	for (i = 0; i < length; ++str, ++i) {
		hash ^= ((i & 1) == 0)
			? ((hash <<  7) ^ (*str) * (hash >> 3))
			: (~((hash << 11) + ((*str) ^ (hash >> 5))))
		;
	}

	return hash;
}

static PROCESS_INFORMATION StartChild(wchar_t* cmdline) {
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

static wchar_t* SetEnv(wchar_t* conffile) {
	int code;
	size_t buflen;
	size_t expandedlen;
	wchar_t* tmp;
	wchar_t* buf;
	wchar_t* expanded;
	wchar_t* msystem;
	FILE* handle;

	msystem = NULL;

	handle = _wfopen(conffile, L"rt");
	if (handle == NULL) {
		ShowErrno(L"Could not open configuration file");
		return msystem;
	}

	buflen = 512;
	buf = (wchar_t*)malloc(buflen * sizeof(wchar_t));
	*buf = L'\0';
	expandedlen = 2 * buflen;
	expanded = (wchar_t*)malloc(expandedlen * sizeof(wchar_t));
	while (true) {
		tmp = fgetws(buf + wcslen(buf), buflen - wcslen(buf), handle);
		if (tmp == NULL && !feof(handle)) {
			ShowErrno(L"Could not read from configuration file");
			return NULL;
		}

		tmp = buf + wcslen(buf) - 1;
		if (!feof(handle) && *tmp != L'\n') {
			buflen *= 2;
			buf = (wchar_t*)realloc(buf, buflen * sizeof(wchar_t));
			continue;
		}
		if (!feof(handle)) {
			*tmp = L'\0';
		}

		if (*buf != L'\0' && *buf != L'#') {
			tmp = wcschr(buf, L'=');
			if (tmp != NULL) {
				*tmp++ = L'\0';
				while (expandedlen < 32768) {
					code = ExpandEnvironmentStrings(tmp, expanded, expandedlen);
					if ((size_t)code <= expandedlen) {
						break;
					}
					expandedlen *= 2;
					expanded = (wchar_t*)realloc(expanded, expandedlen * sizeof(wchar_t));
				}
				if ((*tmp != L'\0' && code == 0) || (size_t)code > expandedlen) {
					ShowLastError(L"Could not expand string");
				}
				if (0 == wcscmp(L"MSYSTEM", buf)) {
					msystem = _wcsdup(expanded);
					if (msystem == NULL) {
						ShowError(L"Could not duplicate string", expanded, 0);
						return NULL;
					}
				}
				code = SetEnvironmentVariable(buf, expanded);
				if (code == 0) {
					ShowLastError(L"Could not set environment variable");
				}
			} else {
				ShowError(L"Could not parse environment line", buf, 0);
			}
		}

		*buf = L'\0';
		if (feof(handle)) {
			break;
		}
	}

	code = fclose(handle);
	if (code != 0) {
		ShowErrno(L"Could not close configuration file");
	}

	return msystem;
}

int wmain(int argc, wchar_t* argv[]) {
	PROCESS_INFORMATION child;
	int code;
	size_t buflen;
	wchar_t* buf;
	wchar_t* tmp;
	wchar_t* args;
	wchar_t* msystem;
	wchar_t* msysdirhash;
	wchar_t msysdir[PATH_MAX];
	wchar_t exepath[PATH_MAX];
	wchar_t confpath[PATH_MAX];

	code = GetModuleFileName(NULL, exepath, sizeof(exepath) / sizeof(*exepath));
	if (code == 0) {
		ShowLastError(L"Could not determine executable path");
		return __LINE__;
	}

	tmp = exepath;
	while ((tmp = wcschr(tmp, L'/')) != NULL) {
		*tmp = L'\\';
	}

	wcscpy(msysdir, exepath);
	tmp = wcsrchr(msysdir, L'\\');
	if (tmp == NULL) {
		ShowError(L"Could not find root directory", msysdir, 0);
		return __LINE__;
	}
	*tmp = L'\0';

	msysdirhash = (wchar_t*)alloca(10 * sizeof(wchar_t)); // dot + unsigned int as %x + null
	if (msysdirhash == NULL) {
		ShowError(L"Could not allocate memory", L"", 0);
		return __LINE__;
	}
	if (wcsicmp(msysdir, L"C:\\msys64") == 0) {
		code = swprintf(msysdirhash, 10, L""); // no change in AppID for default installations
	} else {
		code = swprintf(msysdirhash, 10, L".%8x", APHash(msysdir, wcslen(msysdir)));
	}
	if (code < 0) {
		ShowErrno(L"Could not write to buffer");
		return __LINE__;
	}

	wcscpy(confpath, exepath);
	tmp = confpath + wcslen(confpath) - 4;
	if (wcsicmp(L".exe", tmp) != 0) {
		ShowError(L"Could not find configuration file", confpath, 0);
		return __LINE__;
	}
	*tmp++ = L'.';
	*tmp++ = L'i';
	*tmp++ = L'n';
	*tmp++ = L'i';

	if (argc > 1) {
		code = SetEnvironmentVariable(L"CHERE_INVOKING", L"1");
		if (code == 0) {
			ShowLastError(L"Could not set environment variable");
		}
	}

	msystem = SetEnv(confpath);
	if (msystem == NULL) {
		ShowError(L"Did not find the MSYSTEM variable", confpath, 0);
		return __LINE__;
	}

	code = SetEnvironmentVariable(L"MSYSCON", L"mintty.exe");
	if (code == 0) {
		ShowLastError(L"Could not set environment variable");
	}

	args = GetCommandLine();
	tmp = argv[0];
	while (*tmp != L'\0') {
		if (*args == *tmp) {
			args++;
			tmp++;
		} else if (*args == L'"') {
			args++;
		} else {
			ShowError(L"Could not parse command name", argv[0], 0);
			return __LINE__;
		}
	}
	while (*args == L'"') {
		args++;
	}
	while (*args == L' ') {
		args++;
	}

	code = -1;
	buf = NULL;
	buflen = 1024;
	while (code < 0 && buflen < 8192) {
		buf = (wchar_t*)realloc(buf, buflen * sizeof(wchar_t));
		if (buf == NULL) {
			ShowError(L"Could not allocate memory", L"", 0);
			return __LINE__;
		}
		code = swprintf(buf, buflen, L"%ls\\usr\\bin\\mintty.exe -i '%ls' -o 'AppLaunchCmd=%ls' -o 'AppID=MSYS2.Shell.%ls.%d%ls' -o 'AppName=MSYS2 %ls Shell' -t 'MSYS2 %ls Shell' --store-taskbar-properties -- %ls %ls", msysdir, exepath, exepath, msystem, APPID_REVISION, msysdirhash, msystem, msystem, argc == 1 ? L"-" : L"/usr/bin/sh -lc '\"$@\"' sh", args);
		buflen *= 2;
	}
	if (code < 0) {
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
