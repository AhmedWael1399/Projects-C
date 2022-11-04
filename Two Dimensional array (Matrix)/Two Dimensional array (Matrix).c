#include <stdio.h>
#include <stdlib.h>

int main()
{
   int a[2][3]= {{1,2,3},{4,5,6}};
   int b[2][3]= {{7,8,9},{10,11,12}};
   int c[2][3];
   for (int i=0;i<=1;i++)
   {
       for (int j=0;j<=2;j++)
       {
           c[i][j]= 3 * a[i][j] + 5 * b[i][j];
       }
   }
   printf("Values of the array c = 3 * a + 5 * b \n");
   for(int i=0;i<=1;i++)
   {
       for(int j=0;j<=2;j++)
       {
           printf("%4d",c[i][j]);
       }
       printf("\n");
   }

    return 0;
}
