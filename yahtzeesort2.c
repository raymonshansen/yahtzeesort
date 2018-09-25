#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


// Struct to hold an array and its size
typedef struct numarray array_t;
struct numarray {
	int *array;
	int size;
};

/*
  Allocate a new numbered array.
*/
array_t* new_array(int size){
    array_t* new = malloc(sizeof(array_t));
    new->size = size;
    new->array = calloc(size, sizeof(int));
    return new;
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
void shuffle(container_t *array){
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
array_t* get_remaing_array(array_t* array, int sub_size, int sub_start){
    array_t* new = new_array(array->size - sub_size);
    int i, n;
    // Hackety, hack!
    for(i = 0, n = 0; i < array->size; i++, n++){
        if(i == sub_start){
            i += sub_size;
        }
        new->array[n] = array->array[i];
    }
    return new;
}

/*
  Function to merge two sorted arrays and return
  the resulting array.
*/
array_t* merge_sorted_arrays(array_t* first, array_t* second){
    // Make space for the combined arrays
    third = new_array(first->size + second->size);
    
    // Loop over both and insert smallest all the time.
    int first_cur = 0;
    int second_cur = 0;
    int third_cur = 0;

    while((first_cur < first->size) && (second_cur < second->size)){
        if(first->array[first_cur] < second->array[second_cur]){
            third->array[third_cur++] = first->array[first_cur++];
        } else {
            third->array[third_cur++] = second->array[second_cur++];
        }
        // Insert whatever remains.
        while(first_cur < first->size){
            third->array[third_cur++] = first->array[first_cur++];
        }
        while(second_cur < second->size){
            third->array[third_cur++] = second->array[second_cur++];
        }
    }
    return third;
}

/*
  Yahtzee-sort algorithm. 
*/
array_t* yahtzee_sort(array_t* original){
    array_t* result = new_array(original->size);
    int* sub_size = calloc(1, sizeof(int));
    int* sub_start = calloc(1, sizeof(int));
    array_t* sub = find_largest_sub_array(original, *sub_size, *sub_start);
    array_t* remaining = get_remaing_array(original, sub_size, sub_start);
    while(sub->size != 0){
        // Put together...
    }
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

    printf("original array:");
    print_array(original_array);
    int* sub_size = calloc(1, sizeof(int));
    int* sub_start = calloc(1, sizeof(int));
    array_t* sub = find_largest_sub_array(original_array, sub_size, sub_start);
    printf("sub_array_size: %d, sub_array_start: %d\n", *sub_size, *sub_start);
    printf("sub_array:");
    print_array(sub);
    array_t* remaining = get_remaing_array(original_array, *sub_size, *sub_start);
    printf("remaining:");
    print_array(remaining);

    // Cleanup
    free(original_array);
    return 0;
}