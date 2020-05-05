#include <gtk/gtk.h>
static gboolean 
delete_event(GtkWidget *window, GdkEvent *event, gpointer parent){
  GtkWidget *dialog;
  dialog = gtk_dialog_new_with_buttons("Exit program", 
              GTK_WINDOW(parent), GTK_DIALOG_MODAL, 
              GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT, 
              GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, NULL);
 
  GtkWidget *label = gtk_label_new(
        "กรุณายืนยัน, ต้องการออกจากโปรแกรมใช่หรือไม่");
  GtkWidget *image = gtk_image_new_from_stock(
        GTK_STOCK_DIALOG_QUESTION, GTK_ICON_SIZE_DIALOG);
  GtkWidget *hbox = gtk_hbox_new(FALSE, 5);
 
  gtk_container_set_border_width(GTK_CONTAINER(hbox), 10);
  gtk_box_pack_start_defaults(GTK_BOX(hbox), image);
  gtk_box_pack_start_defaults(GTK_BOX(hbox), label);
 
  gtk_box_pack_start_defaults(
        GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox);
 
  gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);
  gtk_widget_show_all(dialog);
 
  int result = gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
 
  if (result == GTK_RESPONSE_ACCEPT){
    gtk_main_quit();
    return FALSE;
  }else{
    return TRUE;
  }
}
static gboolean
btn_clicked(GtkWidget *widget, gpointer parent){
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(GTK_WINDOW(parent), 
              GTK_DIALOG_DESTROY_WITH_PARENT, 
              GTK_MESSAGE_QUESTION, 
              GTK_BUTTONS_YES_NO, 
              "คุณต้องการออกจากโปรแกรมใช่หรือไม่?");
  gtk_window_set_title(GTK_WINDOW(dialog), "Question");
  int result = gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
  if (result == GTK_RESPONSE_YES){
    gtk_main_quit();
    return FALSE;
  }else{
    return TRUE;
  }
}
int main(int argc, char *argv[]){
  gtk_init(&argc, &argv);
  GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(GTK_OBJECT(win), 
         "delete_event", G_CALLBACK(delete_event),(gpointer) win);
 
  gtk_window_set_title(GTK_WINDOW(win), "Hello world");
  gtk_window_set_default_size(GTK_WINDOW(win), 400, 300);
  gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
 
  GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(win), vbox);
 
  GtkWidget *label = gtk_label_new("C GUI with Gtk+-2.0");
  gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, FALSE, 0);
  
  GtkWidget *hbox = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_end(GTK_BOX(vbox), hbox, FALSE, FALSE, 10);
  GtkWidget *button = gtk_button_new_from_stock(GTK_STOCK_QUIT);
  gtk_widget_set_size_request(GTK_WIDGET(button), 80, 30);
  gtk_box_pack_end(GTK_BOX(hbox), button, FALSE, FALSE, 10);
  g_signal_connect(G_OBJECT(button), 
         "clicked", G_CALLBACK(btn_clicked), (gpointer) win);
 
  gtk_widget_show_all(win);
 
  gtk_main();
  return 0;
}
