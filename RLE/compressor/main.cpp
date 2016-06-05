#include <iostream>
#include <unistd.h>

#include "../RLE/RLE.h"

int main()
{
	RLE rle("files/in.txt", "files/out.txt");
	rle.compress();	

    return 0;
}
