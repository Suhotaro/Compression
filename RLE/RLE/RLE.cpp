#include <iostream>
#include <stdio.h>
#include <vector>
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

void RLE::compress()
{
	unsigned char T = 0x0;
	char ch;
	char tmp = -1;

	std::vector<char> v;
	int count_same = 0;
	int count_diff = 0;
	int size = 0;

	std::cout << "compress\n";

	in.get(ch);
	tmp = ch;
	in.get(ch);

	if (tmp == ch)
	{
		v.push_back(tmp);
		v.push_back(ch);
		tmp = -1;

		count_same++;
	}
	else
	{
		v.push_back(tmp);
		tmp = ch;

		count_diff++;
	}

	/*TODO: handle "121212" sequence*/
	while(in.get(ch))
	{
        if (ch == v.back())
		{
			v.push_back(ch);
			count_same++;
		}
		else if (ch != v.back() && tmp == -1)
		{
			if (count_same > 0)
			{
				flush(0, v);

				v.clear();
				count_same = 0;
			}

			tmp = ch;
			count_diff++;
		}
		else if (tmp != ch)
		{
			if (count_same > 0)
			{
				flush(0, v);

				v.clear();
				count_same = 0;
			}

			v.push_back(tmp);
			tmp = ch;
			count_diff++;
		}
		else if (tmp == ch)
		{
			if (count_diff == 1)
				count_diff = 0;
			else if (count_diff > 0)
			{
				flush(1, v);

				v.clear();
				count_diff = 0;
			}

			v.push_back(tmp);
			v.push_back(ch);
			tmp = -1;

			count_same++;
		}
		else
		{
			/* Never get here */
		}
	}


	if (ch == v.back())
	{
		v.push_back(ch);
		flush(0, v);

		v.clear();
	}
	if (ch != v.back())
	{
		if (count_same > 0)
		{
			flush(0, v);

			v.clear();
			count_same = 0;
		}

		v.push_back(ch);
		flush(1, v);
		v.clear();
	}

}

void RLE::decompress()
{
	char ch;
	int opt = 0, size = 0;

	std::cout << "decompress\n";

	while(in.get(ch))
	{
		unsigned char T = ch;

		get_T(T, opt, size);

		if (opt == 0)
		{
			in.get(ch);
			for (int i = 0; i<size;i++)
				out << ch;
		}
		else
		{
			for (int i = 0; i<size;i++)
			{
				in.get(ch);
				out << ch;
			}
		}
	}
}


unsigned char RLE::set_T(int type, int size)
{
	unsigned char T = 0;

    T |= (type << 7);
    T += size;

    return T;
}

void RLE::get_T(unsigned char T, int &opt, int &size)
{
	if (((T >> 7) & 1) == 1)
	{
		opt = 1;
		size = T - 128;
	}
	else
	{
		opt = 0;
		size = T;
	}
}


void RLE::flush(int type, std::vector<char> v)
{
	unsigned char T;

	if (type == 0)
	{
		T = set_T(0, v.size());
		out << T;
		out << v.back();
	}
	else
	{
		int size = v.size();

		T = set_T(1, v.size());

		out << T;
		for(int i = 0; i < size; i++)
			out << v.at(i);
	}
}

