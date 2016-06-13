#include <iostream>
#include <stdio.h>
#include <vector>
#include "LZW.h"

/***************************************************/

LZW::LZW()
{
}

LZW::LZW(std::string src, std::string dst)
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

LZW::~LZW()
{
	if (in.is_open())
		in.close();

	if (out.is_open())
		out.close();
}

void LZW::set_src_file(std::string src)
{
	/* TODO: Not implemented yet */
}

void LZW::set_dst_file(std::string src)
{
	/* TODO: Not implemented yet */
}

void LZW::compress()
{
	char ch;
	std::string chh;

	std::string P;
	std::string C;
	std::string PC;

	std::cout << "compress\n";

	/* Create base table */
	while(in.get(ch))
	{
		chh = ch;

		table.add(chh);
	}

	table.flush(out);

	in.clear();
	in.seekg(0, std::ios::beg);

	while(in.get(ch))
	{
		chh = ch;
		C = chh;

		PC = P + C;

		if (table.get(PC) != -1)
		{
			P = PC;
		}
		else
		{
			table.add(PC);
			char output = table.get(P);
			out << output;
			P = C;
		}
	}

	table.show();

	in.clear();
	in.seekg(0, std::ios::beg);
}

void LZW::decompress()
{
	char ch;
	std::string chh;
	int table_size;

	int pW = -1;
	int cW =-1;
	std::string str_pW;
	std::string str_cW;

	std::string P;
	std::string C;
	std::string PC;

	std::cout << "decompress\n";

	in.get(ch);

	table_size = ch;

	for (int i = 0; i < table_size; i++)
	{
		in.get(ch);
		chh = ch;
		table.add(chh);
	}

	table.show();

	in.get(ch);

	pW = ch;
	str_pW = table.get(pW);
	out << table.get(pW);

	while(in.get(ch))
	{
		std::cout << "ch: " << (int)ch << std::endl;

		cW = ch;
		str_cW = table.get(cW);
		out << table.get(cW);

		table.add(str_pW + str_cW[0]);

		pW = cW;
		str_pW = str_cW;
	}
}

/***************************************************/

Table::Table() {}
Table::~Table() {}

void Table::add(std::string str)
{
	struct node *n;

	if (table.size() == 0)
	{
		n = new struct node;
		n->token = str;
		n->num = 1;

		table.push_back(n);
		return;
	}

	for (int i = 0; i < table.size(); i++)
	{
		if (table[i]->token == str)
			return;
	}

	n = new struct node;
	n->token = str;
	n->num = table.back()->num + 1;

	table.push_back(n);
}

int Table::get(std::string str)
{
	for (int i = 0; i < table.size(); i++)
	{
		if (table[i]->token == str)
			return table[i]->num;
	}

	return -1;
}

std::string Table::get(int idx)
{
	for (int i = 0; i < table.size(); i++)
	{
		if (table[i]->num == idx)
			return table[i]->token;
	}

	/* Never get here */
	return "";
}

int Table::size()
{
	return table.size();
}

void Table::flush(std::ofstream &out)
{
	char size = (char)(table.size());

	out << size;

	for (int i = 0; i < table.size(); i++)
	{
		out << table[i]->token;
	}
}

void Table::show()
{
	for (int i = 0; i < table.size(); i++)
	{
		printf("num:%d  token:%s\n", table[i]->num, table[i]->token.c_str());
	}
}
