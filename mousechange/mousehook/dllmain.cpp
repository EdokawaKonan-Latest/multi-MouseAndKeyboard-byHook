// dllmain.cpp : Defines the entry point for the DLL application.
#include <iostream>
#include <Header/dllmain.h>
#include "Header/Helper.hpp"
#include <qDebug>
#include <atlbase.h>
#include <atlconv.h>
#include <unordered_map>
#include <fstream>
struct mouseMessage{
    LONG x;
    LONG y;
    ULONG button;
    int id;
    USHORT dist;
};
int i = 0;
int directionx[4] = {1, 1, 1, 1};
int directiony[4] = {1, 1, 1, 1};
//设备id不同鼠标不一样的 注意\\转义字符
string str[100] = {"\\\\?\\HID#VID_046D&PID_C53F&MI_01&Col01#7&26a318b7&0&0000#{378de44c-56ef-11d1-bc8c-00a0c91405dd}",
                   "\\\\?\\HID#VID_17EF&PID_602E#6&2a8933e&2&0000#{378de44c-56ef-11d1-bc8c-00a0c91405dd}",
                   "\\\\?\\HID#VID_18F8&PID_0F97&MI_00#7&2fd1be7a&0&0000#{378de44c-56ef-11d1-bc8c-00a0c91405dd}",
                   "\\\\?\\HID#VID_413C&PID_301A#6&1bc7e9a5&0&0000#{378de44c-56ef-11d1-bc8c-00a0c91405dd}"
                  };
unordered_map<HANDLE, mouseMessage> Points; //保存鼠标设备的句柄和该鼠标的位置
int button;
HWND m_hWnd = NULL; //窗口的句柄
HHOOK hHook = NULL; //钩子的句柄
DWORD ThreadID = 0; //记录线程的id,在main函数里面初始化

void PositiveDirectionX(int id) {
    directionx[id] = 1;
}
void OppositeDirectionX(int id){
    directionx[id] = -1;
}
void PositiveDirectionY(int id) {
    directiony[id] = 1;
}
void OppositeDirectionY(int id) {
    directiony[id] = -1;
}

/// <summary>
///  注册设备，因为只有一个设备类型，所以不管多少个鼠标，组测一个就够了
/// </summary>
/// <param name="hWnd">主窗口的句柄</param>
/// <returns></returns>
void RawRegister(HWND hWnd) {
    m_hWnd = hWnd;
    RAWINPUTDEVICE Rid[1];
    Rid[0].usUsagePage = 0x01;  //设备类型为鼠标
    Rid[0].usUsage = 0x02;
    Rid[0].dwFlags = RIDEV_INPUTSINK; //RIDEV_INPUTSINK参数让程序可以后台运行
    Rid[0].hwndTarget = hWnd;
    //  Rid[1].usUsagePage = 0x01;
    //  Rid[1].usUsage = 0x02;
    //  Rid[1].dwFlags = RIDEV_INPUTSINK;
    // Rid[1].hwndTarget = hWnd;
    //若要接收 WM_INPUT 消息，应用程序必须先使用 RegisterRawInputDevices 注册原始输入设备。 默认情况下，应用程序不会接收原始输入。
    RegisterRawInputDevices(Rid, 1, sizeof(Rid[0])); //注册鼠标设备
    hHook = SetWindowsHookEx(WH_GETMESSAGE, GetMessageProc, NULL, ThreadID);  //注册钩子

}

/// <summary>
/// 获取当前检测到的设备数量
int GetDeviceCount() {
    return Points.size();
}

/// 获取某个鼠标设备的X轴或Y轴
/// <param name="Index">鼠标设备的下标</param>
/// <param name="XY">true为X轴，false为Y轴</param>
int GetData(int Index, int XY) {
    for (auto i : Points) {
        if(i.second.id != Index) continue;
        if (XY == 1) { //x
            return i.second.x;
        }
        else if(XY == 0) { //y
            return i.second.y;
        }
    }
    return 0;
}

ULONG GetButton(int Index) {
    for (auto i : Points) {
        if(i.second.id != Index) continue;
        return i.second.button;
    }
}

USHORT GetDistance(int Index) {
    for (auto i : Points) {
        if(i.second.id != Index) continue;
        return i.second.dist;
    }
}

LRESULT CALLBACK GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam) {//nCode  消息 消息参数
    LPMSG pMsg = (LPMSG)lParam;
    //将挂钩信息传递到当前挂钩链中的下一个挂钩
    //判断拦截到的消息是不是给自己窗口的如果是就处理不是的话就继续传递下去，不能直接丢弃，你丢了别人咋办 那你也不能不让别的窗口处理啊
    if (pMsg->hwnd != m_hWnd) return CallNextHookEx(hHook, nCode, wParam, lParam);

    switch (pMsg->message) {
    case WM_INPUT: { //只处理WM_INPUT消息
        UINT dataSize;
        GetRawInputData(reinterpret_cast<HRAWINPUT>(pMsg->lParam),
                        RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));
        //Need to populate data size first
        //获取数据的大小
        if (dataSize > 0) {
            //如果数据不为空则处理数据
            std::vector<BYTE> rawdata(dataSize);
            //获取数据
            if (GetRawInputData(reinterpret_cast<HRAWINPUT>
                                (pMsg->lParam), RID_INPUT,
                                rawdata.data(), &dataSize,
                                sizeof(RAWINPUTHEADER)) == dataSize) {
                RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawdata.data());
                if (raw->header.dwType == RIM_TYPEMOUSE) { //如果接收到的是鼠标消息
                    int nResult;
                    if (Points.count(raw->header.hDevice) == 0) { //如果map中不存在该鼠标句柄，则说明是一个新的鼠标，将其插入map中
                        UINT nBufferSize = 0;
                        nResult = GetRawInputDeviceInfo(raw->header.hDevice,
                                                        RIDI_DEVICENAME,
                                                        NULL,
                                                        &nBufferSize
                                                        );
                        WCHAR* wcDeviceName = new WCHAR[nBufferSize + 1];
                        nResult = GetRawInputDeviceInfo(raw->header.hDevice, // Device
                                                        RIDI_DEVICENAME,                // Get Device Name
                                                        wcDeviceName,                   // Get Name!
                                                        &nBufferSize);                 // Char Count
                        USES_CONVERSION;
                        const char *s = W2A(wcDeviceName);
                        qDebug() << s;
                        //比较设备名字
                        if(str[0].compare(s) == 0) i = 0;
                        else if(str[1].compare(s) == 0) i = 1;
                        else if(str[2].compare(s) == 0) i = 2;
                        else if(str[3].compare(s) == 0) i = 3;
                        Points.insert({ raw->header.hDevice, { 0,0,0, i, 0}});
                    }
                    mouseMessage new_point = {
                        Points[raw->header.hDevice].x,
                        Points[raw->header.hDevice].y,
                        Points[raw->header.hDevice].button,
                        Points[raw->header.hDevice].id,
                        Points[raw->header.hDevice].dist
                    };
                    int k1 = directionx[new_point.id];
                    int k2 = directiony[new_point.id];
                    new_point.button = raw->data.mouse.ulButtons;
                    new_point.x += k1 * raw->data.mouse.lLastX;
                    new_point.y += k2 * raw->data.mouse.lLastY;
                    //滚轮数据
                    new_point.dist += raw->data.mouse.usButtonData;
                    //接线判定
                    if(new_point.x <= 0)
                        new_point.x = 0;
                    else if(new_point.x >= 1250)
                        new_point.x = 1250;
                    if(new_point.y <= 0)
                        new_point.y = 0;
                    else if(new_point.y >= 760)
                        new_point.y = 760;
                    //将map中保存的鼠标位置，和本次消息中获取到的鼠标位移相加，然后更新map中保存的值
                    Points[raw->header.hDevice] = new_point;
                }
            }
        }
        return 0;
    }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}
