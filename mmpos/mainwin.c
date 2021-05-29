#include "mainwin.h"

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
