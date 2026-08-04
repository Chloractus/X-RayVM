#pragma once
// Win32Window.h
//
// Thin wrapper around the raw Win32 API calls needed to create a window
// and pump its message queue. This is deliberately separate from
// D3D11Context and Application so that "how we talk to Windows" stays
// isolated from "how we talk to Direct3D" and "what our app does."

#include <windows.h>
#include <string>
#include <functional>

class Win32Window
{
public:
    // `wndProc` is the function the OS calls for every window message
    // (resize, close, input, etc). Application supplies this so it can
    // react to WM_SIZE (to resize the swapchain) and WM_DESTROY (to quit).
    using WndProc = LRESULT(*)(HWND, UINT, WPARAM, LPARAM);

    Win32Window(const std::wstring& title, int width, int height, WndProc wndProc);
    ~Win32Window();

    // Pumps all pending Windows messages. Returns false once a
    // WM_QUIT message has been received, signalling the app should exit.
    bool PumpMessages();

    HWND GetHandle() const { return m_hwnd; }

private:
    HWND m_hwnd = nullptr;
    ATOM m_windowClassAtom = 0;
    std::wstring m_className;
};
