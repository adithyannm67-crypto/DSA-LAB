/*
Our department is organizing a tech fest with so many exciting events. By participating in
an event, you can claim for activity points as stipulated by KTU. Each event i gives you A[i]
activity points where A is an array. If you are not allowed to participate in more than k events,
what’s the max number of points that you can earn?
*/

#include<stdio.h>

int main(){

    int A[100],n;
    int k;
    printf("\nENTER THE NO OF EVENTS  :  ");
    scanf("%d",n);
    printf("\nENTER ACTIVITY POINTS ARRAY   :   ");
    for(int i=0;i<n;i++){
        scanf("%d",&A[i]);
    }
    printf("ENTER MAX EVENTS THAT CAN BE PARTICICPATED");
    scanf("%d",k);


    for(int i=1;i<n;i++){
        int item=A[i],j=i-1;

        while(j>-1 && A[j]<item){
            A[j+1]=A[j];
            j--;

        }
        A[j+1]=item;
    }
    int maxPoints = 0;
    int maxNumber = k > n ? n : k;
    for (int i = 0; i < maxNumber; i++)
    {
        maxPoints+=A[i];
    }

    printf("%d",maxPoints);

    return 0;

}