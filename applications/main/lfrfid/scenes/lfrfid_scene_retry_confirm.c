#include "../lfrfid_i.h"

void lfrfid_scene_retry_confirm_on_enter(void* context) {
    LfRfid* app = context;
    Widget* widget = app->widget;

    widget_add_button_element(widget, GuiButtonTypeRight, "Exit", lfrfid_widget_callback, app);
    widget_add_button_element(widget, GuiButtonTypeLeft, "Stay", lfrfid_widget_callback, app);
    widget_add_string_element(
        widget, 64, 19, AlignCenter, AlignBottom, FontPrimary, "Retry Reading?");
    widget_add_string_element(
        widget, 64, 29, AlignCenter, AlignBottom, FontSecondary, "All unsaved data will be lost!");

    view_dispatcher_switch_to_view(app->view_dispatcher, LfRfidViewWidget);
}

bool lfrfid_scene_retry_confirm_on_event(void* context, SceneManagerEvent event) {
    LfRfid* app = context;
    SceneManager* scene_manager = app->scene_manager;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeBack) {
        consumed = true; // Ignore Back button presses
    } else if(event.type == SceneManagerEventTypeCustom) {
        consumed = true;
        if(event.event == GuiButtonTypeRight) {
            scene_manager_search_and_switch_to_previous_scene(scene_manager, LfRfidSceneRead);
        } else if(event.event == GuiButtonTypeLeft) {
            scene_manager_previous_scene(scene_manager);
        }
    }

    return consumed;
}

void lfrfid_scene_retry_confirm_on_exit(void* context) {
    LfRfid* app = context;
    widget_reset(app->widget);
}
