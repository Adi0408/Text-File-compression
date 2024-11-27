#include <iostream>
#include <vector>
#include <queue>
#include <memory>  // For a smart pointer make_unique
#include <fstream>
#include <unordered_map> 

using namespace std;

// for implementation of priority queue and its working in depth refer gfg

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


// structure for adding initial data into the txt file i.e char-len-dec code
struct Code {
    char k;
    char len;
    vector<int> codeArr;
};


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


// func to check leaf node reached or not
bool isLeaf(const Node* node) {
    if (node->left == nullptr && node->right == nullptr)
        return true;
    else 
        return false;
}

// func to convert bin to dec
int convertBintoDec (const vector<int>& binary) {
    int decimal = 0;
    for (int i = 0; i < binary.size(); i++) {
        decimal = (decimal << 1) | binary[i];
    }

    return decimal;
}

// func to write char-len-dec code to the file
void huffmandicttofile (ofstream& outputfile, Node* root, vector<int>& codePath, unordered_map<char, Code>& codeBook){
    if (root == NULL) return;

    // traverse left
    if (root -> left) {
        codePath.push_back(0);
        huffmandicttofile(outputfile, root->left, codePath, codeBook);
        codePath.pop_back(); 
    }

    // right node 
    if (root -> right) {
        codePath.push_back(1);
        huffmandicttofile(outputfile, root -> right, codePath, codeBook);
        codePath.pop_back();
    }

    // we reach leaf node and append that to the file
    if (isLeaf(root)) {
        Code data;
        data.k = root->character;
        data.len = codePath.size();
        data.codeArr = codePath;

        codeBook[data.k] = data; 
        // convert bin to dec
        int decCode = convertBintoDec(codePath);

        // write char to file
        outputfile << data.k << " ";

        // write codeword length
        outputfile << data.len << " ";

        // write dec form of codeword
        outputfile << decCode << "\n";

    }
}


// Function to compress the file using Huffman codes
void compressFile(const string& inputFile, const string& outputFile, const unordered_map<char, Code>& codebook) {
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);

    if (!inFile.is_open()) {
        cerr << "Error opening input file!" << endl;
        return;
    }

    if (!outFile.is_open()) {
        cerr << "Error opening output file!" << endl;
        return;
    }

    unsigned char buffer = 0;
    int bitCount = 0;

    char ch;
    while (inFile.get(ch)) {
        const Code& data = codebook.at(ch);  // Get the Huffman code for the character

        // Iterate through the Huffman code for this character
        for (int i = 0; i < data.len; ++i) {
            if (bitCount < 8) {
                buffer <<= 1;  // Shift buffer to make space for next bit
                buffer |= data.codeArr[i];  // Add the next bit from the code
                ++bitCount;
            } else {
                // Write out the buffer to file once it is full (8 bits)
                outFile.put(buffer);
                buffer = 0;  // Reset buffer
                bitCount = 0;

                // Add the bit from the code to the buffer
                buffer |= data.codeArr[i];
                ++bitCount;
            }
        }
    }

    // Write any remaining bits in the buffer
    if (bitCount > 0) {
        buffer <<= (8 - bitCount);  // Shift out remaining bits
        outFile.put(buffer);
    }

    inFile.close();
    outFile.close();
}

int main() {
    return 0;
}