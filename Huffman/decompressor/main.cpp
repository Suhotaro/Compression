#include <iostream>
#include <unistd.h>

#include "../Huffman/Huffman.h"

int main()
{
	Huffman huffman("files/out.txt", "files/res.txt", "files/table.txt");
	huffman.decompress();

    return 0;
}
