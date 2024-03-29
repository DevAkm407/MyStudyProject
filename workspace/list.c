#include<stdio.h>
#include<stdlib.h>
typedef struct list list;
void listopen(list* w );
list* listappend(list* w,int b);
list* listsort(list* w);
void listfree(list* w);

struct data
{
    list* address;
    list* origin;
    int a;
    
    }data;

struct list
{
int count;
struct data data;
};

int main()
{
    list a;
    list* w=&a;
    w->data.a=1;
    listopen(w);
    while(1){
        char a;
        printf("숫자를 넣을까요? Y OR N  ");
        a=getchar();
        if(a=='Y'||a=='y')
        {
            int i;
            printf("어떤숫자를 넣을까요?");
            scanf("%d",&i);
            w=listappend(w,i);
        }
        else if(a=='N'||a=='n')
            break;
        while(getchar()!='\n')
            continue;        
    }
    printf("카운트:%d\n",w->count);
    for (int i = 0; i <= w->count; i++)
    {
        w= i==0 ? w->data.origin: w->data.address;
        printf("%d\n",w->data.a); 
    }
    listfree(w);

    return 0;
}

void listopen(list* w)
{
    w->count=1;
    w->data.address=NULL;
    w->data.origin=w;
}


list* listappend(list* w,int b)
{
    list* a=(list*)malloc(sizeof(list));
    listopen(a);
    a->data.origin=w->data.origin;
    w->data.address=a;
    a->count=w->count+1; //시작이 1 그다음 카운트는 2 그다음카운트는 3 그다음 카운트는 4
    a->data.a=b;
   return a;
}   

void listfree(list* w)
{
    list* c=w->data.origin;
    list *a=c->data.address;
    for (int i = 0; i <= w->count; i++)
    {
        list* b=a->data.address;
        a=b->data.address;
        free(b);
    }    
}
