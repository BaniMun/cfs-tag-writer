#include "src/core/cfs_app_i.h"
#include "src/data/cfs_shades.h"

// Color step 1: pick a hue family. Items 0..CFS_SHADE_FAMILY_COUNT-1 are the
// generated shade families, CFS_SHADE_FAMILY_BASIC is the classic named palette
// (sized by the settings option), and the last item opens raw hex input.
// The chosen family is browsed shade by shade in cfs_scene_write_color_shade.

#define CFS_COLOR_ITEM_CUSTOM (CFS_SHADE_FAMILY_BASIC + 1)

void cfs_scene_write_color_on_enter(void* context) {
    CfsApp* app = context;
    Submenu* submenu = app->submenu;
    submenu_reset(submenu);
    submenu_set_header(submenu, "Color");
    for(uint32_t i = 0; i < CFS_SHADE_FAMILY_COUNT; i++) {
        submenu_add_item(submenu, cfs_shade_families[i].name, i, cfs_submenu_send_index, app);
    }
    submenu_add_item(
        submenu, "Basic colors", CFS_SHADE_FAMILY_BASIC, cfs_submenu_send_index, app);
    submenu_add_item(
        submenu, "Custom hex...", CFS_COLOR_ITEM_CUSTOM, cfs_submenu_send_index, app);
    // Reopen on the family used last (also when stepping back from a shade).
    submenu_set_selected_item(
        submenu, scene_manager_get_scene_state(app->scene_manager, CfsSceneWriteColor));
    view_dispatcher_switch_to_view(app->view_dispatcher, CfsViewSubmenu);
}

bool cfs_scene_write_color_on_event(void* context, SceneManagerEvent event) {
    CfsApp* app = context;
    if(event.type != SceneManagerEventTypeCustom) return false;
    if(event.event > CFS_COLOR_ITEM_CUSTOM) return false;

    scene_manager_set_scene_state(app->scene_manager, CfsSceneWriteColor, event.event);

    if(event.event == CFS_COLOR_ITEM_CUSTOM) {
        // Seed byte-input with the current pending color, so a picked shade
        // can be fine-tuned by hand.
        app->color_bytes[0] = app->pending.color_r;
        app->color_bytes[1] = app->pending.color_g;
        app->color_bytes[2] = app->pending.color_b;
        scene_manager_next_scene(app->scene_manager, CfsSceneWriteColorCustom);
    } else {
        app->shade_family = (uint8_t)event.event;
        scene_manager_next_scene(app->scene_manager, CfsSceneWriteColorShade);
    }
    return true;
}

void cfs_scene_write_color_on_exit(void* context) {
    CfsApp* app = context;
    submenu_reset(app->submenu);
}
