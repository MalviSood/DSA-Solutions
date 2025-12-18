#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


static int *gas;
static int *dist;

int find_starting_point(int *gas, int *dist, int count) {
    int i;
    int start = 0;
    int end = 1;
    
    int gas_left = gas[start] - dist[start];
    while((start != end) || (gas_left < 0)) {
        while ((start != end) && (gas_left < 0)) {
            gas_left -= gas[start] - dist[start];
            start = (start+1)%count;
            if (start == 0)
                return -1;
        } 

        gas_left += gas[end] - dist[end];
        end = (end+1)%count;
     }
    
    return(start);
}

int main() {
   int _ar_size;
   int _ar_i;
    
   scanf("%dn", &_ar_size);
   gas = (int *)malloc(sizeof(int)*_ar_size);
   if (gas == NULL)
       return 0;
    
   dist = (int *)malloc(sizeof(int)*_ar_size);
   if (dist == NULL) {
       free(gas);
       return 0;
   }
    
   for(_ar_i = 0; _ar_i < _ar_size; _ar_i++) { 
      scanf("%d %d", &gas[_ar_i], &dist[_ar_i]); 
   }
    
   #if 0
   for(_ar_i = 0; _ar_i < _ar_size; _ar_i++) { 
      printf("%d %dn", gas[_ar_i], dist[_ar_i]); 
   }
   #endif
    
   printf("%d", find_starting_point(gas, dist, _ar_i));
    
   free(gas);
   free(dist);
    
   return 0;
}