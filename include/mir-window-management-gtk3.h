#ifndef GTK_LAYER_SHELL_H
#define GTK_LAYER_SHELL_H

#include <gtk/gtk.h>

/**
 * SECTION: mir-window-management-gtk3
 * @title: Mir Window Managemetn for GTK3
 * @short_description: A library to allow more specialized window management for GTK3 in Mir
 */
G_BEGIN_DECLS

/**
 * MirWindowType:
 * @MIR_WINDOW_TYPE_DEFAULT: The normal type of the window.
 * @MIR_WINDOW_TYPE_SATELLITE: A helper child window.
 */
typedef enum {
    MIR_WM_WINDOW_TYPE_DEFAULT,
    MIR_WM_WINDOW_TYPE_SATELLITE,
} MirWmWindowType;

/**
 * mir_window_management_set_type:
 * @window: A #GtkWindow to set the type on.
 *
 * Set @window's Mir type
 */
void mir_wm_set_window_type(GtkWindow *window, MirWmWindowType type);

/**
 * mir_window_management_get_type:
 * @window: A #GtkWindow to get the type on.
 *
 * Returns the @window's Mir type or MIR_WINDOW_TYPE_DEFAULT if none is set
 */
MirWmWindowType mir_wm_get_window_type(GtkWindow *window);

G_END_DECLS

#endif // GTK_LAYER_SHELL_H
