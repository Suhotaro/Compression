#include <iostream>
#include <unistd.h>

#include "../LZW/LZW.h"

int main()
{
    LZW lzw("files/in.txt", "files/out.txt");
	lzw.compress();	

    return 0;
}
