#include "crack.h"

__declspec(dllexport) void Useless() {}

int __declspec(naked) CrackAfterDecompressFile(void)        //�㺯����ʽ����ֹ����Ҫ�Ķ�ջ�仯
{
    static bool isFixed = false;
    if (!isFixed) {        //ֻ�е�һ�α�����ʱ�޸��ڴ�����
        __asm mov BYTE PTR[edi + 017Ch], 30h
        //�Ͼ佫edi��ʼ�Ľ�ѹ�����е�"1"��Ϊ"0"
        isFixed = true;
    }
    __asm jmp DWORD PTR[OrgAfterDecompressFile]
        //ʹ��jmp����ת����ֹ�ƻ���ջ
}