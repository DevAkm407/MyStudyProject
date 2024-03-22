#include<stdio.h>
#include<stdlib.h>
void turning(int(*ptr)[],const unsigned int size);
int main(void)
{
 int list[5][5]={ {1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20},{21,22,23,24,25} };
for (int i = 0; i < 5; i++)
{
    for (int j = 0; j < 5; j++)
    {
        printf("%2d ",list[i][j]);
    }
    printf("\n");
}

turning(list,5);


printf("\n\n");

for (int i = 0; i < 5; i++)
{
    for (int j = 0; j < 5; j++)
    {
        printf("%2d ",list[i][j]);
    }
    printf("\n");
}

return 0; 

}
void turning(int(*ptr)[],const unsigned int size)
{
int (*list)[size]=ptr;
int clist[size][size];
int a=size-1;
for (int i = 0; i < size; i++)
{
    for (int j = 0; j < size; j++)
    {
        clist[i][j]=list[i][j];
    } 
}
for (int i = 0; i < size; i++)
{
    for (int j = 0; j < size; j++)
    {
        list[i][4-j]=clist[j][a];
    }
   a--; 
}

}