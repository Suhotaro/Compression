#include <iostream>
#include <unistd.h>

#include "../RLE/RLE.h"

int main()
{
	RLE rle("files/out.txt", "files/res.txt");
	rle.decompress();

    return 0;
}
