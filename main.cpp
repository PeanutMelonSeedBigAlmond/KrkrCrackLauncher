#include <Windows.h>
#include <detours.h>
#include "IniConstant.h"
#pragma comment(lib,"detours.lib")

/** ������Դ��
* ���̡̳�kirikiri���к���֤ä��ʼ�
* https://bbs.zdfx.net/thread-385589-1-1.html
* (����: �յ����)
*/

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	wchar_t CommandLine[256] = { 0 };
	GetCurrentDirectory(_countof(CommandLine), CommandLine);

	// ��ȡini·��
	TCHAR fullIniName[1024] = { 0 };
	CopyMemory(fullIniName, CommandLine, sizeof(CommandLine));
	wcscat_s(fullIniName, _countof(fullIniName), TEXT(INI_NAME));

	// ��ȡini����Ϸexe������
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
		(const wchar_t*)exeName // ��Ϸ����������
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
		"KrkrCrack.dll", // ��������ƽ�dll�ļ���
		NULL
	);
	return 0;
}