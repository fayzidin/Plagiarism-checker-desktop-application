#include<gtk/gtk.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<gdk/gdk.h>
#include<glib-object.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<pthread.h>
#include<webkit2/webkit2.h>

GtkBuilder *builder;
GtkWidget *LoginWindow;
GtkWidget *window_selection;
GtkWidget *window_application;
GtkWidget 	*window;
GtkWidget	*window_browser;
GtkWidget 	*w_txtvw_main;            // Pointer to text view object
GtkWidget 	*w_dlg_file_choose;       // Pointer to file chooser dialog box
GtkTextBuffer 	*textbuffer_main;     // Pointer to text buffer
GtkWidget	*w_dlg_about;             // Pointer to about dialog box

#define BUFSIZE 1024

static char *plagiarism[]={'\0'};
static int counter=0;
char detection[]="detections";

void f(const char* s, char* res) {
    char* l = strchr(s, ' ');
    char* r = strchr(l + 1, ' ');
    memcpy(res, l + 1, r - l);
    res[r - l - 1] = '\0';
}


void send_recv(int i, int sockfd)
{
  char send_buf[BUFSIZE];
  char recv_buf[BUFSIZE];
  int nbyte_recvd;
  
  if (i == 0){

    fgets(send_buf, BUFSIZE, stdin);
    //send_buf=bus_num;
    if (strcmp(send_buf , "quit\n") == 0) {
      exit(0);
    }else
      send(sockfd, send_buf, strlen(send_buf), 0);
  }else {
    nbyte_recvd = recv(sockfd, recv_buf, BUFSIZE, 0);
    recv_buf[nbyte_recvd] = '\0';
    printf("%s\n" , recv_buf);
    fflush(stdout);
  }
}
    
    
void connect_request(int *sockfd, struct sockaddr_in *ser_address)
{
  if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("Socket error");
    exit(1);
  }
  
  ser_address->sin_port = htons(8888);
  ser_address->sin_family = AF_INET;
  ser_address->sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(ser_address->sin_zero, '0', sizeof ser_address->sin_zero);
  
  if(connect(*sockfd, (struct sockaddr *)ser_address, sizeof(struct sockaddr)) == -1) {
    perror("connected");
    exit(1);
  }
}

void send_plagiarism(char str[]){

  char sockfd, fdmax, i;
  struct sockaddr_in ser_address;
  fd_set master;
  fd_set read_fds;
 
  connect_request(&sockfd, &ser_address);
  FD_ZERO(&master);
        FD_ZERO(&read_fds);
        FD_SET(0, &master);
        FD_SET(sockfd, &master);
  fdmax = sockfd;

  for(i=0;i<counter;i++){
  send(sockfd, plagiarism[i], strlen(plagiarism[i]), 0);
  printf("%s\n", plagiarism[i]);
   }

  printf("Client socket closed\n");
  close(sockfd);

}

typedef struct {
    GtkWidget 	*w_txtvw_main;            // Pointer to text view object
    GtkWidget 	*w_dlg_file_choose;       // Pointer to file chooser dialog box
    GtkTextBuffer 	*textbuffer_main;     // Pointer to text buffer
    GtkWidget 	*w_dlg_about;             // Pointer to about dialog box
    GtkWidget *w_webkit_webview;
} app_widgets;

int main (int argc, char *argv[])
{
	GtkBuilder      *builder; 
    GtkWidget       *window_txt;
    
    app_widgets     *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);
    
    // Workaround from: https://bugs.webkit.org/show_bug.cgi?id=175937
    //g_object_unref (g_object_ref_sink (webkit_web_view_new ()));
    webkit_web_view_get_type();
    webkit_settings_get_type();
   
    builder = gtk_builder_new_from_file ("client.glade");
    //gtk_builder_connect_signals(builder, NULL);


    LoginWindow  = GTK_WIDGET(gtk_builder_get_object(builder, "login"));
   
    window_selection  = GTK_WIDGET(gtk_builder_get_object(builder, "window_selection"));
    window_application  = GTK_WIDGET(gtk_builder_get_object(builder, "window_application"));
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window_txt"));
	window_browser = GTK_WIDGET(gtk_builder_get_object(builder, "window_browser"));
    // Get pointers to widgets
    widgets->w_webkit_webview  = GTK_WIDGET(gtk_builder_get_object(builder, "webkit_webview"));
    widgets->w_txtvw_main = GTK_WIDGET(gtk_builder_get_object(builder, "txtvw_main"));
    widgets->w_dlg_file_choose = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_file_choose"));
    widgets->textbuffer_main = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "textbuffer_main"));
    widgets->w_dlg_about = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_about"));

    gtk_widget_hide (GTK_WIDGET(LoginWindow));
    gtk_widget_hide (GTK_WIDGET(window_selection));
    gtk_widget_hide (GTK_WIDGET(window_application));
    
    
	gtk_builder_connect_signals(builder, widgets);
	
	webkit_web_view_load_uri(WEBKIT_WEB_VIEW(widgets->w_webkit_webview), "https://plagiarismdetector.net/");
	
	g_object_unref(builder);
	
    gtk_widget_show(LoginWindow);
   
    gtk_main();
    g_slice_free(app_widgets, widgets);

    return 0;
}


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
		gtk_widget_show(window_selection);
		                
    }  
        
}
 
 
 // File --> Open
void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gchar *file_name = NULL;        // Name of file to open from dialog box
    gchar *file_contents = NULL;    // For reading contents of file
    gboolean file_success = FALSE;  // File read status
    
    // Show the "Open Text File" dialog box
    gtk_widget_show(app_wdgts->w_dlg_file_choose);
    
    // Check return value from Open Text File dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_dlg_file_choose)) == GTK_RESPONSE_OK) {
        // Get the file name from the dialog box
        file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->w_dlg_file_choose));
        if (file_name != NULL) {
            // Copy the contents of the file to dynamically allocated memory
            file_success = g_file_get_contents(file_name, &file_contents, NULL, NULL);
            if (file_success) {
                // Put the contents of the file into the GtkTextBuffer
                gtk_text_buffer_set_text(app_wdgts->textbuffer_main, file_contents, -1);
            }
            g_free(file_contents);
        }
        g_free(file_name);
    }

    // Finished with the "Open Text File" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}

// File --> Close
void on_menuitm_close_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    // Clear the text from window "Close the file"
    gtk_text_buffer_set_text(app_wdgts->textbuffer_main, "", -1);
}

// File --> Quit
void on_menuitm_quit_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gtk_main_quit();
}
// Help --> About
void on_menuitm_about_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gtk_widget_show(app_wdgts->w_dlg_about);
}
// About dialog box Close button
void on_dlg_about_response(GtkDialog *dialog, gint response_id, app_widgets *app_wdgts)
{
    gtk_widget_hide(app_wdgts->w_dlg_about);
}
// called when window is closed
void on_window_txt_destroy()
{
    gtk_main_quit();
}

 
 
 
 


void on_btn_apply_clicked(){
	gtk_widget_show(window_application);
	gtk_widget_hide(window);
}

                                                             //menu selection


	

void on_selection_next_clicked(GtkButton *button)
{
    gtk_widget_show(window);
    gtk_widget_hide(window_selection);
}

//selection menu start
 
void on_OnlineCheck_toggled(GtkToggleButton *togglebutton,  gpointer *user_data)
{
    gboolean state_toggled;
    
    state_toggled = gtk_toggle_button_get_active(togglebutton);
         GtkTreeIter iter;
    GtkTreeView *treeview_application = GTK_TREE_VIEW(user_data);
    GtkListStore *liststore1 = GTK_LIST_STORE(gtk_tree_view_get_model(treeview_application));

    if (state_toggled) {
    gtk_list_store_append(liststore1, &iter);
    gtk_list_store_set(liststore1, &iter, 0, "S.O.P", 1, 5,2, 100,3, "20%", -1);
    plagiarism[counter++]="S.O.P";
     
    }
    else {
    gtk_list_store_remove (GTK_LIST_STORE(liststore1), &iter);
    }
}
//selection menu end


// User presses Enter in the URL bar
void on_entry_url_activate(GtkEntry *entry, app_widgets *app_wdgts)
{
    const gchar *the_url;
    
    the_url = gtk_entry_get_text(entry);
    
    webkit_web_view_load_uri(WEBKIT_WEB_VIEW(app_wdgts->w_webkit_webview), the_url);
}

// called when window is closed
void on_window_browser_destroy()
{
    gtk_main_quit();
}
void on_online_check_clicked(){
	
	gtk_widget_show(window_browser);
    gtk_widget_hide(window_selection);
}
                                                
void on_order_clicked()
{
    send_plagiarism(detection);
  
}

void on_selection_out_clicked()
{
       gtk_widget_destroy(window_selection);
}

void on_application_cancel_clicked()
{
    gtk_widget_show(window_selection);
    gtk_widget_hide(window_application);
}

void on_application_back_clicked()
{
    gtk_widget_show(window);
    gtk_widget_hide(window_application);
}

