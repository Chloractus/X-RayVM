// Win32Window.cpp
//
// Registers a window class, creates the window, and pumps messages.
// No ImGui or D3D knowledge lives here on purpose.

#include "Win32Window.h"

Win32Window::Win32Window(const std::wstring& title, int width, int height, WndProc wndProc)
    : m_className(L"NetCheckWindowClass")
{
    // Register the window class. We use CS_CLASSDC because that's what
    // the ImGui DX11 example expects -- it means all windows of this
    // class share one device context, which is fine since we only ever
    // create a single window.
    WNDCLASSEXW windowClass = {};
    windowClass.cbSize = sizeof(WNDCLASSEXW);
    windowClass.style = CS_CLASSDC;
    windowClass.lpfnWndProc = wndProc;
    windowClass.hInstance = GetModuleHandleW(nullptr);
    windowClass.lpszClassName = m_className.c_str();
    m_windowClassAtom = RegisterClassExW(&windowClass);

    // Create the actual OS window. WS_OVERLAPPEDWINDOW gives us a normal
    // resizable window with a title bar, minimize/maximize/close buttons.
    m_hwnd = CreateWindowW(
        m_className.c_str(),
        title.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        nullptr, nullptr,
        windowClass.hInstance,
        nullptr);

    ShowWindow(m_hwnd, SW_SHOWDEFAULT);
    UpdateWindow(m_hwnd);
}

Win32Window::~Win32Window()
{
    if (m_hwnd)
        DestroyWindow(m_hwnd);
    if (m_windowClassAtom)
        UnregisterClassW(m_className.c_str(), GetModuleHandleW(nullptr));
}

bool Win32Window::PumpMessages()
{
    MSG msg;
    // PeekMessage (rather than GetMessage) so we never block -- we want
    // to keep rendering frames continuously, not wait for input events.
    while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (msg.message == WM_QUIT)
            return false;
    }
    return true;
}
