#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[100];
    int i,searchKey,found,element;
    for (i=0;i<100;i++)
    {
        a[i]=2*i;
    }
    found =0;
    i=0;
    printf("Enter the value you want to search for: ");
    scanf("%d",&searchKey);
    printf("\n");
    while (!found && i<100)
    {
        if (searchKey==a[i])
        {
            found =1;
            element=i;
        }
        i++;
    }

    if (found)
        printf("The value is found at the number:%d\n",element);
    else printf("Value not found\n");
    return 0;
}
