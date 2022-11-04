#include <stdio.h>
#include <stdlib.h>

struct student
{
    char name[25];
    float GPA;
    int ID;
};


int main()
{
    struct student S[10];
    FILE *f;
    int i;
    for (i=0;i<2;i++)
    {
        printf("Enter the name of the #%d Student: ",i+1);
        scanf("%s",S[i].name);
        printf("\n");
        printf("Enter the GPA of the #%d Student: ",i+1);
        scanf("%f",&S[i].GPA);
        printf("\n");
        printf("Enter the ID of the #%d Student: ",i+1);
        scanf("%d",&S[i].ID);
        printf("\n");
    }
    f = fopen ("Data Base.txt","w");
    for (i=0;i<2;i++)
    {
    fprintf (f," %s ",S[i].name);
    fprintf (f," %.2f ",S[i].GPA);
    fprintf (f," %d\n\n",S[i].ID);
    }
    fclose(f);
    return 0;
}
