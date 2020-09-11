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
#include <gtk/gtk.h>

static void activate(GtkApplication* app, void *_data)
{
    (void)_data;

    GtkWindow *parent_window = GTK_WINDOW(gtk_application_window_new(app));
    GtkWindow *child_window = GTK_WINDOW(gtk_application_window_new(app));
    gtk_window_set_transient_for(child_window, parent_window);

    GtkWidget *parent_label = gtk_label_new("");
    gtk_label_set_markup(
        GTK_LABEL(parent_label),
        "<span font_desc=\"20.0\">"
            "Mir window management example"
        "</span>");
    gtk_container_add(GTK_CONTAINER(parent_window), parent_label);
    gtk_container_set_border_width(GTK_CONTAINER(parent_window), 24);
    gtk_widget_show_all(GTK_WIDGET(parent_window));

    GtkWidget *child_label = gtk_label_new("");
    gtk_label_set_markup(
        GTK_LABEL(child_label),
        "<span font_desc=\"16.0\">"
            "This is a satellite"
        "</span>");
    gtk_container_add(GTK_CONTAINER(child_window), child_label);
    gtk_container_set_border_width(GTK_CONTAINER(child_window), 24);
    gtk_widget_show_all(GTK_WIDGET(child_window));

    mir_wm_set_window_type(child_window, MIR_WM_WINDOW_TYPE_SATELLITE);
}

int main(int argc, char **argv)
{
    GtkApplication * app = gtk_application_new("com.github.wmww.mir-window-management-gtk3", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
