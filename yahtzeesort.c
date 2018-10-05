#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_SUB_ARRAY 4

// Struct to hold an array and its size
typedef struct vector array_t;
struct vector {
	int *array;
	int size;
};

/*
  Allocate a new numbered array.
*/
array_t* new_array(int size){
    array_t* new = malloc(sizeof(array_t) * sizeof(*new));
    if(new == NULL){
        printf("Error in new_array() struct allocation.");
        exit(-1);
    }
    new->size = size;
    new->array = malloc(sizeof(int) * size);
    if(new->array == NULL){
        printf("Error in new_array() array allocation.");
        exit(-1);
    }
    return new;
}

/*
  Deallocate a vector struct properly.
*/
void dealloc_array(array_t* vector){
    free(vector->array);
    free(vector);
}

/*
  A simple PRNG(Pseudo Random Number Generator)
  used to populate the array with numbers. Takes in
  the min and max values that sets the wanted range.
  Return values can include BOTH input values!
*/
int randint(int from, int to){
    int low = 0;
    int high = 0;
    // Health checks
    if(from < to){
        low = from;
        high = to + 1;
    } else {
        low = to;
        high = from + 1;
    }
    return (rand() % (high - low)) + low;
}

/*
  Utility function to print an array of integers
*/
void print_array(array_t *array){
    int i;
    printf("\n");
    for(i = 0; i < array->size; i++){
        printf("%d\t", array->array[i]);
    }
    printf("\n");
}

/*
  The modern version of the Fisher-Yates
  shuffle algorithm, introduced in 1964
  by Richard Durstenfeld. It does an
  in-place shuffle of the array.
*/
void shuffle(array_t *array){
    int i, j, temp;
    // Find a random index in the array and swap with current
    for(i = 0; i <= array->size - 2; i++){
        j = randint(i, array->size-1);
        temp = array->array[i];
        array->array[i] = array->array[j];
        array->array[j] = temp;
    }
}

/*
  Function to find the largest sequential
  part of an array, including the index where it starts.
*/
array_t* find_largest_sub_array(array_t* array, int* sub_array_size, int* sub_array_start){
    int cur_length = 1;
    int i;
    *sub_array_size = 1;
    *sub_array_start = 0;
    // Traverse from second index
    for(i = 1; i < array->size; i++){
        if (array->array[i] > array->array[i-1]){
            cur_length++;
        } else {
            // Update if we found new max
            if (*sub_array_size < cur_length){
                *sub_array_size = cur_length;
                *sub_array_start = i - *sub_array_size;
            }
            // Reset length for next check
            cur_length = 1;
        }
    }
    // Check the last length
    if (*sub_array_size < cur_length){
        *sub_array_size = cur_length;
        *sub_array_start = i - *sub_array_size;
    }
    // Return the newfound array
    array_t* sub_array = new_array(*sub_array_size);
    for(i = 0; i < sub_array->size; i++){
        sub_array->array[i] = array->array[*sub_array_start + i];
    }
    return sub_array;
}

/*
  Function to remove the sub array and return the remaining one.
*/
array_t* get_remaining_array(array_t* array, int sub_size, int sub_start){
    array_t* new = new_array(array->size - sub_size);
    int i = 0;
    int n;
    for(n = 0; n < new->size; n++){
        if(i == sub_start){
            i += sub_size;
        }
        new->array[n] = array->array[i];
        i++;
    }
    dealloc_array(array);
    return new;
}

/*
  Function to merge two sorted arrays and return
  the resulting array.
*/
array_t* merge_sorted_arrays(array_t* a, array_t* b){
    // Make space for the combined arrays
    array_t* merged = new_array(a->size + b->size);

    // Loop over both and insert smallest all the time.
    int i = 0;
    int j = 0;
    int k = 0;

    while((i < a->size) && (j < b->size)){
        if (a->array[i] < b->array[j]){
            merged->array[k++] = a->array[i++];
        } else {
            merged->array[k++] = b->array[j++];
        }
    }
    // Insert whatever remains.
    while(i < a->size){
        merged->array[k++] = a->array[i++];
    }
    while(j < b->size){
        merged->array[k++] = b->array[j++];
    }
    dealloc_array(a);
    return merged;
}

/*
  Yahtzee-sort algorithm. 
*/
array_t* yahtzee_sort(array_t* remaining){
    int start_size = remaining->size;
    int cur_size = 0;
    array_t* result = new_array(0);
    int sub_size = 0;
    int sub_start = 0;
    array_t* sub;
    do{
        sub = find_largest_sub_array(remaining, &sub_size, &sub_start);
        remaining = get_remaining_array(remaining, sub_size, sub_start);
        // Only shuffle when we can't find large enough runs
        if(sub_size < MIN_SUB_ARRAY || remaining->size < (MIN_SUB_ARRAY * 3)){
            shuffle(remaining);
        }
        result = merge_sorted_arrays(result, sub);
        cur_size = result->size;
        dealloc_array(sub);
    } while(cur_size < start_size);

    dealloc_array(remaining);
    return result;
}

int main(int argc, char const *argv[])
{
    int size;
    if(argc != 2){
        printf("Usage:\n./yahtzee <size of array>\n");
        return 0;
    } else {
        size = (int)strtoul(argv[1], NULL, 10);
    }

    // Allocate space and populate the initial array with random int.
    array_t* original_array = new_array(size);
    srand((unsigned int)time(NULL));
    int i;
    for(i = 0; i < original_array->size; i++){
        original_array->array[i] = randint(0, original_array->size - 1);
    }

    //printf("original array:");
    //print_array(original_array);

    array_t* result = yahtzee_sort(original_array);

    //printf("sorted array:");
    //print_array(result);

    // Cleanup
    dealloc_array(result);
    return 1;
}