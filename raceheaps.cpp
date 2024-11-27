#include <iostream>  // Include input/output stream for console operations
#include <vector>    // Include vector to store dynamic arrays (heap)
#include <string>    // Include string for car names
#include <iomanip>   // Include for formatted output
using namespace std; // Use standard namespace to avoid prefixing std::

// Structure for Car and Lap Time
struct Car {
    string name;    // Name of the car
    int lapTime;    // Lap time in seconds
};

// Helper function to print heap as rankings
void visualizeRankings(const vector<Car>& heap) {
    cout << "\nLap Time Rankings:" << endl;
    // Loop through the heap vector and print each car's name and lap time
    for (size_t i = 0; i < heap.size(); ++i) {
        cout << i + 1 << ". " << heap[i].name << " - " << heap[i].lapTime << "s" << endl;
    }
    cout << endl;
}

// Max-Heapify to maintain the max-heap property
void heapifyMax(vector<Car>& heap, int n, int i) {
    int largest = i;            // Assume the current index is the largest
    int left = 2 * i + 1;       // Left child index
    int right = 2 * i + 2;      // Right child index

    // If left child is larger than root
    if (left < n && heap[left].lapTime > heap[largest].lapTime)
        largest = left;
    
    // If right child is larger than largest so far
    if (right < n && heap[right].lapTime > heap[largest].lapTime)
        largest = right;

    // If largest is not root, swap and heapify again
    if (largest != i) {
        swap(heap[i], heap[largest]);
        heapifyMax(heap, n, largest); // Recursively heapify the affected subtree
    }
}

// Min-Heapify to maintain the min-heap property
void heapifyMin(vector<Car>& heap, int n, int i) {
    int smallest = i;           // Assume the current index is the smallest
    int left = 2 * i + 1;       // Left child index
    int right = 2 * i + 2;      // Right child index

    // If left child is smaller than root
    if (left < n && heap[left].lapTime < heap[smallest].lapTime)
        smallest = left;
    
    // If right child is smaller than smallest so far
    if (right < n && heap[right].lapTime < heap[smallest].lapTime)
        smallest = right;

    // If smallest is not root, swap and heapify again
    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heapifyMin(heap, n, smallest); // Recursively heapify the affected subtree
    }
}

// Insert new lap time into the heap
void insertLapTime(vector<Car>& heap, Car car, bool isMinHeap) {
    heap.push_back(car);  // Add car to the end of the heap
    int i = heap.size() - 1;  // Get the index of the newly added car

    // Percolate the new car up to maintain heap property
    while (i > 0) {
        int parent = (i - 1) / 2;  // Find the index of the parent
        // If it's a Min-Heap and the current car's lap time is less than the parent's
        if (isMinHeap && heap[i].lapTime < heap[parent].lapTime) {
            swap(heap[i], heap[parent]);  // Swap the car with the parent
            i = parent;  // Move the index to the parent
        }
        // If it's a Max-Heap and the current car's lap time is greater than the parent's
        else if (!isMinHeap && heap[i].lapTime > heap[parent].lapTime) {
            swap(heap[i], heap[parent]);  // Swap the car with the parent
            i = parent;  // Move the index to the parent
        } else {
            break;  // If the heap property is satisfied, break the loop
        }
    }
}

// Remove the car with best or worst lap time from the heap
void removeTopCar(vector<Car>& heap, bool isMinHeap) {
    if (heap.empty()) {  // If the heap is empty, there's nothing to remove
        cout << "Heap is empty!" << endl;
        return;
    }

    swap(heap[0], heap[heap.size() - 1]);  // Swap the root with the last element
    heap.pop_back();  // Remove the last element (formerly the root)

 
    if (isMinHeap)
        heapifyMin(heap, heap.size(), 0);  // Min-Heap: heapify from the root
    else
        heapifyMax(heap, heap.size(), 0);  // Max-Heap: heapify from the root
}

// Convert between min-heap and max-heap
void convertHeap(vector<Car>& heap, bool toMinHeap) {
    // Start from the last non-leaf node and apply heapify
    for (int i = heap.size() / 2 - 1; i >= 0; --i) {
        // If converting to Min-Heap, apply Min-Heapify
        if (toMinHeap)
            heapifyMin(heap, heap.size(), i);
        // If converting to Max-Heap, apply Max-Heapify
        else
            heapifyMax(heap, heap.size(), i);
    }
}

// Main function - Executes the heap operations and visualizes results
int main() {
    vector<Car> heap;           
    bool isMinHeap = true;      

    // Add sample lap times (insert cars into the heap)
    insertLapTime(heap, {"Car #5 - Lightning", 95}, isMinHeap);
    insertLapTime(heap, {"Car #3 - Thunderbolt", 100}, isMinHeap);
    insertLapTime(heap, {"Car #9 - Road Blazer", 89}, isMinHeap);

    // Visualize rankings after inserting lap times
    cout << "Heap after adding lap times:" << endl;
    visualizeRankings(heap);


    cout << "Removing fastest car..." << endl;
    removeTopCar(heap, isMinHeap);
    visualizeRankings(heap);

    // Convert the heap to Max-Heap for slowest lap times
    cout << "Converting to Max-Heap for slowest lap times..." << endl;
    isMinHeap = false;  
    convertHeap(heap, isMinHeap);  // Convert the heap to Max-Heap
    visualizeRankings(heap); 

    return 0; 
}
