#include "gui.h"
#include "../../globals.h"
#include "../widgets/widgets.h"
#include "../elements/icons.h"
#include "tabs.h"
#include "sidebar.h"

void draw_gui() {
    ImGuiIO& io = ImGui::GetIO();

    const float W = 849.0f, H = 538.0f;
    static bool first_run = true;
    if (first_run) {
        ImGui::SetNextWindowPos(ImVec2((io.DisplaySize.x - W) * 0.5f,
            (io.DisplaySize.y - H) * 0.5f), ImGuiCond_Once);
        first_run = false;
    }
    ImGui::SetNextWindowSize(ImVec2(W, H), ImGuiCond_Always);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
    ImGui::Begin("##skech_main", nullptr,
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse |
        ImGuiWindowFlags_NoCollapse);
    ImGui::PopStyleVar(3);

    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 wp = ImGui::GetWindowPos();
    ImVec2 ws = ImGui::GetWindowSize();
    const float bottom_bar_h = 23.0f;

    dl->AddRectFilled(wp, wp + ws, to_u32(col::window_bg));

    dl->AddRect(wp, ImVec2(wp.x + ws.x, wp.y + ws.y - bottom_bar_h),
        to_u32(col::red), 0, 0, 1.0f);

    auto blob = [&](float cx, float cy, float base_r, float max_alpha) {
        for (int i = 24; i > 0; i--) {
            float t = (float)i / 24.0f;
            float r = base_r * (0.4f + 1.4f * t);
            float a = max_alpha * (1.0f - t) * (1.0f - t);
            dl->AddCircleFilled(ImVec2(cx, cy), r,
                ImGui::ColorConvertFloat4ToU32(ImVec4(1, 0, 0, a)));
        }
    };
    blob(wp.x - 20, wp.y - 30, 80, 0.45f);
    blob(wp.x + ws.x - 30, wp.y + ws.y - 80, 80, 0.40f);

    ImGui::SetCursorScreenPos(wp);
    ImGui::InvisibleButton("##drag", ImVec2(ws.x, 40));
    if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
        ImVec2 d = io.MouseDelta;
        ImGui::SetWindowPos(ImVec2(wp.x + d.x, wp.y + d.y));
    }

    {
        ImGui::PushFont(font_black_39);
        ImVec2 logo_pos(wp.x + 27, wp.y + 10);
        const char* s = "SKECH";
        float spacing = 6.0f;
        float x = logo_pos.x;
        for (const char* p = s; *p; p++) {
            char ch[2] = { *p, 0 };
            dl->AddText(ImVec2(x + 1, logo_pos.y + 1), to_u32(ImVec4(1, 0, 0, 0.20f)), ch);
            dl->AddText(ImVec2(x, logo_pos.y), to_u32(ImVec4(1, 0, 0, 0.75f)), ch);
            x += ImGui::CalcTextSize(ch).x + spacing;
        }
        ImGui::PopFont();
    }

    const char* tabs[] = { "Aim", "Player", "Visuals", "Miscellaneous" };
    {
        ImGui::PushFont(font_semibold_13);
        float tabs_x = wp.x + 330;
        float tab_y = wp.y + 38;
        float x = tabs_x;
        for (int i = 0; i < 4; i++) {
            ImVec2 ts = ImGui::CalcTextSize(tabs[i]);
            bool active = (i == state.active_tab);
            ImU32 tcol = active ? to_u32(col::text_active)
                : to_u32(ImVec4(1, 1, 1, 0.20f));
            dl->AddText(ImVec2(x, tab_y), tcol, tabs[i]);

            if (active) {
                dl->AddRectFilled(ImVec2(x, tab_y + ts.y + 4),
                    ImVec2(x + ts.x, tab_y + ts.y + 5),
                    to_u32(col::red));
            }

            ImRect bb(ImVec2(x - 6, tab_y - 4), ImVec2(x + ts.x + 6, tab_y + ts.y + 8));
            char tid[16]; snprintf(tid, sizeof(tid), "##tab%d", i);
            ImGuiID id = ImGui::GetID(tid);
            ImGui::ItemAdd(bb, id);
            bool h, hd;
            if (ImGui::ButtonBehavior(bb, id, &h, &hd)) state.active_tab = i;

            x += ts.x + 38;
        }
        ImGui::PopFont();
    }

    const float divider_x = wp.x + 268;
    const float header_y = wp.y + 65;
    dl->AddLine(ImVec2(wp.x, header_y), ImVec2(wp.x + ws.x, header_y),
        to_u32(col::divider_line), 1.0f);
    dl->AddLine(ImVec2(divider_x, header_y), ImVec2(divider_x, wp.y + ws.y - bottom_bar_h),
        to_u32(col::divider_line), 1.0f);

    {
        float line_y = wp.y + 78.5f;
        float lx1 = wp.x + 16, lx2 = wp.x + ws.x - 16;
        dl->AddLine(ImVec2(lx1, line_y), ImVec2(lx2, line_y),
            to_u32(ImVec4(1, 0, 0, 0.35f)), 1.0f);
        auto spark = [&](float sx, float sy, float r) {
            ImU32 c = to_u32(ImVec4(1, 0, 0, 0.9f));
            dl->AddLine(ImVec2(sx - r, sy), ImVec2(sx + r, sy), c, 1.0f);
            dl->AddLine(ImVec2(sx, sy - r), ImVec2(sx, sy + r), c, 1.0f);
            dl->AddCircleFilled(ImVec2(sx, sy), 0.8f, c);
        };
        spark(lx1 + 4, line_y, 3.0f);
        spark(lx1 + (lx2 - lx1) * 0.25f, line_y, 2.5f);
        spark(lx1 + (lx2 - lx1) * 0.55f, line_y, 2.0f);
        spark(lx2 - 4, line_y, 3.0f);
    }

    draw_sidebar(wp.x, wp.y + 95, 268, wp.y + ws.y - bottom_bar_h);

    {
        float content_x = divider_x + 14;
        float content_y = wp.y + 95;
        switch (state.active_tab) {
        case 0: draw_tab_aim(content_x, content_y); break;
        case 1: draw_tab_player(content_x, content_y); break;
        case 2: draw_tab_visuals(content_x, content_y); break;
        case 3: draw_tab_misc(content_x, content_y); break;
        }
    }

    {
        float bar_y = wp.y + ws.y - bottom_bar_h;
        dl->AddRectFilled(ImVec2(wp.x, bar_y), ImVec2(wp.x + ws.x, wp.y + ws.y),
            to_u32(col::status_bar));
        ImGui::PushFont(font_semibold_13);
        const char* msg = "SKECH [beta] Figma Remake";
        ImVec2 ts = ImGui::CalcTextSize(msg);
        dl->AddText(ImVec2(wp.x + (ws.x - ts.x) * 0.5f, bar_y + 4),
            to_u32(col::text_ghost), msg);
        ImGui::PopFont();
        dl->AddCircleFilled(ImVec2(wp.x + ws.x - 18, bar_y + bottom_bar_h * 0.5f),
            5.5f, to_u32(col::cyan));
    }

    ImGui::End();
}
