#include <iostream>
#include <stdio.h>
#include <vector>

extern "C" {
#include "bitrw.h"
}

#include "Huffman.h"

Huffman::Huffman(std::string src, std::string dst)
{
	int ret = 0;

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

	ret = bitrw_init(dst.c_str());
	if(ret != 1)
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

	bitrw_deinit();
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

	node *t = NULL;
	std::vector <node *> tmp_table;


	int a[6][2] =
	{
		{'f', 5},
		{'e', 9},
		{'a', 45},
		{'b', 13},
		{'d', 16},
		{'c', 12},
	};

	for (int i = 0; i < 6; i++)
	{
		node *n = new node;
		n->ch = a[i][0];
		n->freq = a[i][1];

		n->left = NULL;
		n->right = NULL;

		tmp_table.push_back(n);
	}

/*
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

		node *n = new node;
		n->ch = ch;
		n->freq = 1;

		n->left = NULL;
		n->right = NULL;

		table.push_back(n);
	}
*/
	for (int i = 0; i < tmp_table.size(); i++)
	{
		queue.push(tmp_table[i]);
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

	huffman_tree_create_table(head, -1, -1);

/*
	for (int i =0; i < table.size(); i++)
	{
		table_node * tmp = table[i];
		printf("ch:%c  data:%d  size:%d\n",
			   tmp->ch, tmp->data, tmp->size );
	}
*/


	std::cout << "compress\n";
}

void Huffman::huffman_tree_create()
{
	int n = queue.size();

	node *x, *y, *z;

	for (int i = 0; i < (n-1); i++)
	{
		z = new node;
		z->left = x = queue.top();
		queue.pop();

		z->right = y = queue.top();
		queue.pop();

		z->ch = 0;
	    z->freq = x->freq + y->freq;

	    queue.push(z);
	}

	head = queue.top();
	queue.pop();
}

void Huffman::huffman_tree_create_table(node *n, int num, int depth)
{
	if (n == NULL)
		return;

	if (num != -1)
	{
		arr[depth] = num;

		if (n->ch != 0)
		{
			table_node *tmp = new table_node;
			tmp->ch = n->ch;
			tmp->size = depth;
			tmp->data = 0;

			for (int i = depth, j = 0; i >= 0; i--, j++)
				tmp->data |= (arr[i] << j);

			table.push_back(tmp);
		}
	}

	Huffman::huffman_tree_create_table(n->left, 0, depth+1);
	Huffman::huffman_tree_create_table(n->right, 1, depth+1);
}

void Huffman::decompress()
{
	std::cout << "decompress\n";
}

