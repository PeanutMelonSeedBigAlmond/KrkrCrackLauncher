#include <Windows.h>
#include <detours.h>
#include "IniConstant.h"
#pragma comment(lib,"detours.lib")

/** 代码来源：
* 【教程】kirikiri序列号验证盲拆笔记
* https://bbs.zdfx.net/thread-385589-1-1.html
* (出处: 终点分享)
*/

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	wchar_t CommandLine[256] = { 0 };
	GetCurrentDirectory(_countof(CommandLine), CommandLine);

	// 获取ini路径
	TCHAR fullIniName[1024] = { 0 };
	CopyMemory(fullIniName, CommandLine, sizeof(CommandLine));
	wcscat_s(fullIniName, _countof(fullIniName), TEXT(INI_NAME));

	// 获取ini中游戏exe的名称
	TCHAR exeName[256] = { 0 };
	GetPrivateProfileString(
		TEXT(GAME_CONFIG_SECTION_NAME),
		TEXT(GAME_EXECUTABLE_NAME),
		TEXT(""),
		exeName,
		_countof(exeName),
		(const wchar_t*)fullIniName
	);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);
	wcscat_s(
		CommandLine,
		_countof(CommandLine),
		TEXT("\\")
	);
	wcscat_s(
		CommandLine,
		_countof(CommandLine),
		(const wchar_t*)exeName // 游戏主程序名称
	);
	DetourCreateProcessWithDllEx(
		NULL,
		CommandLine,
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi,
		"KrkrCrack.dll", // 编译出的破解dll文件名
		NULL
	);
	return 0;
}