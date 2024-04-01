#include<stdio.h>
#include<stdlib.h>
typedef struct list list;
void listopen(list* w );
int* memoryalloc(int* a);
list* listappend(list* w,int b);
list* listsort(list* w);
void listfree(list* w);

// 크게 할당함 그리고 할당한 주소의 맨끝에 \0 이런거넣어둠 그다음에 포인터가 주소를읽으면 사용
// \0 주소의 끝이라고 알려주게함 그다음에 더큰 주소가 필요함 그러면 더크게 할당 malloc(이전꺼 보다 크게)
// 이전데이터를 옮겨 줘야함 근본적인 방법 for문으로 바꿔주기 간편한방법 stdlib에 있는 메모리 copy함수 사용
//이전데이터 주소는 더이상 필요없음 free(이전 주소)
// 그냥 realloc 쓰기 다만 운없으면 실패
// 구조체를 변수를 메인에 선언하는 이유 함수는 자기할일 끝나면 없어짐 그래서 함수가 자기일끝나면 메모리 해재함 동적제외
//static을 함수에 넣으면 똑같이 메인이 끝날때 없어짐
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
typedef struct itme
{
   int a;
}itme;


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

