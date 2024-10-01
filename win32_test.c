#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define Assert(x) if((x) == 0) { *(int*)(0) = 0; }

#define BTN_HELLO 0x1234

LRESULT WindowProc(HWND Window, UINT Msg, WPARAM Wparam, LPARAM Lparam)
{
    LRESULT Result = 0;
    switch(Msg)
    {
        case WM_COMMAND:
        {
            switch(HIWORD(Wparam))
            {
                case BN_CLICKED:
                {
                    if(LOWORD(Wparam) == BTN_HELLO)
                    {
                        MessageBox( Window, "Hello world!", "OK", MB_OK );
                    }
                } break;
            }
        } break;

        case WM_NOTIFY:
        {
        } break;

        case WM_KEYDOWN:
        {
            switch(Wparam)
            {
                case VK_ESCAPE:
                {
                    DestroyWindow(Window);
                } break;
            }
        } break;

        case WM_DESTROY:
        {
            PostQuitMessage(0);
        } break;

        default:
        {
            Result = DefWindowProc(Window, Msg, Wparam, Lparam);
        } break;
    }
    return Result;
}

typedef struct
{
    char Data[128 * 1024];
} big;

void __stdcall WinMainCRTStartup(void)
{
    big Big = {0};

    HINSTANCE Instance = GetModuleHandle(0);

    WNDCLASSEXA WindowClassEx = {0};
    WindowClassEx.cbSize = sizeof(WindowClassEx);
    WindowClassEx.style = CS_OWNDC|CS_VREDRAW|CS_HREDRAW|CS_DROPSHADOW;
    WindowClassEx.lpfnWndProc = WindowProc;
    WindowClassEx.cbClsExtra = 0;
    WindowClassEx.cbWndExtra = 0;
    WindowClassEx.hInstance = Instance;
    WindowClassEx.hIcon = 0;
    WindowClassEx.hCursor = 0;
    WindowClassEx.hbrBackground = 0;
    WindowClassEx.lpszMenuName = 0;
    WindowClassEx.lpszClassName = "TestWindowClass";
    WindowClassEx.hIconSm = 0;
    Assert(RegisterClassExA(&WindowClassEx));

    HWND Window;
    Assert(Window = CreateWindowExA(WS_EX_OVERLAPPEDWINDOW,
                                    "TestWindowClass",
                                    "Test",
                                    WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                                    CW_USEDEFAULT, CW_USEDEFAULT,
                                    250, 200,
                                    0, 0, Instance, 0));

    HDC DC;
    Assert(DC = GetDC(Window));

    HWND Button;
    Assert(Button = CreateWindowA("BUTTON", "Hello world",
                                  WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
                                  10, 20, 100, 25,
                                  Window, (HMENU) BTN_HELLO, (HINSTANCE) GetWindowLongPtr(Window, GWLP_HINSTANCE), 0));

    MSG Msg;
    while(GetMessage(&Msg, 0, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    ExitProcess((UINT) Msg.wParam);
}