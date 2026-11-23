# Write a C++ program to sort the elements of an array using Randomized Quick Sort and report the number of comparisons.


#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int comparisons = 0;

// Partition function
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        comparisons++;

        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Randomized partition
int randomizedPartition(int arr[], int low, int high)
{
    int randomIndex = low + rand() % (high - low + 1);

    swap(arr[randomIndex], arr[high]);

    return partition(arr, low, high);
}

// Randomized Quick Sort
void randomizedQuickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex = randomizedPartition(arr, low, high);

        randomizedQuickSort(arr, low, pivotIndex - 1);
        randomizedQuickSort(arr, pivotIndex + 1, high);
    }
}

int main()
{
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n];

    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    srand(time(0));

    randomizedQuickSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\nNumber of comparisons: " << comparisons;

    return 0;
}
