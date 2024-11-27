#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Structure for Car and Lap Time
struct Car {
    string name;
    int lapTime; // Time in seconds
};

// Helper function to print heap as rankings
void visualizeRankings(const vector<Car>& heap) {
    cout << "\nLap Time Rankings:" << endl;
    for (size_t i = 0; i < heap.size(); ++i) {
        cout << i + 1 << ". " << heap[i].name << " - " << heap[i].lapTime << "s" << endl;
    }
    cout << endl;
}

// Max-Heapify
void heapifyMax(vector<Car>& heap, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].lapTime > heap[largest].lapTime)
        largest = left;
    if (right < n && heap[right].lapTime > heap[largest].lapTime)
        largest = right;

    if (largest != i) {
        swap(heap[i], heap[largest]);
        heapifyMax(heap, n, largest);
    }
}

// Min-Heapify
void heapifyMin(vector<Car>& heap, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].lapTime < heap[smallest].lapTime)
        smallest = left;
    if (right < n && heap[right].lapTime < heap[smallest].lapTime)
        smallest = right;

    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heapifyMin(heap, n, smallest);
    }
}

// Insert new lap time
void insertLapTime(vector<Car>& heap, Car car, bool isMinHeap) {
    heap.push_back(car);
    int i = heap.size() - 1;

    while (i > 0) {
        int parent = (i - 1) / 2;
        if (isMinHeap && heap[i].lapTime < heap[parent].lapTime) {
            swap(heap[i], heap[parent]);
            i = parent;
        } else if (!isMinHeap && heap[i].lapTime > heap[parent].lapTime) {
            swap(heap[i], heap[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

// Remove car with best or worst lap time
void removeTopCar(vector<Car>& heap, bool isMinHeap) {
    if (heap.empty()) {
        cout << "Heap is empty!" << endl;
        return;
    }

    swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();

    if (isMinHeap)
        heapifyMin(heap, heap.size(), 0);
    else
        heapifyMax(heap, heap.size(), 0);
}

// Convert between min-heap and max-heap
void convertHeap(vector<Car>& heap, bool toMinHeap) {
    for (int i = heap.size() / 2 - 1; i >= 0; --i) {
        if (toMinHeap)
            heapifyMin(heap, heap.size(), i);
        else
            heapifyMax(heap, heap.size(), i);
    }
}

// Main function
int main() {
    vector<Car> heap;
    bool isMinHeap = true; // Start with min-heap for fastest lap times

    // Add sample lap times
    insertLapTime(heap, {"Car #5 - Lightning", 95}, isMinHeap);
    insertLapTime(heap, {"Car #3 - Thunderbolt", 100}, isMinHeap);
    insertLapTime(heap, {"Car #9 - Road Blazer", 89}, isMinHeap);

    cout << "Heap after adding lap times:" << endl;
    visualizeRankings(heap);

    cout << "Removing fastest car..." << endl;
    removeTopCar(heap, isMinHeap);
    visualizeRankings(heap);

    cout << "Converting to Max-Heap for slowest lap times..." << endl;
    isMinHeap = false;
    convertHeap(heap, isMinHeap);
    visualizeRankings(heap);

    return 0;
}
