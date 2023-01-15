#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

// Node of Huffman tree
class Node {
    public:
    char ch;
    int freq;
    Node *left, *right;

    Node(char ch, int freq, Node* left = nullptr, Node* right = nullptr) : ch(ch), freq(freq), left(left), right(right) { }

    bool operator<(const Node &other) const {
        return freq > other.freq;
    }
};

// Build Huffman tree
void buildTree(string text, Node* &root) {
    map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    priority_queue<Node> q;
    for(auto x : freq) {
    q.push(Node(x.first, x.second));
    }

    while (q.size() > 1) {
        Node *left = new Node(q.top());
        q.pop();
        Node *right = new Node(q.top());
        q.pop();

        int sum = left->freq + right->freq;
        q.push(Node('\0', sum, left, right));
    }

    root = new Node(q.top());
    q.pop();
}

// Generate Huffman codes
void generateCodes(Node* root, string code, map<char, string> &codes) {
    if (!root) {
        return;
    }
    if (root->ch != '\0') {
        codes[root->ch] = code;
    }
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

// Compress text
string compress(string text, map<char, string> codes) {
    string compressed;
    for (char ch : text) {
        compressed += codes[ch];
    }
    return compressed;
}

int main() {
    string text, fileName;

    cout << "Enter text to compress: ";
    getline(cin, text);

    fileName = "compressed_message.txt";

    Node* root = nullptr;
    buildTree(text, root);

    map<char, string> codes;
    generateCodes(root, "", codes);

    string compressed = compress(text, codes);
    ofstream outFile(fileName);
    for(auto x : codes) outFile << x.first << ':' << x.second << '|';
    outFile << "\n";
    outFile << compressed;
    outFile.close();

    return 0;
}