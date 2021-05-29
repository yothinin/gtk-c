#include "mainwin.h"

void crateReportWindow(GtkWidget *widget, gpointer win){
  const gchar *btnLabel = gtk_tool_button_get_label(GTK_TOOL_BUTTON(widget));
  g_print("%s\n", btnLabel);
}
