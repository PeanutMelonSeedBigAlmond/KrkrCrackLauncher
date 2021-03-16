#include <Windows.h>
#include <detours.h>
#pragma comment(lib,"detours.lib")

BOOL SelectGameExecutableFile(WCHAR* fileName) {
	WCHAR currentDirectory[256] = { 0 };
	GetCurrentDirectory(_countof(currentDirectory), currentDirectory);

	OPENFILENAME file;
	WCHAR selectedFileName[MAX_PATH] = { 0 };
	ZeroMemory(&file, sizeof(file));
	file.lStructSize = sizeof(file);
	file.hwndOwner = NULL;
	file.lpstrFile = selectedFileName;
	file.nMaxFile = sizeof(selectedFileName);
	file.lpstrFilter = L"Executable File(*.exe)\0*.exe\0\0";
	file.nFilterIndex = 1;
	file.lpstrFileTitle = NULL;
	file.nMaxFileTitle = 0;
	file.lpstrInitialDir = currentDirectory;
	file.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	BOOL fileOpened = GetOpenFileName(&file);

	if (fileOpened) {
		CopyMemory(fileName, selectedFileName, _countof(selectedFileName));
	}
	return fileOpened;
}

/** 代码来源：
* 【教程】kirikiri序列号验证盲拆笔记
* https://bbs.zdfx.net/thread-385589-1-1.html
* (出处: 终点分享)
*/

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	WCHAR fileName[512] = { 0 };
	BOOL success = SelectGameExecutableFile(fileName);
	if (!success) {
		return -1;
	}

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);
	DetourCreateProcessWithDllEx(
		NULL,
		fileName,
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