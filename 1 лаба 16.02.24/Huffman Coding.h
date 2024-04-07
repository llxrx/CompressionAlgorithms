#pragma once
#include "library.h"

using namespace std;

class Huffman_Class {
public:
	struct MinHeapNode {
		char data;
		int freq;
		MinHeapNode* left, * right;

		MinHeapNode(char data, int freq)
		{
			left = right = NULL;
			this->data = data;
			this->freq = freq;
		}
	};

	struct compare {
		bool operator()(MinHeapNode* l, MinHeapNode* r)
		{
			return (l->freq > r->freq);
		}
	};

	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare>* minHeap;

	map<char, string> codes;
	map<char, int> freq;

	void printCodes(struct MinHeapNode* root, string str);
	void storeCodes(struct MinHeapNode* root, string str);
	void HuffmanCodes(int size);
	void calcFreq(string str, int n);
	string decode_file(struct MinHeapNode* root, string s);
	string saveHuffCode(string str);
};