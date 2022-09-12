#include <iostream>

using namespace std;

int32_t __declspec(naked) Sort(int16_t* arr)
{
    __asm
    {
        push        ebp
        push        ecx
        push        edi
        mov         ebp, esp
        xor         eax, eax                    // tortoise = 0
        xor         ecx, ecx                    // hare = 0
        mov         edi, dword ptr[ebp + 16]    // arr

        _loop:
        mov         ax, [edi + eax * 2]         // tortoise = arr[tortoise]
        mov         cx, [edi + ecx * 2]         // ecx = arr[hare]
        mov         cx, [edi + ecx * 2]         // hare = arr[ecx]

        cmp         eax, ecx
        jne         _loop

        xor         eax, eax                    // tortoise = 0

        _loop2 :
        cmp         eax, ecx
        je          _end

        mov         ax, [edi + eax * 2]         // tortoise = arr[tortoise]
        mov         cx, [edi + ecx * 2]         // hare = arr[hare]
        jmp         _loop2

        _end :
        mov         esp, ebp
        pop         edi
        pop         ecx
        pop         ebp
        ret
    }
}

int main(int argc, char* argv[])
{
    int16_t arr[] = { 7, 1, 4, 2, 5, 8, 3, 9, 6, 8 };
    cout << Sort(arr);

    return 0;
}
