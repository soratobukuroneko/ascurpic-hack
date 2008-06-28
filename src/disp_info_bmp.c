#include <stdio.h>
#include "ascurpic.h"

void	disp_info_bmp(t_bitmap *bmp)
{
  printf("Bitmap info:\n"	\
	 " width:  %dpx\n"	\
	 " height: %dpx\n"	\
	 " bpp:    %dpx\n",
	 bmp->width, bmp->height, bmp->bytes_per_px * 8);
  return ;
}
