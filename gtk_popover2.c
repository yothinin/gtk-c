/*
 * Build:
 * gcc $(pkg-config --cflags gtk+-3.0) popover_sample.c -o popover_sample $(pkg-config --libs gtk+-3.0)
 */

#include <gtk/gtk.h>

static void clickLabel(gpointer user_data){
	g_print("Label clicked\n");
}

int main (int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *button, *popover, *vbox, *lbl;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_realize (window);

  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width (GTK_CONTAINER (window), 5);
  gtk_window_set_default_size (GTK_WINDOW (window), 640, 480);

  button = gtk_menu_button_new ();
  gtk_button_set_image (GTK_BUTTON (button), gtk_image_new_from_icon_name ("open-menu-symbolic", GTK_ICON_SIZE_BUTTON));
  gtk_widget_set_valign (button, GTK_ALIGN_START);
  gtk_widget_set_halign (button, GTK_ALIGN_START);
  gtk_container_add (GTK_CONTAINER (window), button);

  vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  lbl = gtk_label_new ("แฟ้มข้อมูลหลัก");
  gtk_label_set_xalign(GTK_LABEL(lbl), 0.0); // จัดให้ตัวอักษรอยู่ชิดซ้าย
  gtk_box_pack_start (GTK_BOX (vbox), lbl, FALSE, FALSE, 0);
  g_signal_connect(G_OBJECT(lbl), "clicked", G_CALLBACK(clickLabel), lbl);

  lbl = gtk_label_new ("ทำรายการ");
  gtk_label_set_xalign(GTK_LABEL(lbl), 0.0); // จัดให้ตัวอักษรอยู่ชิดซ้าย
  gtk_box_pack_start (GTK_BOX (vbox), lbl, FALSE, FALSE, 0);

  lbl = gtk_label_new ("รายงาน");
  gtk_label_set_xalign(GTK_LABEL(lbl), 0.0); // จัดให้ตัวอักษรอยู่ชิดซ้าย
  gtk_box_pack_start (GTK_BOX (vbox), lbl, FALSE, FALSE, 0);

  lbl = gtk_label_new ("จัดการระบบ");
  gtk_label_set_xalign(GTK_LABEL(lbl), 0.0); // จัดให้ตัวอักษรอยู่ชิดซ้าย
  gtk_box_pack_start (GTK_BOX (vbox), lbl, FALSE, FALSE, 0);

  popover = gtk_popover_new (button);
  gtk_container_add (GTK_CONTAINER (popover), vbox);
  gtk_menu_button_set_popover (GTK_MENU_BUTTON (button), popover);
  gtk_widget_show_all (popover);

  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);

  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}
