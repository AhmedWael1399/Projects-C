#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[15];
    int searchKey,found,low,high,middle,result,i;
    for (i=0;i<15;i++)
    {
        a[i]=2*i;
    }
    printf("Enter the value you want to search for: ");
    scanf("%d",&searchKey);
    printf("\n\n");
    low=0;
    high=15-1;
    found=0;
    while(!found && low<=high)
    {
        middle = (low+high)/2;
        if (searchKey==a[middle])
        {
            found = 1;
            result=middle;
        }

        else if (searchKey < a[middle])
            high = middle-1;

        else if (searchKey > a[middle])
            low = middle+1;
    }
    if (found)
    printf("The value is found at number: %d\n",result);
    else printf("Value not found");
    return 0;
}
