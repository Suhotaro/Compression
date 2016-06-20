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
	std::string table_file;

	std::ifstream in;
	std::ofstream out;

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
		int ch;
		int size;

		/* Compressing data */
		int c_data;

		/* Compressing data */
		std::vector<int> d_data;
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

	/* Compressing methods */
	void create_queue();
	void huffman_tree_create();
	void huffman_tree_create_table(node*n, int num, int depth);
	void table_to_file(void);

	/* Decompressing methods */
	void table_from_file(void);
	int table_get_indx(std::vector<int> bits, int &idx);

	/* util */
	void table_show(int num);

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
