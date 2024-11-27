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


int main() {
    return 0;
}