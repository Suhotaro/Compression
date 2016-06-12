#include <iostream>
#include <unistd.h>

#include "../LZW/LZW.h"

int main()
{
	LZW lzw("files/out.txt", "files/res.txt");
	lzw.decompress();

    return 0;
}
