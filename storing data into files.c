#include<stdio.h>
#include<stdlib.h>
void write_to_file(FILE *p);
void read_from_file(FILE *p);
void computers_details(FILE *p);
int main()
{
    FILE *p;
    write_to_file(p);
    read_from_file(p);
    return 0;
}
void write_to_file(FILE *p)
{
     char computer_name[20];
    int ram,windows,i,n;
    p=fopen("computer.txt","w");
    printf("Enter the number of computers: ");
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++\n");

        printf("\nEnter the Details of computer %d: \n",i);
        printf("ENTER COMPUTER NAME: ");
        scanf("%s",computer_name);
        printf("ENTER THE RAM OF THE COMPUTER: ");
        scanf("%d",&ram);
        printf("ENTER THE WINDOWS VERSION: ");
        scanf("%d",&windows);
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
        fprintf(p,"\n%s\t%d\t%d\n",computer_name,ram,windows);
    }
    fclose(p);
}
void read_from_file(FILE *p)
{
    char computer_name[20];
    int ram,windows;
    p=fopen("computer.txt","r");
    printf("computer name\RAM\tWindows\n");
    while(!feof(p))
    {
        fscanf(p,"%s %d %d\n",computer_name,&ram,&windows);
        printf("%s\t%d\t%d\n",computer_name,ram,windows);
    }
    fclose(p);
}

