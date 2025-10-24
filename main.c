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
    //gtk_window_set_default_size(GTK_WINDOW(windowLogin),200,200);
    gtk_window_set_title(GTK_WINDOW(windowLogin),"Login");
    gtk_window_present(GTK_WINDOW(windowLogin));

    //Init of gridParent
    gridParent = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowLogin),gridParent);
    //Margins & Paddings
    gtk_widget_set_margin_start(gridParent,10);
    gtk_widget_set_margin_end(gridParent,10);
    gtk_widget_set_margin_top(gridParent,10);
    gtk_widget_set_margin_bottom(gridParent,10);
    gtk_widget_set_halign(gridParent,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(gridParent,GTK_ALIGN_CENTER);


    //Init of LabelGmail
    labelGmail = gtk_label_new("Gmail:");
    gtk_grid_attach(GTK_GRID(gridParent),labelGmail,0,0,1,1);
    //Margins & Paddings
    gtk_widget_set_margin_end(labelGmail,10);


    //Init of entryGmail
    entryGmail = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParent),entryGmail,1,0,5,1);
    //Margins & Paddings
    gtk_widget_set_size_request(entryGmail,200,-1);

    //Init of labelPassword
    labelPassword = gtk_label_new("Pass:");
    gtk_grid_attach(GTK_GRID(gridParent),labelPassword,0,1,1,1);
    //Margins & Paddings
    gtk_widget_set_margin_end(labelPassword,10);


    //Init of entryPassword
    entryPassword = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParent),entryPassword,1,1,5,1);


    //init of buttonLogin
    buttonLogin = gtk_button_new_with_label("Login");
    gtk_grid_attach(GTK_GRID(gridParent),buttonLogin,1,2,5,1);


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
