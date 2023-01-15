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

// Function to decode the encoded message
string decompress(string encodedMessage, unordered_map<char, string> huffmanCodes) {
    string decodedMessage;
    string code;
    for (char bit : encodedMessage) {
        code += bit;
        for (auto it = huffmanCodes.begin(); it != huffmanCodes.end(); it++) {
            if (it->second == code) {
                decodedMessage += it->first;
                code.clear();
                break;
            }
        }
    }
    return decodedMessage;
}

int main() {
    unordered_map<char, string> freq;
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
            freq[line[pos]] = (line.substr(colon + 1, next - colon - 1));
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

    string decodedMessage = decompress(encodedMessage, freq);

    cout << "Decoded message: " << decodedMessage << endl;

    return 0;
}