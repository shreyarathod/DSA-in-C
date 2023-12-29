#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define MaxHeap ADT
typedef struct {
    int *array;
    int size;
    int capacity;
} MaxHeap;

/// @brief Creates an empty max-heap of size 'capacity'
/// @param capacity - max size of heap
/// @return Pointer to MaxHeap
MaxHeap *initHeap(int capacity){
	MaxHeap * maxheap = (MaxHeap *)malloc(sizeof(MaxHeap));
	maxheap->size = 0;
	maxheap->capacity = capacity;
	maxheap->array = (int *)malloc(sizeof(int) * maxheap->capacity);
	return maxheap;
}

// Delete and free the max-heap structure
void destroyHeap(MaxHeap* heap){
    free(heap->array);
    free(heap);
}

/// @brief This restores the heap-order property for max-heap array at index 'i'
/// @param heap 
/// @param i - index of the max-heap array, which might potentialy be breaking the heap order
void heapify(MaxHeap* heap, int i){
	int left = 2*i + 1;
	int right = 2*i + 2;
	int max = i;

	if(left >=0 && left<heap->size && heap->array[left]> heap->array[max]){
		max = left;
	}

	if(right >=0 && right<heap->size && heap->array[right]> heap->array[max]){
		max = right;
	}

	if(max != i){
		int temp = heap->array[max];
		heap->array[max] = heap->array[i];
		heap->array[i] = temp;

		heapify(heap , max);
	}
}

//
/// @brief This inserts a value into a max-heap
/// @param heap 
/// @param value 
void insert(MaxHeap* heap, int value){
	if(heap->size<heap->capacity){
		heap->array[heap->size] = value;
		
	    heap->size++;
	}else{
		printf("Heap is Full");
	}

}



// displays the max element in the MaxHeap array
void peek_max(MaxHeap* heap){
	printf("%d", heap->array[0]);
}

// extracts the max element from the MaxHeap array
int extractMax(MaxHeap* heap){
	if(heap->size==0){
		printf("Heap is empty.");
		return -1;
	}
	int max = heap->array[0];
	heap->array[0] = heap->array[heap->size-1];
	heap->size--;
	heapify(heap,0);
	return max;
}


/// @brief - Display the given MaxHeap in a visually clear way.
/// @param heap 
/// @param stop_idx - This index in the MaxHeap array corresponds to the last item of the heap
void display_heap(MaxHeap* heap, int stop_idx){
	for(int i = 0;i <= stop_idx;i++){
		printf( "%d ", heap->array[i]);
	}
}



/// @brief Build max-heap using the Floyd's method. This method should call initHeap
/// @param heap 
MaxHeap *constructHeap(int *arr, int arr_length){
	MaxHeap * maxheap = initHeap(arr_length);
	
	for(int i = 0;i<arr_length;i++){
		insert(maxheap,arr[i]);
	}
	
	for(int j = arr_length/2 ;j>= 0;j--){
		heapify(maxheap,j);
	}
	
	return maxheap;
}


// Sorts the given MaxHeap array in ascending order. 
// Post running this function, heap->array should contain the elements in the sorted order
// NOTE: This function should not use any additional data structures
void heapSort_ascending(MaxHeap* heap){
	int size = heap->size;
	for(int i =0; i<size ; i++){
	 	int element = extractMax(heap);
	 	heap->array[heap->size] = element;
	}
	heap->size = size;
}

int main (){
    int arr[] = {1,2,3,4,5,6,7,8};
	int arr_length = 8;
	MaxHeap * heap = constructHeap(arr,arr_length);
	printf("Heap:");
	display_heap(heap,heap->size-1);

	printf("\nMax Element:");
    peek_max(heap);

	printf("\nAfter Removing Element:");
	extractMax(heap);
	display_heap(heap,heap->size-1);

	printf("\nSorted Heap:");
	heapSort_ascending(heap);
	display_heap(heap,heap->size-1);

	return 0;
}