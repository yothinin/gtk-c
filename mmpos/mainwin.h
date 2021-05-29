#include <gtk/gtk.h>

void on_shutdown(GtkWidget *widget, gpointer user_data);
gint updateclock(gpointer ptr);
void onMenuClick(GtkWidget *widget, gpointer user_data);
void createPopover(gpointer btn);
void createToolbar(gpointer win);
void activate(GtkApplication *app, gpointer user_data);
