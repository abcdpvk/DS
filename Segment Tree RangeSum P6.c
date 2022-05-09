#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include<time.h>

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

int Range_Sum(int Seg_Tree[],int qlow,int qhigh,int low,int high,int pos)
{
	if(low >= qlow && high <= qhigh){
        printf("\n[%d,%d] :: Contained",low,high);
		return Seg_Tree[pos];
	}

	if(low > qhigh || high < qlow){
        printf("\n[%d,%d] :: Disjoint",low,high);
		return 0;
	}

	int mid = (low+high)/2;
	printf("\n[%d,%d] :: Partially Overlapped",low,high);
	return Range_Sum(Seg_Tree,qlow,qhigh,low,mid,pos*2+1) +
			   Range_Sum(Seg_Tree,qlow,qhigh,mid+1,high,pos*2+2);

}

void Tree_Build(int A[],int Seg_Tree[],int low,int high,int pos)
{
	if(low == high)
	{
		Seg_Tree[pos] = A[low];
		return;
	}

	int mid = (low+high)/2;
	Tree_Build(A,Seg_Tree,low,mid,pos*2+1);
	Tree_Build(A,Seg_Tree,mid+1,high,pos*2+2);
	Seg_Tree[pos] = Seg_Tree[pos*2+1] + Seg_Tree[pos*2+2];

}

int main(){
    int A[] = {5,6,7,8,9,10,11,12,13,14};

	int n = sizeof(A)/sizeof(A[0]);

	int h = (int)(ceil(log2(n)));
	int size = 2*(int)pow(2,h)-1;

	int *Seg_Tree = (int *)malloc(sizeof(int)*size);

    //Tree Build
	Tree_Build(A,Seg_Tree,0,n,0);

	int choice=1;
    {
        printf("\n*******************Practical 6 : Range Sum Problem*********************");
         printf("\n\nValues are :: ");
	for(int i=0;i<n;i++)
    {
        printf("%d ",A[i]);
    }
        printf("\n\nEnter Ranges... \n \n");
        int lower_Range,Higher_Range;
        printf("Lower Bound :: ");
        scanf("%d",&lower_Range);
        printf("Upper Bound :: ");
        scanf("%d",&Higher_Range);
        if(lower_Range<0 || Higher_Range>n){
            printf("\n\n Kindly Check the Range and Re Enter it...");
        }
        else{
            //Range's Sum
            int sum=Range_Sum(Seg_Tree,lower_Range,Higher_Range,0,n,0);
            printf("\n\nSum of Range is :: %d\n",sum);
        }
    }
    printf("\nT");delay(1);printf("H");delay(1);printf("A");delay(1);printf("N");delay(1);printf("K");delay(1);printf(" U!!!!\n\n");
}
