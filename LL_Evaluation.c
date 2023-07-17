#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct node
{
    int data;
    struct node*next;
};
FILE*fp1,*fp2,*fp3;
struct node*insert_at_begi(struct node*,struct node*);
void sort(struct node*);
void display(struct node*);

main()
{
    fp1=fopen("f1.txt","w");
    fp2=fopen("f2.txt","w");
    fp3=fopen("f3.txt","w");
    struct node*head;
    struct node*temp,*temp1,*newnode,*temp2;
    int i,n;
    time_t s;
    srand((unsigned)time(&s));
    double time;
    clock_t start,end;
    head=NULL;
     for(i=0;i<10000;i++)
    {
       newnode=(struct node*)malloc(sizeof(struct node));
       newnode->data=rand();
       head=insert_at_begi(newnode,head);
       fprintf(fp1,"%d ",newnode->data);

    }
    start=clock();
    sort(head);
    end=clock();
    time=(double)(end-start);
    fprintf(fp3,"time delay=%lf\n",time);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}
struct node*insert_at_begi(struct node*newnode,struct node*head)
{
  if(head==NULL)
  {
      head=newnode;
      head->next=NULL;
      return(head);
  }
  else
  {
      newnode->next=head;
      head=newnode;
      return(head);
  }
}
void sort(struct node* head)
{
    int n,i,j,x;
    n=5000;
    if(head==NULL)
    {
        printf("linked list is empty\n");
    }
    else
    {
        if(head->next==NULL)
        {
            printf("%d ",head->data);
        }
        else
        {
            struct node*temp1,*temp;
            for(i=0;i<n;i++)
            {
                temp=head;
                for(j=0;j<n-i-1;j++)
                {
                    if(temp->data>(temp->next)->data)
                    {
                       x=temp->data;
                       temp->data=(temp->next)->data;
                       (temp->next)->data=x;
                    }
                    temp=temp->next;
                }
            }
        }
        display(head);
    }
}
void display(struct node *head)
{
    struct node*temp;
    if(head==NULL)
    {
        fprintf(fp2,"linked list is empty\n");
    }
    else
    {
        temp=head;
        while(temp!=NULL)
        {
            fprintf(fp2,"%d->",temp->data);
            temp=temp->next;
        }
    }
    printf("\n");
}
