#include <Windows.h>
#include <detours.h>
#pragma comment(lib,"detours.lib")

/** ������Դ��
* ���̡̳�kirikiri���к���֤ä��ʼ�
* https://bbs.zdfx.net/thread-385589-1-1.html
* (����: �յ����)
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
        TEXT("\\syugaten.exe") // ��Ϸ����������
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
