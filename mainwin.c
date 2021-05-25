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
  g_application_quit(G_APPLICATION(user_data));
}

static void createMenu(GtkWidget *header){
  GtkWidget *pmenu = gtk_menu_new();
  GtkWidget *mnuMaster, *mnuSetting;
  mnuMaster = gtk_menu_item_new_with_label("แฟ้มข้อมูลหลัก");
  gtk_widget_show(mnuMaster);
  gtk_menu_shell_append(GTK_MENU_SHELL(pmenu), mnuMaster);
  mnuSetting = gtk_menu_item_new_with_label("ตั้งค่าระบบ");
  gtk_widget_show(mnuSetting);
  gtk_menu_shell_append(GTK_MENU_SHELL(pmenu), mnuSetting);
  
}

static void createToolbar(gpointer win){
  GtkWidget *tool_bar, *vbox;
  GtkToolItem *home_button,
              *pos_button,
              *rep_button;
  tool_bar = gtk_toolbar_new ();
  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start (GTK_BOX (vbox), tool_bar, FALSE, FALSE, 0);
  gtk_container_add (GTK_CONTAINER (GTK_WINDOW(win)), vbox);
  
  home_button = gtk_tool_button_new (NULL, NULL);
  gtk_tool_button_set_label (GTK_TOOL_BUTTON (home_button), ("_Home"));
  gtk_tool_button_set_use_underline (GTK_TOOL_BUTTON (home_button), TRUE);
  gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (home_button), "go-home");
  gtk_tool_item_set_is_important (home_button, TRUE);
  gtk_toolbar_insert (GTK_TOOLBAR (tool_bar), home_button, -1);

  pos_button = gtk_tool_button_new (NULL, NULL);
  gtk_tool_button_set_label (GTK_TOOL_BUTTON (pos_button), ("หน้าขาย"));
  gtk_tool_button_set_use_underline (GTK_TOOL_BUTTON (pos_button), TRUE);
  gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (pos_button), "accessories-text-editor");
  gtk_tool_item_set_is_important (pos_button, TRUE);
  gtk_toolbar_insert (GTK_TOOLBAR (tool_bar), pos_button, -1);

  rep_button = gtk_tool_button_new (NULL, NULL);
  gtk_tool_button_set_label (GTK_TOOL_BUTTON (rep_button), ("รายงาน"));
  gtk_tool_button_set_use_underline (GTK_TOOL_BUTTON (rep_button), TRUE);
  gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (rep_button), "printer");
  gtk_tool_item_set_is_important (rep_button, TRUE);
  gtk_toolbar_insert (GTK_TOOLBAR (tool_bar), rep_button, -1);
}

static void activate(GtkApplication *app, gpointer user_data){
  GtkWidget *window, *header, *lblClock;
  GtkWidget *button;
  GtkWidget *popover, *vbox;
  
  window = gtk_application_window_new(app);
  //gtk_widget_realize (window);

  //gtk_window_set_title(GTK_WINDOW(window), "Meamoo POS");
  gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(on_shutdown), app);

  header = gtk_header_bar_new();

  gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);
  gtk_header_bar_set_decoration_layout(GTK_HEADER_BAR(header),
      "close,maximize,minimize:menu");
  gtk_header_bar_set_title (GTK_HEADER_BAR (header), "MaeMoo POS v.0.1");
  lblClock = gtk_label_new("");
  gtk_header_bar_pack_end(GTK_HEADER_BAR(header), lblClock);
  g_timeout_add(1000, updateclock, (gpointer)lblClock);

  gtk_window_set_titlebar(GTK_WINDOW(window), header);

  //button = gtk_button_new_from_icon_name("open-menu-symbolic", GTK_ICON_SIZE_LARGE_TOOLBAR);
  
  button = gtk_menu_button_new ();
  gtk_button_set_image (GTK_BUTTON (button), gtk_image_new_from_icon_name ("open-menu-symbolic", GTK_ICON_SIZE_BUTTON));
  //gtk_widget_set_valign (button, GTK_ALIGN_CENTER);
  //gtk_widget_set_halign (button, GTK_ALIGN_CENTER);
  gtk_header_bar_pack_end(GTK_HEADER_BAR(header), button);
  
  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *btnMenu;
  btnMenu = gtk_button_new_with_label("แฟ้มข้อมูลหลัก");
  gtk_box_pack_start(GTK_BOX(vbox), btnMenu, FALSE, FALSE, 0);
  btnMenu = gtk_button_new_with_label("จัดการระบบ");
  gtk_box_pack_start(GTK_BOX(vbox), btnMenu, FALSE, FALSE, 0);
  
  popover = gtk_popover_new (button);
  gtk_container_add (GTK_CONTAINER (popover), vbox);
  gtk_menu_button_set_popover (GTK_MENU_BUTTON (button), popover);

  gtk_widget_realize (popover);
  gtk_widget_show_all (popover);

  //สร้าง Tool bar 
  createToolbar((gpointer)window);
  createMenu(header);
  
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
