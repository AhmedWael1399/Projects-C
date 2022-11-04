#include <stdio.h>
#include <stdlib.h>
#include<string.h>

/* Function to calculate the position of the value to be exchanged in memory frames */
int computeLRU(int LRUTime[],int l)
{
    int i = 0;
    int minimumValue = LRUTime[0];
    int positionLRU = 0;
    for (i = 0; i < l; i++)
    {
        if(LRUTime[i] < minimumValue)
        {
            minimumValue =  LRUTime[i];
            positionLRU = i;
        }

    }

    return positionLRU;
}

int main()

{
    char pageAlgo[20];
    char FIFO[] = "FIFO";
    char OPTIMAL[] = "OPTIMAL";
    char LRU[] = "LRU";
    char CLOCK[] = "CLOCK";
    int pageReference[4200];
    int pageNumber;
    int i=0;
    int j = 0;
    int pageFaults = 0;
    int counterPlace = 0;
    int counter = 0;


    /* The Number of Pages Allocated to the Process */
    scanf("%d",&pageNumber);

    /* The Page Replacement Technique */
    scanf("%s",pageAlgo);

    int algorithmFIFO = strcmp(pageAlgo,FIFO);
    int algorithmLRU = strcmp(pageAlgo,LRU);
    int algorithmOPTIMAL = strcmp(pageAlgo,OPTIMAL);
    int algorithmCLOCK = strcmp(pageAlgo,CLOCK);

    /* The Page References */
    while(1)
    {
        scanf("%d",&pageReference[i]);
        if (pageReference[i] == -1)
            break;
        i++;
        counterPlace++;
    }
    /* FIFO replacement Technique */
    if (algorithmFIFO == 0)
    {
        int pageReplacementFIFO[pageNumber];
        int pageFlag = 0;
        i=0;

        for(i=0; i<pageNumber; i++)
        {
            pageReplacementFIFO[i] = 0;
        }
        int m = 0;
        printf("Replacement Policy = %s\n",pageAlgo);
        printf("-------------------------------------\n");
        printf("Page   Content of Frames\n");
        printf("----   -----------------\n");

        i=0;
        for(i = 0; i < counterPlace; i++)
        {
            pageFlag = 0;
            for(int j = 0; j < pageNumber; j++)
            {
                if(pageReplacementFIFO[j] == pageReference[i])
                    pageFlag = 1;
            }
            if (pageFlag == 0)
            {
                pageReplacementFIFO[m] = pageReference[i];
                m++;
                counter++;
                if(m == pageNumber)
                {
                    m=0;
                }
                pageFaults++;
            }
            if(pageFlag==0 && counter>pageNumber)
            {
                printf("%02d F   ",pageReference[i]);
            }
            else
            {
                printf("%02d     ",pageReference[i]);
            }
            for(int j=0; j<pageNumber; j++)
            {
                if(pageReplacementFIFO[j] == 0)
                {
                    break;
                }
                printf("%02d ", pageReplacementFIFO[j]);
            }
            printf("\n");
        }
    }

    /* LRU Replacement Technique */
    if (algorithmLRU == 0)
    {
        int pageReplacementLRU[pageNumber];
        int timeLRU[5000];
        int flagLRU1 = 0;
        int flagLRU2 = 0;
        int position;
        counter = 0;
        j = 0;
        i = 0;
        for(i=0; i<pageNumber; i++)
        {
            pageReplacementLRU[i] = 0;
        }
        printf("Replacement Policy = %s\n",pageAlgo);
        printf("-------------------------------------\n");
        printf("Page   Content of Frames\n");
        printf("----   -----------------\n");

        i=0;
        for(i = 0; i < counterPlace; i++)
        {
            flagLRU1 = flagLRU2 = 0;
            for(j = 0; j < pageNumber; j++)
            {
                if(pageReplacementLRU[j] == pageReference[i])
                {
                    counter++;
                    timeLRU[j] = counter;
                    flagLRU1 = flagLRU2 = 1;
                }
            }
            if (flagLRU1 == 0)
            {
                j = 0;
                for (j = 0; j < pageNumber; j++)
                {
                    if (pageReplacementLRU[j] == 0)
                    {
                        pageFaults++;
                        counter++;
                        pageReplacementLRU[j] = pageReference[i];
                        timeLRU[j] = counter;
                        flagLRU2 = 1;
                        break;
                    }

                }
            }
            if (flagLRU2 == 0)
            {
                counter++;
                pageFaults++;
                position = computeLRU(timeLRU,pageNumber);
                pageReplacementLRU[position] = pageReference[i];
                timeLRU[position] = counter;
            }

            if(flagLRU2 == 0)
            {
                printf("%02d F   ",pageReference[i]);
            }
            else
            {
                printf("%02d     ",pageReference[i]);
            }
            for(j=0; j<pageNumber; j++)
            {
                if(pageReplacementLRU[j] == 0)
                {
                    break;
                }
                printf("%02d ", pageReplacementLRU[j]);
            }
            printf("\n");
        }
    }

    /* OPTIMAL Replacement Technique */
    if (algorithmOPTIMAL == 0)
    {
        int pageReplacementOPTIMAL[pageNumber];
        int timeOPTIMAL[5000];
        int flagOPTIMAL1 = 0;
        int flagOPTIMAL2 = 0;
        int flagOPTIMAL3 = 0;
        int position;
        int positionOPTIMAL[5000];
        int p = 0;
        int maximumValueOptimal;
        counter = 0;
        j = 0;
        i = 0;
        for(i=0; i<pageNumber; i++)
        {
            pageReplacementOPTIMAL[i] = 0;
        }
        printf("Replacement Policy = %s\n",pageAlgo);
        printf("-------------------------------------\n");
        printf("Page   Content of Frames\n");
        printf("----   -----------------\n");

        i=0;
        for(i = 0; i < counterPlace; i++)
        {
            flagOPTIMAL1 = flagOPTIMAL2 = 0;
            for(j = 0; j < pageNumber; j++)
            {
                if(pageReplacementOPTIMAL[j] == pageReference[i])
                {
                    counter++;
                    timeOPTIMAL[j] = counter;
                    flagOPTIMAL1 = flagOPTIMAL2 = 1;
                }
            }
            if (flagOPTIMAL1 == 0)
            {
                j = 0;
                for (j = 0; j < pageNumber; j++)
                {
                    if (pageReplacementOPTIMAL[j] == 0)
                    {
                        pageFaults++;
                        counter++;
                        pageReplacementOPTIMAL[j] = pageReference[i];
                        timeOPTIMAL[j] = counter;
                        flagOPTIMAL2 = 1;
                        break;
                    }

                }
            }
            if (flagOPTIMAL2 == 0)
            {
                flagOPTIMAL3 = 0;
                for (j = 0; j < pageNumber; j++)
                {
                    positionOPTIMAL[j] = -1;

                    for (p = i+1; p < counterPlace; p++)
                    {
                        if(pageReplacementOPTIMAL[j] == pageReference[p])
                        {
                            positionOPTIMAL[j] = p;
                            break;
                        }
                    }
                }

                for (j=0; j <pageNumber; j++)
                {
                    if (positionOPTIMAL[j] == -1 )
                    {
                        position = j;
                        flagOPTIMAL3 = 1;
                        break;
                    }
                }

                if (flagOPTIMAL3 == 0)
                {
                    maximumValueOptimal = positionOPTIMAL [0];
                    position = 0;
                    for(j = 1; j < pageNumber; j++)
                    {
                        if(positionOPTIMAL[j] > maximumValueOptimal)
                        {
                            maximumValueOptimal = positionOPTIMAL[j];
                            position = j;
                        }
                    }
                }
                pageReplacementOPTIMAL[position] = pageReference[i];
                pageFaults++;
            }

            if(flagOPTIMAL2 == 0)
            {
                printf("%02d F   ",pageReference[i]);
            }
            else
            {
                printf("%02d     ",pageReference[i]);
            }
            for(j=0; j<pageNumber; j++)
            {
                if(pageReplacementOPTIMAL[j] == 0)
                {
                    break;
                }
                printf("%02d ", pageReplacementOPTIMAL[j]);
            }
            printf("\n");
        }
    }

    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",pageFaults-pageNumber);

    return 0;
}
