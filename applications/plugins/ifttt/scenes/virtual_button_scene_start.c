#include "../ifttt_virtual_button.h"

enum VirtualButtonSubmenuIndex {
    VirtualButtonSubmenuIndexSendView,
    VirtualButtonSubmenuIndexModuleView,
    VirtualButtonSubmenuIndexRebootView,
    VirtualButtonSubmenuIndexResetView,
};

static void virtual_button_scene_start_submenu_callback(void* context, uint32_t index) {
    furi_assert(context);
    VirtualButtonApp* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, index);
}

void virtual_button_scene_start_on_enter(void* context) {
    VirtualButtonApp* app = context;
    Submenu* submenu = app->submenu;

    submenu_add_item(
        submenu,
        "Send IFTTT command",
        VirtualButtonSubmenuIndexSendView,
        virtual_button_scene_start_submenu_callback,
        app);
    submenu_add_item(
        submenu,
        "Configure module",
        VirtualButtonSubmenuIndexModuleView,
        virtual_button_scene_start_submenu_callback,
        app);
    submenu_add_item(
        submenu,
        "Reboot module",
        VirtualButtonSubmenuIndexRebootView,
        virtual_button_scene_start_submenu_callback,
        app);
    submenu_add_item(
        submenu,
        "Reset module",
        VirtualButtonSubmenuIndexResetView,
        virtual_button_scene_start_submenu_callback,
        app);
    submenu_set_selected_item(
        submenu, scene_manager_get_scene_state(app->scene_manager, VirtualButtonAppSceneStart));

    view_dispatcher_switch_to_view(app->view_dispatcher, VirtualButtonAppViewSubmenu);
}

bool virtual_button_scene_start_on_event(void* context, SceneManagerEvent event) {
    VirtualButtonApp* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == VirtualButtonSubmenuIndexSendView) {
            scene_manager_next_scene(app->scene_manager, VirtualButtonAppSceneSendView);
        } else if(event.event == VirtualButtonSubmenuIndexModuleView) {
            scene_manager_next_scene(app->scene_manager, VirtualButtonAppSceneModuleView);
        } else if(event.event == VirtualButtonSubmenuIndexRebootView) {
            scene_manager_next_scene(app->scene_manager, VirtualButtonAppSceneRebootView);
        } else if(event.event == VirtualButtonSubmenuIndexResetView) {
            scene_manager_next_scene(app->scene_manager, VirtualButtonAppSceneResetView);
        }
        scene_manager_set_scene_state(app->scene_manager, VirtualButtonAppSceneStart, event.event);
        consumed = true;
    }
    return consumed;
}

void virtual_button_scene_start_on_exit(void* context) {
    VirtualButtonApp* app = context;
    submenu_reset(app->submenu);
}
