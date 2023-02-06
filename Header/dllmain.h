#ifndef DLLMAIN_H
#define DLLMAIN_H
#include <vector>
#include <windows.h>
#include <iostream>
#include <qDebug>
#include <atlbase.h>
#include <atlconv.h>
#include <unordered_map>
#include <fstream>
#include <sstream>
using namespace std;
//但是WINAPI不能删 就是APIENTRY
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                       );
void Test();
void RawRegister(HWND hWnd);
int GetMouseCount();
ULONG GetMouseButton(int Index);
USHORT GetDistance(int Index);
int GetData(int Index, int XY);
int setMouse(int id, int i);
void GetMouseDevice(RAWINPUT* raw);
void PositiveDirectionX(int id);
void OppositeDirectionX(int id);
void PositiveDirectionY(int id);
void OppositeDirectionY(int id);
void UpdateMouseData(RAWINPUT *raw);
void KeyValueInit();
void GetKeyBoardDevice(RAWINPUT* raw);
void UpdateKeyboardData(RAWINPUT *raw);
void Limit(long &x, long &y);
void mouseIdInit();
void keyIdInit();
void setMouseFlag(int f);
void setKeyFlag(int f);
WCHAR* GetDeviceName(RAWINPUT* raw);
QString GetKeyString(int Index);

LRESULT CALLBACK GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam);
#endif // DLLMAIN_H
