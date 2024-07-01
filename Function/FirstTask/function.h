static struct list{
 char name[20];
 char second_name[20];
 char tel[20];
};

void* add_ab(struct list*, int*, int*);
void* delete_ab(struct list*, int*, int*);
void* search_ab(struct list*);
void* show_all(struct list*, int*);
