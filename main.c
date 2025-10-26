#include <stdio.h>
#include <gtk/gtk.h>
#include <curl/curl.h>

void initProject();
void navFolder();
void setFilePath(GObject *source, GAsyncResult *res, gpointer user_data);
void updateFilePath();

void commit();
void clearCommitInfo();

//Global Variables
char filepath[256];


//Globalised stuff for initProject
GtkWidget
*windowInit,
*entryDir;

void initProject() {
    GtkWidget
    *gridParent,
    *buttonNav,
    *buttonProceed;

    //Init of windowInit
    windowInit = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(windowInit),"Navigate to Project");
    gtk_window_present(GTK_WINDOW(windowInit));
    //Init of gridParent
    gridParent = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowInit),gridParent);
    //MArgins & Paddings
    gtk_widget_set_margin_start(gridParent,10);
    gtk_widget_set_margin_end(gridParent,10);
    gtk_widget_set_margin_top(gridParent,10);
    gtk_widget_set_margin_bottom(gridParent,10);
    gtk_widget_set_halign(gridParent,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(gridParent,GTK_ALIGN_CENTER);

    //Init of entryDir
    entryDir = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParent),entryDir,0,1,5,1);
    //Margins& Paddings
    gtk_widget_set_size_request(entryDir,250,-1);

    //Init of buttonNav
    buttonNav = gtk_button_new_with_label("🗀");
    gtk_grid_attach(GTK_GRID(gridParent),buttonNav,5,1,1,1);
    g_signal_connect(buttonNav,"clicked",G_CALLBACK(navFolder),NULL);

    //Init of buttonProceed
    buttonProceed = gtk_button_new_with_label("Proceed");
    gtk_grid_attach(GTK_GRID(gridParent),buttonProceed,0,2,6,1);
    g_signal_connect(buttonProceed,"clicked",G_CALLBACK(updateFilePath),NULL);


}

void navFolder() {
    GtkWindow *windowNav = GTK_WINDOW(NULL);
    GtkFileDialog *dialogNav = gtk_file_dialog_new();

    GFile *home = g_file_new_for_path(g_get_home_dir());
    gtk_file_dialog_set_initial_folder(dialogNav, home);
    g_object_unref(home);
    gtk_file_dialog_select_folder(dialogNav, windowNav, NULL,setFilePath,windowNav);
}

void setFilePath(GObject *source, GAsyncResult *res, gpointer user_data) {
    //Fetches the file path
    GtkFileDialog *dialogNav = GTK_FILE_DIALOG(source);
    GFile *folder = gtk_file_dialog_select_folder_finish(dialogNav, res, NULL);
    char *path = g_file_get_path(folder);
    //Set the entryDir to the desired file path
    gtk_editable_set_text(GTK_EDITABLE(entryDir),path);

}

void updateFilePath() {
    //sets the filepath var to the file path in the entry
    strcpy(filepath,gtk_editable_get_text(GTK_EDITABLE(entryDir)));
    gtk_window_destroy(GTK_WINDOW(windowInit));
}

//Globalised Variables
    GtkWidget
    *entryCommitTitle,
    *textviewCommitMessage,
    *windowMain;

static void activate(GtkApplication *app,gpointer user_data) {
    //Executes the navigater window thingy
    initProject();
    //Widgets for MainProgram
    GtkWidget
    *gridParent,
    *labelCommitMsg,
    *buttonCommit;

    //Init of windowMain
    windowMain = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(windowMain),"NotSoNotFallty");
    gtk_window_set_default_size(GTK_WINDOW(windowMain),270,320);
    gtk_window_present(GTK_WINDOW(windowMain));

    //Init of gridParent
    gridParent = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(windowMain),gridParent);
    //Margins & Paddings
    gtk_widget_set_margin_start(gridParent,10);
    gtk_widget_set_margin_end(gridParent,10);
    gtk_widget_set_margin_top(gridParent,10);
    gtk_widget_set_margin_bottom(gridParent,10);
    gtk_widget_set_halign(gridParent,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(gridParent,GTK_ALIGN_CENTER);

    //Init of entryCommitTitle
    entryCommitTitle = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(gridParent),entryCommitTitle,0,1,10,1);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryCommitTitle),"Enter Commit Title");
    //MArgins & Paddings
    gtk_widget_set_size_request(entryCommitTitle,300,-1);
    gtk_widget_set_margin_bottom(entryCommitTitle,6);

    //Init of labelCommitMsg
    labelCommitMsg = gtk_label_new("Commit Message:");
    gtk_grid_attach(GTK_GRID(gridParent),labelCommitMsg,0,2,10,1);
    //Margins & Padding
    gtk_widget_set_halign(labelCommitMsg,GTK_ALIGN_START);


    //Init of textviewCommitMessage
    textviewCommitMessage = gtk_text_view_new();
    gtk_grid_attach(GTK_GRID(gridParent),textviewCommitMessage,0,3,10,10);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textviewCommitMessage), GTK_WRAP_WORD_CHAR);
    //Margins & Paddings
    gtk_widget_set_size_request(textviewCommitMessage,300,200);
    gtk_widget_set_margin_bottom(textviewCommitMessage,10);


    //Init of buttonCommit
    buttonCommit = gtk_button_new_with_label("Commit");
    gtk_grid_attach(GTK_GRID(gridParent),buttonCommit,0,15,10,1);
    g_signal_connect(buttonCommit,"clicked",G_CALLBACK(commit),NULL);


}

void commit() {
    char command[1024];
    snprintf(command,sizeof(command),"cd %s && git add .",filepath);
    if (system(command)==0) {
        //Fetching text from the textviewCommitMesage
        GtkTextBuffer *bufferCommitMessage = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textviewCommitMessage));
        GtkTextIter start,end;
        gchar *commitMsg;
        gtk_text_buffer_get_start_iter(bufferCommitMessage,&start);
        gtk_text_buffer_get_end_iter(bufferCommitMessage,&end);
        commitMsg = gtk_text_buffer_get_text(bufferCommitMessage,&start,&end,FALSE);
        snprintf(command,sizeof(command),"cd %s && git commit -m \"%s\" -m \"%s\"",
            filepath,
            gtk_editable_get_text(GTK_EDITABLE(entryCommitTitle)),
            commitMsg);
        system(command);
        clearCommitInfo();
    }
    else {
        //Place a window that prompts user to init git if it fails and to try again
    }
}

void clearCommitInfo() {
    gtk_editable_set_text(GTK_EDITABLE(entryCommitTitle),NULL);
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(textviewCommitMessage),NULL);

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
