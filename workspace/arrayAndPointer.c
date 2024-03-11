# include<stdio.h>

void main(){
    int array[5]={1,2,3,4,5};
    int *p =&array;
    int *p0=&array[0];
    int *p1=&array[1];
    int *p2=&array[2];
    int *p3=&array[3];
    int *p4=&array[4];
    
    printf("p0의주소 %d\n",p0);
    printf("p1의주소 %d\n",p1);
    printf("p2의주소 %d\n",p2);
    printf("p3의주소 %d\n",p3);
    printf("p4의주소 %d\n",p4);

    /*
    배열의 주소는 연속적이라는 것이 중요하다.
    배열은 선언시 자료형의 크기를 기준으로 주소를 할당한다.
    처음 주소부터 끝날때 까지의 주소를 자료형의 크기로 나눈다는 것이다.
    그래서 포인터로 배열의 주소를 확인하면 int의 경우 4씩 차이는 주소값을 보이며 연속적으로 저장된다.
    */
    for (*p ; p < &array[4]+1; p++)
    {
        printf("array %d \n",*p);
    }
    /*
    포인터로 선언한p를 ++를 이용해서 주소를 증가 시킨다 포인터에서 ++는 p = p + sizeof(p)로 작동하는 것 같다.
    */
    int one=1;
    int *pointer=&one;
    
    printf("pointer의 주소 %d\n",pointer);
    printf("pointer의 주소 %d\n",pointer);   
    printf("*poiner의 사이즈 %zd\n",sizeof(*pointer));
    printf("poiner의 사이즈 %zd\n",sizeof(pointer));
    pointer=(int)pointer+sizeof(*pointer); //pointer가 int*타입이기 때문에 sizeof랑 더해질때 계산 오류를 일으킴 따라서
    //int형으로 형변환을 시켜주고 더해야함
    printf("pointer의 변한주소값:%d\n",pointer);
    printf("one의 사이즈 %zd\n",sizeof(one));

}