
#include <Windows.h>

__declspec(dllexport) BOOL WINAPI DllMain(HANDLE hInstance, DWORD dwReason, LPVOID v)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {

    }

    return true;
}
