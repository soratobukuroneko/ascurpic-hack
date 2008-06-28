#include <stdlib.h>
#include "bitmap.h"

void		free_bitmap(t_bitmap *bmp)
{
  free(bmp->data);
  free(bmp);
  return ;
}
