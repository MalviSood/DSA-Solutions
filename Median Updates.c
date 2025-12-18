#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
/* Head ends here */
void insertionSort(int N,int *x){
        int temp = x[N-1];
        int j=N-2;
        while ( j>=0 && x[j]>temp){
            x[j+1] = x[j];
            j--;  
        } 
        x[j+1] = temp;
}
void median(int N,char (*s), int *x) {
    int size = 0;
    int a[N];
    for(int i=0; i<N; i++){
        if (s[i] == 'a'){
            a[size++] = x[i];
            insertionSort(size,&a[0]);
            if (size % 2 == 1)
                printf("%d",a[size/2]);
            else{
                 if ((a[size/2]+a[(size/2)-1]) % 2 == 0)
                       printf("%ld",((long)a[size/2]+a[(size/2)-1])/2);
                 else 
                     printf("%1.1f",((signed long)a[size/2]+a[(size/2)-1])/2.0);
                 }
            printf("n");
        }
        else{
            if (size == 0) {printf("Wrong!n");continue;}
            int found = 0;
            for(int j=0; j<size; j++){
                if (a[j] == x[i]){
                    for(int k=j; k<size-1; k++){
                        a[k] = a[k+1];
                    }
                    size--;
                    if (size == 0) printf("Wrong!");
                    else if (size % 2 == 1)
                        printf("%d",a[size/2]);
                    else{
                        if ((a[size/2]+a[(size/2)-1]) % 2 == 0)
                            printf("%ld",((long)a[size/2]+a[(size/2)-1])/2);
                        else 
                            printf("%1.1f",((signed long)a[size/2]+a[(size/2)-1])/2.0);
                    }
                    printf("n");
                    found = 1;
                    break;
                }
            }
            if (!found) printf("Wrong!n");
        }
   }
}

int main(){

//Helpers for input/output
   int i, N;

   scanf("%d", &N);
   char s[N];
   int x[N];
   

   for(i=0; i<N; i++){
      scanf("%s %d", &(s[i]), &(x[i]));
   }
   
   median(N,s,x);
   
}