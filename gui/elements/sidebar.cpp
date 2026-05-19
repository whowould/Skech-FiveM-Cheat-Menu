#include "sidebar.h"
#include "../../globals.h"
#include "../elements/icons.h"
#include <cstdio>

struct side_item { const char* label; icon_fn icon; int tab; };
struct side_section { const char* header; side_item items[4]; int n; };

static side_section sections[] = {
    { nullptr,         { { "Aimbot",        icon_crosshair, 0 },
                         { "Player",        icon_player,    1 } }, 2 },
    { "Visuals",       { { "Players",       icon_player,    1 },
                         { "World",         icon_world,     2 } }, 2 },
    { "Miscellaneous", { { "Lists",         icon_list,      3 },
                         { "Miscellaneous", icon_gear,      3 },
                         { "Configs",       icon_folder,    3 } }, 3 },
};

void draw_sidebar(float x, float y, float w, float bottom_limit) {
    ImDrawList* dl = ImGui::GetWindowDrawList();
    int idx = 0;

    for (auto& sec : sections) {
        if (sec.header) {
            ImGui::PushFont(font_medium_14);
            dl->AddText(ImVec2(x + 14, y), to_u32(col::text_ghost), sec.header);
            ImGui::PopFont();
            y += 22;
        }
        for (int i = 0; i < sec.n; i++) {
            const float H = 38.0f;
            ImRect bb(ImVec2(x, y), ImVec2(x + w, y + H));
            bool is_active = (sec.items[i].tab == state.active_tab);

            char sid[32];
            snprintf(sid, sizeof(sid), "##side_%d", idx);
            ImGuiID iid = ImGui::GetID(sid);
            ImGui::ItemAdd(bb, iid);
            bool hov, hld;
            if (ImGui::ButtonBehavior(bb, iid, &hov, &hld))
                state.active_tab = sec.items[i].tab;

            if (is_active) {
                dl->AddRectFilled(bb.Min, bb.Max, to_u32(col::sidebar_active), 4.0f);
                dl->AddRectFilled(ImVec2(bb.Min.x, bb.Min.y + 7),
                    ImVec2(bb.Min.x + 3, bb.Max.y - 7),
                    to_u32(col::red), 1.0f);
            }
            else if (hov) {
                dl->AddRectFilled(bb.Min, bb.Max, to_u32(ImVec4(1, 1, 1, 0.02f)), 4.0f);
            }

            ImU32 ic = is_active ? to_u32(col::text_active) : to_u32(col::text_dim);
            ImU32 tc = is_active ? to_u32(col::text_active) : to_u32(col::text_dim);
            ImVec2 ip(x + 22, y + (H - 18.0f) * 0.5f);
            sec.items[i].icon(dl, ip, 18.0f, ic);

            ImGui::PushFont(font_medium_14);
            dl->AddText(ImVec2(x + 56, y + 11), tc, sec.items[i].label);
            ImGui::PopFont();

            y += H + 4;
            idx++;
        }
        y += 6;
    }
    (void)bottom_limit;
}
