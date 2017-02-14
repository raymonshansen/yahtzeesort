#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Struct to hold an array and its size
typedef struct container container_t;
struct container {
	int *array;
	int size;
};

/*
  Utility function to print an array of integers
*/
void print_array(container_t *array){
	int i;
	printf("\n");
	for(i = 0; i < array->size; i++){
		printf("%d\t", array->array[i]);
	}
	printf("\n");
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
  The modern version of the Fisher-Yates 
  shuffle algorithm, introduced in 1964 
  by Richard Durstenfeld. It does an 
  in-place shuffle of the array.
*/
void shuffle(container_t *array){
	int i, j, temp;
	for(i = 0; i <= array->size - 2; i++){
		// find a random index in the array...
		j = randint(i, array->size-1);
		// ...and swap this with the current index
		temp = array->array[i];
		array->array[i] = array->array[j];
		array->array[j] = temp;
	}
}

/*
  Function to find the largest sequential 
  part of an array. This is then extracted
  and returned. The remaining array is
  rewritten to omit the missing part. Takes
  the array and its size(N) as input.
*/
void extract_sequence(container_t *array){
	// Declaring the conters
	int i;
	int greatest = 1;
	int size = 1;
	int j = 0; 
	int startindex = 0;
	// Iterate through the array.
	for(i = 0; i < (array->size-greatest); i++){
		size = 1;
		j = i;
		// Check for increasing consequtive values, 
		// or falling off the edge of the array.
		while((j+1 < array->size) && (array->array[j+1] >= array->array[j])){
			size++;
			j++;
		}
		// If new greatest consequtive sequence was found,
		// store the size and starting position
		if(size >= greatest){
			startindex = i;
			greatest = size;
		}
	}
	// Extract the wanted sub-array
	printf("Startindex: %d Size of subarray: %d\n",startindex, greatest);
	container_t *subarray = malloc(sizeof(container_t));
	subarray->array = malloc(sizeof(int)*greatest);
	subarray->size = greatest;
	int k = 0;
	int l = startindex;
	while(k < subarray->size){
		subarray->array[k] = array->array[l];
		k++;
		l++;
	}
	print_array(subarray);

	// Reassemble the remaining
	container_t *newarray = malloc(sizeof(container_t));
	newarray->array = malloc(sizeof(int)*(array->size-greatest));
	newarray->size = array->size-greatest;
	// Fill before
	for(i = 0; i < startindex; i++){
		newarray->array[i] = array->array[i];
	}
	// Fill after
	i = startindex + greatest;
	j = startindex;
	while(i < array->size){
		newarray->array[j] = array->array[i];
		j++;
		i++;
	}
	print_array(newarray);

}

/*
  A sorting algorithm based on 
  yahtzee. It randomly shuffles
  the array and extracts the largest 
  sequential part and merges that into the 
  finished array, then repeat until the 
  whole array is sorted.
*/
int main(int argc, char const *argv[])
{
	// Need the exact number of arguments
	if(argc != 2){
		printf("Usage:\nyahtzeesort <size of array>");
		return 1;
	}
	container_t *array = malloc(sizeof(container_t));
	array->size = atoi(argv[1]);
	printf("Filling array of %d with random numbers\n", array->size);
	array->array = malloc(sizeof(int)*array->size);
	// Seed the generator with time
	srand((unsigned int)time(NULL));
	// Populate the array with random int.
	int i;
	for(i = 0; i < array->size; i++){
		array->array[i] = randint(0, array->size);
	}
	printf("Original array\n");
	print_array(array);
	shuffle(array);
	print_array(array);
	// Find the largest sequential part of the array
	extract_sequence(array);
	return 0;
}