#include "../../globals.h"
#include "gui/widgets/renderer.h"
#include "gui/elements/gui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

AppState state;
ImFont* font_semibold_13 = nullptr;
ImFont* font_medium_14   = nullptr;
ImFont* font_black_39    = nullptr;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) return true;
    switch (msg) {
    case WM_SIZE:
        if (device && wparam != SIZE_MINIMIZED) {
            cleanup_render_target();
            swap_chain->ResizeBuffers(0, (UINT)LOWORD(lparam), (UINT)HIWORD(lparam), DXGI_FORMAT_UNKNOWN, 0);
            create_render_target();
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wparam, lparam);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int) {
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, wnd_proc, 0, 0, instance,
        nullptr, nullptr, nullptr, nullptr, L"i", nullptr };
    RegisterClassExW(&wc);
    HWND hwnd = CreateWindowW(wc.lpszClassName, L"SKECH",
        WS_OVERLAPPEDWINDOW, 100, 100, 1280, 720,
        nullptr, nullptr, wc.hInstance, nullptr);

    if (!create_device_d3d(hwnd)) {
        cleanup_device_d3d();
        UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    font_semibold_13 = io.Fonts->AddFontFromFileTTF("Inter.ttf", 13.0f);
    if (!font_semibold_13) font_semibold_13 = io.Fonts->AddFontDefault();

    font_medium_14 = io.Fonts->AddFontFromFileTTF("Inter.ttf", 14.0f);
    if (!font_medium_14) {
        ImFontConfig cfg; cfg.SizePixels = 14.0f;
        font_medium_14 = io.Fonts->AddFontDefault(&cfg);
    }

    font_black_39 = io.Fonts->AddFontFromFileTTF("Inter.ttf", 39.0f);
    if (!font_black_39) {
        ImFontConfig cfg; cfg.SizePixels = 39.0f;
        font_black_39 = io.Fonts->AddFontDefault(&cfg);
    }

    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg]      = col::window_bg;
    style.Colors[ImGuiCol_PopupBg]       = ImVec4(0.07f, 0.07f, 0.07f, 0.98f);
    style.Colors[ImGuiCol_Text]          = col::text_active;
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(1, 0, 0, 0.20f);
    style.Colors[ImGuiCol_Header]        = ImVec4(1, 0, 0, 0.30f);
    style.Colors[ImGuiCol_HeaderActive]  = ImVec4(1, 0, 0, 0.45f);
    style.FrameRounding  = 3.0f;
    style.PopupRounding  = 4.0f;
    style.ItemSpacing    = ImVec2(4, 4);

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(device, device_context);

    MSG msg{};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        draw_gui();
        ImGui::Render();

        const float clear_col[4] = { 0.04f, 0.04f, 0.04f, 1.0f };
        device_context->OMSetRenderTargets(1, &render_target, nullptr);
        device_context->ClearRenderTargetView(render_target, clear_col);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        swap_chain->Present(1, 0);
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    cleanup_device_d3d();
    DestroyWindow(hwnd);
    UnregisterClassW(wc.lpszClassName, wc.hInstance);
    return 0;
}
