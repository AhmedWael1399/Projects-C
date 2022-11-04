#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include<unistd.h>
#include<time.h>


    int rowMatrix1;
    int columnMatrix1;
    int rowMatrix2;
    int columnMatrix2;
    int row = 0;	
    int inputMatrix1[350][350];
    int inputMatrix2[350][350];
    int outputMatrix[350][350];
    


void *computeElement(void *arg){

        
  int *data = (int *)arg;
  int k = 0, i = 0; 
  int x = data[0];
    for (i = 1; i <= x; i++)
           {
           k = k + data[i]*data[i+x];
           }
    int *p = (int*)malloc(sizeof(int));
        *p = k;
     
   /*Terminate Thread*/
     pthread_exit(p);
     
}


void *computeRow(void *arg){

     int i = row++;
     int j = 0;  	
     int k = 0;
     
   
      for (j = 0; j < columnMatrix1; j++)
      for (k = 0; k < rowMatrix2; k++)
        outputMatrix[i][j] += inputMatrix1[i][k] * inputMatrix2[k][j];
        
        pthread_exit(0);
        return NULL;
        
}

int main (){
     
    int i = 0;
    int j = 0; 
    int k = 0;
    char filename [50];
     
    /* Accessing the Input File Matrix */
    printf("Enter the Name of the file:");
    scanf("%s",filename);
    FILE *f;
    f = fopen (filename, "r");
    
    if (f == NULL)
        return 0;

    /* Reading the first input matrix */
    	
    fscanf(f,"%d %d",&rowMatrix1, &columnMatrix1);
    inputMatrix1 [rowMatrix1][columnMatrix1];
   
    for(i = 0; i < rowMatrix1; i++)
    {
        for(j = 0; j < columnMatrix1; j++)
            fscanf(f, "%d", &inputMatrix1[i][j]);
    }
    
    /* Reading the second input matrix */

    fscanf(f,"%d %d",&rowMatrix2, &columnMatrix2);
    inputMatrix2 [rowMatrix2][columnMatrix2];
    
    for(i = 0; i < rowMatrix2; i++)
    {
        for(j = 0; j < columnMatrix2; j++)
            fscanf(f, "%d", &inputMatrix2[i][j]);
    }
    
    /*Accessing the Output File */
    
     FILE *fout;
     fout = fopen("output-matrix.txt","w");
    
     if (fout == NULL)
        return 0;
    
  if (columnMatrix1 != rowMatrix2)
  {
    fprintf(fout,"Multiplication is not possible !!");
    fclose(fout);
    
  }
    
  else{  
     clock_t begin1 = clock();
    
    /* Declaration of Element Computation Threads */
     pthread_t *threads;
     threads = (pthread_t*)malloc((rowMatrix1 * columnMatrix2)*sizeof(pthread_t));
 
    int count = 0;
    int* data = NULL;
    int k;
     for (i = 0; i < rowMatrix1; i++)
        for (j = 0; j < columnMatrix2; j++)
               {
                
    /*storing row and column elements in data*/
     data = (int *)malloc((columnMatrix1 + rowMatrix2)*sizeof(int));
     data[0] = columnMatrix1;
     
     for (k = 0; k < columnMatrix1; k++)
      data[k+1] = inputMatrix1[i][k];
     
     for (k = 0; k < rowMatrix2; k++)
      data[k+columnMatrix1+1] = inputMatrix2[k][j];
      
      /* Creation of threads, each evaluating each element computation */
       pthread_create(&threads[count++], NULL,computeElement, (void*)(data));
                    }
                    
     /* Print the Output Matrix from each element computation*/               
     fprintf(fout,"The Output Matrix with each element computation is \n");
 
     for (i = 0; i < rowMatrix1 * columnMatrix2; i++)
        {
          void *k;
          
     /* Joining and Waiting for element computation threads to complete */
       pthread_join(threads[i], &k); 
       
         
         /* Displaying the output matrix */
         int *p = (int *)k;
         fprintf(fout,"%d ",*p);
         if ((i + 1) % columnMatrix2 == 0)
         fprintf(fout,"\n"); 
        } 
        
    /* Calculate the time taken by element computation */
    clock_t end1 = clock();
    double time_spent1 = (double)(end1 - begin1) / CLOCKS_PER_SEC;
    fprintf(fout,"Element Computation took %f seconds to execute \n", time_spent1);
        
        fprintf(fout,"\n"); 
        fprintf(fout,"\n"); 
        
     /* Print the Output Matrix from each row computation*/               
     fprintf(fout,"The Output Matrix with each row computation is \n");  
       
     clock_t begin2 = clock();   
     
    /* Creation of threads, each evaluating each row computation */
    pthread_t threads2[rowMatrix1];
  
  	i = 0;
    /* Creation of threads equal to the number of rows of the evaluated matrix */
    for (i = 0; i < rowMatrix1; i++) {
        pthread_create(&threads2[i], NULL, computeRow, NULL);
    }
    
   /* Joining and Waiting for row computation threads to complete */
    for (i = 0; i < rowMatrix1; i++)
        pthread_join(threads2[i], NULL);   
        i = 0;
 	j = 0;
    /* Displaying the output matrix */
    for (i = 0; i < rowMatrix1; i++) {
        for (j = 0; j < columnMatrix2; j++)
            fprintf(fout,"%d ", outputMatrix[i][j]);
            fprintf(fout,"\n");       
    }
    
    /* Calculate the time taken by row computation */
    clock_t end2 = clock();
    double time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
    fprintf(fout,"Row Computation took %f seconds to execute \n", time_spent2);
       
       
fclose(fout);      
fclose(f);    
} 
return 0;
}
