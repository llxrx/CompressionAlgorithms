#pragma once
#define BINARY_FILE_H

#include <string>
#include <fstream>
#include <bitset>

using namespace std;

class Binary_File {
public:
	Binary_File(string filename, ios_base::openmode mode);
	~Binary_File();

	void write(bool bit);
	int read();				//read the next bit from the binary file, return int to accomodate EOF
	void close();			//flush the buffer into the stream, write difference between char_bit and the remaining bits in buffer (the offset) as 0's in the least sig bits
private:
	bool last_op_write;		/*
							*  http://stackoverflow.com/questions/17536570/reading-and-writing-to-the-same-file-using-the-same-fstream
							*	Since we're intermixing read and write, we must:
							*		1. flush the stream or call a file positioning function when reading after writing
							*		2. call a file positioning function when writing after reading
							*/
	streampos next_read_pos;
	streampos next_write_pos;
	string filename;
	fstream rle_stream;
	bitset<CHAR_BIT> write_buffer;
	int write_buffer_cursor;
	bitset<CHAR_BIT> read_buffer;
	int read_buffer_cursor;
	bool is_reading_from_write_buffer;
	int max_read_write_buffer_cursor;	//When reading from the write buffer, this is the smallest valid index

	void flush();
	void initialize();
};