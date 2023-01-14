#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

// Node structure for building the Huffman tree
class Node {
    public:
        char data;
        int freq;
        Node* left;
        Node* right;

        Node(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}

        Node(char data, int freq, Node* left, Node* right) : data(data), freq(freq), left(left), right(right) {}
};

// Function to build the Huffman tree
Node* buildHuffmanTree(unordered_map<char, int> freq) {
    auto compare = [](Node* left, Node* right) {
        return left->freq > right->freq;
    };
    priority_queue<Node*, vector<Node*>, decltype(compare)> minHeap(compare);

    // Insert all characters of the frequency map into the min heap
    for (auto it = freq.begin(); it != freq.end(); it++) {
    minHeap.push(new Node(it->first, it->second));
    }

    // Build the Huffman tree
    while (minHeap.size() > 1) {
        // Extract the two nodes with the lowest frequency
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with these two nodes as children
        // and the frequency equal to the sum of the two nodes' frequencies
        int sum = left->freq + right->freq;
        minHeap.push(new Node('\0', sum, left, right));
    }

    return minHeap.top();
}

// Function to decode the encoded message
void decode(Node* root, string encodedMessage, string& decodedMessage) {
    Node* current = root;
    for (char ch : encodedMessage) {
        current = (ch == '0') ? current->left : current->right;
        if (!current->left && !current->right) {
            decodedMessage += current->data;
            current = root;
        }
    }
}

int main() {
    unordered_map<char, int> freq;
    ifstream encodedFile("compressed_message.txt");
    string encodedMessage;

    // Reading encoded message from file and buliding the map simenteneously 
    if (encodedFile.is_open()) {
        char ch;
        while(encodedFile >> ch){
            freq[ch]++;
            encodedMessage += ch;
        }
        encodedFile.close();
    } else {
        cout << "Error opening file" << endl;
        return 1;
    }

    Node* root = buildHuffmanTree(freq);

    string decodedMessage;
    decode(root, encodedMessage, decodedMessage);

    cout << "Decoded message: " << decodedMessage << endl;

    return 0;
}