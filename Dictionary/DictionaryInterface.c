#include<gtk/gtk.h>
#include<bt.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
BTA * tree;
GtkCssProvider *css_provider;
GtkWidget *window;
GtkWidget *entry;
GtkWidget *grid;
GtkWidget *isearch;
GtkWidget *idictionary;
GtkWidget *iadd;
GtkWidget *ichange;
GtkWidget *idelete;
GtkWidget *inext;	
GtkWidget *iprevious;
GtkWidget *isound;
GtkWidget *badd;
GtkWidget *bchange;
GtkWidget *bdelete;
GtkWidget *bnext;
GtkWidget *bprevious;
GtkWidget *bsound;
GdkPixbuf *pixbuf;
GdkPixbuf *pixbuf_search;
GtkWidget *treeview;
GtkTextBuffer *text_buffer;
GtkListStore *store;
GtkTreeIter iter;
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkWidget *scroll_window;
GtkWidget *textview1;
GtkWidget *scroll_window1;
GSList *listkey=NULL;
GtkEntryCompletion *completion;
GtkWidget *entry_mean;
GtkWidget *entry_kind;
GtkWidget *entry_speak;
GtkWidget *entry_word;
int flag=1;
typedef struct{
  char* english;
}string;
string list[3500];
char* trim (char*a){
  int i=0;
  char *s;
  while(a[i]==' '){
    i++;
  }
  s=a+i;
  return s;
}
static void set_flag_unused(void){
  flag=1;
}
static int check_flag_can_can_use(void){
  if(flag==0) return 0;
  else return 1;
}
static void set_flag_is_using(void){
  flag=0;
}
static void add_all_data_to_list_again(void)
{
  char s1[100],s2[256];
  int size;
  gtk_list_store_clear(GTK_LIST_STORE(store));
  btpos(tree, 1);
  while(btseln(tree,s1,s2,256,&size)==0){
    gtk_list_store_append(store,&iter);
    gtk_list_store_set(store,&iter,0,s1,-1);
  }
}
void Search (GtkWidget *widget, gpointer data)
{
  int size;
  char English[100],Vietnamese[256];
  GtkTreeSelection *selection;
  GtkTreeModel	 *model;
  GtkTreeIter 	 iter;
  gchar		 *word;
  model=gtk_tree_view_get_model (GTK_TREE_VIEW(treeview));
  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
  if (gtk_tree_selection_get_selected(selection, &model, &iter)){
    gtk_tree_model_get (model, &iter, 0, &word, -1);
    printf("%s\n",word);
    gtk_entry_set_text(GTK_ENTRY(entry),word);
  }else
  word=gtk_entry_get_text(GTK_ENTRY(widget));
  if(btsel(tree,word,Vietnamese,256,&size)==0){
    gtk_text_buffer_set_text (data,Vietnamese,-1);
  }
  else 
    gtk_text_buffer_set_text (data,"Không tìm thấy từ.",-1);
}
/*BTA *add(BTA* tree1)
{
  char t1[100],t2[256];
  FILE *f1,*f2;
  printf("enter English:");
  gets(t1);
  printf("enter Vietnamese:");
  gets(t2);
  if(btins(tree1,t1,t2,strlen(t2)*sizeof(char*)))
    printf("error.can not inster\n");
  else
    printf("compelete\n");
  return(tree1);
}

BTA * delete(BTA *tree1)
{
  char t1[100];
  printf("enter English:\n");
  gets(t1);
  if( btdel(tree1,t1))
    printf("error.can not inster\n");
  else
    printf("compelete\n");
  return(tree1);
}*/
/*static void setup_tree_view(GtkWidget*treeview){
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	//renderer=gtk_cell_renderer_text_new();
	//column=gtk_tree_view_column_new_with_attributes("Count",renderer,"text",QUANTITY,NULL);
	//gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),column);
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("Danh sach tu",renderer,"text",0,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),column);
}
*/
static void quit_signal(GtkWidget *widget, gpointer data){
    gtk_window_close(GTK_WINDOW(data));
    set_flag_unused();
}
static void search_signal(GtkSearchEntry *entry, gpointer user_data){
	g_print("%s\n",gtk_entry_get_text(GTK_ENTRY(user_data)));
}
/*static gboolean press_enter(GtkTreeView *treeview, GtkEntry *entry){
	gchar *string;
	GtkTreeModel *model;
	GtkTreeIter iter;
	GtkTreeSelection *selection;
	model=gtk_tree_view_get_model (treeview);
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
	if (gtk_tree_selection_get_selected(selection, &model,&iter)){
	   gtk_tree_model_get (model,&iter, 0, word, -1);
	   gtk_entry_set_text(GTK_ENTRY(entry),word);
	   return TRUE;
	}
	return FALSE;
}
static gboolean window_key_press_event_tree_view(GtkWidget *window, GdkEvent *event, GtkTreeView *treeview,GtkEntry){
  if(event->keyval==GDK_ISO_Enter||event->keyval==GDK_KP_Enter)
    return press_enter(treeview,entry);
}*/
static void sound_click(GtkWidget *widget, gpointer data){
  gchar *string=gtk_entry_get_text(GTK_ENTRY(data));
  //printf("%s\n",gtk_entry_get_text(GTK_ENTRY(data)));
  char string1[50]="mpg123 sound/\0",*string2=string;
  strcat(string1,string2);
  strcat(string1,".mp3");
  system(string1);
}
static void button_click(GtkWidget *widget, gpointer data){
	g_print("%s\n",gtk_entry_get_text(GTK_ENTRY(data)));
}
/*static void entry_activated(GtkWidget *entry,gpointer data){
	GtkTreeSelection *selection;
	GtkTreeModel	 *model;
	GtkTreeIter 	 iter;
	gchar		 *word;
	model=gtk_tree_view_get_model (GTK_TREE_VIEW(data));
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(data));
 	if (gtk_tree_selection_get_selected(selection, &model, &iter)){
 	   gtk_tree_model_get (model, &iter, 0, &word, -1);
	   printf("%s\n",word);
 	   gtk_entry_set_text(GTK_ENTRY(entry),word);
	}
}*/
static void user_function (	GtkEntry *entry,
               				GtkEntryIconPosition icon_pos,
               				GdkEvent	*event,
              				gpointer	user_data){
	g_print("%s\n",gtk_entry_get_text(GTK_ENTRY(user_data)));
}
static void row_click(GtkTreeView *treeview,GtkTreePath *path,GtkTreeViewColumn *column,gpointer user_data){	
	gchar *English;
	GtkTreeModel *tree_model;
	GtkTreeIter iter;
	//GtkTreeSelection *selection;
	tree_model=gtk_tree_view_get_model (treeview);
	if(gtk_tree_model_get_iter(tree_model,&iter,path)){
		gtk_tree_model_get(tree_model, &iter, 0, &English, -1);
		gtk_entry_set_text(GTK_ENTRY(user_data),English); 
	}
	int size;
	char Vietnamese[256];	
	if(btsel(tree,English,Vietnamese,256,&size)==0){
	  gtk_text_buffer_set_text (text_buffer,Vietnamese,-1);
	}
	else 
	  gtk_text_buffer_set_text (text_buffer,"Không tìm thấy từ.",-1);
}
static gboolean entry_complete(GtkEntryCompletion *widget,
  GtkTreeModel       *model,
  GtkTreeIter        *iter,
  GtkTreePath        *path,
  gpointer            user_data)
{  
  GtkTreeSelection *selection;
  gboolean bool;
  GValue value = {0, };
  gtk_tree_model_get_value(model, iter, 0, &value);
  gtk_tree_view_set_cursor(GTK_TREE_VIEW(user_data),path,NULL,1);
  /*selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
  if (gtk_tree_selection_get_selected(selection, &model, &iter))
  {
    gchar *name;

    gtk_tree_model_get (model, &iter, COL_NAME, &name, -1);

    g_print ("selected row is: %s\n", name);

    g_free(name);
  }
  else
  {
    g_print ("no row selected.\n");
  }*/
  //fprintf(stdout, "You have selected %s\n", g_value_get_string(&value));
  g_value_unset(&value);
  return FALSE;
} 
static void delete_ok(GtkWidget *widget, gpointer data){
  char *English;
  English=gtk_entry_get_text(GTK_ENTRY(entry_word));
  English=trim(English);
  if( btdel(tree,English))
    gtk_label_set_text(GTK_LABEL(data),"Thông báo:____________________________________\n\n           -Từ này không tồn tại.");
  else{
    add_all_data_to_list_again();
    gtk_label_set_text(GTK_LABEL(data),"Thông báo:____________________________________\n\n           -Xóa từ thành công."); 
  }
}
static void button_delete_click(GtkWidget *widget, gpointer data){
	if(check_flag_can_can_use()!=0){
	  set_flag_is_using();
	}else return;
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *button_ok;
	GtkWidget *button_cancel;
	GtkWidget *label_search;
	GtkWidget *label_check;
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Delete");
	grid=gtk_grid_new();
	button_ok=gtk_button_new_with_label("Ok");
	button_cancel=gtk_button_new_with_label("Cancel");
	label_search=gtk_label_new("Nhập từ cần xóa:_______");
	label_check=gtk_label_new("Thông báo:____________________________________");
	entry_word=gtk_entry_new();
	gtk_entry_set_placeholder_text (GTK_ENTRY(entry_word),"Nhập từ...");
	gtk_grid_attach (GTK_GRID(grid),label_search,0,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),entry_word,1,0,2,1);
	gtk_grid_attach(GTK_GRID(grid),label_check,0,2,3,1);
	gtk_grid_attach (GTK_GRID(grid),button_ok,1,1,1,1);
	gtk_grid_attach(GTK_GRID(grid),button_cancel,2,1,1,1);
	gtk_container_add(GTK_CONTAINER(window),grid);
	gtk_widget_show_all(window);
	gtk_widget_set_size_request(window,200,100);
	g_signal_connect(button_cancel,"clicked",G_CALLBACK(quit_signal),window);
	g_signal_connect(button_ok,"clicked",G_CALLBACK(delete_ok),label_check);
	g_signal_connect (window, "destroy", G_CALLBACK (quit_signal), NULL);
}
static void add_ok(GtkWidget *widget, gpointer data){
	char *English, *Vietnamese,vn[256],*s;
	int size;
	English=gtk_entry_get_text(GTK_ENTRY(entry_word));
	English=trim(English);;
	Vietnamese=gtk_entry_get_text(GTK_ENTRY(entry_mean));
	Vietnamese=trim(Vietnamese);
	if((strcmp(English,"")==0)||(strcmp(Vietnamese,"")==0)){
	  gtk_label_set_text(GTK_LABEL(data),"Thông báo:__________________________________________\n\n           -Bạn chưa nhập đầy đủ dữ liệu.\n           -Dữ liệu nhập vào không được chứa toàn dấu cách.\n           (Chỉ áp dụng cho 2 ô từ và nghĩa của từ).");
	  return;
	}
	if(btsel(tree,English,vn,256,&size)==0){
	  gtk_label_set_text(GTK_LABEL(data),"Thông báo:__________________________________________\n\n           -Từ này đã tồn tại.");
	  return;
	}
	s=trim(gtk_entry_get_text(GTK_ENTRY(entry_speak)));
	strcpy(vn,"");
	strcat(vn,s);
	strcat(vn,"\n");
	s=trim(gtk_entry_get_text(GTK_ENTRY(entry_kind)));
	strcat(vn,s);
	strcat(vn,"\n");
	strcat(vn,Vietnamese);
	Vietnamese=vn;
	if(btins(tree,English,Vietnamese,strlen(Vietnamese)*sizeof(char*)))
	  gtk_label_set_text(GTK_LABEL(data),"Thông báo:__________________________________________\n\n           -Thêm từ không thành công - Tràn bộ nhớ");
	else{
	  add_all_data_to_list_again();
	  gtk_label_set_text(GTK_LABEL(data),"Thông báo:__________________________________________\n\n           -Thêm từ thành công.");
	}
	
}
static void button_add_click(GtkWidget *widget, gpointer data){
	if(check_flag_can_can_use()!=0){
	  set_flag_is_using();
	}else return;
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *button_ok;
	GtkWidget *button_cancel;
	GtkWidget *label_search;
	GtkWidget *label_mean;
	GtkWidget *label_check;
	GtkWidget *label_kind;
	GtkWidget *label_speak;
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Add");
	grid=gtk_grid_new();
	button_ok=gtk_button_new_with_label("Ok");
	button_cancel=gtk_button_new_with_label("Cancel");
	label_search=gtk_label_new("Nhập từ cần thêm:________");
	label_mean=gtk_label_new  ("Nghĩa của từ:_____________");
	label_kind=gtk_label_new  ("Loại từ:__________________");
	label_speak=gtk_label_new ("Cách phát âm:____________");
	label_check=gtk_label_new ("Thông báo:__________________________________________");
	entry_word=gtk_entry_new();
	entry_mean=gtk_entry_new();
	entry_kind=gtk_entry_new();
	entry_speak=gtk_entry_new();
	gtk_entry_set_placeholder_text (GTK_ENTRY(entry_word),"Nhập từ...");
	gtk_entry_set_placeholder_text (GTK_ENTRY(entry_mean),"Nhập nghĩa...");
	gtk_entry_set_placeholder_text (GTK_ENTRY(entry_kind),"Nhập loại từ...");
	gtk_entry_set_placeholder_text (GTK_ENTRY(entry_speak),"Nhập cách phát âm...");
	gtk_grid_attach (GTK_GRID(grid),label_search,0,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),entry_word,1,0,2,1);
	gtk_grid_attach(GTK_GRID(grid),label_mean,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid),entry_mean,1,1,2,1);
	gtk_grid_attach(GTK_GRID(grid),entry_speak,1,2,2,1);
	gtk_grid_attach(GTK_GRID(grid),label_speak,0,2,1,1);
	gtk_grid_attach(GTK_GRID(grid),entry_kind,1,3,2,1);
	gtk_grid_attach(GTK_GRID(grid),label_kind,0,3,1,1);
	gtk_grid_attach (GTK_GRID(grid),button_ok,1,4,1,1);
	gtk_grid_attach(GTK_GRID(grid),button_cancel,2,4,1,1);
	gtk_grid_attach(GTK_GRID(grid),label_check,0,5,3,1);
	gtk_container_add(GTK_CONTAINER(window),grid);
	gtk_widget_show_all(window);
	gtk_widget_set_size_request(window,400,220);
	gtk_widget_set_margin_top(entry_mean,10);
	gtk_widget_set_margin_top(label_mean,10);
	gtk_widget_set_margin_top(entry_kind,10);
	gtk_widget_set_margin_top(label_kind,10);
	gtk_widget_set_margin_top(entry_speak,10);
	gtk_widget_set_margin_top(label_speak,10);
 	gtk_widget_set_margin_left(label_check,20);
	g_signal_connect(button_cancel,"clicked",G_CALLBACK(quit_signal),window);
	g_signal_connect(button_ok,"clicked",G_CALLBACK(add_ok),label_check);
	g_signal_connect (window, "destroy", G_CALLBACK (quit_signal), NULL);
}
static void change_ok (GtkWidget *widget, gpointer data){
	char *English, *Vietnamese,vn[256],*s;
	int size;
	English=gtk_entry_get_text(GTK_ENTRY(entry_word));
	English=trim(English);;
	Vietnamese=gtk_entry_get_text(GTK_ENTRY(entry_mean));
	Vietnamese=trim(Vietnamese);
	if((strcmp(English,"")==0)||(strcmp(Vietnamese,"")==0)){
	  gtk_label_set_text(GTK_LABEL(data),"Thông báo:__________________________________________\n\n           -Bạn chưa nhập đầy đủ dữ liệu.\n           -Dữ liệu nhập vào không được chứa toàn dấu cách.\n           (Chỉ áp dụng cho 2 ô từ và nghĩa của từ).");
	  return;
	}
	if(btsel(tree,English,vn,256,&size)==0){
	  if( btdel(tree,English))
	     printf("error.can not delete\n");
	  else
	    printf("compelete\n");
	  s=trim(gtk_entry_get_text(GTK_ENTRY(entry_speak)));
	  strcpy(vn,"");
	  strcat(vn,s);
	  strcat(vn,"\n");
	  s=trim(gtk_entry_get_text(GTK_ENTRY(entry_kind)));
	  strcat(vn,s);
	  strcat(vn,"\n");
	  strcat(vn,Vietnamese);
	  Vietnamese=vn;
	  if(btins(tree,English,Vietnamese,strlen(Vietnamese)*sizeof(char*)))
	    gtk_label_set_text(GTK_LABEL(data),"Thông báo:__________________________________________\n\n           -Sửa từ không thành công - Tràn bộ nhớ");
	  else{
	    add_all_data_to_list_again();
	    gtk_label_set_text(GTK_LABEL(data),"Thông báo:__________________________________________\n\n           -Sửa từ thành công.");
	  }
	}
	else{
	  gtk_label_set_text(GTK_LABEL(data),"Thông báo:__________________________________________\n\n           -Từ này không tồn tại.");
	  return;
	}
}
static void button_change_click(GtkWidget *widget, gpointer data){
	if(check_flag_can_can_use()!=0){
	  set_flag_is_using();
	}else return;
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *button_ok;
	GtkWidget *button_cancel;
	GtkWidget *label_search;
	GtkWidget *label_mean;
	GtkWidget *label_check;
	GtkWidget *label_kind;
	GtkWidget *label_speak;
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Change");
	grid=gtk_grid_new();
	button_ok=gtk_button_new_with_label("Ok");
	button_cancel=gtk_button_new_with_label("Cancel");
	label_search=gtk_label_new("Nhập từ cần sửa :_________");
	label_mean=gtk_label_new  ("Nghĩa của từ:_____________");
	label_kind=gtk_label_new  ("Loại từ:__________________");
	label_speak=gtk_label_new ("Cách phát âm:____________");
	label_check=gtk_label_new ("Thông báo:__________________________________________");
	entry_word=gtk_entry_new();
	entry_mean=gtk_entry_new();
	entry_kind=gtk_entry_new();
	entry_speak=gtk_entry_new();
	gtk_entry_set_placeholder_text (GTK_ENTRY(entry_word),"Nhập từ...");
	gtk_entry_set_placeholder_text (GTK_ENTRY(entry_mean),"Nhập nghĩa...");
	gtk_entry_set_placeholder_text (GTK_ENTRY(entry_kind),"Nhập loại từ...");
	gtk_entry_set_placeholder_text (GTK_ENTRY(entry_speak),"Nhập cách phát âm...");
	gtk_grid_attach (GTK_GRID(grid),label_search,0,0,1,1);
	gtk_grid_attach(GTK_GRID(grid),entry_word,1,0,2,1);
	gtk_grid_attach(GTK_GRID(grid),label_mean,0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid),entry_mean,1,1,2,1);
	gtk_grid_attach(GTK_GRID(grid),entry_speak,1,2,2,1);
	gtk_grid_attach(GTK_GRID(grid),label_speak,0,2,1,1);
	gtk_grid_attach(GTK_GRID(grid),entry_kind,1,3,2,1);
	gtk_grid_attach(GTK_GRID(grid),label_kind,0,3,1,1);
	gtk_grid_attach (GTK_GRID(grid),button_ok,1,4,1,1);
	gtk_grid_attach(GTK_GRID(grid),button_cancel,2,4,1,1);
	gtk_grid_attach(GTK_GRID(grid),label_check,0,5,3,1);
	gtk_container_add(GTK_CONTAINER(window),grid);
	gtk_widget_show_all(window);
	gtk_widget_set_size_request(window,400,220);
	gtk_widget_set_margin_top(entry_mean,10);
	gtk_widget_set_margin_top(label_mean,10);
	gtk_widget_set_margin_top(entry_kind,10);
	gtk_widget_set_margin_top(label_kind,10);
	gtk_widget_set_margin_top(entry_speak,10);
	gtk_widget_set_margin_top(label_speak,10);
 	gtk_widget_set_margin_left(label_check,20);
	g_signal_connect(button_cancel,"clicked",G_CALLBACK(quit_signal),window);
	g_signal_connect(button_ok,"clicked",G_CALLBACK(change_ok),label_check);
	g_signal_connect (window, "destroy", G_CALLBACK (quit_signal), NULL);
}
int main (int argc, char*argv[]){
	char s1[100],s2[256];
	char c;
	char English[100];
	int k=0,size;
	FILE *f = fopen("file1.txt","rt");
	while(fscanf(f,"    %s\n",English)>0){
	  list[k].english=(char*)malloc(strlen(English)*sizeof(char));
	  strcpy(list[k].english,English);	
	  k++;
	}
	fclose(f);
	gtk_init(&argc,&argv);
	tree = btopn("mytree1",0,0);
	
	//lay anh tu file goc ra de ti nua add vao
	//isearch=gtk_image_new_from_file("icon/search.png");
	iadd=gtk_image_new_from_file("icon/add.png");
	idelete=gtk_image_new_from_file("icon/delete.png");
	ichange=gtk_image_new_from_file("icon/change.png");
	idictionary=gtk_image_new_from_file("icon/dictionary.png");
	inext=gtk_image_new_from_file("icon/next.png");
	iprevious=gtk_image_new_from_file("icon/previous.png");
	isound=gtk_image_new_from_file("icon/sound.png");
	//pixbuf_search=gtk_image_get_pixbuf(GTK_IMAGE(isearch));
	//thiet lap cua so
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	pixbuf = gtk_image_get_pixbuf(GTK_IMAGE(idictionary));
	gtk_window_set_icon (GTK_WINDOW(window),pixbuf);
	gtk_window_set_title(GTK_WINDOW(window),"Dictionary");
	g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),5);
	gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
	//tao 1 grid	
	grid=gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window),grid);
	//tao entry
	//entry=gtk_entry_new();
	entry=gtk_search_entry_new();
	gtk_entry_set_placeholder_text (GTK_ENTRY(entry),"Tìm kiếm");
	//gtk_entry_set_icon_from_icon_name(GTK_ENTRY(entry),GTK_ENTRY_ICON_PRIMARY,"system-search");
	//gtk_entry_set_icon_from_pixbuf(GTK_ENTRY(entry),GTK_ENTRY_ICON_PRIMARY,pixbuf_search);
	//gtk_entry_set_icon_activatable(GTK_ENTRY(entry),GTK_ENTRY_ICON_PRIMARY,TRUE);
	//tao 6 button
	badd=gtk_button_new_with_label("Add");
	bdelete=gtk_button_new_with_label("Delete");
	bchange=gtk_button_new_with_label("Change");
	bnext=gtk_button_new();
	bprevious=gtk_button_new();
	bsound=gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(badd),iadd);
	gtk_button_set_image(GTK_BUTTON(bdelete),idelete);
	gtk_button_set_image(GTK_BUTTON(bchange),ichange);
	gtk_button_set_image(GTK_BUTTON(bnext),inext);
	gtk_button_set_image(GTK_BUTTON(bprevious),iprevious);
	gtk_button_set_image(GTK_BUTTON(bsound),isound);
	//tao list tu va nghia
	//create tree view
	scroll_window=gtk_scrolled_window_new(NULL, NULL);
	treeview=gtk_tree_view_new();
	store=gtk_list_store_new(1,G_TYPE_STRING);
	gtk_container_add(GTK_CONTAINER(scroll_window), treeview);
	renderer=gtk_cell_renderer_text_new();
	column=gtk_tree_view_column_new_with_attributes("Danh sách từ",renderer,"text",0,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),column);
	/*int i=0;
	while(list[i].english!=NULL){
		gtk_list_store_append(store,&iter);
		gtk_list_store_set(store,&iter,0,list[i].english,-1);
		i++;
	}*/
	btpos(tree, 1);
	while(btseln(tree,s1,s2,256,&size)==0){
	    gtk_list_store_append(store,&iter);
	    gtk_list_store_set(store,&iter,0,s1,-1);
	}
	//gtk_list_store_clear(store); //lenh nay de clear danh sach va phai clear danh sach trc ms ghi de` cai khac vao dc 
	/*i=0;
	while(i<15){
		gtk_list_store_append(store,&iter);
		gtk_list_store_set(store,&iter,0,"kien heehee",-1);
		i++;
	}*/
	gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(store));
	g_object_unref(store);
	gtk_tree_view_set_activate_on_single_click(GTK_TREE_VIEW(treeview),1);
	gtk_tree_view_set_search_entry (GTK_TREE_VIEW(treeview),GTK_ENTRY(entry));
	//end of create tree view
	// set up completion
	/*completion=gtk_entry_completion_new();
	gtk_entry_completion_set_text_column(completion,0);
	gtk_entry_set_completion(GTK_ENTRY(entry),completion);
	gtk_entry_completion_set_model(completion,GTK_TREE_MODEL(store));*/
	//end of completion
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW(scroll_window),GTK_SHADOW_OUT);
	scroll_window1=gtk_scrolled_window_new(NULL, NULL);
	textview1=gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(scroll_window1), textview1);
	text_buffer=gtk_text_buffer_new(NULL);
	gtk_text_buffer_set_text (text_buffer,"Kien test :v hahahaha\nKien is testing this dictionary :)) ",-1);
	//gtk_text_buffer_set_text (text_buffer,"kien hehe",-1); //khi set lan 2 no se xoa lan 1 va ghi lan 2 vao
	gtk_text_view_set_buffer(GTK_TEXT_VIEW(textview1),text_buffer);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW(scroll_window1),GTK_SHADOW_OUT);
	//add cac thu vao grid 0 0 1 1 la toa do chen vao
	gtk_grid_attach (GTK_GRID(grid),entry,0,0,1,1);
	gtk_grid_attach (GTK_GRID(grid),bprevious,1,0,1,1);
	gtk_grid_attach (GTK_GRID(grid),bnext,2,0,1,1);
	gtk_grid_attach (GTK_GRID(grid),bsound,3,0,1,1);
	gtk_grid_attach (GTK_GRID(grid),badd,4,0,1,1);
	gtk_grid_attach (GTK_GRID(grid),bdelete,5,0,1,1);
	gtk_grid_attach (GTK_GRID(grid),bchange,6,0,1,1);
	gtk_grid_attach (GTK_GRID(grid),scroll_window,0,1,1,1);
	gtk_grid_attach (GTK_GRID(grid),scroll_window1,1,1,6,1);
	gtk_widget_set_size_request(scroll_window,100,300);
	gtk_widget_set_size_request(scroll_window,0,300);
	//chinh margin
	gtk_widget_set_margin_left(badd,10);
	gtk_widget_set_margin_left(bdelete,10);
	gtk_widget_set_margin_left(bchange,10);
	gtk_widget_set_margin_left(bnext,10);
	gtk_widget_set_margin_left(bprevious,10);
	gtk_widget_set_margin_left(bsound,10);
	gtk_widget_set_margin_top(scroll_window,5);
	gtk_widget_set_margin_top(scroll_window1,5);
	gtk_widget_set_margin_left(scroll_window1,10);
	gtk_widget_set_margin_bottom(scroll_window1,5);
	gtk_widget_set_margin_bottom(scroll_window,5);
	gtk_widget_show_all(window);
	//signal
	//g_signal_connect (window, "key-press-event",G_CALLBACK (window_key_press_event_tree_view), treeview);
	g_signal_connect(badd,"clicked",G_CALLBACK(button_add_click),entry);
	g_signal_connect(bchange,"clicked",G_CALLBACK(button_change_click),NULL);
	g_signal_connect(entry,"activate",G_CALLBACK(Search),text_buffer);
	//g_signal_connect(entry,"icon-press",G_CALLBACK(entry_activated),treeview);
	//g_signal_connect(entry,"icon-press",G_CALLBACK(user_function),entry);
	g_signal_connect(bsound,"clicked",G_CALLBACK(sound_click),entry);
	g_signal_connect(GTK_SEARCH_ENTRY(entry),"search-changed",G_CALLBACK(search_signal),entry);
	g_signal_connect(treeview,"row-activated",G_CALLBACK(row_click),entry);
	g_signal_connect(bdelete,"clicked",G_CALLBACK(button_delete_click),NULL);
	//g_signal_connect(G_OBJECT(completion),"match-selected",G_CALLBACK(entry_complete),treeview);//lenh nay de complete va goi y
	//css
	// doan nay k load tu file css
	GtkCssProvider *provider; 
  	GdkDisplay *display;
  	GdkScreen *screen;
	provider = gtk_css_provider_new ();
  	display = gdk_display_get_default ();
  	screen = gdk_display_get_default_screen (display);

  	gtk_style_context_add_provider_for_screen (screen,
                                 GTK_STYLE_PROVIDER (provider),
                                 GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	gtk_css_provider_load_from_data (GTK_CSS_PROVIDER (provider),
                                               " GtkWindow {\n"                          
                                               "   background-color: tan;\n"
                                               "}\n", -1, NULL);
  	g_object_unref (provider);

	//doan nay load tu file css
	/*provider = gtk_css_provider_new ();
  	display = gdk_display_get_default ();
 	screen = gdk_display_get_default_screen (display);
 	gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  	gsize bytes_written, bytes_read;
  	const gchar* home = "test.css";  // your path, for instance: /home/zerohour/Documents/programming/cssexternal.css
	GError *error = 0;
   	gtk_css_provider_load_from_path (provider,g_filename_to_utf8(home, strlen(home), &bytes_read, &bytes_written, &error),NULL);
  	g_object_unref (provider);*/
	gtk_main();
}
