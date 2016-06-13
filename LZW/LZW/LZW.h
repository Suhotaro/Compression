#ifndef __LZW_H__
#define __LZW_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Table
{
private:
	struct node
	{
		int num;
		std::string token;
	};

	std::vector<struct node *> table;

public:
	Table();
	~Table();

	void add(std::string str);
	int get(std::string str);
	std::string get(int idx);
	int size();
	void show();

	void flush(std::ofstream &out);
};

class LZW
{
private:
	std::string src;
	std::string dst;
	
	std::ifstream in;
	std::ofstream out;

	Table table;

public:
	LZW();
	LZW(std::string src, std::string dst);
	
	~LZW();
	
	void set_src_file(std::string src);
	void set_dst_file(std::string src);
	
	void compress();
	void decompress();
};

#endif //__LZW_H__
