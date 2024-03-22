#include<stdio.h>
#include<stdlib.h>
#include<time.h>


/*
전체 적인 로직 설명
랜덤으로 숫자를 뽑는다. 그런 다음 숫자를
*/

int bingoCreating(int(*bingo)[],const unsigned int size);
int imBingo(int(*bingo)[],const unsigned int size);
int main(void)
{
   
 int bingo[10][10];
 int success=bingoCreating(bingo,10);
 if(success==-1)
    printf("빙고판 사이즈에러"); 
 
while (1)
{
 int a;
 if(a=imBingo(bingo,10)==0)
    break;
else
continue;
}
        

        
    
  return 0;  

}

int bingoCreating(int (*bingo)[],const unsigned int size)
{
    if(size<=0){
        printf("배열의 사이즈가 0보다작거나 같습니다.");
        return -1;
    } 

    srand(time(NULL));
    int overlap=0;
    int (*pf)[size]=bingo; //2차원배열의 값을 검색하기위해서 사용하기위한 포인터

    
    for (int i = 0; i < size; i++) //빙고판 0으로 초기화
    {
        for (int j = 0; j < size; j++)
        {
            pf[i][j]=0;          
        }
        
    }
    
    int k,g=0;  
    while ((pf[size-1][size-1]==0)) //마지막 5행5열 부분까지 숫자가 변환되면 종료
    {
        overlap=0;
        int randint = (rand()%(size*size)) +1; //1~25 까지 뽑기
            
            for (int i = 0; i < size; i++) //숫자를 뽑아서 중복인지 아닌지 확인 overlap이 한번이라도 1이되면 중복
            {
                for ( int j = 0; j < size; j++)
                {
                    if(randint == pf[i][j])
                        overlap++;                       
                }
            }
                      
            if(overlap==0) //중복이 없다 그러니까 숫자를 넣어주자
            {
                k= g==size? k+1:k; //열이 다차면 행을 바꿔주자
                g= g==size? 0:g;   //행 끝번호까지 다썻으면 0으로 초기화
                pf[k][g]=randint; //숫자넣기
                g++; //다음 행번호에 숫자넣기
            }
    }   


return 1;

}


int imBingo(int(*bingo)[],const unsigned int size)
{
int a;
int(*handsup)[size]=bingo;
  for (int i = 0; i < size; i++) //빙고출력
        {
            for (int j = 0; j < size; j++)
            {
                printf("| %d | ",handsup[i][j]);
            }
            printf("\n");
        }
printf("숫자를 입력해주세요: ");
        scanf("%d",&a);
        getchar();
        if(a==0)
        {
            printf("%d은 입력할 수 없습니다.",0);
            return -1;
        }
        if(a>size*size)
        {
            printf("%d이상은 입력할 수 없습니다.",size*size);
            return -1;
        }

for (int i = 0; i < size; i++) 
            {
                for ( int j = 0; j < size; j++)
                {
                    if( handsup[i][j] == a)
                        handsup[i][j]=0;                       
                }
            }

        
        
        int sum=0;   
        
        
        for (int i = 0; i < size; i++) //가로빙고 검출 
        {
            for (int j = 0; j < size; j++)
            {
               sum+=handsup[i][j];
            }
           if(sum==0)
           {
            printf("축하합니다!! 빙고");
            return 0; 

           }
        
        }
        sum =0;
        
        for (int i = 0; i < size; i++) //세로빙고 검출
        {
            for (int j = 0; j < size; j++)
            {
               sum+=handsup[j][i];
            }
           if(sum==0)
           {
            printf("축하합니다!! 빙고");
            return 0;
           }
        }
        sum=0;
        for (int i = 0; i < size; i++) //  '\'빙고 검출
        {
           sum+=handsup[i][i];
           
        }
        if(sum==0){
            printf("축하합니다!! 빙고");
            return 0;
        }
        sum=0;
        for (int i = 0; i < size; i++) //  '/'빙고 검출
        {
           sum+=handsup[i][4-i];
           
        }
        if(sum==0){
            printf("축하합니다!! 빙고");
            return 0;
        }
    }