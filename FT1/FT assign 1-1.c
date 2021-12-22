#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[][2], int s, int mid, int e)
{
    int i, j, k;
    int n1 = mid - s + 1;
    int n2 =  e - mid;

    //divide and conquer
    int Left[n1][2], Right[n2][2];


    //every time i is less then n1, the array is copied to left region
    for (i = 0; i < n1; i++)
    {
       Left[i][0] = arr[s+i][0];
       Left[i][1] = arr[s+i][1];
    }

    for (j = 0; j < n2; j++)
    {
      Right[j][0] = arr[mid + 1+ j][0];
      Right[j][1] = arr[mid + 1+ j][1];
    }



    i = 0;
    j = 0;
    k = s;

 //array placed in order
    while (i < n1 && j < n2)
    {
        if (Left[i][0] <= Right[j][0])
        {
            arr[k][0] = Left[i][0];
            arr[k][1] = Left[i][1];
            i++;
        }
        else
        {
            arr[k][0] = Right[j][0];
            arr[k][1] = Right[j][1];
            j++;
        }
        k++;
    }
//while loop checks for unassigned array indexes
    while (i < n1)
    {
        arr[k][0] = Left[i][0];
        arr[k][1] = Left[i][1];

        i++;
        k++;
    }


    while (j < n2)
    {
        arr[k][0] = Right[j][0];
        arr[k][1] = Right[j][1];
        j++;
        k++;
    }
}


void mergeSort(int arr[][2], int s, int e)
{
    if (s < e)
    {

        int mid = s+(e-s)/2;


        mergeSort(arr, s, mid);
        mergeSort(arr, mid+1, e);

        merge(arr, s, mid, e);
    }
}


int binarySearch(int list[][2], int item1, int item2, int len)
{
int l = 0, h = len-1;
int mid;
while (l <= h)
{
mid = (l + h) / 2;
// Check if item is present at mid + nested while loop
if (list[mid][0] == item1)
{
    if(list[mid][1] == item2)
return mid;

}



if (list[mid][0] < item1)
l = mid + 1;

else
h = mid -1;
}


return -1;
}

int main()
{
    FILE *fp1, *fp2;
    int coor, ch, x, y;



    fp1 = fopen("input.txt", "r");
    fp2 = fopen("output.txt", "w");

    fscanf(fp1, "%d", &coor );

    int xy[coor][2], i =0;

    while (!feof (fp1))
        {
            fscanf(fp1, "%d %d ", &xy[i][0],&xy[i][1]);

            ++i;
        }

    for(i=0;i<coor;i++)
        printf("%d %d\n", xy[i][0], xy[i][1]);

        puts("");
   mergeSort(xy,0,coor-1);

    for(i=0;i<coor;i++)
        printf("%d %d\n", xy[i][0],xy[i][1]);

    for(i=0;i<coor;i++)
        fprintf(fp2, "(%d ,%d)\n", xy[i][0],xy[i][1]);


    ch=1;

    //sentinel while loop
       while(ch!=-1)
        {

            printf("Look for Coordinates: \n");
            scanf("%d %d", &x, &y);

            if(binarySearch(xy,x, y,coor)==-1)
            {
                printf("Coordinates not found: (%d,%d)\n", x, y);
            }
            else
            {
               printf("Coordinates found (%d,%d)\n", x, y);
            }

            printf("End loop? 1 for no, -1 for yes: \n");
            scanf("%d", &ch);
        }

    fclose(fp1);
    fclose(fp2);


}
