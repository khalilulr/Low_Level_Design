#include <bits/stdc++.h>
using namespace std;

/*
    Generic Priority Queue / Heap

    By default:
        Heap<int>              -> Max Heap

    Min Heap:
        Heap<int, greater<int>>

    Supports:
        int
        pair<int, int>
        pair<string, int>
        tuple<int, int, int>
        custom structs
*/

template <typename T, typename Compare = less<T>>
class Heap {
private:
    vector<T> data;
    Compare comp;

    int parent(int index) const {
        return (index - 1) / 2;
    }

    int leftChild(int index) const {
        return 2 * index + 1;
    }

    int rightChild(int index) const {
        return 2 * index + 2;
    }

    void upHeapify(int index) {
        while (index > 0) {
            int parentIndex = parent(index);

            // If parent already has higher priority, stop.
            if (!comp(data[parentIndex], data[index]))
                break;

            swap(data[parentIndex], data[index]);

            index = parentIndex;
        }
    }

    void downHeapify(int index) {
        int n = data.size();

        while (true) {
            int bestIndex = index;

            int left = leftChild(index);
            int right = rightChild(index);

            // Compare left child with current best
            if (left < n && comp(data[bestIndex], data[left])) {
                bestIndex = left;
            }

            // Compare right child with current best
            if (right < n && comp(data[bestIndex], data[right])) {
                bestIndex = right;
            }

            // Current node already has highest priority
            if (bestIndex == index)
                break;

            swap(data[index], data[bestIndex]);

            index = bestIndex;
        }
    }

public:
    // Constructor
    Heap() = default;

    explicit Heap(const Compare& comparator)
        : comp(comparator) {}

    // Insert element
    void push(const T& value) {
        data.push_back(value);
        upHeapify(static_cast<int>(data.size()) - 1);
    }

    // Move element into heap
    void push(T&& value) {
        data.push_back(std::move(value));
        upHeapify(static_cast<int>(data.size()) - 1);
    }

    // Remove highest-priority element
    void pop() {
        if (empty()) {
            throw runtime_error("Heap is empty");
        }

        swap(data[0], data.back());

        data.pop_back();

        if (!data.empty()) {
            downHeapify(0);
        }
    }

    // Return highest-priority element
    const T& top() const {
        if (empty()) {
            throw runtime_error("Heap is empty");
        }

        return data[0];
    }

    // Check if empty
    bool empty() const {
        return data.empty();
    }

    // Number of elements
    size_t size() const {
        return data.size();
    }
};


// --------------------------------------------------
// Custom Comparator Example
// --------------------------------------------------

struct Job {
    string name;
    int priority;
    int duration;
};

struct JobComparator {
    bool operator()(const Job& a, const Job& b) const {
        return a.priority < b.priority;
    }
};


// --------------------------------------------------
// Main
// --------------------------------------------------

int main() {

    // ==================================================
    // 1. MAX HEAP
    // ==================================================

    cout << "----- MAX HEAP -----\n";

    Heap<int> maxHeap;

    maxHeap.push(4);
    maxHeap.push(5);
    maxHeap.push(10);
    maxHeap.push(2);
    maxHeap.push(20);

    cout << "Top: " << maxHeap.top() << '\n';

    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }

    cout << "\n\n";


    // ==================================================
    // 2. MIN HEAP
    // ==================================================

    cout << "----- MIN HEAP -----\n";

    Heap<int, greater<int>> minHeap;

    minHeap.push(4);
    minHeap.push(5);
    minHeap.push(1);
    minHeap.push(10);
    minHeap.push(2);

    cout << "Top: " << minHeap.top() << '\n';

    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }

    cout << "\n\n";


    // ==================================================
    // 3. PAIR
    // ==================================================

    cout << "----- PAIR -----\n";

    Heap<pair<int, int>, greater<pair<int, int>>> pairHeap;

    pairHeap.push({10, 1});
    pairHeap.push({3, 5});
    pairHeap.push({7, 2});
    pairHeap.push({1, 9});

    while (!pairHeap.empty()) {
        auto [distance, node] = pairHeap.top();

        cout << "distance = "
             << distance
             << ", node = "
             << node
             << '\n';

        pairHeap.pop();
    }

    cout << '\n';


    // ==================================================
    // 4. PAIR<string, int>
    // ==================================================

    cout << "----- PAIR<string, int> -----\n";

    Heap<pair<string, int>> stringPairHeap;

    stringPairHeap.push({"Alice", 10});
    stringPairHeap.push({"Bob", 20});
    stringPairHeap.push({"Charlie", 15});

    while (!stringPairHeap.empty()) {
        auto [name, score] = stringPairHeap.top();

        cout << name << " " << score << '\n';

        stringPairHeap.pop();
    }

    cout << '\n';


    // ==================================================
    // 5. TUPLE
    // ==================================================

    cout << "----- TUPLE -----\n";

    Heap<tuple<int, int, int>, greater<tuple<int, int, int>>> tupleHeap;

    tupleHeap.push({3, 5, 10});
    tupleHeap.push({1, 8, 20});
    tupleHeap.push({2, 2, 30});
    tupleHeap.push({1, 3, 40});

    while (!tupleHeap.empty()) {

        auto [a, b, c] = tupleHeap.top();

        cout << a << " "
             << b << " "
             << c << '\n';

        tupleHeap.pop();
    }

    cout << '\n';


    // ==================================================
    // 6. CUSTOM STRUCT
    // ==================================================

    cout << "----- CUSTOM STRUCT -----\n";

    Heap<Job, JobComparator> jobHeap;

    jobHeap.push({"Job A", 5, 10});
    jobHeap.push({"Job B", 10, 3});
    jobHeap.push({"Job C", 7, 8});
    jobHeap.push({"Job D", 20, 2});

    while (!jobHeap.empty()) {

        const Job& job = jobHeap.top();

        cout << "Name: "
             << job.name
             << ", Priority: "
             << job.priority
             << ", Duration: "
             << job.duration
             << '\n';

        jobHeap.pop();
    }

    return 0;
}