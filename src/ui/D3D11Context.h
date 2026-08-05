#pragma once
// D3D11Context.h
//
// Owns the Direct3D 11 device, swapchain, and render target view --
// the minimum set of D3D objects ImGui's DX11 backend needs to draw
// into. Isolated from Win32Window and Application so the D3D
// bring-up/teardown code (which is fiddly and easy to get wrong) lives
// in exactly one place.

#include <d3d11.h>
#include <windows.h>

class D3D11Context
{
public:
    D3D11Context() = default;
    ~D3D11Context();

    // Creates the device, swapchain (bound to `hwnd`), and the initial
    // render target view. Returns false if device/swapchain creation
    // fails (e.g. no compatible GPU/driver).
    bool Initialize(HWND hwnd);

    // Releases the render target view and resizes the swapchain's
    // buffers, then recreates the render target view. Call this from
    // the WM_SIZE handler.
    void ResizeSwapChain(UINT width, UINT height);

    // Clears the back buffer to `clearColor` and binds the render
    // target -- call once per frame before rendering ImGui.
    void ClearAndSetRenderTarget(const float clearColor[4]);

    // Presents the back buffer to the screen. `vsync` of true caps the
    // frame rate to the monitor's refresh rate.
    void Present(bool vsync);

    ID3D11Device* GetDevice() const { return m_device; }
    ID3D11DeviceContext* GetDeviceContext() const { return m_deviceContext; }

private:
    // Builds (or rebuilds after a resize) the render target view from
    // the swapchain's current back buffer.
    void CreateRenderTarget();

    // Releases just the render target view -- needed before resizing
    // swapchain buffers, since D3D forbids resizing while a view still
    // references the old buffer.
    void ReleaseRenderTarget();

    ID3D11Device* m_device = nullptr;
    ID3D11DeviceContext* m_deviceContext = nullptr;
    IDXGISwapChain* m_swapChain = nullptr;
    ID3D11RenderTargetView* m_renderTargetView = nullptr;
};
