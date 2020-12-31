#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<gtk/gtk.h>
#include<gtk/gtkx.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>
#include<signal.h>
#include<Libgen.h>
#include<sys/mman.h>
#include<ctype.h>
#include<time.h>



void 	on_bottom_admin_apply_clicked (GtkButton *b);

GtkWidget 		*window_txt;
GtkWidget		*dlg_file_choose;
GtkWidget		*button1;
GtkWidget		*button2;
GtkWidget		*dlg_about;
GtkWidget		*btn_close;

struct myStruct{
	char name[10];
	int userId;
	char password[10];
};
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
	
	button1 = gtk_button_new_with_label("image 1");
	button2 = gtk_button_new_with_label("image 2");
	btn_close = gtk_button_new_with_label("quit 2");

	g_signal_connect(button1, "clicked", (GCallback)on_button1_clicked, NULL);
	g_signal_connect(button2, "clicked", (GCallback)on_button2_clicked, NULL);
	g_signal_connect(btn_close, "clicked", (GCallback)on_btn_close_activate, NULL);
	
	
	fixed = gtk_fixed_new();
	
	gtk_container_add(GTK_CONTAINER(plug), fixed);

	gtk_widget_show_all(plug);

	gtk_main();

	return EXIT_SUCCESS;
	
                                                            //Starting window
    const gchar *USERNAME;
    const gchar *PASSWORD;
gboolean enteredUsername(GtkEntry *un, gpointer  user)
    {
        USERNAME = gtk_entry_get_text ((un));
        return FALSE;
    }
    gboolean enteredPassword(GtkEntry *pw, gpointer  user)
    {
        PASSWORD = gtk_entry_get_text ((pw));
        return FALSE;
    }

                                    //Starting window
void submit_clicked(GtkButton *b1, gpointer  entry1)

    {
        if (strcmp(USERNAME,"user") == 0 && strcmp(PASSWORD,"1234") == 0)
        {
      
        gtk_widget_hide(LoginWindow);
        gtk_widget_show (MainWindow);                
        
         }  
        
    }
 
 void on_quit_clicked()
{
    gtk_widget_destroy(MainWindow);
}	
	
	
	
	
	
	
	
	server.sin_family = AF_INET;
	server.sin_port = htons(3050);
	server.sin_addr.s_addr = INADDR_ANY;
	
	
	int x=connect(sockfd, (struct sockaddr *)&server, sizeof(server));
	if(x==-1){
		printf("Connection Failure\n");
		exit(0);
	}
	
	struct myStruct myst;
	printf("Enter userId : "); 
	scanf("%d",&myst.userId);
	printf("Enter password : "); 
	scanf("%s",myst.password);

	
	send(sockfd,&myst,sizeof(myst),0);
	
	char message[20];
	recv(sockfd, message, sizeof(message), 0);
	
	printf("%s",message);
	
	
	close(sockfd);
	return 0;
}
