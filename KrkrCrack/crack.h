#pragma once
#include<windows.h>
#include "detours.h"
#pragma comment(lib,"detours.lib")

typedef int
(__cdecl* PFN_AfterDecompressFile)(
    void
    );//��������ָ�룬���ڲ�ȷ��ʵ��ԭ�ͣ�����Ϊ�����ܲ���

extern DWORD BaseAddr;        //�����ַ

extern DWORD AfterDecompressFileVA;        //������hook��ַ

extern PFN_AfterDecompressFile OrgAfterDecompressFile;        //ԭ�������ָ��(Trampoline)

int CrackAfterDecompressFile(void);        //hook����

extern "C" __declspec(dllexport) void Useless();        //���õĵ���������ֻ�Ǳ���DLL����
