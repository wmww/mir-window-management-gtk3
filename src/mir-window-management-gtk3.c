/* This entire file is licensed under MIT
 *
 * Copyright 2020 William Wold
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "mir-window-management-gtk3.h"
#include "mir-window-management-unstable-v1-client.h"
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkwayland.h>

static const char *mir_wm_window_data_key = "mir-wm-data";

static gboolean globals_initialized = FALSE;
static struct zmir_wm_base_v1* mir_wm_base_v1_global = NULL;

static enum zmir_shell_surface_v1_window_type into_proto_window_type(MirWmWindowType type) {
    switch (type) {
        case MIR_WM_WINDOW_TYPE_DEFAULT: return ZMIR_SHELL_SURFACE_V1_WINDOW_TYPE_DEFAULT;
        case MIR_WM_WINDOW_TYPE_SATELLITE: return ZMIR_SHELL_SURFACE_V1_WINDOW_TYPE_SATELLITE;
        default: g_error("Invalid window type %d", type); g_abort();
    }
}

static void registry_global(
        void *_data,
        struct wl_registry *registry,
        uint32_t id,
        const char *interface,
        uint32_t version) {
    (void)_data;
    if (strcmp(interface, zmir_wm_base_v1_interface.name) == 0) {
        g_warn_if_fail(zmir_wm_base_v1_interface.version == 1);
        mir_wm_base_v1_global = wl_registry_bind(
            registry,
            id,
            &zmir_wm_base_v1_interface,
            MIN((uint32_t)zmir_wm_base_v1_interface.version, version));
    }
}

static void registry_global_remove(void *_data, struct wl_registry *_registry, uint32_t _id)
{
    (void)_data;
    (void)_registry;
    (void)_id;
}

static const struct wl_registry_listener registry_listener = {
    .global = registry_global,
    .global_remove = registry_global_remove,
};

static void lazy_globals_init() {
    if (globals_initialized)
        return;

    GdkDisplay* gdk_display = gdk_display_get_default();
    g_return_if_fail(gdk_display);
    g_return_if_fail(GDK_IS_WAYLAND_DISPLAY(gdk_display));

    struct wl_display* wl_display = gdk_wayland_display_get_wl_display(gdk_display);
    struct wl_registry* registry = wl_display_get_registry(wl_display);
    wl_registry_add_listener(registry, &registry_listener, NULL);
    wl_display_roundtrip(wl_display);
    wl_registry_destroy(registry);

    if (!mir_wm_base_v1_global)
        g_warning("It appears your Wayland compositor does not support zmir_shell_surface_v1");

    globals_initialized = TRUE;
}

typedef struct {
    MirWmWindowType type;
    struct zmir_shell_surface_v1* mir_shell_surface;
} MirWmWindowData;

static void window_data_destroy(MirWmWindowData* data) {
    g_free(data);
}

static void on_window_realize(GtkWidget *window, MirWmWindowData *data) {
    GdkWindow* gdk_window = gtk_widget_get_window(window);
    struct wl_surface* wl_surface = gdk_wayland_window_get_wl_surface(gdk_window);

    if (mir_wm_base_v1_global && wl_surface) {
        data->mir_shell_surface = zmir_wm_base_v1_get_shell_surface(mir_wm_base_v1_global, wl_surface);
        if (data->type != MIR_WM_WINDOW_TYPE_DEFAULT) {
            zmir_shell_surface_v1_set_window_type(data->mir_shell_surface, into_proto_window_type(data->type));
        }
    } else {
        g_warning("Failed to create zmir_shell_surface_v1");
    }
}

static MirWmWindowData* get_window_data(GtkWindow *window) {
    MirWmWindowData* data = g_object_get_data(G_OBJECT(window), mir_wm_window_data_key);

    if (!data) {
        lazy_globals_init();

        data = g_new0(MirWmWindowData, 1);
        data->type = MIR_WM_WINDOW_TYPE_DEFAULT;

        g_object_set_data_full(G_OBJECT(window), mir_wm_window_data_key, data, (GDestroyNotify)window_data_destroy);

        g_signal_connect(window, "realize", G_CALLBACK(on_window_realize), data);
        if (gtk_widget_get_realized(GTK_WIDGET(window))) {
            on_window_realize(GTK_WIDGET(window), data);
        }
    }

    return data;
}

void mir_wm_set_window_type(GtkWindow *window, MirWmWindowType type) {
    MirWmWindowData* data = get_window_data(window);
    if (type == data->type)
        return;

    data->type = type;
    if (data->mir_shell_surface)
        zmir_shell_surface_v1_set_window_type(data->mir_shell_surface, into_proto_window_type(type));
}

MirWmWindowType mir_wm_get_window_type(GtkWindow *window) {
    MirWmWindowData* data = get_window_data(window);
    return data->type;
}
