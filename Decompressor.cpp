#include <iostream>
#include <algorithm>
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
string decode(Node* root, string encodedMessage) {
    Node* current = root;
    string decodedMessage = "";
    for (char ch : encodedMessage) {
        current = (ch == '0') ? current->left : current->right;
        if (!current->left && !current->right) {
            decodedMessage += current->data;
            current = root;
        }
    }
    reverse(decodedMessage.begin(), decodedMessage.end());
    return decodedMessage;
}

int main() {
    unordered_map<char, int> freq;
    // Reading encoded message from file
    string fileName = "compressed_message.txt";
    ifstream file(fileName);
    string encodedMessage, line;

    // Extracting the hashmap from the beginning of the file
    if (file.is_open()) {
        getline(file, line);
        size_t pos = 0, next;
        while ((next = line.find("|", pos)) != string::npos) {
            size_t colon = line.find(":", pos);
            char ch = line[pos];
            freq[line[pos]] = stoi(line.substr(colon + 1, next - colon - 1));
            pos = next + 1;
        }
        // Reading the rest of the file (the encoded message)
        while (getline(file, line)) {
            encodedMessage += line;
        }
        file.close();
    } else {
        cout << "Error opening file" << endl;
        return 1;
    }

    for(auto x : freq) cout<<x.first <<" "<<x.second<<endl;

    Node* root = buildHuffmanTree(freq);

    string decodedMessage = decode(root, encodedMessage);

    cout << "Decoded message: " << decodedMessage << endl;

    return 0;
}