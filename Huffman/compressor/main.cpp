#include <iostream>
#include <unistd.h>

#include "../Huffman/Huffman.h"

int main()
{
	Huffman huffman("files/in.txt", "files/out.txt", "files/table.txt");
	huffman.compress();

    return 0;
}
