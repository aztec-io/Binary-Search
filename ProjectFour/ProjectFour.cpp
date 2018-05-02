// ProjectFour.cpp : Defines the entry point for the console application.
//
// COSC-2425, Project 4
// ASM Procedure Linking with C++ for Binary Search comparison

#include <iostream>
#include <time.h>

using namespace std;

// Function prototype for selection sort and swap functions
void selectionSort(int array[], int size);
void swap(int &a, int &b);

// Function Prototype for binarySearch()
int binarySearch(int value, int array[], int size);

// Function Prototype for the assembly language version of binary search
extern "C" {
	int AsmBinarySearch(int n, int array[], int count);
}

int main()
{
	// Local Variables
	const int SIZE = 10000;
	const int LOOP_SIZE = 1000000;
	int numbers[SIZE];
	int value;  // Value entered by the user
	int index;	// The subscript value of the matching array element or -1

	// Declare the starting and ending clock time variables
	clock_t startTime, endTime;
	double duration;

	// Define the array elements. Values will range from 1 to 1000.
	for (int i = 0; i < SIZE; i++)
	{
		numbers[i] = (rand() % 1000) + 1;
	}

	// Prompt the user for a 3-digit number
	cout << "Enter a Positive 3-digit Number as the Search Value: ";
	cin >> value;
	cout << endl << "Please Be Patient. This may take several seconds . . ." << endl;

	// Validate the value entered by the user
	cout << endl << "Using a linear search." << endl;
	startTime = clock();
	for (int n = 0; n < LOOP_SIZE; n++)
	{
		index = -1;
		for (int i = 0; i < SIZE; i++) {
			if (value == numbers[i]) {
				index = i;
				break;
			}
		}
	}
	endTime = clock();

	// Calculate the duration.
	duration = (double)(endTime - startTime) / CLOCKS_PER_SEC;

	// Display the results of the Linear validation search
	if (index == -1) {
		cout << "The number you entered is Not Valid." << endl << endl;
	}
	else {
		cout << "The number you entered is Valid. ";
		cout << "It was found at subscript " << index << endl << endl;
	}
	cout << "   Elapsed time for the Linear Search was " << duration << " seconds." << endl << endl;

	// Sort the elements in the array
	selectionSort(numbers, SIZE);

	// Perform a Binary Search
	cout << endl << "Using the C++ Binary Search:" << endl;
	startTime = clock();
	for (int n = 0; n < LOOP_SIZE; n++) {
		index = binarySearch(value, numbers, SIZE);
	}
	endTime = clock();

	// Calculate the duration.
	duration = (double)(endTime - startTime) / CLOCKS_PER_SEC;

	// Display the results of the C++ validation search
	if (index == -1) {
		cout << "The number you entered is Not Valid." << endl << endl;
	}
	else {
		cout << "The number you entered is Valid. ";
		cout << "It was found at subscript " << index << endl << endl;
	}
	cout << "   Elapsed time for the C++ Binary Search was " << duration << " seconds." << endl << endl;

	// Invoke the Assembly Language version of the Binary Search Algorithm
	cout << "Using the Assembly Language Binary Search." << endl;
	startTime = clock();
	for (int n = 0; n < LOOP_SIZE; n++) {
		index = AsmBinarySearch(value, numbers, SIZE);
	}
	endTime = clock();

	// Calculate the duration.
	duration = (double)(endTime - startTime) / CLOCKS_PER_SEC;

	// Display the results of the Assembly Language validation search
	if (index == -1) {
		cout << "The number you entered is Not Valid." << endl << endl;
	}
	else {
		cout << "The number you entered is Valid. ";
		cout << "It was found at subscript " << index << endl << endl;
	}
	cout << "   Elapsed time for the ASM Binary Search was " << duration << " seconds." << endl << endl;

	return 0;
}

int binarySearch(int value, int array[], int size)
{
	// Declare and initialize the variable that will hold the subscript of the first element
	int first = 0;

	// Declare and initialize the variable that will hold the subscript of the last element
	int last = size - 1;

	// Declare the variable that will hold the subscript of the midpoint
	int middle;

	// Declare and initialize the variable that identifies the position of the search value
	int position = -1;

	// Initialize the Boolean flag that indicates whether or not the search value has been found
	bool found = false;

	while (!found && (first <= last))
	{
		// Calculate the subscript of the midpoint
		middle = (first + last) / 2;

		// Check to see if the search value is at the midpoint
		if (array[middle] == value) {
			found = true;
			position = middle;
		}
		else if (array[middle] > value) {  // Else, if the value is in the lower half
			last = middle - 1;
		}
		else {  // Else, the value is in the upper half
			first = middle + 1;
		}
	}  // end of while loop

	// Return the position (subscript value) of the element that
	// matched the search value, or -1 if the search value was not found.
	return position;
}

void selectionSort(int array[], int size)
{
	int minIndex;  // Subscript of smallest value in scanned area
	int minValue;  // Smallest value in the scanned area

	// The outer loop steps through all of the array elements,
	// except the last one. The startScan variable marks the
	// position where the sacn should begin.
	for (int startScan = 0; startScan < size - 1; startScan++)
	{
		// Assume the first element in the scannable area
		// is the smallest value.
		minIndex = startScan;
		minValue = array[startScan];

		// Scan the array, starting at the second element in the
		// scannable area, looking for the smallest value.
		for (int index = startScan + 1; index < size; index++)
		{
			if (array[index] < minValue)
			{
				minValue = array[index];
				minIndex = index;
			}
		}

		// Swap the element with the smallest value with the
		// first element in the scannable area.
		swap(array[minIndex], array[startScan]);
	}
}

void swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}