#include "crack.h"
#include <TlHelp32.h>

/** ������Դ��
* ���̡̳�kirikiri���к���֤ä��ʼ�
* https://bbs.zdfx.net/thread-385589-1-1.html
* (����: �յ����)
*/

DWORD pid = 0;
bool failed = false;        //�ƽ�������Ƿ�������
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
        HANDLE phSnapshot;        //���վ��
        MODULEENTRY32 me32;        //��ſ�����Ϣ�Ľṹ��
        me32.dwSize = sizeof(MODULEENTRY32);        //��ʼ����С
        phSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);        //��ȡ��ǰ���̿���
        if (phSnapshot == INVALID_HANDLE_VALUE) {
            MessageBox(NULL, L"Crack failed!\r\nIn CreateToolhelp32Snapshot.", L"Error", MB_OK | MB_ICONERROR);
            failed = true;
            break;
        }
        if (!Module32First(phSnapshot, &me32)) {        //��ģ�鷵��ʱ����
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
        } while (Module32Next(phSnapshot, &me32));        //�����ҵ����̻�ַ����ImageBase
        CloseHandle(phSnapshot);
        if (BaseAddr == -1) {
            MessageBox(NULL, L"Crack failed!\r\nImageBase not found.", L"Error", MB_OK | MB_ICONERROR);
            failed = true;
            break;
        }
        AfterDecompressFileVA = 0x00070600 + BaseAddr + 0x0C00;        //VA = File Offset + ImageBase + ��k
        OrgAfterDecompressFile = (PFN_AfterDecompressFile)AfterDecompressFileVA;        //���˻��������Ŀ���ַ


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
