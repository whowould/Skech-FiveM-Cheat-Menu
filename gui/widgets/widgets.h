#pragma once
#include "../../globals.h"
#include "../elements/icons.h"

bool skech_toggle(const char* id_str, bool* v);
bool skech_checkbox(const char* id_str, bool* v);
bool skech_slider(const char* id_str, float* v, float v_min, float v_max);
bool skech_combo(const char* id_str, int* current, const char* const items[], int count);
void skech_color_circle(float* col3);

enum row_kind { ROW_CHECK, ROW_SLIDER, ROW_COMBO, ROW_HOTKEY, ROW_COLOR };

struct row_data {
    const char*         label;
    row_kind            kind;
    void*               value;
    const char*         uid;
    const char*         hotkey_text;
    const char* const*  combo_items;
    int                 combo_count;
    bool                label_active;
};

float draw_panel(float x, float y, float w, float h,
    const char* title, const char* uid, bool* toggle, icon_fn icon);
float draw_row(float x, float y, float panel_w, const row_data& r);
