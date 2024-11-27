#include <iostream>
#include <vector>
#include <queue>
#include <memory>  // For std::make_unique

using namespace std;

// Structure for tree node
struct Node {
    char character;
    int freq;
    Node *left, *right;

    Node(char c, int f) : character(c), freq(f), left(nullptr), right(nullptr) {}
    
    // Overloading the comparison operator to use this node in a priority_queue
    bool operator>(const Node& other) const {
        return freq > other.freq;
    }
};

// Function to create and build a Min-Heap using priority_queue
priority_queue<Node, vector<Node>, greater<Node>> createAndBuildMinHeap(char arr[], int freq[], int unique_size) {
    priority_queue<Node, vector<Node>, greater<Node>> minHeap;

    // Add nodes to the min heap (priority_queue)
    for (int i = 0; i < unique_size; ++i) {
        minHeap.push(Node(arr[i], freq[i]));
    }

    return minHeap;
}

int main() {
    return 0;
}