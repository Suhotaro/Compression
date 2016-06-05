#include <iostream>
#include <stdio.h>
#include "RLE.h"

RLE::RLE()
{
}

RLE::RLE(std::string src, std::string dst)
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

RLE::~RLE()
{
	if (in.is_open())
		in.close();

	if (out.is_open())
		out.close();
}

void RLE::set_src_file(std::string src)
{
	/* TODO: Not implemented yet */
}

void RLE::set_dst_file(std::string src)
{
	/* TODO: Not implemented yet */
}

unsigned char RLE::get_T(int type, int size)
{
	unsigned char T = 0;

    T |= (type << 7);
    T += size;

    return T;
}

void RLE::compress()
{
	char c1 , c2;
	unsigned char T = 0x0;
	int diff = 0, same = 0;
	char str[100];

	std::cout << "compress\n";

	in.get(c2);

	while(in.get(c1))
	{
		if (c1 == c2)
		{
			if (diff > 0)
			{
				T = get_T(1, diff);
				printf("1: T:%d S:%d  c:%c\n", T, diff, c2);
				out << T;

				for(int i = 0; i < diff;i++)
					out << str[i];

				diff = 0;
			}

			same +=1;
		}

		if (c1 != c2)
		{
			if (same > 0)
			{
				T = get_T(0, same);
				printf("0: T:%d S:%d  c:%c\n", T, same, c2);

				out << T;
				out << c2;

				same = 0;
			}

			str[diff] = c1;
			diff +=1;
		}

		c2 = c1;
	}
}

void RLE::decompress()
{
	char c;

	std::cout << "decompress\n";

	while(in.get(c))
	{
		out << c;
	}
}



