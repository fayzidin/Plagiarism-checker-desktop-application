#include<gtk/gtk.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<pthread.h>


GtkBuilder *builder;
GtkWidget *window_admin;
GtkWidget *window_application;
GtkWidget *window_application_history;


#define PORT 8888
#define BUFSIZE 1024


int signal_cpp=0;




void send_to_all(int j, int i, int sockfd, int nbytes_recvd, char *recv_buf, fd_set *master)
{
  if (FD_ISSET(j, master)){
    if (j != sockfd && j != i) {
      if (send(j, recv_buf, nbytes_recvd, 0) == -1) {
        perror("send");
      }
    }
  }
}
    
void send_recv(int i, fd_set *master, int sockfd, int fdmax)
{
  int nbytes_recvd, j;
  char recv_buf[BUFSIZE], buf[BUFSIZE];
  
  if ((nbytes_recvd = recv(i, recv_buf, BUFSIZE, 0)) <= 0) {
    if (nbytes_recvd == 0) {
      printf("socket %d is activated\n", i);
    }else {
      perror("recv");
    }
    close(i);
    FD_CLR(i, master);
  }else { 
	recv_buf[nbytes_recvd] = '\0';

  if(!strcmp(recv_buf,"S.O.P"))
  {
      signal_cpp=1;
  }

  
  if(!strcmp(recv_buf,"Core"))
  {
      signal_manager;
  }
  

    for(j = 0; j <= fdmax; j++){
      send_to_all(j, i, sockfd, nbytes_recvd, recv_buf, master );
    }
	fflush(stdout);
  }  
}
    
void connection_accept(fd_set *master, int *fdmax, int sockfd, struct sockaddr_in *client_addr)
{
  socklen_t addrlen;
  int newsockfd;
  
  addrlen = sizeof(struct sockaddr_in);
  if((newsockfd = accept(sockfd, (struct sockaddr *)client_addr, &addrlen)) == -1) {
    perror("accept");
    exit(1);
  }else {
    FD_SET(newsockfd, master);
    if(newsockfd > *fdmax){
      *fdmax = newsockfd;
    }
    printf("%s connected to port %d \n",inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port));
  }
}
  
void connect_request(int *sockfd, struct sockaddr_in *my_addr)
{
  int yes = 1;
    
  if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("Socket");
    exit(1);
  }
    
  my_addr->sin_family = AF_INET;
  my_addr->sin_port = htons(8888);
  my_addr->sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(my_addr->sin_zero, '0', sizeof my_addr->sin_zero);
    
  if (setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
    perror("setsockopt");
    exit(1);
  }
    
  if (bind(*sockfd, (struct sockaddr *)my_addr, sizeof(struct sockaddr)) == -1) {
    perror("Unable to bind");
    exit(1);
  }
  if (listen(*sockfd, 10) == -1) {
    perror("listen");
    exit(1);
  }
  printf("\nSystem is waiting for users to connect to the port 8888\n");
  fflush(stdout);
}

int main (int argc, char *argv[])
{
	
   pthread_t thread_glade;
	
	fd_set master;
  fd_set read_fds;
  int fdmax, i;
  int sockfd= 0;
  struct sockaddr_in my_addr, client_addr;
  
  FD_ZERO(&master);
  FD_ZERO(&read_fds);
  connect_request(&sockfd, &my_addr);
  FD_SET(sockfd, &master);
  
  fdmax = sockfd;




    gtk_init(&argc, &argv);
   
    builder = gtk_builder_new_from_file ("glade/admin.glade");
    gtk_builder_connect_signals(builder, NULL);

    window_admin = GTK_WIDGET(gtk_builder_get_object(builder, "window_admin"));
    window_application = GTK_WIDGET(gtk_builder_get_object(builder, "window_application"));
    window_application_history = GTK_WIDGET(gtk_builder_get_object(builder, "window_application_history"));
 
    gtk_widget_hide (GTK_WIDGET(window_admin));
    gtk_widget_hide (GTK_WIDGET(window_application));
    gtk_widget_hide (GTK_WIDGET(window_application_history));
  

    gtk_widget_show(window_admin);
   
//    gtk_main 
pthread_create(&thread_glade, NULL, gtk_main, NULL);

	
  while(1){
    read_fds = master;
    if(select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1){
      perror("select");
      exit(4);
    }
    
    for (i = 0; i <= fdmax; i++){
      if (FD_ISSET(i, &read_fds)){
        if (i == sockfd)
          connection_accept(&master, &fdmax, sockfd, &client_addr);
        else
          send_recv(i, &master, sockfd, fdmax);
      }
    }
  }
pthread_join (thread_glade, NULL);
    return 0;

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

//menu application
void on_bottom_confirm_clicked()
{

    gtk_widget_show(window_application_history);
    gtk_widget_hide(window_application);
}

void on_bottom_history_clicked(GtkButton *button,gpointer *admin_data)
{  
  // selection signal start
if(signal_cpp == 1)
  {
    GtkTreeIter iter;
  
    GtkTreeView *treeview_application_admin = GTK_TREE_VIEW(admin_data);
  
    GtkListStore *liststore2 = GTK_LIST_STORE(gtk_tree_view_get_model(treeview_application_admin));
    
    gtk_list_store_append(liststore2, &iter); 
 
    gtk_list_store_set(liststore2, &iter, 0,"S.O.P", 1, 5,2, 100,3, "20%" , 4, "User_1", 5, "Mars", -1);

     signal_cpp=0;
    }

    

//selection signal end

    gtk_widget_show(window_application_history);
    gtk_widget_hide(window_application);

    
}

void on_bottom_application_history_back_clicked()
{
    gtk_widget_show(window_application);
    gtk_widget_hide(window_application_history);
}
