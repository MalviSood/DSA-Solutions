#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int *array;
    int count;
    int size;
} Heap;

void heap_init(Heap *heap, int size) {
    heap->size = size;
    heap->array = (int *)malloc(size*sizeof(int));
    heap->count = 0;
}

void minheap_push(Heap *heap, int x) {
    assert(heap->count < heap->size);
    int i = heap->count;
    int p = (i-1)/2;
    while (i > 0 && x < heap->array[p]) {
        heap->array[i] = heap->array[p];
        i = p;
        p = (i-1)/2;
    }
    heap->array[i] = x;
    heap->count++;
}

void maxheap_push(Heap *heap, int x) {
    assert(heap->count < heap->size);
    int i = heap->count;
    int p = (i-1)/2;
    while (i > 0 && x > heap->array[p]) {
        heap->array[i] = heap->array[p];
        i = p;
        p = (i-1)/2;
    }
    heap->array[i] = x;
    heap->count++;
}

int minheap_pop(Heap *heap) {
    assert(heap->count > 0);
    int result = heap->array[0];
    int x = heap->array[--heap->count];
    int next, i = 0;
    while (1) {
        int left = 2*i + 1;
        int right = left + 1;
        if (left >= heap->count) break;
        if (heap->array[left] < x) {
            if (right < heap->count && heap->array[right] < heap->array[left]) {
                next = right;
            } else {
                next = left;
            }
        } else if (right < heap->count && heap->array[right] < x) {
            next = right;
        } else {
            break;
        }
        heap->array[i] = heap->array[next];
        i = next;
    }
    heap->array[i] = x;
    return result;
}

int maxheap_pop(Heap *heap) {
    assert(heap->count > 0);
    int result = heap->array[0];
    int x = heap->array[--heap->count];
    int next, i = 0;
    while (1) {
        int left = 2*i + 1;
        int right = left + 1;
        if (left >= heap->count) break;
        if (heap->array[left] > x) {
            if (right < heap->count && heap->array[right] > heap->array[left]) {
                next = right;
            } else {
                next = left;
            }
        } else if (right < heap->count && heap->array[right] > x) {
            next = right;
        } else {
            break;
        }
        heap->array[i] = heap->array[next];
        i = next;
    }
    heap->array[i] = x;
    return result;
}


int main(void) {
    int n, x;
    scanf("%d", &n);
    
    int size = n/2 + 2;
    Heap minheap, maxheap;
    heap_init(&minheap, size);
    heap_init(&maxheap, size);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);

        // Decide which heap x should go on.
        if (minheap.count == 0) {
            minheap_push(&minheap, x);
        } else if (x > minheap.array[0]) {
            minheap_push(&minheap, x);
        } else {
            maxheap_push(&maxheap, x);
        }
        
        // Then adjust sizes of heaps until they differ by at most 1.
        while (minheap.count - maxheap.count > 1) {
            int x = minheap_pop(&minheap);
            maxheap_push(&maxheap, x);
        }
        while (maxheap.count - minheap.count > 1) {
            int x = maxheap_pop(&maxheap);
            minheap_push(&minheap, x);
        }

        float median;        
        if (minheap.count == maxheap.count) {
            median = 0.5*(minheap.array[0] + maxheap.array[0]);
        } else if (minheap.count > maxheap.count) {
            median = minheap.array[0];
        } else {
            median = maxheap.array[0];
        }
        printf("%.1fn", median);
    }
    return 0;
}