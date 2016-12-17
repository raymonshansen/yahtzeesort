#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


/*
  Utility function to print an array of integers
*/
void print_array(int *array, int N){
	int i;
	printf("\n");
	for(i = 0; i < N; i++){
		printf("%d\t", array[i]);
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
void shuffle(int *array, int N){
	int i, j, temp;
	for(i = 0; i <= N - 2; i++){
		j = randint(i, N-1);
		// Swap the two values
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

/*
  Function to find the largest sequential 
  part of an array. This is then extracted
  and returned. The remaining array is
  rewritten to omit the missing part. Takes
  the array and its size(N) as input.
*/
void extract_sequence(int *array, int N){
	int i;
	int greatest = 1;
	int size = 1;
	int j = 0; 
	int startindex = 0;
	// Iterate through the array
	for(i = 0; i < (N-greatest); i++){
		size = 1;
		j = i;
		// Check for increasing consequtive values, or falling off
		while((j+1 < N) && (array[j+1] >= array[j])){
			size++;
			j++;
		}
		// If new greatest conseq. sequence was found,
		// store the size and starting position
		if(size >= greatest){
			startindex = i;
			greatest = size;
		}
	}
	// Extract the wanted sub-array
	printf("Startindex: %d Size of subarray: %d\n",startindex, greatest);
	int subarray[greatest];
	int k = 0;
	int l = startindex;
	while(k < greatest){
		subarray[k] = array[l];
		k++;
		l++;
	}
	print_array(subarray, greatest);

	// Reassemble the remaining
	int *newarray = malloc(sizeof(int)*(N-greatest));
	// Fill before
	for(i = 0; i < startindex; i++){
		newarray[i] = array[i];
	}
	// Fill after
	i = startindex + greatest;
	j = startindex;
	while(i < N){
		newarray[j] = array[i];
		j++;
		i++;
	}
	print_array(newarray, N-greatest);

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
	int size = atoi(argv[1]);
	printf("Filling array of %d with random numbers\n", size);
	int *array = malloc(sizeof(int)*size);
	// Populate the array with random int.
	int i;
	// Seed the generator with time
	srand((unsigned int)time(NULL));
	printf("Original array\n");
	for(i = 0; i < size; i++){
		array[i] = randint(0, size);
	}
	print_array(array, size);
	shuffle(array, size);
	print_array(array, size);
	// Find the largest sequential part of the array
	extract_sequence(array, size);
	return 0;
}