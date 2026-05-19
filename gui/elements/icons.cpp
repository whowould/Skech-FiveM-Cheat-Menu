#include "../elements/icons.h"
#include <cmath>

void icon_crosshair(ImDrawList* dl, ImVec2 p, float s, ImU32 c) {
    float cx = p.x + s * 0.5f, cy = p.y + s * 0.5f, r = s * 0.32f;
    dl->AddCircle(ImVec2(cx, cy), r, c, 14, 1.4f);
    dl->AddLine(ImVec2(cx - s * 0.48f, cy), ImVec2(cx + s * 0.48f, cy), c, 1.2f);
    dl->AddLine(ImVec2(cx, cy - s * 0.48f), ImVec2(cx, cy + s * 0.48f), c, 1.2f);
}

void icon_player(ImDrawList* dl, ImVec2 p, float s, ImU32 c) {
    float cx = p.x + s * 0.5f;
    dl->AddCircle(ImVec2(cx, p.y + s * 0.3f), s * 0.18f, c, 12, 1.4f);
    dl->AddBezierCubic(
        ImVec2(p.x + s * 0.22f, p.y + s * 0.95f),
        ImVec2(p.x + s * 0.22f, p.y + s * 0.55f),
        ImVec2(p.x + s * 0.78f, p.y + s * 0.55f),
        ImVec2(p.x + s * 0.78f, p.y + s * 0.95f), c, 1.4f);
}

void icon_world(ImDrawList* dl, ImVec2 p, float s, ImU32 c) {
    float cx = p.x + s * 0.5f, cy = p.y + s * 0.5f, r = s * 0.4f;
    dl->AddCircle(ImVec2(cx, cy), r, c, 18, 1.2f);
    dl->AddLine(ImVec2(cx - r, cy), ImVec2(cx + r, cy), c, 1.0f);
    dl->AddBezierCubic(ImVec2(cx, cy - r), ImVec2(cx - r * 0.55f, cy - r * 0.3f),
        ImVec2(cx - r * 0.55f, cy + r * 0.3f), ImVec2(cx, cy + r), c, 1.0f);
    dl->AddBezierCubic(ImVec2(cx, cy - r), ImVec2(cx + r * 0.55f, cy - r * 0.3f),
        ImVec2(cx + r * 0.55f, cy + r * 0.3f), ImVec2(cx, cy + r), c, 1.0f);
}

void icon_list(ImDrawList* dl, ImVec2 p, float s, ImU32 c) {
    for (int i = 0; i < 3; i++) {
        float y = p.y + s * (0.27f + 0.22f * i);
        dl->AddRectFilled(ImVec2(p.x + s * 0.18f, y),
            ImVec2(p.x + s * 0.82f, y + s * 0.1f), c, 1.0f);
        dl->AddCircleFilled(ImVec2(p.x + s * 0.10f, y + s * 0.05f), s * 0.06f, c);
    }
}

void icon_gear(ImDrawList* dl, ImVec2 p, float s, ImU32 c) {
    float cx = p.x + s * 0.5f, cy = p.y + s * 0.5f;
    dl->AddCircle(ImVec2(cx, cy), s * 0.18f, c, 14, 1.4f);
    for (int i = 0; i < 8; i++) {
        float a = (float)i * 3.14159f / 4.0f;
        dl->AddLine(
            ImVec2(cx + cosf(a) * s * 0.26f, cy + sinf(a) * s * 0.26f),
            ImVec2(cx + cosf(a) * s * 0.42f, cy + sinf(a) * s * 0.42f), c, 1.6f);
    }
}

void icon_folder(ImDrawList* dl, ImVec2 p, float s, ImU32 c) {
    dl->AddRect(ImVec2(p.x + s * 0.10f, p.y + s * 0.32f),
        ImVec2(p.x + s * 0.90f, p.y + s * 0.82f), c, 2.0f, 0, 1.4f);
    dl->AddLine(ImVec2(p.x + s * 0.10f, p.y + s * 0.32f),
        ImVec2(p.x + s * 0.45f, p.y + s * 0.32f), c, 1.4f);
    dl->AddLine(ImVec2(p.x + s * 0.45f, p.y + s * 0.32f),
        ImVec2(p.x + s * 0.55f, p.y + s * 0.22f), c, 1.4f);
}
