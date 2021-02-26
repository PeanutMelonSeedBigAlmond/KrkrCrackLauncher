#include "crack.h"
#include <TlHelp32.h>

/** 代码来源：
* 【教程】kirikiri序列号验证盲拆笔记
* https://bbs.zdfx.net/thread-385589-1-1.html
* (出处: 终点分享)
*/

DWORD pid = 0;
bool failed = false;        //破解过程中是否发生错误
DWORD BaseAddr = -1;
DWORD AfterDecompressFileVA = 0;
PFN_AfterDecompressFile OrgAfterDecompressFile = (PFN_AfterDecompressFile)0;


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        pid = GetCurrentProcessId();
        if (!pid) {
            MessageBox(NULL, L"Crack failed!\r\nIn GetCurrentProcessId.", L"Error", MB_OK | MB_ICONERROR);
            failed = true;
            break;
        }
        HANDLE phSnapshot;        //快照句柄
        MODULEENTRY32 me32;        //存放快照信息的结构体
        me32.dwSize = sizeof(MODULEENTRY32);        //初始化大小
        phSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);        //获取当前进程快照
        if (phSnapshot == INVALID_HANDLE_VALUE) {
            MessageBox(NULL, L"Crack failed!\r\nIn CreateToolhelp32Snapshot.", L"Error", MB_OK | MB_ICONERROR);
            failed = true;
            break;
        }
        if (!Module32First(phSnapshot, &me32)) {        //无模块返回时报错
            MessageBox(NULL, L"Crack failed!\r\nNo modules returned from CreateToolhelp32Snapshot.", L"Error", MB_OK | MB_ICONERROR);
            CloseHandle(phSnapshot);
            failed = true;
            break;
        }
        do {
            if (me32.th32ProcessID == pid) {
                BaseAddr = (DWORD)me32.modBaseAddr;
                break;
            }
        } while (Module32Next(phSnapshot, &me32));        //遍历找到进程基址，即ImageBase
        CloseHandle(phSnapshot);
        if (BaseAddr == -1) {
            MessageBox(NULL, L"Crack failed!\r\nImageBase not found.", L"Error", MB_OK | MB_ICONERROR);
            failed = true;
            break;
        }
        AfterDecompressFileVA = 0x00070600 + BaseAddr + 0x0C00;        //VA = File Offset + ImageBase + Δk
        OrgAfterDecompressFile = (PFN_AfterDecompressFile)AfterDecompressFileVA;        //至此获得真正的目标地址


        DisableThreadLibraryCalls(hModule);
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)OrgAfterDecompressFile, CrackAfterDecompressFile);
        DetourTransactionCommit();
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        if (!failed) {
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourDetach(&(PVOID&)OrgAfterDecompressFile, CrackAfterDecompressFile);
            DetourTransactionCommit();
        }
        break;
    }
    return TRUE;
}
