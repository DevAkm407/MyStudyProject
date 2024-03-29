#include<stdio.h>
#include<stdlib.h>
//최소 키
typedef struct tree tree;
tree* treeopen(tree*data,char* st);
tree* treeplus(tree* data,char* st);
tree* maxtree(tree* data,int max);

struct addr{
tree* root;
tree* adress1;
tree* adress2;
};

struct tree{
char* str;
int count;
struct addr addr;
};

int main(void)
{
    return 0;
}
tree* treeopen(tree* data , char* st)
{
data->count=0;
data->str=st;
data->addr.adress1=NULL;
data->addr.adress2=NULL;
return data;
}
tree* treeplus(tree* data,char* st)
{
tree* a=(tree*)malloc(sizeof(tree));
a->count=data->count+1; //해당 노드가 몇번째로 만들어 졌는지 카운트할 필요가 있음
a->str=st; //문자열 넣기(데이터 넣기)
if(data->addr.adress1 ==NULL || data->addr.adress2 ==NULL){
data->addr.adress1=data->addr.adress1 ==NULL ? a : data->addr.adress1; //1번 저장소가 비면 넣기
data->addr.adress2= data->addr.adress1 ==NULL ? a : data->addr.adress2; //1번 저장소가 사용중이면 넣기
a->addr.root=data; //이전 노드 찾아가야지...
return a;//새로만든 노드 주기     
}
else
{

free(a);//다 쓴노드 였네? 일단 새로할당한 힙메모리 삭제

printf("해당 노드에는 더이상 주소를 추가할 수 없습니다.");

return data;//안돼 돌아가

}

}

tree* maxtree(tree* data,int zero)
{
    if(data->count>zero)
        zero=data->count;
    if(data->addr.adress1!=NULL){
        if(data->addr.adress1->count > zero)
            data=maxtree(data,zero);
    }
return data;
}