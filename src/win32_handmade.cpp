#include <windows.h>

LRESULT MainWindowCallback(
  HWND Window,
  UINT Message,
  WPARAM WParam,
  LPARAM LParam
)
{
    LRESULT Result = 0;

    switch(Message)
    {
        case WM_SIZE:
        {
            OutputDebugStringA("WM_SIZE\n");
            break;
        }

        case WM_DESTROY:
        {
            OutputDebugStringA("WM_DESTROY\n");
            break;
        }

        case WM_CLOSE:
        {
            OutputDebugStringA("WM_CLOSE\n");
            break;
        }

        case WM_ACTIVATEAPP:
        {
            OutputDebugStringA("WM_ACTIVATEAPP\n");
            break;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT Paint;
            HDC DeviceContext = BeginPaint(Window, &Paint);
            int X  = Paint.rcPaint.left;
            int Y = Paint.rcPaint.top;
            int Width = Paint.rcPaint.right - Paint.rcPaint.left;
            int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;

            // Test painting to window
            static DWORD Operation = WHITENESS;
            if (Operation == WHITENESS)
            {
                Operation = BLACKNESS;
            }
            else
            {
                Operation = WHITENESS;
            }

            PatBlt(DeviceContext, X, Y, Width, Height, Operation); 
            EndPaint(Window, &Paint);
            break;
        }

        default:
        {
            // OutputDebugStringA("default\n");
            Result = DefWindowProc(Window, Message, WParam, LParam);
        }
    }

    return Result;
}

int WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PSTR CommandLine, int ShowCode)
{
    WNDCLASS WindowClass = {};

    WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    WindowClass.lpfnWndProc = MainWindowCallback;
    WindowClass.hInstance = Instance;
    WindowClass.lpszClassName = "HandmadeHeroWindowClass";

    if(!RegisterClass(&WindowClass))
    {
        // TODO: Logging
        return 0;
    }

    HWND WindowHandle = CreateWindowEx(
        0,
        WindowClass.lpszClassName,
        "Handmade Hero",
        WS_OVERLAPPEDWINDOW|WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        Instance,
        0
    );

    if (!WindowHandle)
    {
        // TODO: Logging
        return 0;
    }

    // Game Loop
    for (;;)
    {
        MSG Message;
        BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
        // GetMessage can return -1 
        if (MessageResult < 0)
        {
            break;
        }

        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }

    return 0;
}
