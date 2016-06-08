#ifndef __RLE_H__
#define __RLE_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class RLE
{
private:
	std::string src;
	std::string dst;
	
	std::ifstream in;
	std::ofstream out;
	
	unsigned char set_T(int type, int size);
	void get_T(unsigned char T, int &opt, int &size);
	void flush(int type, std::vector<char> v);

public:
	RLE();
	RLE(std::string src, std::string dst);
	
	~RLE();
	
	void set_src_file(std::string src);
	void set_dst_file(std::string src);
	
	void compress();
	void decompress();
};

#endif //__RLE_H__
