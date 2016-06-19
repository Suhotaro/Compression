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

	int arr[100];

	struct node
	{
		char ch;
		int freq;

		node*left;
		node*right;
	};

	struct MyComparator {
		bool operator() (node *arg1, node *arg2)
		{
			return arg1->freq > arg2->freq;
		}
	};

	std::priority_queue<node*,
	                    std::vector<node*>,
						MyComparator> queue;

	node*head = NULL;

	struct table_node
	{
		int data;
		int size;
		int ch;
	};

	std::vector <table_node *> table;

	void huffman_tree_create();
	void huffman_tree_create_table(node*n, int num, int depth);

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
