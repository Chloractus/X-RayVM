// D3D11Context.cpp
//
// Standard D3D11 device/swapchain bring-up. This follows the same
// pattern as Dear ImGui's official "example_win32_directx11" -- there's
// not much room for creativity here, D3D setup is fairly boilerplate.

#include "D3D11Context.h"

D3D11Context::~D3D11Context()
{
    ReleaseRenderTarget();
    if (m_swapChain) { m_swapChain->Release(); m_swapChain = nullptr; }
    if (m_deviceContext) { m_deviceContext->Release(); m_deviceContext = nullptr; }
    if (m_device) { m_device->Release(); m_device = nullptr; }
}

bool D3D11Context::Initialize(HWND hwnd)
{
    // Describe the swapchain: one back buffer, standard 32-bit color,
    // sized to match the window initially (we'll resize on WM_SIZE).
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 2;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = hwnd;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };

    // D3D11CreateDeviceAndSwapChain creates the device, its immediate
    // context, and the swapchain all in one call. We try the hardware
    // driver first; if that fails outright there's no GPU we can use.
    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags,
        featureLevelArray, 2, D3D11_SDK_VERSION,
        &swapChainDesc, &m_swapChain, &m_device, &featureLevel, &m_deviceContext);

    if (FAILED(hr))
        return false;

    CreateRenderTarget();
    return true;
}

void D3D11Context::CreateRenderTarget()
{
    // Fetch the swapchain's back buffer and create a render target view
    // for it. This has to be redone any time the swapchain's buffers
    // are resized, since the old buffer (and thus the old view) is gone.
    ID3D11Texture2D* backBuffer = nullptr;
    m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    if (backBuffer)
    {
        m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
        backBuffer->Release();
    }
}

void D3D11Context::ReleaseRenderTarget()
{
    if (m_renderTargetView)
    {
        m_renderTargetView->Release();
        m_renderTargetView = nullptr;
    }
}

void D3D11Context::ResizeSwapChain(UINT width, UINT height)
{
    if (!m_swapChain || width == 0 || height == 0)
        return;

    // Must release the render target view before calling ResizeBuffers,
    // otherwise D3D refuses because something still references the old
    // back buffer.
    ReleaseRenderTarget();
    m_swapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
    CreateRenderTarget();
}

void D3D11Context::ClearAndSetRenderTarget(const float clearColor[4])
{
    m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, nullptr);
    m_deviceContext->ClearRenderTargetView(m_renderTargetView, clearColor);
}

void D3D11Context::Present(bool vsync)
{
    m_swapChain->Present(vsync ? 1 : 0, 0);
}
