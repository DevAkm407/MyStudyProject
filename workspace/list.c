#include<stdio.h>
#include<stdlib.h>
typedef struct list list;
void listopen(list w );
list listappend(list w,int b);
void listfree(list w);
struct data
{
    list* address;
    list* origin;
    int a;
    float b;
    double c;    
}data;
struct list
{
int count;
struct data data;

};


int main()
{
    list test;
    listopen(test);
    test.data.a=5;
    test=listappend(test,10);
 
    return 0;
}

void listopen(list w)
{
    list* a=&w;  
    a->count=0;
    a->data.address=a;
    a->data.origin=a;
}
list listappend(list w,int b)
{
    list* a=&w;
    a->count++;
    list* c=a->data.address;
    a=(list*)malloc(sizeof(list));
    c->data.address=a;
    a->data.origin=c->data.origin;
    a->data.a=b;
return *(w.data.origin);
}

void listfree(list w)
{
    list* a=&w;
    for(int i=0;i< a->count;i++)
    {
        if(a->data.address !=NULL){
        list* b=a->data.address;
        free(a);
        a=b;
        }
    }

}
