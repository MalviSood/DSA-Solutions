#include <stdio.h>
#include <stdlib.h>
void sort_a2(int*a,int*b,int size);
void merge2(int*a,int*left_a,int*right_a,int*b,int*left_b,int*right_b,int left_size, int right_size);
int a[100000],ans[100000],stack1[100000],stack2[100000],left[100000],right[100000],c[100000];

int main(){
  int N,Q,x,p,min,i,j;
  scanf("%d%d",&N,&Q);
  for(i=0;i<N;i++)
    scanf("%d",a+i);
  for(i=p=0;i<N;i++){
    while(p && stack1[p-1]<=a[i])
      p--;
    stack1[p]=a[i];
    stack2[p++]=i;
    if(p==1)
      left[i]=0;
    else
      left[i]=stack2[p-2]+1;
  }
  for(i=N-1,p=0;i>=0;i--){
    while(p && stack1[p-1]<=a[i])
      p--;
    stack1[p]=a[i];
    stack2[p++]=i;
    if(p==1)
      right[i]=N-1;
    else
      right[i]=stack2[p-2]-1;
  }
  for(i=0;i<N;i++)
    c[i]=right[i]-left[i]+1;
  sort_a2(c,a,N);
  for(i=N,j=N-1,min=-1;i>0;i--){
    for(;c[j]==i;j--)
      if(min==-1 || a[j]<min)
        min=a[j];
    ans[i-1]=min;
  }
  while(Q--){
    scanf("%d",&x);
    printf("%dn",ans[x-1]);
  }
  return 0;
}
void sort_a2(int*a,int*b,int size){
  if (size < 2)
    return;
  int m = (size+1)/2,i;
  int*left_a,*left_b,*right_a,*right_b;
  left_a=(int*)malloc(m*sizeof(int));
  right_a=(int*)malloc((size-m)*sizeof(int));
  left_b=(int*)malloc(m*sizeof(int));
  right_b=(int*)malloc((size-m)*sizeof(int));
  for(i=0;i<m;i++){
    left_a[i]=a[i];
    left_b[i]=b[i];
  }
  for(i=0;i<size-m;i++){
    right_a[i]=a[i+m];
    right_b[i]=b[i+m];
  }
  sort_a2(left_a,left_b,m);
  sort_a2(right_a,right_b,size-m);
  merge2(a,left_a,right_a,b,left_b,right_b,m,size-m);
  free(left_a);
  free(right_a);
  free(left_b);
  free(right_b);
  return;
}
void merge2(int*a,int*left_a,int*right_a,int*b,int*left_b,int*right_b,int left_size, int right_size){
  int i = 0, j = 0;
  while (i < left_size|| j < right_size) {
    if (i == left_size) {
      a[i+j] = right_a[j];
      b[i+j] = right_b[j];
      j++;
    } else if (j == right_size) {
      a[i+j] = left_a[i];
      b[i+j] = left_b[i];
      i++;
    } else if (left_a[i] <= right_a[j]) {
      a[i+j] = left_a[i];
      b[i+j] = left_b[i];
      i++;
    } else {
      a[i+j] = right_a[j];
      b[i+j] = right_b[j];
      j++;
    }
  }
  return;
}