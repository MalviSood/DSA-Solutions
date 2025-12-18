#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
  int val;
  int day;
} node_t;

int main(void) {
  int len = 0;
  scanf("%dn", &len);

  int *A = (int*)calloc(len, sizeof(int));
  for (int i = 0; i < len; i++) {
    scanf("%d", &A[i]);
  }
  node_t *stack = (node_t*)calloc(len, sizeof(node_t));
  int stack_top = -1;
  
  int min_so_far = A[0];
  int max_days = 0;
  for (int i = 1; i < len; i++) {
    // pop things off the stack with greater or equal value and keep track of max day seen
    int my_days = 0;
    while (stack_top > -1 && stack[stack_top].val >= A[i]) {
      if (my_days < stack[stack_top].day) my_days = stack[stack_top].day;
      //printf("popping (%d,%d) from stackn", stack[stack_top].val, stack[stack_top].day);
      stack_top--;
    }   
    // if this value is a left to right min, it will never die
    if (A[i] <= min_so_far) {
      min_so_far = A[i];
    } else {
      stack_top++;
      stack[stack_top].val = A[i];
      stack[stack_top].day = my_days+1;
      //printf("adding (%d,%d) to stackn", A[i], my_days+1);
      if (max_days < my_days+1) max_days = my_days+1;
    }
  }
  
  // chcek for max of anything remaining in stack
  while (stack_top > -1) {
    if (max_days < stack[stack_top].day) max_days = stack[stack_top].day;
    //printf("popping (%d,%d) from stackn", stack[stack_top].val, stack[stack_top].day);
    stack_top--;
  }

  printf("%dn", max_days);

  free(A);
  free(stack);
  return 0;
}