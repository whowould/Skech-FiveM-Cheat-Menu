#pragma once
#include <d3d11.h>

extern ID3D11Device*            device;
extern ID3D11DeviceContext*     device_context;
extern IDXGISwapChain*          swap_chain;
extern ID3D11RenderTargetView*  render_target;

bool create_device_d3d(HWND hwnd);
void cleanup_device_d3d();
void create_render_target();
void cleanup_render_target();
