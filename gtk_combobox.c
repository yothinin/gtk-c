#include <gtk/gtk.h>

enum
{
  ICON_NAME_COL,
  TEXT_COL
};

static GtkTreeModel *
create_icon_store (void)
{
  const gchar *icon_names[5] = {
    "dialog-warning",
    "process-stop",
    "document-new",
    "edit-clear",
    "document-open"
  };
  const gchar *labels[5] = {
    "Warning",
    "Stop",
    "New",
    "Clear",
    "Open"
  };

  GtkTreeIter iter;
  GtkListStore *store;
  gint i;

  store = gtk_list_store_new (2, G_TYPE_STRING, G_TYPE_STRING);

  for (i = 0; i < G_N_ELEMENTS (icon_names); i++)
    {
      if (icon_names[i])
        {
          gtk_list_store_append (store, &iter);
          gtk_list_store_set (store, &iter,
                              ICON_NAME_COL, icon_names[i],
                              TEXT_COL, labels[i],
                              -1);
        }
    }
  return GTK_TREE_MODEL (store);
}

void on_changed(GtkWidget *widget, gpointer user_data){
  GtkTreeModel *model;
  GtkTreeIter iter;
  gchar *value;
  
  //get model and iter.
  model = gtk_combo_box_get_model(GTK_COMBO_BOX(widget));
  gtk_combo_box_get_active_iter(GTK_COMBO_BOX(widget), &iter);
  
  //get active id from combobox.
  gint active_id = gtk_combo_box_get_active(GTK_COMBO_BOX(widget));
  //get value from combobox.
  gtk_tree_model_get(model, &iter, TEXT_COL, &value, -1);
  
  g_print("active_id = %d, value = %s\n", active_id, value);
  g_free(value);    
}

int main(int argc, char *argv[])
{
  static GtkWidget *window = NULL;
  GtkWidget *box, *combo;
  GtkTreeModel *model;
  GtkCellRenderer *renderer;
  
  gtk_init(&argc, &argv);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
  gtk_container_set_border_width (GTK_CONTAINER (box), 10);

  model = create_icon_store ();
  combo = gtk_combo_box_new_with_model (model);
  
  g_object_unref (model);
  gtk_container_add (GTK_CONTAINER (box), combo);
  
  //render pixbuf to draw icon.
  renderer = gtk_cell_renderer_pixbuf_new ();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combo), renderer, FALSE);
  gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo), renderer,
                                  "icon-name", ICON_NAME_COL,
                                  NULL);

  //render text to display label.
  renderer = gtk_cell_renderer_text_new ();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combo), renderer, TRUE);
  gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (combo), renderer,
                                  "text", TEXT_COL,
                                  NULL);
  
  gtk_combo_box_set_active (GTK_COMBO_BOX (combo), 0);
  g_signal_connect(G_OBJECT(combo), "changed", G_CALLBACK(on_changed), NULL);

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_widget_show_all(window);
  
  gtk_main();

  return 0;
}
