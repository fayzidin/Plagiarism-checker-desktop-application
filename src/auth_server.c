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


GtkBuilder		*builder;
GtkWidget 		*window_admin;
GtkWidget		*bottom_admin_apply
GtkWidget		*textbuffer_main;
GtkWidget		*sock;



void onPlugAdded (GtkSocket *socket_, gpointer user_data);
void on_window_destroy();

unsigned int sockId = 0;
char cmd[2048];

struct myStruct{
	char name[10];
	int userId;
	char password[10];
};
int main(int argc, char *&argv[]){
	gtk_init(&argc, &argv);

	builder = gtk_builder_new_from_file ("glade/window_main.glade");
	window_admin = GTK_WIDGET(gtk_builder_get_object(builder, "window_admin"));
	bottom_admin_apply = GTK_WIDGET(gtk_builder_get_object(builder, "bottom_admin_apply"));
	textbuffer_main = GTK_WIDGET(gtk_builder_get_object(builder, "textbuffer_main"));
	
	
	gtk_buider_connect_signals(builder, NULL);

	g_object_unref(builder);

	g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

	gtk_main();
	return EXIT_SUCCESS;
	
void on_button_clicked(GtkButton *b){

	sock = gtk_socket_new ();
	gtk_widget_set_size_request(sock, 200, 200);

	g_signal_connect(sock, "plug-added", G_CALLBACK(onPlugAdded), NULL);
	gtk_container_add(GTK_CONTAINER(fixed), sock);

	sockId = gtk_socket_get_id (GTK_SOCKET(sock));

	printf("Socket created=%#x\n", sockId);
	gtk_widget_show_all(window);

	sprintf(cmd, "./auth_client %#x &", sockId);
	system(cmd); //run client app
}


//menu admin

    const gchar *USERNAME;
    const gchar *PASSWORD;
gboolean enteredUsername(GtkEntry *e1, gpointer  user)
    {
        USERNAME = gtk_entry_get_text ((e1));
        return FALSE;
    }
    gboolean enteredPassword(GtkEntry *e2, gpointer  user)
    {
        PASSWORD = gtk_entry_get_text ((e2));
        return FALSE;
    }

void on_bottom_admin_apply_clicked()
{
    if (strcmp(USERNAME,"admin") == 0 && strcmp(PASSWORD,"1") == 0)
    {
    
        gtk_widget_show(window_application);
        gtk_widget_hide(window_admin);
    }
}

void on_logout_clicked()
{
       gtk_widget_destroy(window_application);
}




	
	server.sin_family = AF_INET;
	server.sin_port = htons(3050);
	server.sin_addr.s_addr = INADDR_ANY;
	//INET_ADDR("127.0.0.1")
	int x=bind(sockfd, (struct sockaddr *)&server, sizeof(server));
	if(x==-1){
		printf("bind Failure\n");
		exit(0);
	}else{
		printf("bind Successful\n");
	}
	
	listen(sockfd, 5);
	int s=sizeof(client);
	
	struct myStruct st[5]={{"nikhil1",1,"nikhil1"},
						   {"nikhil2",2,"nikhil2"},
						   {"nikhil3",3,"nikhil3"},
						   {"nikhil14",4,"nikhil4"},
						   {"nikhil5",5,"nikhil15"}};
	struct myStruct myst;
	int fd1=accept(sockfd, (struct sockaddr *)&client, &s);
	
	recv(fd1, &myst, sizeof(myst), 0);
	//recvfrom(sockfd,buff,100,0,(struct sockaddr *)&client,&s);
	
	printf("userId received :%d\n",myst.userId);
	printf("password received :%s\n",myst.password);
	int fl=1;
	for(int i=0;i<5;i++){
		if(myst.userId==st[i].userId && strcmp(myst.password,st[i].password)==0){
			fl=0;
			break;
		}
	}
	
	
	if(fl==0){		
		char message[20]="Login Successful\n";
		send(fd1, message, sizeof(message), 0);
	}else{
		char message[20]="Login Failure\n";
		send(fd1, message, sizeof(message), 0);
	}	
	
	
	close(sockfd);
	return 0;
}
