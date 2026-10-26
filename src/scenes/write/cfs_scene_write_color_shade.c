#include "src/core/cfs_app_i.h"
#include "src/data/cfs_shades.h"

// Color step 2: the shades of the family picked in cfs_scene_write_color,
// listed light -> dark. Item ids are indexes into that family's shade list.
// The basic pseudo-family maps onto cfs_color_table (sized by settings).

static const CfsColorPreset* cfs_shade_list(const CfsApp* app, size_t* count) {
    if(app->shade_family >= CFS_SHADE_FAMILY_COUNT) {
        *count = cfs_palette_count(app->settings.color_palette);
        return cfs_color_table;
    }
    const CfsShadeFamily* fam = &cfs_shade_families[app->shade_family];
    *count = fam->count;
    return fam->shades;
}

void cfs_scene_write_color_shade_on_enter(void* context) {
    CfsApp* app = context;
    Submenu* submenu = app->submenu;
    size_t count;
    const CfsColorPreset* list = cfs_shade_list(app, &count);

    submenu_reset(submenu);
    submenu_set_header(
        submenu,
        app->shade_family >= CFS_SHADE_FAMILY_COUNT ? "Basic colors" :
                                                      cfs_shade_families[app->shade_family].name);

    // Land on the current pending color when it is in this list (e.g. after
    // stepping back from the weight screen), otherwise on the first shade.
    uint32_t selected = 0;
    for(uint32_t i = 0; i < count; i++) {
        submenu_add_item(submenu, list[i].name, i, cfs_submenu_send_index, app);
        if(list[i].r == app->pending.color_r && list[i].g == app->pending.color_g &&
           list[i].b == app->pending.color_b) {
            selected = i;
        }
    }
    submenu_set_selected_item(submenu, selected);
    view_dispatcher_switch_to_view(app->view_dispatcher, CfsViewSubmenu);
}

bool cfs_scene_write_color_shade_on_event(void* context, SceneManagerEvent event) {
    CfsApp* app = context;
    if(event.type != SceneManagerEventTypeCustom) return false;
    size_t count;
    const CfsColorPreset* list = cfs_shade_list(app, &count);
    if(event.event >= count) return false;

    const CfsColorPreset* c = &list[event.event];
    app->pending.color_r = c->r;
    app->pending.color_g = c->g;
    app->pending.color_b = c->b;
    scene_manager_next_scene(app->scene_manager, CfsSceneWriteWeight);
    return true;
}

void cfs_scene_write_color_shade_on_exit(void* context) {
    CfsApp* app = context;
    submenu_reset(app->submenu);
}
