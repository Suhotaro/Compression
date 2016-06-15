#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

class Huffman
{
private:
	std::string src;
	std::string dst;
	
	std::ifstream in;
	std::ofstream out;

	struct node
	{
		char ch;
		int freq;

		struct node *left;
		struct node *right;
	};

	struct MyComparator {
		bool operator() (struct node *arg1, struct node *arg2)
		{
			return arg1->freq < arg2->freq;
		}
	};

	std::priority_queue<struct node *,
	                    std::vector<struct node *>,
						MyComparator> queue;

	struct node *head = NULL;

	void huffman_tree_create();

public:
	Huffman();
	Huffman(std::string src, std::string dst);
	
	~Huffman();
	
	void set_src_file(std::string src);
	void set_dst_file(std::string src);
	
	void compress();
	void decompress();
};

#endif //__HUFFMAN_H__
