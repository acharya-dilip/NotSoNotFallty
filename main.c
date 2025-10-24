#include <stdio.h>
#include <gtk/gtk.h>
#include <curl/curl.h>

void login();

//Globalised Variables
    GtkWidget *windowMain;

static void activate(GtkApplication *app,gpointer user_data) {
    login();

    //Widgets for MainProgram


    windowMain = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(windowMain),"NotSoNotSocial");
    gtk_window_set_default_size(GTK_WINDOW(windowMain),600,600);

}

void login() {
    GtkWidget *windowLogin;
    GtkWidget *gridParent;
    GtkWidget *labelGmail;
    GtkWidget *entryGmail;
    GtkWidget *labelPassword;
    GtkWidget *entryPassword;
    GtkWidget *buttonLogin;

    //Initalization of windowLogin
    windowLogin = gtk_window_new();
    gtk_window_set_default_size(GTK_WINDOW(windowLogin),200,200);
    gtk_window_set_title(GTK_WINDOW(windowLogin),"Login");
    gtk_window_present(GTK_WINDOW(windowLogin));

    //Init of gridParent
    gridParent = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowLogin),gridParent);




}

int main(int argc, char **argv){
    GtkApplication *app;
    int status;
    app= gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);


    return status;
}
