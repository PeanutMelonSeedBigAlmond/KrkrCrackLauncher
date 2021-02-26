#pragma once
#include<windows.h>
#include "detours.h"
#pragma comment(lib,"detours.lib")

typedef int
(__cdecl* PFN_AfterDecompressFile)(
    void
    );//声明函数指针，由于不确定实际原型，故视为不接受参数

extern DWORD BaseAddr;        //镜像基址

extern DWORD AfterDecompressFileVA;        //真正的hook地址

extern PFN_AfterDecompressFile OrgAfterDecompressFile;        //原函数入口指针(Trampoline)

int CrackAfterDecompressFile(void);        //hook函数

extern "C" __declspec(dllexport) void Useless();        //无用的导出函数，只是便于DLL挂载
