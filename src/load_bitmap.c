#include <fcntl.h>
#include <unistd.h>
#include "ascurpic.h"
#include "bitmap.h"

static int              get_int(unsigned char *str)
{
  t_dword               dword;
  int                   i;

  for (i = 0; i < 4; i++)
    dword.chr[i] = str[i];
  return (dword.nb);
}

void                    fill_bmp_data(int fd, t_bitmap *bitmap)
{
  int                   px_per_line;
  int                   nb_null;
  int                   data_size;

  px_per_line = bitmap->width * bitmap->bytes_per_px;
  nb_null = 0;
  while ((px_per_line + nb_null) % 4)
    nb_null++;
  bitmap->nb_null = nb_null;
  data_size = bitmap->height * (px_per_line + nb_null);
  bitmap->data = xmalloc(sizeof(*(bitmap->data)) * data_size);
  read(fd, bitmap->data, data_size);
  return ;
}

t_bitmap                  *load_bitmap(int fd)
{
  t_bitmap                *bitmap;
  t_bmp_file_header       file_header;
  t_bmp_info_header       info_header;

  if (read(fd, &file_header, sizeof(file_header)) < (int)sizeof(file_header))
    return (NULL);
  if (file_header.type[0] != 'B' || file_header.type[1] != 'M')
    return (NULL);
  if (read(fd, &info_header, sizeof(info_header)) < (int)sizeof(info_header))
    return (NULL);
  bitmap = xmalloc(sizeof(*bitmap));
  bitmap->width = get_int(info_header.width);
  bitmap->height = get_int(info_header.height);
  bitmap->bytes_per_px = get_int(info_header.bitcount) / 8;
  fill_bmp_data(fd, bitmap);
  close(fd);
  return (bitmap);
}
