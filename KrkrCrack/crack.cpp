#include "crack.h"

__declspec(dllexport) void Useless() {}

int __declspec(naked) CrackAfterDecompressFile(void)        //裸函数形式，防止不必要的堆栈变化
{
    static bool isFixed = false;
    if (!isFixed) {        //只有第一次被调用时修改内存内容
        __asm mov BYTE PTR[edi + 017Ch], 30h
        //上句将edi开始的解压内容中的"1"改为"0"
        isFixed = true;
    }
    __asm jmp DWORD PTR[OrgAfterDecompressFile]
        //使用jmp做跳转，防止破坏堆栈
}