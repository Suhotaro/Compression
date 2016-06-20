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
	std::ifstream in;
	std::ofstream out;
	std::ofstream table_file;

	int arr[100];

	struct node
	{
		char ch;
		int freq;

		node* left;
		node* right;
	};

	struct table_node
	{
		int data;
		int size;
		int ch;
	};

	struct MyComparator
	{
		bool operator() (node *arg1, node *arg2)
		{
			return arg1->freq > arg2->freq;
		}
	};

	std::priority_queue<node*, std::vector<node*>, MyComparator> queue;
	node* head = NULL;
	std::vector <table_node *> table;

	void create_queue();
	void huffman_tree_create();
	void huffman_tree_create_table(node*n, int num, int depth);
	void flush_table(void);

public:
	Huffman();
	Huffman(std::string src, std::string dst, std::string table);
	
	~Huffman();
	
	void set_src_file(std::string src);
	void set_dst_file(std::string src);
	
	void compress();
	void decompress();
};

#endif //__HUFFMAN_H__
