#include <gtk/gtk.h>
#ifndef MAINWIN_H
#define MAINWIN_H
gint updateclock(gpointer ptr);
void on_shutdown(GtkWidget *widget, gpointer user_data);
void onMenuClick(GtkWidget *widget, gpointer user_data);
void createPopover(gpointer btn);
void createToolbar(gpointer win);
void activate(GtkApplication *app, gpointer user_data);

void crateHomeWindow();
void crateSaleWindow(GtkWidget *widget, gpointer win);
void crateReportWindow(GtkWidget *widget, gpointer win);

#endif
