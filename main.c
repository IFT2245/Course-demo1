#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

struct wack{
    long long undeux;
    int trois;
    int quatre;
};

void malloc_is_tableau() {
    size_t l = sizeof(void *);
    size_t size_int = sizeof(int);
    size_t size_long = sizeof(long long);
    size_t size_wack = sizeof(struct wack);

    struct wack *ptr = malloc(sizeof(struct wack));

    ptr->undeux = 12;
    ptr->trois = 3;
    ptr->quatre = 4;

    int un = ((int *) ptr)[0];
    int deux = ((int*) ptr)[1];
    int trois = ((int*)ptr)[2];
    int quatre = ((int*)ptr)[3];

    int *oh_no = malloc(sizeof(struct wack));
    oh_no[0] = un;
    oh_no[1] = deux;
    oh_no[2] = trois;
    oh_no[3] = quatre;

    struct wack *oh_no_no_no = (struct wack*) oh_no;

    long long einzwei = oh_no_no_no->undeux;
    long long drei = oh_no_no_no->trois;
    int vier = oh_no_no_no->quatre;

    return;
}

struct l_node {
    int nb;
    struct l_node* next;
};

#define l_node struct l_node*

/*l_node link(l_node current, l_node next) {
    current->next = next;
    return next;
}*/

l_node new_node(int val) {
    l_node node = malloc(sizeof(l_node));
    node->nb = val;
    node->next = NULL; //bonne pratique!
    return node;
}

l_node free_node(l_node node) {
    l_node next = node->next;
    printf("%d\n", node->nb);
    free(node);
    return next;
}

void free_l_list(l_node head) {
    //Tres laid! ne faites pas ça! Mais, free n'est pas si compliqué: en une seule for-loop, sans corps, on peut libérer
    //toute une liste chaînée!
    for(; head != NULL; head = free_node(head));
}

void malloc_is_new() {
    l_node head = new_node(0);
    l_node current = head;

    //for loop sur une seule ligne
    for(int i=1; i<1000; i++) current = link(current, new_node(i)); //current = current.link(new Node(i));

    free_l_list(head);
}

void illegal_access() {
    int* x = malloc(sizeof(int)*10);
    for(int i=0; i<10; i++) x[i] = i;

    x[10] = 10;

    //???
    int y = x[10];
    free(x);
}

void ptr_of_ptr() {
    char **string_array = malloc(sizeof(char*) * 10);

    char buf[11];
    int i = 0;
    for(; i<10; i++) {
        buf[i] = 'o';
        buf[i+1] = NULL;

        char *string = malloc(sizeof(char) * (i+ 1 + 3 +1) );
        string[0] = 'a'; string[1] = 'l'; string[2] = 'l';
        string[3] = NULL;

        string_array[i] = strcat(string, buf);
        printf("%s\n", string); //strcat modifie string...
    }

    for(i--; i!=-1; i--) printf("%s\n", string_array[i]);

    //comment free ça?
    for(i=0; i<10; i++) free(string_array[i]);
    free(string_array);
}

int main() {
    //malloc_is_tableau();
    //malloc_is_new();
    //illegal_access();

    char *x[] = {"echo", "https://www.google.com/", NULL};
    execvp("echo", x);

    ptr_of_ptr();

    char *bla = malloc(sizeof(char) * 10);
    for(int i=0; i<9; i++) bla[i] = 'a';
    bla[9] = NULL;

    char *bla2 = realloc(bla, sizeof(char) * 20);


    return 0;
}