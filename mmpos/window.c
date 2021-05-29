/*
 * window.c, pupose to create main window and toolbar.
 */

#include "mainwin.h"

void on_shutdown(GtkWidget *widget, gpointer user_data){
  g_print("Exit program...\nPlease press anykey to exit console.\n");
  g_application_quit(G_APPLICATION(user_data));
}

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

void activate(GtkApplication *app, gpointer user_data){
  GtkWidget *window, *header, *lblClock;
  GtkWidget *button;

  // สร้าง  window ผ่าน gtk_applicateion
  // ตรงนี้จะแตกต่างจาก gtk_window_new()
  window = gtk_application_window_new(app);
  gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(on_shutdown), app);

  // สร้าง Headerbar มาใช้แทน titlebar
  header = gtk_header_bar_new();
  gtk_window_set_titlebar(GTK_WINDOW(window), header);
  gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);
  gtk_header_bar_set_decoration_layout(GTK_HEADER_BAR(header),
      "close,maximize,minimize:menu");
  gtk_header_bar_set_title (GTK_HEADER_BAR (header), "MaeMoo POS");

  // สร้าง Label สำหรับแสดงเวลา
  lblClock = gtk_label_new("");
  gtk_header_bar_pack_end(GTK_HEADER_BAR(header), lblClock);

  // กำหนดเวลาอัพเดทนาฬกาทุก 1 วินาที
  g_timeout_add(1000, updateclock, (gpointer)lblClock);	

  //สร้างปุ่มสำหรับบรรจุ popover menu
  button = gtk_menu_button_new ();
  gtk_button_set_image (GTK_BUTTON (button), gtk_image_new_from_icon_name ("open-menu-symbolic", GTK_ICON_SIZE_BUTTON));
  gtk_header_bar_pack_end(GTK_HEADER_BAR(header), button);

  //สร้าง Popover Menu (menu.c)
  createPopover((gpointer)button);

  //สร้าง Tool bar (menu.c)
  createToolbar((gpointer)window);

  gtk_widget_show_all(window);
}

