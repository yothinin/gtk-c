#include <gtk/gtk.h>

static void on_shutdown(GtkWidget *widget, gpointer user_data){
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

static void onMenuClick(GtkWidget *widget, gpointer user_data){
  g_print("%s\n", (gchar *)user_data);
}

static void createPopover(gpointer btn){
  GtkWidget *popover, *vbox;
  GtkWidget *btnMenu, *lbl;

  // สร้าง vbox เพื่อบรรจุ ปุ่มกดของ popover menu
  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);

  // สร้างปุ่ม แฟ้มข้อมูลหลัก โดยใช้ label บรรจุไว้ใน button
  lbl = gtk_label_new("แฟ้มข้อมูลหลัก");
  gtk_label_set_xalign(GTK_LABEL(lbl), 0.0); // จัดให้ตัวอักษรอยู่ชิดซ้าย
  // สร้างปุ่ม เพื่อบรรจุ label ที่สร้างไว้ข้างบน
  btnMenu = gtk_button_new();
  gtk_button_set_relief(GTK_BUTTON(btnMenu), GTK_RELIEF_NONE);
  gtk_container_add(GTK_CONTAINER(btnMenu), lbl);
  gtk_box_pack_start(GTK_BOX(vbox), btnMenu, FALSE, FALSE, 0);
  g_signal_connect(G_OBJECT(btnMenu), "clicked", G_CALLBACK(onMenuClick), "master");

  lbl = gtk_label_new("จัดการระบบ");
  gtk_label_set_xalign(GTK_LABEL(lbl), 0.0); // จัดให้ตัวอักษรอยู่ชิดซ้าย
  btnMenu = gtk_button_new();
  gtk_button_set_relief(GTK_BUTTON(btnMenu), GTK_RELIEF_NONE);
  gtk_container_add(GTK_CONTAINER(btnMenu), lbl);
  gtk_box_pack_start(GTK_BOX(vbox), btnMenu, FALSE, FALSE, 0);
  g_signal_connect(G_OBJECT(btnMenu), "clicked", G_CALLBACK(onMenuClick), "setting");

  lbl = gtk_label_new("About");
  gtk_label_set_xalign(GTK_LABEL(lbl), 0.0); // จัดให้ตัวอักษรอยู่ชิดซ้าย
  btnMenu = gtk_button_new();
  gtk_button_set_relief(GTK_BUTTON(btnMenu), GTK_RELIEF_NONE);
  gtk_container_add(GTK_CONTAINER(btnMenu), lbl);
  gtk_box_pack_start(GTK_BOX(vbox), btnMenu, FALSE, FALSE, 0);
  g_signal_connect(G_OBJECT(btnMenu), "clicked", G_CALLBACK(onMenuClick), "About");

  // สร้าง popover สำหรับปุ่ม btn (รับค่ามาจาก parameter)
  popover = gtk_popover_new (GTK_WIDGET(btn));
  // บรรจุ vbox รายการเมนูไปไว้ใน popover
  gtk_container_add (GTK_CONTAINER (popover), vbox);
  // บรรจุ popover ไว้ใน btn
  gtk_menu_button_set_popover (GTK_MENU_BUTTON (btn), popover);

  // แสดงผลของ popover
  gtk_widget_realize (popover);	// กำหนดก่อนเรียก gdk
  gtk_widget_show_all (popover);
}

static void createToolbar(gpointer win){
  GtkWidget *tool_bar, *vbox;
  GtkToolItem *home_button, *pos_button, *rep_button;

  // สร้าง toolbar แล้วเพิ่มเข้าไปใน vbox
  tool_bar = gtk_toolbar_new ();
  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start (GTK_BOX (vbox), tool_bar, FALSE, FALSE, 0);
  // เพิ่ม vbox เข้าไปในหน้าจอ win
  gtk_container_add (GTK_CONTAINER (GTK_WINDOW(win)), vbox);

  // สร้างปุ่ม  Home
  home_button = gtk_tool_button_new (NULL, NULL);
  gtk_tool_button_set_label (GTK_TOOL_BUTTON (home_button), ("_Home"));
  gtk_tool_button_set_use_underline (GTK_TOOL_BUTTON (home_button), TRUE);
  gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (home_button), "go-home");
  gtk_tool_item_set_is_important (home_button, TRUE);
  gtk_toolbar_insert (GTK_TOOLBAR (tool_bar), home_button, -1);

  // สร้างปุ่ม หน้าขาย
  pos_button = gtk_tool_button_new (NULL, NULL);
  gtk_tool_button_set_label (GTK_TOOL_BUTTON (pos_button), ("หน้าขาย"));
  gtk_tool_button_set_use_underline (GTK_TOOL_BUTTON (pos_button), TRUE);
  gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (pos_button), "accessories-text-editor");
  gtk_tool_item_set_is_important (pos_button, TRUE);
  gtk_toolbar_insert (GTK_TOOLBAR (tool_bar), pos_button, -1);

  // สร้างปุ่ม รายงาน
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

  //สร้าง Popover Menu
  createPopover((gpointer)button);

  //สร้าง Tool bar
  createToolbar((gpointer)window);

  gtk_widget_show_all(window);
}

int main(int argc, char *argv[]){
  GtkApplication *app;
  int status;

  //สร้าง window ผ่าน gtk_application
  app = gtk_application_new("com.maemoo.pos", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  //รัน application ที่สร้างไว้ด้านบน
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
