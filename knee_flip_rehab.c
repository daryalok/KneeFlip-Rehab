#include <furi.h>
#include <gui/gui.h>
#include <gui/modules/submenu.h>
#include <gui/modules/text_box.h>
#include <gui/view_dispatcher.h>
#include <stdlib.h>

#define KNEE_FLIP_DISCLAIMER                         \
    "KneeFlip Rehab is a timer and journaling tool " \
    "only. It does not provide medical advice, "     \
    "diagnosis, or treatment. Always follow the "    \
    "recovery plan provided by your doctor, "        \
    "surgeon, or physical therapist."

typedef enum {
    KneeFlipViewMenu,
    KneeFlipViewText,
} KneeFlipView;

typedef enum {
    KneeFlipMenuIceTimer,
    KneeFlipMenuElevationTimer,
    KneeFlipMenuQuadSets,
    KneeFlipMenuHeelSlides,
    KneeFlipMenuPainLog,
    KneeFlipMenuHistory,
    KneeFlipMenuAbout,
} KneeFlipMenuItem;

typedef struct {
    Gui* gui;
    ViewDispatcher* view_dispatcher;
    Submenu* menu;
    TextBox* text_box;
    bool showing_text;
    bool views_added;
} KneeFlipApp;

static void knee_flip_show_text(KneeFlipApp* app, const char* text) {
    furi_assert(app);
    furi_assert(text);

    text_box_reset(app->text_box);
    text_box_set_text(app->text_box, text);
    app->showing_text = true;
    view_dispatcher_switch_to_view(app->view_dispatcher, KneeFlipViewText);
}

static void knee_flip_menu_callback(void* context, uint32_t index) {
    furi_assert(context);
    KneeFlipApp* app = context;

    switch(index) {
    case KneeFlipMenuIceTimer:
        knee_flip_show_text(app, "Ice Timer\n\nTimer setup will be added next.");
        break;
    case KneeFlipMenuElevationTimer:
        knee_flip_show_text(app, "Elevation\n\nTimer setup will be added next.");
        break;
    case KneeFlipMenuQuadSets:
        knee_flip_show_text(app, "Quad Sets\n\nExercise pacing will be added next.");
        break;
    case KneeFlipMenuHeelSlides:
        knee_flip_show_text(app, "Heel Slides\n\nCounter input will be added next.");
        break;
    case KneeFlipMenuPainLog:
        knee_flip_show_text(app, "Pain Log\n\n0-10 before/after input will be added next.");
        break;
    case KneeFlipMenuHistory:
        knee_flip_show_text(app, "History\n\nNo sessions saved yet.");
        break;
    case KneeFlipMenuAbout:
        knee_flip_show_text(app, "KneeFlip Rehab\n\n" KNEE_FLIP_DISCLAIMER);
        break;
    default:
        knee_flip_show_text(app, "KneeFlip Rehab\n\nUnknown menu item.");
        break;
    }
}

static bool knee_flip_navigation_callback(void* context) {
    furi_assert(context);
    KneeFlipApp* app = context;

    if(app->showing_text) {
        app->showing_text = false;
        view_dispatcher_switch_to_view(app->view_dispatcher, KneeFlipViewMenu);
        return true;
    }

    view_dispatcher_stop(app->view_dispatcher);
    return true;
}

static KneeFlipApp* knee_flip_app_alloc(void) {
    KneeFlipApp* app = malloc(sizeof(KneeFlipApp));
    if(!app) {
        return NULL;
    }

    app->gui = NULL;
    app->view_dispatcher = NULL;
    app->menu = NULL;
    app->text_box = NULL;
    app->showing_text = false;
    app->views_added = false;

    app->gui = furi_record_open(RECORD_GUI);
    app->view_dispatcher = view_dispatcher_alloc();
    app->menu = submenu_alloc();
    app->text_box = text_box_alloc();

    if(!app->gui || !app->view_dispatcher || !app->menu || !app->text_box) {
        return app;
    }

    view_dispatcher_set_event_callback_context(app->view_dispatcher, app);
    view_dispatcher_set_navigation_event_callback(
        app->view_dispatcher, knee_flip_navigation_callback);

    submenu_add_item(app->menu, "Ice Timer", KneeFlipMenuIceTimer, knee_flip_menu_callback, app);
    submenu_add_item(
        app->menu, "Elevation", KneeFlipMenuElevationTimer, knee_flip_menu_callback, app);
    submenu_add_item(app->menu, "Quad Sets", KneeFlipMenuQuadSets, knee_flip_menu_callback, app);
    submenu_add_item(
        app->menu, "Heel Slides", KneeFlipMenuHeelSlides, knee_flip_menu_callback, app);
    submenu_add_item(app->menu, "Pain Log", KneeFlipMenuPainLog, knee_flip_menu_callback, app);
    submenu_add_item(app->menu, "History", KneeFlipMenuHistory, knee_flip_menu_callback, app);
    submenu_add_item(app->menu, "About", KneeFlipMenuAbout, knee_flip_menu_callback, app);

    view_dispatcher_add_view(app->view_dispatcher, KneeFlipViewMenu, submenu_get_view(app->menu));
    view_dispatcher_add_view(
        app->view_dispatcher, KneeFlipViewText, text_box_get_view(app->text_box));
    app->views_added = true;

    return app;
}

static void knee_flip_app_free(KneeFlipApp* app) {
    if(!app) {
        return;
    }

    if(app->view_dispatcher) {
        if(app->views_added) {
            view_dispatcher_remove_view(app->view_dispatcher, KneeFlipViewMenu);
            view_dispatcher_remove_view(app->view_dispatcher, KneeFlipViewText);
        }
        view_dispatcher_free(app->view_dispatcher);
    }

    if(app->text_box) {
        text_box_free(app->text_box);
    }

    if(app->menu) {
        submenu_free(app->menu);
    }

    if(app->gui) {
        furi_record_close(RECORD_GUI);
    }

    free(app);
}

int32_t knee_flip_rehab_app(void* p) {
    UNUSED(p);

    KneeFlipApp* app = knee_flip_app_alloc();
    if(!app || !app->gui || !app->view_dispatcher || !app->menu || !app->text_box) {
        knee_flip_app_free(app);
        return -1;
    }

    view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui, ViewDispatcherTypeFullscreen);
    view_dispatcher_switch_to_view(app->view_dispatcher, KneeFlipViewMenu);
    view_dispatcher_run(app->view_dispatcher);

    knee_flip_app_free(app);
    return 0;
}
