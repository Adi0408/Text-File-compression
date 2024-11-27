#include <iostream>
#include <vector>
#include <queue>
#include <memory>  // For a smart pointer make_unique

using namespace std;

// Structure for tree node
struct Node {
    char character;
    int freq;
    Node *left, *right;

    Node(char c, int f) : character(c), freq(f), left(nullptr), right(nullptr) {}
    
    // Overloading the comparison operator to use this node in a priority_queue
    // Comparator for the priority queue
};

struct CompareNode {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq; // Min-Heap (smallest freq at top)
    }
};

// for implementation of priority queue and its working in depth refer gfg

// function for huffman tree , directly using priority queue
Node* huffmanTree(char arr[], int freq[], int unique_size) {
    // priority queue - min-heap 
    priority_queue<Node, vector<Node*>, CompareNode> minHeap;

    // inserting elements into the min heap
    for (int i = 0; i < unique_size; i++) {
        minHeap.push(new Node(arr[i], freq[i]));
    }

    while (minHeap.size() > 1) {
        // taking first two elements at a time
        Node* leftNode = minHeap.top();
        minHeap.pop();
        Node* rightNode = minHeap.top();
        minHeap.pop();

        // Create a new internal node
        Node* parentNode = new Node('$', leftNode->freq + rightNode->freq);
        parentNode->left = leftNode;
        parentNode->right = rightNode;

        // Push the parent node back into the priority queue
        minHeap.push(parentNode);
    }

    // root of the Huffman Tree
    Node* root = minHeap.top();
    return root;
}


int main() {
    return 0;
}