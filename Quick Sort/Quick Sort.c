#include <stdio.h>
#include <stdlib.h>



void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[] ,int lowIndex ,int highIndex)
{
    int pivot = arr[highIndex];
    int i= (lowIndex - 1) , j;

    for (j = lowIndex ; j <= highIndex - 1 ; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
           swap (&arr[i] , &arr[j] );
        }
    }
     swap(&arr[i + 1] ,&arr[highIndex]);
     return (i + 1);
}

void quickSort (int arr[], int lowIndex,int highIndex)
{
    if (lowIndex < highIndex)
    {
        int pivot = partition (arr , lowIndex , highIndex);
        quickSort(arr, lowIndex , pivot - 1 );
        quickSort(arr, pivot + 1 , highIndex );
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
       printf("%d\t",arr[i]);
}

int main()
{
int arr[6] = {18, 56, 34, 12, 89, 98};
quickSort (arr , 0 , 5);
printf("Sorted array\n\n");
printArray(arr, 6);
return 0;
}
