#include <gtk/gtk.h>

gint updateclock(gpointer ptr){
  char curr_time[9];
  time_t now;
  struct tm *now_tm;
  time(&now);
  
  now_tm = localtime(&now);
  sprintf(curr_time, "%02d:%02d:%02d",
                     now_tm->tm_hour,
                     now_tm->tm_min,
                     now_tm->tm_sec);
  gtk_label_set_text(GTK_LABEL(ptr), curr_time);

  return (TRUE);
}

static void on_shutdown(GtkWidget *widget, gpointer user_data){
  g_print("Exit program...\nPlease press anykey to exit console.\n");
  g_application_quit(user_data);
}

static void activate(GtkApplication *app, gpointer user_data){
  GtkWidget *window, *header, *lblClock;
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Meamoo POS");
  gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(on_shutdown), app);

  header = gtk_header_bar_new();
  gtk_window_set_titlebar(GTK_WINDOW(window), header);
  gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);
  gtk_header_bar_set_decoration_layout(GTK_HEADER_BAR(header), 
      "close,maximize,minimize:menu");
  lblClock = gtk_label_new("");
  gtk_header_bar_pack_end(GTK_HEADER_BAR(header), lblClock);
  g_timeout_add(1000, updateclock, (gpointer)lblClock);

  gtk_widget_show_all(window);
}

int main(int argc, char *argv[]){
  GtkApplication *app;
  int status;
  
  app = gtk_application_new("com.maemoo.pos", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  
  return status;
}
