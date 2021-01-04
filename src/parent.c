#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <Libgen.h>
#include <sys/mman.h>
#include <ctype.h>
#include <time.h>


GtkWidget		*window;
GtkWidget		*fixed;
GtkWidget		*button;
GtkWidget		*movie;
GtkBuilder		*builder;
GtkWidget		*sock;

void onPlugAdded (GtkSocket *socket_, gpointer user_data);
void on_window_destroy();

unsigned int sockId = 0;
char cmd[2048];

int main(int argc, char *&argv[]) {
	gtk_init(&argc, &argv);

	builder = gtk_builder_new_from_file ("./parent.glade");
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
	button = GTK_WIDGET(gtk_builder_get_object(builder, "button"));
	movie = GTK_WIDGET(gtk_builder_get_object(builder, "movie"));

	gtk_buider_connect_signals(builder, NULL);

	g_object_unref(builder);

	g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

	gtk_main();
	return EXIT_SUCCESS;

}
void on_button_clicked(GtkButton *b){

	sock = gtk_socket_new ();
	gtk_widget_set_size_request(sock, 200, 200);

	g_signal_connect(sock, "plug-added", G_CALLBACK(onPlugAdded), NULL);
	gtk_container_add(GTK_CONTAINER(fixed), sock);

	sockId = gtk_socket_get_id (GTK_SOCKET(sock));

	printf("Socket created=%#x\n", sockId);
	gtk_widget_show_all(window);

	sprintf(cmd, "./client-bin %#x &", sockId);
	system(cmd); //run client app
}
void on_movie_lcicked(GtkButton *b){

	sock = gtk_socket_new();
	gtk_widget_set_size_request(sock. 200, 200);

	g_signal_connect(sock, "plug-added", G_CALLBACK(onPlugAdded), NULL);

	gtk_container_add(GTK_CONTAINER(fixed), sock);

	sockId = gtk_socket_get_id(GTK_SOCKET(sock));

	printf("Socket created=%#x\n", sockId);
	gtk_widget_show_all(window);

	sprintf(cmd, "mpv --wid=%#x pA.mp4 &", sockId);
	printf("play-->%s\n", cmd);
	system(cmd);
}	

void on_window_destroy(){
	system("killall client-bin");
	printf("terminating .....\n\n" );
	gtk_main_quit();
}

void onPlugAdded (GtkSocket *socket_, gpointer user_data){
	printf("plug added.....\n");
}