#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

/* Global Variables*/
int *heap_array = NULL;
int heap_max_size = 0;
int heap_current_size = 0;

#define SIZE_OF_BLOCK_ALLOCATION  1000 

void heap_heapify_from_top (int counter) {
    int temp_val = 0;
    int child_counter;
    int has_left_child = 0;
    int has_right_child = 0;

    if ((2 * counter + 1) < heap_current_size)
        has_left_child = 1;

    if ((2 * counter + 2) < heap_current_size)
        has_right_child = 1;

    /* Now, let us find the lowest of the two children */
    if (has_left_child && has_right_child) {
        if (heap_array[2* counter + 1] < heap_array[2*counter + 2])
            child_counter = 2 * counter + 1;
        else
            child_counter = 2 * counter + 2;
    } else if (has_left_child) {
        child_counter = 2 * counter + 1;
    } else if (has_right_child) {
        child_counter = 2 * counter + 2;
    } else {
        return;
    }

    if (heap_array[counter] > heap_array[child_counter]) {
        temp_val = heap_array[counter];
        heap_array[counter] = heap_array[child_counter];
        heap_array[child_counter] = temp_val;
        heap_heapify_from_top(child_counter);
    }
    return;
}

int heap_extract () {
    int t = 0;
    if (heap_current_size == 0) {
        printf("The heap is emptyn");
        return -1;
    }

    t = heap_array[0];
    heap_array[0] = heap_array[heap_current_size-1];
    heap_current_size--;

    if (heap_current_size != 1) {
        heap_heapify_from_top(0);
    }
    return t;
}

 void heap_insert_heapify_from_bottom (int counter) {
     int parent = (int) floor((double)(counter-1)/2);
     int temp_val;

     if (counter == 0) {
         return;
     }

     if (heap_array[parent] > heap_array[counter]) {
         temp_val = heap_array[counter];
         heap_array[counter] = heap_array[parent];
         heap_array[parent] = temp_val;
     }

     heap_insert_heapify_from_bottom(parent);
 }

 int heap_add (int value) {
     if (heap_current_size == heap_max_size) {
         heap_max_size += SIZE_OF_BLOCK_ALLOCATION;
         heap_array = (void*)realloc(heap_array,
                         heap_max_size * sizeof(int));
         if (!heap_array) {
             printf("realloc failedn");
             return -1;
         }
     }
     heap_array[heap_current_size] = value;
     heap_insert_heapify_from_bottom(heap_current_size);
     heap_current_size++;
     return 0;
 }

 int main (int argc, char *argv[]) {
    int n, k, i, temp=0, temp2=0, num_oper=0, temp_k;
    bool no_entry_with_max = true;

    scanf("%d %d", &n, &k);
    for (i = 0; i <n; i++) {
        scanf("%d", &temp);
        heap_add(temp);
    }

    temp = heap_extract();
    if (temp >= k) {
        printf("0n");
        return 0;
    }
    while (temp < k && heap_current_size) {
        temp2 = heap_extract();
        temp_k = temp + 2 * temp2;
        num_oper += 1;
        heap_add(temp_k);
        if (temp_k >= k) {
            no_entry_with_max = false;
        }
        temp = heap_extract();
    }
    if (no_entry_with_max == true) {
        printf("-1n");
    } else {
        printf("%dn", num_oper);
    }
    return 0;
 }