#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[10]= { 2, 6, 4, 8, 10, 12, 89, 68, 45, 37 };
    int sorted=0,i,hold,pass;
    printf("Data in the original order\n\n");
    for (i=0;i<10;i++)
    {
        printf("%4d",a[i]);
    }
    for (pass=1;pass<10 && !sorted;pass++)
    {
        sorted = 1;
        for (i=0;i<10;i++)
        {
            if (a[i]>a[i+1])
            {
                hold=a[i];
                a[i]=a[i+1];
                a[i+1]=hold;
                sorted = 0;
            }
        }
    }
    printf("\n\nData in the ascending order\n\n");
    for(i=0;i<10;i++)
    {
        printf("%4d",a[i]);
    }
    return 0;
}
