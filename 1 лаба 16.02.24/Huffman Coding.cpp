#include "Huffman Coding.h"

void Huffman_Class::printCodes(struct MinHeapNode* root, string str)
{
	if (!root)
		return;
	if (root->data != '$')
		//cout << root->data << ": " << str << "\n";
	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}

void Huffman_Class::storeCodes(struct MinHeapNode* root, string str)
{
	if (root == NULL)
		return;
	if (root->data != '$')
		codes[root->data] = str;
	storeCodes(root->left, str + "0");
	storeCodes(root->right, str + "1");
}

void Huffman_Class::HuffmanCodes(int size)
{
	if(minHeap != NULL) delete minHeap;
	minHeap = new priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare>;
	struct MinHeapNode* left, * right, * top;
	for (map<char, int>::iterator v = freq.begin();
		v != freq.end(); v++)
		minHeap->push(new MinHeapNode(v->first, v->second));
	while (minHeap->size() != 1) {
		left = minHeap->top();
		minHeap->pop();
		right = minHeap->top();
		minHeap->pop();
		top = new MinHeapNode('$',
			left->freq + right->freq);
		top->left = left;
		top->right = right;
		minHeap->push(top);
	}
	storeCodes(minHeap->top(), "");
}

void Huffman_Class::calcFreq(string str, int n)
{
	freq.clear();
	for (int i = 0; i < str.size(); i++)
		freq[str[i]]++;
}

string Huffman_Class::decode_file(struct MinHeapNode* root, string s)
{
	string ans = "";
	struct MinHeapNode* curr = root;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '0')
			curr = curr->left;
		else
			curr = curr->right;

		// reached leaf node
		if (curr->left == NULL and curr->right == NULL) {
			ans += curr->data;
			curr = root;
		}
	}
	// cout<<ans<<endl;
	return ans + '\0';
}

string Huffman_Class::saveHuffCode(string str)
{
	std::vector<bool> encodedData;
	//encodedData = { 0, 1, 1, 0, 1, 0, 0, 1, 1, 0 };
	for (size_t i = 0; i < str.length(); i++)
	{
		if ((str[i] - '0') == 1) encodedData.push_back(1);
		if ((str[i] - '0') == 0) encodedData.push_back(0);
	}

	string codes_huff;
	for (size_t i = 0; i < encodedData.size(); i += 8) {
		char byte = 0;
		for (size_t j = 0; j < 8 && i + j < encodedData.size(); ++j) {
			byte |= (encodedData[i + j] << j);
		}
		codes_huff.push_back(byte);
	}

	return codes_huff;
}
