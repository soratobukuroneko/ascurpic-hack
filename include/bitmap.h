#ifndef _BITMAP_H_
# define _BITMAP_H_

# define HEAD_SIZE	(sizeof(t_bmp_file_header) + sizeof(t_bmp_info_header))

typedef struct
{
  unsigned char		type[2];
  unsigned char		size[4];
  unsigned char		reserved1[2];
  unsigned char		reserved2[2];
  unsigned char		offbits[4];
}			t_bmp_file_header;

typedef struct
{
  unsigned char		size[4];
  unsigned char		width[4];
  unsigned char		height[4];
  unsigned char		planes[2];
  unsigned char		bitcount[2];
  unsigned char		compression[4];
  unsigned char		sizeimage[4];
  unsigned char		xpelspermeter[4];
  unsigned char		ypelspermeter[4];
  unsigned char		clrused[4];
  unsigned char		clrimportant[4];
}			t_bmp_info_header;

typedef union
{
  char			chr[4];
  int			nb;
}			t_dword;

typedef struct
{
  int			width;
  int			height;
  int			bytes_per_px;
  int			nb_null;
  unsigned char		*data;
}			t_bitmap;

t_bitmap		*load_bitmap(int fd);
int			get_bmp_color(t_bitmap *bitmap, int x, int y);
void			free_bitmap(t_bitmap *bitmap);

#endif /* !_BITMAP_H_ */
