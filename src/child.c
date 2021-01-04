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


void 	on_btn1_clicked (GtkButton *b);
void	on_btn2_clicked (GtkButton *b);

GtkWidget * fixed;
GtkWidget * image;
GtkWidget *btn1;
GtkWidget *btn2;
GtkWidget *btn3;
GtkWidget *plug;


int main(int argc, char *argv[]){

	unsigned int sockId = 0;
//	Assumes first arg is socket id
	if (argc==2){
		sscanf(argv[1], "%x",&sockId);
	}
	else {
		return EXIT_FAILURE;
	}
	gtk_init(&argc, &argv);

	plug = gtk_plug_new(sockId);
	// make some buttons

	btn1 = gtk_button_new_with_label("image 1");
	btn2 = gtk_button_new_with_label("image 2");
	btn3 = gtk_button_new_with_label("quit 2");

	g_signal_connect(btn1, "clicked", (GCallback)on_btn1_clicked, NULL);
	g_signal_connect(btn2, "clicked", (GCallback)on_btn2_clicked, NULL);
	g_signal_connect(btn3, "clicked", (GCallback)gtk_main_quit, NULL);

	fixed = gtk_fixed_new();

	gtk_fixed_put (GTK_FIXED(fixed), btn1, 0, 0);
	gtk_fixed_put (GTK_FIXED(fixed), btn2, 0, 30);
	gtk_fixed_put (GTK_FIXED(fixed), btn3, 0, 60);

	image = gtk_image_new_from_file ("./test1.jpg");
	gtk_fixed_put(GTK_FIXED(fixed), image, 0, 90);

	gtk_container_add(GTK_CONTAINER(plug), fixed);

	gtk_widget_show_all(plug);

	gtk_main();

	return EXIT_SUCCESS;
}
void on_window_destroy(){
	gtk_main_quit();
}
void on_btn1_clicked(GtkButton *b){
	printf("button 1 clicked\n");

	gtk_container_remove(GTK_CONTAINER (fixed), image);
	image = gtk_image_new_from_file("./test1.jpg");
	gtk_fixed_put(GTK_FIXED(fixed), image, 0, 90);
	gtk_widget_show_all(plug);
}
void on_btn2_clicked(GtkButton *b){
	printf("button 2 clicked\n");

	gtk_container_remove(GTK_CONTAINER(fixed), image);

	image = gtk_image_new_from_file("./test2.jpg");

	gtk_fixed_put(GTK_FIXED(fixed), image, 0, 90);

	gtk_widget_show_all(plug);
}