#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>

extern "C" {
#include "bitrw.h"
}

#include "Huffman.h"

Huffman::Huffman(std::string src, std::string dst, std::string table_file)
{
	if (src.size() == 0 || dst.size() == 0 || table_file.size() == 0)
	{
		std::cout << "files are NULL\n";
		return;
	}

	this->src = src;
	this->dst = dst;
	this->table_file = table_file;
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
	int bits = 0;
	int ret = 0;

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

	create_queue();
	huffman_tree_create();
	huffman_tree_create_table(head, -1, -1);
	table_show(0);
	table_to_file();

	while (in.get(ch))
	{
		for (int i = 0; i < table.size(); i++)
		{
			table_node * tmp = table[i];

			if (tmp->ch == ch)
			{
				for (int i = 0; i <= tmp->size; i++)
				{
					bitrw_write(!!(tmp->c_data & (1 << i)), 0);
					bits++;
				}

				break;
			}
		}
	}

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
			tmp->c_data = 0;

			for (int i = depth, j = 0; i >= 0; i--, j++)
				tmp->c_data |= (arr[i] << j);

			table.push_back(tmp);
		}
	}

	Huffman::huffman_tree_create_table(n->left, 0, depth+1);
	Huffman::huffman_tree_create_table(n->right, 1, depth+1);
}

void Huffman::create_queue()
{
	char ch;
	int size = 0;
	int found = 0;

	node *t = NULL;
	std::vector <node *> tmp_table;

/*
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
*/

	while (in.get(ch))
	{
		found = 0;

		for (int i = 0; i < tmp_table.size(); i++)
		{
			if (tmp_table[i]->ch == ch)
			{
				tmp_table[i]->freq += 1;
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

		tmp_table.push_back(n);
	}

	for (int i = 0; i < tmp_table.size(); i++)
		queue.push(tmp_table[i]);

	in.clear();
	in.seekg(0, std::ios::beg);
}

void Huffman::table_to_file()
{
	std::ofstream table_out;
	int bits = 0;

	table_out.open(table_file.c_str());
	if(table_out.fail())
	{
		std::cout << "failed open src file\n";
		exit(1);
	}

	table_out << table.size();
	table_out << '\n';

	for (int i = 0; i < table.size(); i++)
	{
		table_node * tmp = table[i];

		table_out << (char)tmp->ch;
		table_out << (char)(tmp->size +1);
		for (int i = 0; i <= tmp->size; i++)
			table_out << !!(tmp->c_data & (1 << i));
		table_out << '\n';
	}

	table_out.close();
}

void Huffman::decompress()
{
	std::vector<int> bits;
	int ret = 0;
	int bit = 0;
	int indx = 0;
	int num_indx = 0;

	ret = bitrw_init(src.c_str());
	if(ret != 1)
	{
		std::cout << "failed open dst file\n";
		return;
	}

	out.open(dst.c_str());
	if(out.fail())
	{
		std::cout << "failed open src file\n";
		return;
	}

	table_from_file();

	bit = bitrw_read();
	bits.push_back(bit);

	while(bit != -1)
	{
		printf("decompress: start\n");

		/* TODO: it must be substituted with faster solution */
		num_indx = table_get_indx(bits, indx);
		if (num_indx == 1)
		{
			table_node *t = table[indx];
			printf("  ch:%3d  ch:%3c\n", (int)t->ch, (char)t->ch);
			out << (char)t->ch;

			bits.clear();
			indx = 1;
		}

		printf("decompress: end %d  %d\n", bit, indx);

		bit = bitrw_read();
		bits.push_back(bit);
	}

	std::cout << "decompress\n";
}

void Huffman::table_from_file()
{
	std::ifstream table_in;
	char ch;
	int size = 0;

	table_in.open(table_file.c_str());
	if(table_in.fail())
	{
		std::cout << "failed open table file\n";
		exit(1);
	}

	table_in.get(ch);
	size = ch - 48;

	/* '\n' */
	table_in.get(ch);

	while (size > 0)
	{
		table_in.get(ch);

		table_node *t = new table_node;
		t->ch = ch;

		table_in.get(ch);

		/* TODO: comp size + 1 == decomp size */
		t->size = (int)ch;
		for (int i = 0; i < t->size; i++)
		{
			table_in.get(ch);
			t->d_data.push_back((ch - 48));
		}

		table.push_back(t);

		/* '\n' */
		table_in.get(ch);
		size--;
	}

	table_show(1);

	table_in.close();
}

int Huffman::table_get_indx(std::vector<int> bits, int &idx)
{
	int different = 0;
	int num_idx = 0;

	for (int i = 0 ; i < table.size(); i++)
	{
		table_node *t = table[i];
		different = 0;

		if (bits.size() != t->size)
			continue;

		for (int j = 0; j < bits.size(); j++)
		{
			if (bits[j] != t->d_data[j])
			{
				different = 1;
				break;
			}
		}

		if (different == 0)
		{
			idx = i;
			num_idx += 1;
		}
	}

	return num_idx;
}

void Huffman::table_show(int num)
{
	for (int i = 0; i < table.size(); i++)
	{
		table_node *t = table[i];

		if (t->ch == '\n')
			printf("ch:'\\n' size:%3d  data: ", t->size);
		else
			printf("ch:%3c  size:%3d  data: ",
					t->ch, t->size);

		for (int i = 0; num ? (i < t->size) : (i <= t->size); i++)
		{
			if (num)
				printf("%d ", t->d_data[i]);
			else
				printf("%d ", !!(t->c_data & (1 << i)));
		}
		printf("\n");
	}
}







