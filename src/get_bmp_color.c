#include <unistd.h>
#include "bitmap.h"

#define H	(bitmap->height)
#define W	(bitmap->width)
#define N_NULL	(bitmap->nb_null)
#define BYTESPP	(bitmap->bytes_per_px)

int		get_bmp_color(t_bitmap *bitmap, int x, int y)
{
  unsigned int	char_id;
  unsigned int	color;
  unsigned char	*data;
  int		byte_count;

  color = 0;
  if (x < 0 || y < 0 || x >= bitmap->width || y >= bitmap->height)
    return (0);
  char_id = (H - y - 1) * (W * BYTESPP + N_NULL) + x * BYTESPP;
  data = &(bitmap->data[char_id]);
  byte_count = BYTESPP;
  while (byte_count)
    color = (color << 8) | data[--byte_count];
  return (color);
}
