/*
#include<stdio.h>
1.
각 라인의 실행이 끝났을 때 quack의 값은 얼마인가?
int quack=2;
quack += 5; 7
quack *=10; 70
quack -=6; 64
quack /=8; 8
qucak %=3; 2

2.value기 int형 값으로 주어질 때, 다음 루프는 무엇을 출력하는가?
    for(value =36; value >0; value /=2)
        printf("%3d",value);
    정답:36,18,9,4,2,1
3. 다음과 같은 검사 조건을 나타내라.
    a.x는 5보다 크다. x>5
    b.scanf()가(x라는) double형 변수에 하나의 수를 읽으려다 실패한다 scanf("%lf",&x) !=1.
    c.x는 값 5를 가진다. x==5

4. 다음과 같은 검사 조건을 나타내라.
a.scanf()가 하나의 정수값을 읽는 데 성공한다. scanf("%d",&a) ==1
b.x는 5가 아니다.x !=5
c.x는 20 또는 그보다 크다. x>=20

5.다음 프로그램은 완벽하지 않다고 생각된다. 에러를 찾을 수 있겠는가?
원본

#include<stdio.h>
int main(){
 int i,k,list(10); 

for (i=1,i<=10,i++){
    list[i]=2*i+3;
    for(j=1,j>=i,j++)
        printf(" %d",list[j]);
    printf("\n");
}
}

수정본
#include<stdio.h>
int main(){
    int i,j,list[10]; []을 사용하자
    for(i=0;i<=9;i++){ 배열인덱스 초과
        list[i]=2*i+3;
        for(j=0; j>=i;j++)
            printf("%d",&list[j]) 주소연산자를 사용해야함
    }braces문 닫아야함
    }
6. 다음과 같은 패턴을 풀력하는 프로그램을 작성하라
4,8
for(int i=0;i<4;i++)
{
    for(int j=0; j<8;j++)
        printf("$");
    printf("\n");
}
10.다음과 같은 선언이 있다고 가정하자.
    double mint[10];
a.이 배열의 이름은 무엇인가? mint
b.이 배열은 몇 개의 원소를 가지고 있는가? 10개
c.각 원소에는 어떤 종류의 값을 저장할 수 있는가? double
d.이 배열과 함께 scanf()를 사용할때 다음 중 정확한 것은 어느것인가?
1.scanf("%lf",mint[2])
2.scanf("%lf",&mint[2])
3.scanf("%lf",&mint)
답 2

11.노아 씨는 2의 배수 단위로 카운트하는 것을 좋아한다. 그래서 배열을 하나 만들고, 그배열을 정수 2, 4, 6, 8
등으로 채우는, 다음과 같은 프로그램을 작성 했다. 그런데 이 프로그램에서 무엇이 잘못되었을까?

#include<stdio.h>
#define SIZE 8
int main(void)
{
    int by_twos[SIZE];
    int index;

    for(index= 1; index<=SIZE; index++) 배열의 인덱스길이를 초과하는 에러가 발생한다.
        by_twos[index] = 2*index;
    for(index = 1; index <=SIZE; index++)
        printf("%d",by_twos);
    printf("\n");
    return 0;
}

14.다음 프로그램은 무엇를 출력하는가?
int main(){ 
    int k;
    for(k=1,printf();,prin) 본문에 for에 printf문이들어가고 ;이 아닌 , 를 사용하고 있다.
}
*/
