#include<gtk/gtk.h>

GtkWidget* label;

void undo_redo(GtkWidget* widget,gpointer item)
{
    static gint count=2;
    const gchar* name=gtk_widget_get_name(widget);

    printf("click widget name: %s\r\n",name);   
    if(g_strcmp0(name,"undo"))
    {
        count++;
        
    }
    else
    {
        count--;
    }


    char ch[25];
    memset(ch,0,sizeof(char)*25);
    sprintf(ch,"count: %d",count);
    gtk_label_set_label(GTK_LABEL(label),ch);

    if(count<0)
    {
        gtk_widget_set_sensitive(widget,FALSE);
        gtk_widget_set_sensitive((GtkWidget*)item,TRUE);
    }
    else if(count>5)
    {
         gtk_widget_set_sensitive(widget,FALSE);
         gtk_widget_set_sensitive((GtkWidget*)item,TRUE);
    }
}

int main(int argc,char* argv[])
{
    GtkWidget* window;
    GtkWidget* vbox;

    GtkWidget* toolbar;
    GtkToolItem* undo;
    GtkToolItem* redo;
    GtkToolItem* sep;
    GtkToolItem* exitTb;

    gtk_init(&argc,&argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);
    gtk_window_set_title(GTK_WINDOW(window), "Undo redo");

    vbox=gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window),vbox);

    toolbar=gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar),GTK_TOOLBAR_ICONS);

    gtk_container_set_border_width(GTK_CONTAINER(toolbar),2);

    undo=gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
    gtk_widget_set_name(GTK_WIDGET(undo), "undo");
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar),undo,-1);

    redo=gtk_tool_button_new_from_stock(GTK_STOCK_REDO);
     gtk_widget_set_name(GTK_WIDGET(redo), "redo");
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar),redo,-1);

    sep=gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar),sep,-1);


    exitTb=gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar),exitTb,-1);

    label=gtk_label_new("hi");


    gtk_box_pack_start(GTK_BOX(vbox),toolbar,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);

    g_signal_connect(G_OBJECT(undo), "clicked", 
        G_CALLBACK(undo_redo), redo);

    g_signal_connect(G_OBJECT(redo), "clicked", 
        G_CALLBACK(undo_redo), undo);

    
    g_signal_connect(G_OBJECT(exitTb), "clicked", 
        G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;









}