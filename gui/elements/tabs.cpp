#include "tabs.h"
#include "../../globals.h"
#include "../widgets/widgets.h"
#include "../elements/icons.h"

static const char* hitbox_items[] = { "Head", "Neck", "Body", "Pelvis" };

void draw_tab_aim(float x0, float y0) {
    float lx = x0, ly = y0;
    float col_w = 283;

    {
        float h = 28 + 11 * 22 + 14;
        float cy = draw_panel(lx, ly, col_w, h, "Aimbot", "aim", &state.aimbot_enabled, icon_crosshair);
        row_data rows[] = {
            { "Aimbot Hotkey",  ROW_HOTKEY, nullptr,               "aim_hk",  "Mouse 2", nullptr, 0, false },
            { "Target Peds",    ROW_CHECK,  &state.target_peds,    "aim_tp",  nullptr,   nullptr, 0, true  },
            { "Visible Check",  ROW_CHECK,  &state.visible_check,  "aim_vc",  nullptr,   nullptr, 0, true  },
            { "Field Of View",  ROW_SLIDER, &state.field_of_view,  "aim_fov", nullptr,   nullptr, 0, false },
            { "Smooth",         ROW_SLIDER, &state.smooth,         "aim_sm",  nullptr,   nullptr, 0, false },
            { "Curve",          ROW_SLIDER, &state.curve,          "aim_cv",  nullptr,   nullptr, 0, false },
            { "Aim Distance",   ROW_SLIDER, &state.aim_distance,   "aim_ad",  nullptr,   nullptr, 0, false },
            { "Hitbox",         ROW_COMBO,  &state.hitbox,         "aim_hb",  nullptr,   hitbox_items, 4, false },
            { "Dual Aimbot",    ROW_CHECK,  &state.dual_aimbot,    "aim_da",  nullptr,   nullptr, 0, true  },
            { "FOV Circle",     ROW_CHECK,  &state.fov_circle,     "aim_fc",  nullptr,   nullptr, 0, true  },
        };
        for (auto& r : rows) cy = draw_row(lx, cy, col_w, r);
        ly += h + 14;
    }

    {
        float h = 28 + 7 * 22 + 14;
        float cy = draw_panel(lx, ly, col_w, h, "Triggerbot", "tb", &state.triggerbot_enabled, icon_crosshair);
        row_data rows[] = {
            { "Use Hotkey",     ROW_CHECK,  &state.use_hotkey,     "tb_hk",  nullptr,   nullptr, 0, true  },
            { "Triggerbot Key", ROW_HOTKEY, nullptr,               "tb_kk",  "Mouse 2", nullptr, 0, false },
            { "Target Players", ROW_CHECK,  &state.target_players, "tb_tp",  nullptr,   nullptr, 0, true  },
            { "Target Peds",    ROW_CHECK,  &state.target_peds_tb, "tb_tpe", nullptr,   nullptr, 0, true  },
            { "Target Dead",    ROW_CHECK,  &state.target_dead,    "tb_td",  nullptr,   nullptr, 0, true  },
            { "Delay",          ROW_SLIDER, &state.delay,          "tb_dl",  nullptr,   nullptr, 0, false },
        };
        for (auto& r : rows) cy = draw_row(lx, cy, col_w, r);
    }

    float rx = x0 + col_w + 12, ry = y0;
    float col_w2 = 252;

    {
        float h = 28 + 6 * 22 + 14;
        float cy = draw_panel(rx, ry, col_w2, h, "Silent Aim", "sa", &state.silent_aim_enabled, icon_crosshair);
        row_data rows[] = {
            { "Enable Silent Aim", ROW_CHECK,  &state.enable_silent_aim, "sa_en", nullptr,   nullptr, 0, true  },
            { "Silent Aim Hotkey", ROW_HOTKEY, nullptr,                  "sa_hk", "Mouse 2", nullptr, 0, false },
            { "Field Of View",     ROW_SLIDER, &state.silent_fov,        "sa_fv", nullptr,   nullptr, 0, false },
            { "Hitbox",            ROW_COMBO,  &state.silent_hitbox,     "sa_hb", nullptr,   hitbox_items, 4, false },
            { "FOV Circle",        ROW_CHECK,  &state.silent_fov_circle, "sa_fc", nullptr,   nullptr, 0, false },
        };
        for (auto& r : rows) cy = draw_row(rx, cy, col_w2, r);
        ry += h + 14;
    }

    {
        float h = 28 + 7 * 22 + 14;
        float cy = draw_panel(rx, ry, col_w2, h, "Magic Bullet", "mb", &state.magic_bullet_enabled, icon_crosshair);
        row_data rows[] = {
            { "Enable Magic Bullet", ROW_CHECK,  &state.enable_magic_bullet, "mb_en", nullptr,   nullptr, 0, true  },
            { "Magic Bullet Hotkey", ROW_HOTKEY, nullptr,                    "mb_hk", "Mouse 2", nullptr, 0, false },
            { "Field Of View",       ROW_SLIDER, &state.magic_fov,           "mb_fv", nullptr,   nullptr, 0, false },
            { "Hitbox",              ROW_COMBO,  &state.magic_hitbox,        "mb_hb", nullptr,   hitbox_items, 4, false },
            { "FOV Circle",          ROW_CHECK,  &state.magic_fov_circle,    "mb_fc", nullptr,   nullptr, 0, true  },
            { "FOV Color",           ROW_COLOR,  state.fov_color,            "mb_cl", nullptr,   nullptr, 0, false },
        };
        for (auto& r : rows) cy = draw_row(rx, cy, col_w2, r);
    }
}

void draw_tab_player(float x0, float y0) {
    float col_w = 283;
    float h = 28 + 8 * 22 + 14;
    float cy = draw_panel(x0, y0, col_w, h, "Player ESP", "p_esp", &state.player_esp, icon_player);
    row_data rows[] = {
        { "Boxes",         ROW_CHECK,  &state.player_box,      "p_bx", nullptr, nullptr, 0, true  },
        { "Names",         ROW_CHECK,  &state.player_name,     "p_nm", nullptr, nullptr, 0, true  },
        { "Health",        ROW_CHECK,  &state.player_health,   "p_hp", nullptr, nullptr, 0, true  },
        { "Distance",      ROW_CHECK,  &state.player_distance, "p_ds", nullptr, nullptr, 0, false },
        { "Skeleton",      ROW_CHECK,  &state.player_skeleton, "p_sk", nullptr, nullptr, 0, false },
        { "Weapon",        ROW_CHECK,  &state.player_weapon,   "p_wp", nullptr, nullptr, 0, false },
        { "ESP Distance",  ROW_SLIDER, &state.player_esp_dist, "p_dd", nullptr, nullptr, 0, false },
    };
    for (auto& r : rows) cy = draw_row(x0, cy, col_w, r);
}

void draw_tab_visuals(float x0, float y0) {
    float col_w = 283;
    float h = 28 + 8 * 22 + 14;
    float cy = draw_panel(x0, y0, col_w, h, "World", "v_w", &state.world_esp, icon_world);
    row_data rows[] = {
        { "Pickup ESP",    ROW_CHECK,  &state.pickup_esp,      "v_pe", nullptr, nullptr, 0, true  },
        { "Vehicle ESP",   ROW_CHECK,  &state.vehicle_esp,     "v_ve", nullptr, nullptr, 0, false },
        { "Vehicle Boxes", ROW_CHECK,  &state.vehicle_boxes,   "v_vb", nullptr, nullptr, 0, false },
        { "Fullbright",    ROW_CHECK,  &state.fullbright,      "v_fb", nullptr, nullptr, 0, false },
        { "Remove Fog",    ROW_CHECK,  &state.remove_fog,      "v_rf", nullptr, nullptr, 0, true  },
        { "Night Mode",    ROW_CHECK,  &state.night_mode,      "v_nm", nullptr, nullptr, 0, false },
        { "ESP Distance",  ROW_SLIDER, &state.world_esp_dist,  "v_dd", nullptr, nullptr, 0, false },
    };
    for (auto& r : rows) cy = draw_row(x0, cy, col_w, r);
}

void draw_tab_misc(float x0, float y0) {
    float col_w = 283;
    float h = 28 + 8 * 22 + 14;
    float cy = draw_panel(x0, y0, col_w, h, "Movement & Misc", "m_x", &state.speed_hack, icon_gear);
    row_data rows[] = {
        { "Bypass Ragdoll", ROW_CHECK,  &state.bypass_ragdoll,   "m_br", nullptr, nullptr, 0, true  },
        { "Super Jump",     ROW_CHECK,  &state.super_jump,       "m_sj", nullptr, nullptr, 0, false },
        { "No Recoil",      ROW_CHECK,  &state.no_recoil,        "m_nr", nullptr, nullptr, 0, true  },
        { "Infinite Ammo",  ROW_CHECK,  &state.infinite_ammo,    "m_ia", nullptr, nullptr, 0, false },
        { "God Mode",       ROW_CHECK,  &state.god_mode,         "m_gm", nullptr, nullptr, 0, false },
        { "Speed Mult",     ROW_SLIDER, &state.speed_multiplier, "m_sm", nullptr, nullptr, 0, false },
        { "Walk Speed",     ROW_SLIDER, &state.walk_speed,       "m_ws", nullptr, nullptr, 0, false },
    };
    for (auto& r : rows) cy = draw_row(x0, cy, col_w, r);
}
