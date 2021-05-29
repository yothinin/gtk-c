#include "mainwin.h"

void crateHomeWindow(GtkWidget *widget, gpointer win){
  //const gchar *btnLabel = gtk_tool_button_get_label(GTK_TOOL_BUTTON(widget));
  //g_print("%s\n", btnLabel);
  GtkWidget *homewin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  //gtk_window_set_transient_for(GTK_WINDOW(homewin), GTK_WINDOW(win));
  //gtk_window_set_keep_above(GTK_WINDOW(win), TRUE);
  gtk_window_present(GTK_WINDOW(homewin));
  gtk_widget_show(homewin);
}
