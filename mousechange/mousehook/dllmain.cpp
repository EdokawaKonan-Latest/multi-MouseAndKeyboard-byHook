// dllmain.cpp : Defines the entry point for the DLL application.
#include <Header/dllmain.h>

struct MouseMessage {
    LONG x;
    LONG y;
    ULONG button;
    INT id;
    USHORT dist;
};
struct KeyboardMessage {
    QString letter;
    INT id;
};

int g_mouse_idx = 0;
int g_key_idx = 0;
int g_directionx[4] = {1, 1, 1, 1};
int g_directiony[4] = {1, 1, 1, 1};
HWND g_m_hwnd = NULL; //窗口的句柄
HHOOK g_h_hook = NULL; //线程钩子的句柄
DWORD g_thread_id = 0; //记录线程的id,在main函数里面初始化
unordered_map<HANDLE, MouseMessage> g_points; //保存鼠标设备的句柄和该鼠标的位置
unordered_map<HANDLE, KeyboardMessage> g_keyboard; //保存键盘设备的句柄和键盘的字符
unordered_map<USHORT, QString> g_key_value;//key value

//设备id不同鼠标不一样的 注意\\转义字符

string g_mouse_dev[100] = {"\\\\?\\HID#VID_046D&PID_C53F&MI_01&Col01#7&3aefd595&0&0000#{378de44c-56ef-11d1-bc8c-00a0c91405dd}",
                           "\\\\?\\HID#VID_17EF&PID_602E#6&2a8933e&2&0000#{378de44c-56ef-11d1-bc8c-00a0c91405dd}",
                           "\\\\?\\HID#VID_18F8&PID_0F97&MI_00#7&162b7b0f&0&0000#{378de44c-56ef-11d1-bc8c-00a0c91405dd}",
                           "\\\\?\\HID#VID_413C&PID_301A#6&221bbfb9&0&0000#{378de44c-56ef-11d1-bc8c-00a0c91405dd}"
                          };

string g_keyboard_dev[100] = {"\\\\?\\HID#VID_413C&PID_2113&MI_00#7&2d9b9e3e&0&0000#{884b96c3-56ef-11d1-bc8c-00a0c91405dd}",
                              "\\\\?\\HID#VID_413C&PID_2107#6&38bcfe3c&0&0000#{884b96c3-56ef-11d1-bc8c-00a0c91405dd}",
                              "\\\\?\\HID#{00001124-0000-1000-8000-00805f9b34fb}_VID&000205ac_PID&024f&Col01#8&2b8baa02&1&0000#{884b96c3-56ef-11d1-bc8c-00a0c91405dd}",
                              "\\\\?\\HID#VID_046D&PID_C53F&MI_01&Col01#7&3aefd595&0&0000#{378de44c-56ef-11d1-bc8c-00a0c91405dd}"
                             };
//键盘按键初始化
void KeyValueInit() {
    std::ifstream accfile;
    string s;
    accfile.open("KeyValue.txt");
    if(!accfile.is_open()) {
        cerr << "open failed" << endl;
        return;
    }
    while(getline(accfile, s)) {
        string temp="";
        int a = 0;
        for(auto c : s) {
            if(c == ' ') {
                a = std::stoi(temp);
                temp.clear();
            }
            else temp += c;
        }
        QString c = QString::fromStdString(temp);
        g_key_value.insert({a, c});
        //qDebug() <<a << " "<< c;
    }
    if(accfile.is_open()) {
        accfile.close();
    }
}

void PositiveDirectionX(int id) {
    g_directionx[id] = 1;
}
void OppositeDirectionX(int id){
    g_directionx[id] = -1;
}
void PositiveDirectionY(int id) {
    g_directiony[id] = 1;
}
void OppositeDirectionY(int id) {
    g_directiony[id] = -1;
}

///  注册设备，因为只有一个设备类型，所以不管多少个鼠标，组测一个就够了
void RawRegister(HWND hWnd) {
    g_m_hwnd = hWnd; //窗口句柄赋值
    RAWINPUTDEVICE Rid[2];
    //注册鼠标
    Rid[0].usUsagePage = 0x01;  //设备类型为鼠标
    Rid[0].usUsage = 0x02;
    Rid[0].dwFlags = RIDEV_INPUTSINK; //RIDEV_INPUTSINK参数让程序可以后台运行
    Rid[0].hwndTarget = hWnd;
    //注册键盘
    Rid[1].usUsagePage = 0x01;
    Rid[1].usUsage = 0x06;
    Rid[1].dwFlags = RIDEV_INPUTSINK;
    Rid[1].hwndTarget = hWnd;

    //若要接收 WM_INPUT 消息，应用程序必须先使用 RegisterRawInputDevices 必须注册原始输入设备。
    //因为默认情况下，应用程序不会接收原始输入。
    //注册鼠标设备 键盘设备
    RegisterRawInputDevices(Rid, 2, sizeof(Rid[0])); //注册鼠标设备
    g_h_hook = SetWindowsHookEx(WH_GETMESSAGE, GetMessageProc, NULL, g_thread_id);  //注册钩子
}

/// 获取当前检测到鼠标设备数量
int GetMouseCount() {
    return g_points.size();
}

///获取当前检测到键盘设备的数量
int GetKeyboardCount() {
    return g_keyboard.size();
}

/// 获取某个鼠标设备的X轴或Y轴
/// <param name="Index">鼠标设备的下标</param>
/// <param name="XY">true为X轴，false为Y轴</param>
int GetData(int Index, int XY) {
    for (auto i : g_points) {
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
QString GetKeyString(int Index) {
    for(auto i : g_keyboard) {
        if(i.second.id != Index) continue;
        return i.second.letter;
    }
    return "";
}

ULONG GetMouseButton(int Index) {
    for (auto i : g_points) {
        if(i.second.id != Index) continue;
        return i.second.button;
    }
}

USHORT GetDistance(int Index) {
    for (auto i : g_points) {
        if(i.second.id != Index) continue;
        return i.second.dist;
    }
}
void Limit(long &x, long &y) { //限制数据长度
    if(x <= 0)
        x = 0;
    else if(x >= 960)
        x = 960;
    if(y <= 0)
        y = 0;
    else if(y >= 960)
        y = 960;
}

WCHAR* GetDeviceName(RAWINPUT* raw) {
    int nResult;
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
    return wcDeviceName;
}

//鼠标设备增加 以及设备id获取
void GetMouseDevice(RAWINPUT* raw) {
    //比较设备名字
    if (g_points.count(raw->header.hDevice) == 0) {
        WCHAR* wcDeviceName = GetDeviceName(raw);
        USES_CONVERSION;
        const char * s = W2A(wcDeviceName);
        qDebug() << s;
        if(g_mouse_dev[0].compare(s) == 0) g_mouse_idx = 0;
        else if(g_mouse_dev[1].compare(s) == 0) g_mouse_idx = 1;
        else if(g_mouse_dev[2].compare(s) == 0) g_mouse_idx = 2;
        else if(g_mouse_dev[3].compare(s) == 0) g_mouse_idx = 3;
        else{
            g_mouse_idx = 100;
        }
        g_points.insert({ raw->header.hDevice, { 0,0,0, g_mouse_idx, 0}});
        s = NULL;
    }
}

void UpdateMouseData(RAWINPUT *raw) { //更新鼠标数据
    MouseMessage new_point = {
        g_points[raw->header.hDevice].x,
        g_points[raw->header.hDevice].y,
        g_points[raw->header.hDevice].button,
        g_points[raw->header.hDevice].id,
        g_points[raw->header.hDevice].dist
    };
    int k1 = g_directionx[new_point.id], k2 = g_directiony[new_point.id];
    new_point.button = raw->data.mouse.ulButtons;
    new_point.x += k1 * raw->data.mouse.lLastX;
    new_point.y += k2 * raw->data.mouse.lLastY;
    new_point.dist += raw->data.mouse.usButtonData;//滚轮数据
    Limit(new_point.x, new_point.y);//界限判定
    //将map中保存的鼠标位置，和本次消息中获取到的鼠标位移相加，然后更新map中保存的值
    g_points[raw->header.hDevice] = new_point;
}

void GetKeyBoardDevice(RAWINPUT* raw) {
    if (g_keyboard.count(raw->header.hDevice) == 0) {
        WCHAR* wcDeviceName = GetDeviceName(raw);
        const char * s;
        USES_CONVERSION;
        s = W2A(wcDeviceName);
        qDebug() << s;
        //比较设备名字
        if(g_keyboard_dev[0].compare(s) == 0) g_key_idx = 0;
        else if(g_keyboard_dev[1].compare(s) == 0) g_key_idx = 1;
        else if(g_keyboard_dev[2].compare(s) == 0) g_key_idx = 2;
        else if(g_keyboard_dev[3].compare(s) == 0) g_key_idx = 3;
        else g_key_idx = 100;
        g_keyboard.insert({raw->header.hDevice, {"",g_key_idx}});
        s = NULL;
    }
}


void UpdateKeyboardData(RAWINPUT *raw) { //更新键盘数据  
    KeyboardMessage new_keyboard = {
        g_keyboard[raw->header.hDevice].letter,
        g_keyboard[raw->header.hDevice].id
    };
    int makecode = raw->data.keyboard.MakeCode;
    //如果按压下
    if(raw->data.keyboard.Flags == 0) {
        qDebug() << "the key is pressed";
        new_keyboard.letter += g_key_value[makecode];
    } else {
        qDebug() << "the key is realsed";
    }
    g_keyboard[raw->header.hDevice] = new_keyboard;
    qDebug() << g_keyboard[raw->header.hDevice].letter;
    qDebug() << g_keyboard[raw->header.hDevice].id;
}


LRESULT CALLBACK GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam) {//nCode  消息 消息参数
    LPMSG pMsg = (LPMSG)lParam;
    //将挂钩信息传递到当前挂钩链中的下一个挂钩
    //判断拦截到的消息是不是给自己窗口的如果是就处理不是的话就继续传递下去，不能直接丢弃，你丢了别人咋办 那你也不能不让别的窗口处理啊
    if (pMsg->hwnd != g_m_hwnd) return CallNextHookEx(g_h_hook, nCode, wParam, lParam);
    switch (pMsg->message) {
    case WM_INPUT: { //只处理WM_INPUT消息
        UINT dataSize;
        GetRawInputData(reinterpret_cast<HRAWINPUT>(pMsg->lParam),
                        RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));
        if (dataSize > 0) {
            //如果数据不为空则处理数据
            std::vector<BYTE> rawdata(dataSize);
            //获取数据
            if (GetRawInputData(reinterpret_cast<HRAWINPUT>
                                (pMsg->lParam), RID_INPUT,
                                rawdata.data(), &dataSize,
                                sizeof(RAWINPUTHEADER)) == dataSize) {
                RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawdata.data());
                if (raw->header.dwType == RIM_TYPEMOUSE) {
                    //如果接收到的是鼠标消息
                    GetMouseDevice(raw);
                    UpdateMouseData(raw);
                } else if(raw->header.dwType == RIM_TYPEKEYBOARD) {
                    //如果接受的是键盘消息
                    GetKeyBoardDevice(raw);
                    UpdateKeyboardData(raw);
                }
            }
        }
        return 0;
    }
    }
    return CallNextHookEx(g_h_hook, nCode, wParam, lParam);
}
