#pragma once
#include "imgui.h"

typedef void (*icon_fn)(ImDrawList*, ImVec2, float, ImU32);

void icon_crosshair(ImDrawList* dl, ImVec2 p, float s, ImU32 c);
void icon_player(ImDrawList* dl, ImVec2 p, float s, ImU32 c);
void icon_world(ImDrawList* dl, ImVec2 p, float s, ImU32 c);
void icon_list(ImDrawList* dl, ImVec2 p, float s, ImU32 c);
void icon_gear(ImDrawList* dl, ImVec2 p, float s, ImU32 c);
void icon_folder(ImDrawList* dl, ImVec2 p, float s, ImU32 c);
