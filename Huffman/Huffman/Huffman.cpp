#include <iostream>
#include <stdio.h>
#include <vector>
#include "Huffman.h"

Huffman::Huffman(std::string src, std::string dst)
{
	if (src.size() == 0 || dst.size() == 0)
	{
		std::cout << "files are NULL\n";
		return;
	}

	in.open(src.c_str());
	if(in.fail())
	{
		std::cout << "failed open src file\n";
		return;
	}

	out.open(dst.c_str());
	if(out.fail())
	{
		std::cout << "failed open dst file\n";
		return;
	}
}

Huffman::~Huffman()
{
	if (in.is_open())
		in.close();

	if (out.is_open())
		out.close();
}

void Huffman::set_src_file(std::string src)
{
	/* TODO: Not implemented yet */
}

void Huffman::set_dst_file(std::string src)
{
	/* TODO: Not implemented yet */
}

void Huffman::compress()
{
	char ch;
	int size = 0;
	int found = 0;

	struct node *t = NULL;
	std::vector <struct node *> table;

	while (in.get(ch))
	{
		found = 0;

		for (int i = 0; i < table.size(); i++)
		{
			if (table[i]->ch == ch)
			{
				table[i]->freq += 1;
				found = 1;
				break;
			}
		}

		if (found == 1)
			continue;

		struct node *n = new struct node;
		n->ch = ch;
		n->freq = 1;

		n->left = NULL;
		n->right = NULL;

		table.push_back(n);
	}

	for (int i = 0; i < table.size(); i++)
	{
		queue.push(table[i]);
	}

/*
	for (int i = 0; i < table.size(); i++)
	{
		t = queue.top();
		queue.pop();

		printf("%c  %d\n", t->ch, t->freq);
	}
*/

	huffman_tree_create();

	std::cout << "compress\n";
}

void Huffman::huffman_tree_create()
{
	int n = queue.size();

	struct node *x, *y, *z;

	for (int i = 0; i < (n-1); i++)
	{
		z = new struct node;
		z->left = x = queue.top();
		queue.pop();

		z->left = y = queue.top();
		queue.pop();

		z->ch = 0;
	    z->freq = x->freq + y->freq;

	    queue.push(z);
	}

	head = queue.top();
	printf("%c  %d\n", head->ch, head->freq);
}


void Huffman::decompress()
{
	std::cout << "decompress\n";
}

