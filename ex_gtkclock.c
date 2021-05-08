#include <gtk/gtk.h>
#include <time.h>

static void on_shutdown(GtkWidget *widget, gpointer user_str){
  g_print("Exit program... %s\n", (gchar*) user_str);
  gtk_main_quit();
}

gint updateclock(gpointer ptr){
	char curr_time[9];
	time_t now;
    struct tm *now_tm;
    time (&now);

    now_tm = localtime (&now);
	sprintf(curr_time, "%02d:%02d:%02d",
			now_tm->tm_hour, 
			now_tm->tm_min, 
			now_tm->tm_sec);
	gtk_label_set_text(GTK_LABEL(ptr), curr_time);
	
	return (TRUE);
}

int main (int argc, char *argv[]){
    GtkWidget *window, *header, *statusbar;
    GtkWidget *vbox, *lblClock;
    gchar* info;

    gtk_init (&argc, &argv);

    header = gtk_header_bar_new();
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_titlebar(GTK_WINDOW(window), header);
    gtk_window_set_title(GTK_WINDOW(window), "mmPOS");

    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);
	gtk_header_bar_set_decoration_layout(GTK_HEADER_BAR(header), "close,maximize,minimize:menu");

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(on_shutdown), "Good bye...");

	statusbar = gtk_statusbar_new();
	g_object_set_data(G_OBJECT(statusbar), "info", (gpointer) "1");
	g_object_set_data(G_OBJECT(statusbar), "info", (gpointer) "2");

	guint id = gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar), "info");
	info = "This is statusbar on the button...";
	gtk_statusbar_push(GTK_STATUSBAR(statusbar), id, info);
	
	gtk_box_pack_end(GTK_BOX(vbox), statusbar, FALSE, FALSE, 0);

	lblClock = gtk_label_new("");
	gtk_header_bar_pack_end(GTK_HEADER_BAR(header), lblClock);
    //gtk_box_pack_start (GTK_BOX (vbox), lblClock, FALSE, FALSE, 10);
    
    gtk_widget_show_all(window);
    
    g_timeout_add (1000, updateclock, (gpointer) lblClock);

    gtk_main ();

    return 0;
}
