#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_internal.h"

namespace col {
    const ImVec4 window_bg       = ImVec4(0.059f, 0.063f, 0.063f, 1.0f);
    const ImVec4 panel_bg        = ImVec4(0.067f, 0.071f, 0.071f, 1.0f);
    const ImVec4 panel_header_bg = ImVec4(0.063f, 0.067f, 0.067f, 1.0f);
    const ImVec4 red             = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    const ImVec4 red_accent      = ImVec4(0.984f, 0.106f, 0.031f, 1.0f);
    const ImVec4 red_glow        = ImVec4(1.0f, 0.0f, 0.0f, 0.47f);
    const ImVec4 white           = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    const ImVec4 text_active     = ImVec4(1.0f, 1.0f, 1.0f, 0.92f);
    const ImVec4 text_dim        = ImVec4(1.0f, 1.0f, 1.0f, 0.34f);
    const ImVec4 text_ghost      = ImVec4(1.0f, 1.0f, 1.0f, 0.14f);
    const ImVec4 border          = ImVec4(1.0f, 1.0f, 1.0f, 0.10f);
    const ImVec4 slider_track    = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
    const ImVec4 status_bar      = ImVec4(0.078f, 0.086f, 0.086f, 1.0f);
    const ImVec4 sidebar_active  = ImVec4(1.0f, 1.0f, 1.0f, 0.04f);
    const ImVec4 combo_bg        = ImVec4(0.106f, 0.110f, 0.110f, 1.0f);
    const ImVec4 cyan            = ImVec4(0.0f, 0.859f, 0.925f, 1.0f);
    const ImVec4 divider_line    = ImVec4(1.0f, 1.0f, 1.0f, 0.06f);
}

inline ImU32 to_u32(const ImVec4& c) { return ImGui::ColorConvertFloat4ToU32(c); }

struct AppState {
    int active_tab = 0;

    bool  aimbot_enabled   = true;
    bool  target_peds      = true;
    bool  visible_check    = true;
    float field_of_view    = 0.83f;
    float smooth           = 0.60f;
    float curve            = 0.15f;
    float aim_distance     = 0.70f;
    int   hitbox           = 0;
    bool  dual_aimbot      = false;
    bool  fov_circle       = true;

    bool  silent_aim_enabled  = true;
    bool  enable_silent_aim   = true;
    float silent_fov          = 0.35f;
    int   silent_hitbox       = 0;
    bool  silent_fov_circle   = false;

    bool  magic_bullet_enabled  = true;
    bool  enable_magic_bullet   = true;
    float magic_fov             = 0.30f;
    int   magic_hitbox          = 0;
    bool  magic_fov_circle      = true;
    float fov_color[3]          = { 0.0f, 0.859f, 0.925f };

    bool  triggerbot_enabled = true;
    bool  use_hotkey         = true;
    bool  target_players     = true;
    bool  target_peds_tb     = true;
    bool  target_dead        = true;
    float delay              = 0.65f;

    bool  player_esp       = true;
    bool  player_box       = true;
    bool  player_name      = true;
    bool  player_health    = true;
    bool  player_distance  = false;
    bool  player_skeleton  = false;
    bool  player_weapon    = false;
    float player_esp_dist  = 0.55f;

    bool  world_esp        = true;
    bool  pickup_esp       = true;
    bool  vehicle_esp      = false;
    bool  vehicle_boxes    = false;
    bool  fullbright       = false;
    bool  remove_fog       = true;
    bool  night_mode       = false;
    float world_esp_dist   = 0.40f;

    bool  bypass_ragdoll   = true;
    bool  super_jump       = false;
    bool  no_recoil        = true;
    bool  infinite_ammo    = false;
    bool  god_mode         = false;
    bool  speed_hack       = false;
    float speed_multiplier = 0.30f;
    float walk_speed       = 0.50f;
};

extern AppState state;
extern ImFont* font_semibold_13;
extern ImFont* font_medium_14;
extern ImFont* font_black_39;
