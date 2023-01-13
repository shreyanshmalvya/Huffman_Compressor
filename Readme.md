<p align="center">
  <img src="">
</p>

<h1 align="center">Huffman Compressor</h1>

<!-- <p align="center">
  <a href="https://github.com/shreyanshmalvya/Huffman_Coding/blob/master/LICENSE">
    <img src="https://img.shields.io/github/license/shreyanshmalvya/Huffman_Coding"
      alt="MIT License" />
  </a>
  <a href="https://www.linkedin.com/in/ersel-hengirmen/">
    <img src="https://img.shields.io/badge/-LinkedIn-black.svg?style=plastic-square&logo=linkedin&colorB=555"
      alt="linkedin" />
  </a>
  <a href="https://github.com/shreyanshmalvya/Huffman-Coding/issues">
    <img src="https://img.shields.io/github/issues-raw/shreyanshmalvya/huffman-coding"
      alt="open issues" />
  </a>
  <a href="https://github.com/shreyanshmalvya/Huffman-Coding/issues?q=is%3Aissue+is%3Aclosed">
    <img src="https://img.shields.io/github/issues-closed-raw/shreyanshmalvya/huffman-coding"
      alt="closed issues" />
  </a>
</p> -->

Self-made C++ **file archiver** and **archive extractor** programs based on Huffman's lossless compression algorithm. 
## Table of Contents

* [How does it work](#how-does-it-work)
  * [Compressor](#compressor)
  * [Decompressor](#decompressor)
* [How to use it?](#how-to-use-it)

## How does it work?
The ``Huffman algorithm`` is a lossless data compression technique that assigns variable-length codes to characters in a text based on their frequency of occurrence. It creates a binary tree with the most frequent characters at the top and the least frequent at the bottom, and assigns a `0` or `1` to each path from the root to a leaf node. This way, the characters that appear more frequently in the text will have shorter codes, resulting in a more efficient compression.

### Compressor:
The ```Compressor``` is a ``2-pass program`` that reads input files twice.

In the first pass, the program counts the frequency of occurrence of every unique character in the input text. It then uses this information to create a Huffman tree, where the most frequent characters have shorter codes. The program then writes the Huffman codes for each character to the compressed file, for decompression purposes.

In the second pass, the program translates the input text using the Huffman codes generated in the first pass, and writes the compressed text to a new file.

This is how the code i provided earlier works, it reads the text as input and generate frequency of each character and then it uses this frequency to generate huffman tree and then it uses this tree to generate codes for each character. It then uses these codes to compress the text, and write the compressed text to a new file.

### Decompressor:
The `Decompressor` is a 1-pass program:
The `Decompressor` first reads translation info and creates a binary tree from it. After this process is done, it uses this binary translation tree to decode the rest of the file

# How to use it?
#### Step 1: Prerequisites 🛠️

- Make sure you have Git and a C++ compiler installed on your computer.

#### Step 2: Clone the repository 🗂️

Clone the repository that contains the Huffman compression code by running the following command in your terminal or command prompt:

```sh
git clone https://github.com/shreyanshmalvya/Huffman_Compressor.git
```

#### Step 3: Navigate to the repository 🚶‍♂️
Navigate to the directory where the repository has been cloned:
```sh
cd Huffman_Compressor
```
#### Step 4: Compile the code 🔨
Compile the code by running the following command:
```sh
g++ -o huffman huffman_compressor.cpp
```
#### Step 5: Run the program 🏃‍♂️
Run the program by executing the following command:
```sh
./huffman_compressor
```
#### Step 6: Compress your text 📦
- The program will prompt you to enter a string of text to compress. Type or paste in the text you want to compress and press enter.
- The program will then prompt you to enter a file name to save the compressed text to. Enter a file name and press enter.
- The program will compress the text using the Huffman algorithm and save the compressed text to the specified file.

### All done! 🎉
The program will display a message indicating that the compression is complete and the file has been saved.
