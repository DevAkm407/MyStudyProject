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
    list* address; //다음 리스트에 주소를 저장하는 포인터
    list* origin;  //첫번째를 주소를 위한 포인터
    int a;  //이거 한개때문에 이것저것 만든것이다. 실직적인 데이터
    
    }data; 

struct list
{
int count;         //몇개 할당했는지 알기 위해 카운트를 만듬, 이 카운트로 for문을 이용하며 사용도하고 free도 가능
struct data data; 
};

int main()
{
    list a;     // 실질적인 구조체 선언
    list* w=&a;// 그 구조체 타입에 포인터를 선언해서 사용해보자
    w->data.a=1;//구조체 포인터로 안에있는 데이터 접근후 변경
    listopen(w); //초기화 함수를 만들어서 사용
    while(1){
        char a;
        printf("숫자를 넣을까요? Y OR N  ");
        a=getchar();//  \n이 싫다
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
        w= i==0 ? w->data.origin: w->data.address; //사용하는 과정이 귀찮다,다음주소를 자꾸자꾸 변경해줘 야함
        printf("%d\n",w->data.a); 
    }
    listfree(w);

    return 0;
}
void listopen(list* w) //변수 초기화
{
    w->count=1;
    w->data.address=NULL;
    w->data.origin=w;
}


list* listappend(list* w,int b) //모두가 좋아하는 append
{
    list* a=(list*)malloc(sizeof(list)); //새로운 데이터를 추가하기위해서 새로운 주소를 할당하자
    listopen(a); //새로운 리스트 초기화
    a->data.origin=w->data.origin;//a의 처음주소 w를 넣어줌
    w->data.address=a;//w에 다음주소 a를 넣어줌
    a->count=w->count+1; //시작이 1 그다음 카운트는 2 그다음카운트는 3 그다음 카운트는 4
    a->data.a=b; // 최종목표 새로운 데이터 넣기
   return a;
}   

void listfree(list* w)//할당한 모든 동적메모리를 free시키자
{
    list* c=w->data.origin; //처음 주소는 동적배열이 아니다
    list *a=c->data.address;//여기부턴 동적임
    for (int i = 0; i <= w->count; i++)
    {
        list* b=a->data.address;
        a=b->data.address;
        free(b);
        
    }    
}

