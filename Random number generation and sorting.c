// Generate random numbers and display the time taken to sort those numbers
#include <stdio.h>
#include <time.h>

int main ()
{
    clock_t t ;
    FILE *ft , *f ;
    ft = fopen("text.txt", "w");
    int a[100];

    int  u , i, count, m, j, temp;
    //printf("enter the number of random numbers to be generated ");
    //scanf ("%d", &count);

    count = 10000;

    printf("enter the upper limit ");
    scanf ("%d", &u);


    t= clock();

    for (i = 0; i < count; i++) {
      int random = (rand() % (u + 1));
      printf("%d ", random);
      fprintf(ft , "%d ",random );
   }

   fclose(ft);

    ft = fopen("text.txt", "r");

   i = 0;
   while (i<count)
    {
        fscanf (ft , "%d", &m);
        a[i] = m ;
        i++;
    }


    for (int i = 0 ; i<count ; i++)
    {
        for (int j = 0 ; j< count-i-1 ; j++)
        {
            if(a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1 ] = temp;
            }
        }
    }

    printf("\n\n");
    printf("sorted array : ");
    f = fopen("copy.txt", "w");
    for (int j = 0 ; j< count; j++)
    {

        printf("%d ", a[j]);
        fprintf(f , "%d", a[j]);
    }

     t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("\n\n");
    printf("the sorting took %f seconds to execute \n", time_taken);

}
