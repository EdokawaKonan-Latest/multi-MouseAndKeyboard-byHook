#ifndef DLLMAIN_H
#define DLLMAIN_H
#include <vector>
#include <map>
#include <windows.h>
#include <Header/Helper.hpp>

using namespace std;
//但是WINAPI不能删 就是APIENTRY
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                       );
void Test();
void RawRegister(HWND hWnd);
int GetDeviceCount();
int GetData(int Index, int XY);
LRESULT CALLBACK GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam);
#endif // DLLMAIN_H
