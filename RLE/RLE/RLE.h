#ifndef __RLE_H__
#define __RLE_H__

#include <iostream>
#include <fstream>
#include <string>

class RLE
{
private:
	std::string src;
	std::string dst;
	
	std::ifstream in;
	std::ofstream out;
	
	unsigned char get_T(int type, int size);

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
