#include "widgets.h"
#include <cstdio>

bool skech_toggle(const char* id_str, bool* v) {
    ImGuiWindow* w = ImGui::GetCurrentWindow();
    if (w->SkipItems) return false;
    const ImGuiID id = w->GetID(id_str);

    const float W = 32.0f, H = 14.0f, R = H * 0.5f;
    ImVec2 pos = w->DC.CursorPos;
    ImRect bb(pos, ImVec2(pos.x + W, pos.y + H));
    ImGui::ItemSize(bb, 0);
    if (!ImGui::ItemAdd(bb, id)) return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);
    if (pressed) *v = !*v;

    ImDrawList* dl = w->DrawList;

    if (*v) {
        for (int i = 4; i > 0; i--) {
            float a = 0.08f * (1.0f - (float)i / 5.0f);
            dl->AddRect(ImVec2(bb.Min.x - i, bb.Min.y - i), ImVec2(bb.Max.x + i, bb.Max.y + i),
                ImGui::ColorConvertFloat4ToU32(ImVec4(1, 0, 0, a)), R + i, 0, 1.0f);
        }
    }

    ImU32 track_col = *v ? to_u32(ImVec4(1.0f, 0.106f, 0.024f, 1.0f))
        : to_u32(ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
    dl->AddRectFilled(bb.Min, bb.Max, track_col, R);

    float thumb_r = 4.5f;
    float t = *v ? 1.0f : 0.0f;
    float thumb_x = bb.Min.x + R + t * (W - H);
    float thumb_y = bb.Min.y + R;
    dl->AddCircleFilled(ImVec2(thumb_x, thumb_y), thumb_r, to_u32(col::white));

    return pressed;
}

bool skech_checkbox(const char* id_str, bool* v) {
    ImGuiWindow* w = ImGui::GetCurrentWindow();
    if (w->SkipItems) return false;
    const ImGuiID id = w->GetID(id_str);

    const float S = 13.0f;
    ImVec2 pos = w->DC.CursorPos;
    ImRect bb(pos, ImVec2(pos.x + S, pos.y + S));
    ImGui::ItemSize(bb, 0);
    if (!ImGui::ItemAdd(bb, id)) return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);
    if (pressed) *v = !*v;

    ImDrawList* dl = w->DrawList;
    ImU32 border_col = to_u32(ImVec4(0.388f, 0.388f, 0.388f, 1.0f));

    if (*v) {
        dl->AddRectFilled(bb.Min, bb.Max, to_u32(col::red), 2.0f);
        float x = bb.Min.x, y = bb.Min.y;
        dl->AddLine(ImVec2(x + 3.0f, y + 7.0f), ImVec2(x + 5.5f, y + 9.5f), to_u32(col::white), 1.6f);
        dl->AddLine(ImVec2(x + 5.5f, y + 9.5f), ImVec2(x + 10.0f, y + 4.0f), to_u32(col::white), 1.6f);
    }
    else {
        dl->AddRect(bb.Min, bb.Max, border_col, 2.0f, 0, 1.0f);
    }
    return pressed;
}

bool skech_slider(const char* id_str, float* v, float v_min, float v_max) {
    ImGuiWindow* w = ImGui::GetCurrentWindow();
    if (w->SkipItems) return false;
    ImGuiContext& ctx = *GImGui;
    const ImGuiID id = w->GetID(id_str);

    const float W = 130.0f, H = 7.0f, R = 3.5f;
    ImVec2 pos = w->DC.CursorPos;
    ImRect bb(pos, ImVec2(pos.x + W, pos.y + H));
    ImRect interact(ImVec2(pos.x, pos.y - 4), ImVec2(pos.x + W, pos.y + H + 4));
    ImGui::ItemSize(ImVec2(W, H), 0);
    if (!ImGui::ItemAdd(interact, id)) return false;

    bool hovered, held;
    ImGui::ButtonBehavior(interact, id, &hovered, &held);
    if (held) {
        float mx = ImClamp(ctx.IO.MousePos.x, bb.Min.x, bb.Max.x);
        *v = v_min + (mx - bb.Min.x) / W * (v_max - v_min);
        *v = ImClamp(*v, v_min, v_max);
    }

    ImDrawList* dl = w->DrawList;
    float frac = (*v - v_min) / (v_max - v_min);
    dl->AddRectFilled(bb.Min, bb.Max, to_u32(col::slider_track), R);
    if (frac > 0.005f) {
        ImVec2 fill_max(bb.Min.x + W * frac, bb.Max.y);
        dl->AddRectFilled(bb.Min, fill_max, to_u32(col::red_accent), R);
    }
    return held;
}

bool skech_combo(const char* id_str, int* current, const char* const items[], int count) {
    ImGuiWindow* w = ImGui::GetCurrentWindow();
    if (w->SkipItems) return false;
    const ImGuiID id = w->GetID(id_str);

    const float W = 130.0f, H = 14.0f;
    ImVec2 pos = w->DC.CursorPos;
    ImRect bb(pos, ImVec2(pos.x + W, pos.y + H));
    ImGui::ItemSize(bb, 0);
    if (!ImGui::ItemAdd(bb, id)) return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);

    ImDrawList* dl = w->DrawList;
    dl->AddRectFilled(bb.Min, bb.Max, to_u32(col::combo_bg), 3.0f);
    dl->AddText(ImVec2(pos.x + 6, pos.y + 0), to_u32(col::text_dim), items[*current]);

    ImVec2 arr(pos.x + W - 14, pos.y + 3);
    dl->AddRect(arr, ImVec2(arr.x + 9, arr.y + 8),
        to_u32(ImVec4(0.232f, 0.235f, 0.239f, 0.82f)), 2.0f, 0, 1.0f);
    float cx = arr.x + 4.5f, cy = arr.y + 4.5f;
    dl->AddTriangleFilled(ImVec2(cx - 2, cy - 1), ImVec2(cx + 2, cy - 1), ImVec2(cx, cy + 1.5f),
        to_u32(col::text_dim));

    char popup_id[32];
    snprintf(popup_id, sizeof(popup_id), "##pop_%s", id_str);
    if (pressed) ImGui::OpenPopup(popup_id);

    bool changed = false;
    ImGui::SetNextWindowPos(ImVec2(bb.Min.x, bb.Max.y + 2));
    ImGui::SetNextWindowSize(ImVec2(W, 0));
    if (ImGui::BeginPopup(popup_id)) {
        for (int i = 0; i < count; i++) {
            bool sel = (i == *current);
            if (ImGui::Selectable(items[i], sel)) {
                *current = i;
                changed = true;
            }
        }
        ImGui::EndPopup();
    }
    return changed;
}

void skech_color_circle(float* col3) {
    ImGuiWindow* w = ImGui::GetCurrentWindow();
    if (w->SkipItems) return;
    ImVec2 pos = w->DC.CursorPos;
    float r = 6.5f;
    w->DrawList->AddCircleFilled(ImVec2(pos.x + r, pos.y + r), r,
        ImGui::ColorConvertFloat4ToU32(ImVec4(col3[0], col3[1], col3[2], 1.0f)));
    ImGui::ItemSize(ImVec2(r * 2, r * 2), 0);
}

float draw_panel(float x, float y, float w, float h,
    const char* title, const char* uid, bool* toggle, icon_fn icon)
{
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const float header_h = 28.0f;

    dl->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), to_u32(col::panel_bg), 7.0f);
    dl->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), to_u32(col::border), 7.0f, 0, 0.6f);
    dl->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + header_h), to_u32(col::panel_header_bg), 7.0f);
    dl->AddLine(ImVec2(x + 1, y + header_h), ImVec2(x + w - 1, y + header_h), to_u32(col::border), 0.8f);

    if (icon) {
        ImVec2 ip(x + 10, y + (header_h - 12.0f) * 0.5f);
        icon(dl, ip, 12.0f, to_u32(col::red));
    }
    ImGui::PushFont(font_semibold_13);
    dl->AddText(ImVec2(x + (icon ? 28.0f : 10.0f), y + 8), to_u32(col::text_active), title);
    ImGui::PopFont();

    char tid[48];
    snprintf(tid, sizeof(tid), "##toggle_%s", uid);
    ImGui::SetCursorScreenPos(ImVec2(x + w - 42, y + 7));
    skech_toggle(tid, toggle);

    return y + header_h + 8.0f;
}

float draw_row(float x, float y, float panel_w, const row_data& r) {
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const float row_h = 22.0f;

    ImGui::PushFont(font_semibold_13);
    dl->AddText(ImVec2(x + 12, y + 3),
        r.label_active ? to_u32(col::text_active) : to_u32(col::text_ghost), r.label);
    ImGui::PopFont();

    float right_edge = x + panel_w - 12.0f;

    switch (r.kind) {
    case ROW_CHECK: {
        ImGui::SetCursorScreenPos(ImVec2(right_edge - 13, y + 2));
        skech_checkbox(r.uid, (bool*)r.value);
        break;
    }
    case ROW_SLIDER: {
        ImGui::SetCursorScreenPos(ImVec2(right_edge - 130, y + 6));
        skech_slider(r.uid, (float*)r.value, 0.0f, 1.0f);
        break;
    }
    case ROW_COMBO: {
        ImGui::SetCursorScreenPos(ImVec2(right_edge - 130, y + 2));
        skech_combo(r.uid, (int*)r.value, r.combo_items, r.combo_count);
        break;
    }
    case ROW_HOTKEY: {
        ImGui::PushFont(font_semibold_13);
        ImVec2 ts = ImGui::CalcTextSize(r.hotkey_text);
        dl->AddText(ImVec2(right_edge - ts.x, y + 3), to_u32(col::text_dim), r.hotkey_text);
        ImGui::PopFont();
        break;
    }
    case ROW_COLOR: {
        ImGui::SetCursorScreenPos(ImVec2(right_edge - 13, y + 1));
        skech_color_circle((float*)r.value);
        break;
    }
    }
    return y + row_h;
}
