#include "renderer.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dwmapi.lib")

ID3D11Device*           device         = nullptr;
ID3D11DeviceContext*    device_context = nullptr;
IDXGISwapChain*         swap_chain     = nullptr;
ID3D11RenderTargetView* render_target  = nullptr;

bool create_device_d3d(HWND hwnd) {
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 2;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hwnd;
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    D3D_FEATURE_LEVEL fl;
    D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
    HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
        levels, 2, D3D11_SDK_VERSION, &sd, &swap_chain, &device, &fl, &device_context);
    if (hr == DXGI_ERROR_UNSUPPORTED)
        hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0,
            levels, 2, D3D11_SDK_VERSION, &sd, &swap_chain, &device, &fl, &device_context);
    if (FAILED(hr)) return false;
    create_render_target();
    return true;
}

void cleanup_device_d3d() {
    cleanup_render_target();
    if (swap_chain)     { swap_chain->Release();     swap_chain = nullptr; }
    if (device_context) { device_context->Release(); device_context = nullptr; }
    if (device)         { device->Release();         device = nullptr; }
}

void create_render_target() {
    ID3D11Texture2D* back_buffer = nullptr;
    swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer));
    device->CreateRenderTargetView(back_buffer, nullptr, &render_target);
    back_buffer->Release();
}

void cleanup_render_target() {
    if (render_target) { render_target->Release(); render_target = nullptr; }
}
