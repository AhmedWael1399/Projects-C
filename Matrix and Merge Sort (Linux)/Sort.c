#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>

int* dataMatrix;
int* sortedArray;
int elementsNumber;

struct index
{
int p,r;
};


/* Function for Merging the two sub Arrays */
void*   merge_sort(void* args){
	struct index* pr = (struct index*) args;
	int p = pr->p,  r = pr->r , ret1,ret2;
	/* If there is one Element*/
	if (p==r)
     	 pthread_exit(0);

	/* Creating two Threads for the two sub arrays */
	pthread_t thread1,thread2;
	struct index pr1,pr2;
	int q = (p+r)/2;
	pr1.p = p;    pr1.r = q;
	pr2.p = q+1;  pr2.r = r;

	/* Creating a Thread for each sub part of the array */
	ret1 = pthread_create(&thread1,NULL,merge_sort,(void*) &pr1);
	if (ret1>0)
		printf("failed to create new thread 1\n");

	ret2 = pthread_create(&thread2,NULL,merge_sort,(void*) &pr2);
	if (ret2>0)
		printf("failed to create new thread 2\n");

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	int k = p ,i = p ,j = q+1;

	while (i<=q && j<=r){
		if (dataMatrix[i] < dataMatrix[j])
			sortedArray[k++] = dataMatrix[i++];
		else
			sortedArray[k++] = dataMatrix[j++];
	}
	for (; i<=q ; i++)
		sortedArray[k++] = dataMatrix[i];
	for (; j<=r ; j++)
		sortedArray[k++] = dataMatrix[j];

	for (i= p ; i <= r ;i++)
		dataMatrix[i] = sortedArray[i];

	pthread_exit(0);
	return NULL;
}

int main(){

   int i = 0;
   char filename [50];
   struct index start;

/* Accessing the Input File Merge */
    printf("Enter the Name of the file:");
    scanf("%s",filename);
    FILE *f;
    f = fopen (filename, "r");
    
    if (f == NULL)
        return 0;

    /* Reading the number of elements */
    
    fscanf(f,"%d",&elementsNumber);
    
    /* Reading the data matrix */
    
    dataMatrix = (int*) malloc(sizeof(int)*elementsNumber);
    for(i = 0; i < elementsNumber; i++)
    fscanf(f, "%d", &dataMatrix[i]);
    
    	/* Allocationg Memory for the Sorted Array */
        sortedArray = (int*)malloc(sizeof(int)*elementsNumber);
        start.p = 0;    start.r = elementsNumber-1;
        
        /* Creating Thread for the Merge Operation*/
	pthread_t start_thread;
	pthread_create(&start_thread,NULL,merge_sort,&start);
	pthread_join(start_thread,NULL);

    
    /* Accessing Output Sorted Array file*/
    FILE *fout;
    fout = fopen ("output-merge.txt","w");
    
     /* displaying sorted array */
    fprintf(fout,"Sorted Array: ");
    for (int i = 0; i < elementsNumber; i++)
      fprintf(fout,"%d ",sortedArray[i]);
    
fclose(fout);    
fclose(f);   
return 0;
}
