#include <Windows.h>
#include <detours.h>
#pragma comment(lib,"detours.lib")

/** 代码来源：
* 【教程】kirikiri序列号验证盲拆笔记
* https://bbs.zdfx.net/thread-385589-1-1.html
* (出处: 终点分享)
*/

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);
    wchar_t CommandLine[256] = { 0 };
    GetCurrentDirectory(_countof(CommandLine), CommandLine);
    wcscat_s(
        CommandLine, 
        _countof(CommandLine), 
        TEXT("\\syugaten.exe") // 游戏主程序名称
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
