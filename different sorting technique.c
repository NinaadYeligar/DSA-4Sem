//read the array from the file and sort the array with the sorting technique specified by the user 


#include <stdio.h>

void bubblesort (int a[100] , int n );
void selectionsort (int a[] , int n);
void swap (int*  x , int* y );

int main ()
{
    FILE *f;
    int n , i=0 , a[100], c ;
    f = fopen ("text.txt", "r");

    printf("enter the number of elements u wanna sort ");
    scanf ("%d", &n);

    while (i < n )
    {
        fscanf (f , "%d" , &a[i]);
        i++;
    }
    printf("the array is : ");

    for (i = 0 ;i<n; i++)
    {
        printf("%d ", a[i] );
    }
    printf("\n\n");


    printf("choose the sorting technique \n");
    printf("1 : Bubble sort\n");
    printf("2 : Selection sort \n");
    
    scanf ("%d", &c);

    switch (c)
    {
    case 1:
        bubblesort(a , n);
    
        break;
    case 2 : 
        selectionsort(a, n);
        break ;
        
    default:
        break;
    }
    printf("Sorted array : ");
    for (i = 0 ;i<n; i++)
    {
        printf("%d ", a[i] );
    }

}

void bubblesort (int a[100] , int n )
{
    int i , j , temp ;
    int *x , *y ;

    for (i = 0 ;i<n-1 ; i++)
    {
        for (j=0 ; j<n-i-1 ; j++)
        {
            if(a[j]>a[j+1])
            {
                x  = &a[j];
                y = &a[j+1];
                swap (x,y);
            }
        }
    }
}

void selectionsort (int a[] , int n)
{
    int i , j , min , *x ,*y;

    for (i = 0 ; i< n-1 ; i++)
    {
        min = i ;
        for (j=i+1 ; j<n ; j++)
        {
            if(a[j]< a[min])
            min  = j;
        }

        x = &a[i];
        y = &a[min];
        swap (x, y);

    }
} 

void swap (int*  x , int* y )
{
    int temp = *x;
    *x = *y;
    *y = temp ;
}