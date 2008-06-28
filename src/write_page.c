#include <stdio.h>
#include <stdlib.h>
#include "ascurpic.h"

static char		*get_text(param_t *p)
{
  int			i;
  char			c;
  char			*text;

  text = xmalloc(sizeof(*text) * (p->nbcharpx + 1));
  for (i = 0; i < p->nbcharpx; i++)
  {
    do
    {
      c = fgetc(p->input_text);
      if (c == EOF)
	fseek(p->input_text, 0, SEEK_SET);
    }
    while (c < 33 || c == '\n' || c == '&' || c == '<' || c == '>');
    text[i] = c;
  }
  text[i] = '\0';
  return (text);
}

static void		write_pixel(param_t *p, int x, int y)
{
  static int		first = 1;
  char			*text;
  unsigned int		color;
  static unsigned int	last_color = 0;

  color = get_bmp_color(p->input_bitmap, x, y);
  text = get_text(p);
  if (first || last_color != color)
  {
    if (!first)
      fprintf(p->output_file, HTML_SPAN_C_2);
    fprintf(p->output_file, HTML_SPAN_C_1, color, text);
    first = 0;
  }
  else
    fprintf(p->output_file, "%s", text);
  free(text);
  last_color = color;
  return ;
}

void			write_page(param_t *p)
{
  int			x;
  int			y;

  fprintf(p->output_file, HTML_HEADER);
  fprintf(p->output_file, HTML_INITBODY, p->bgcolor, p->fontsize);
  for (y = 0; y < p->input_bitmap->height; y++)
  {
    for (x = 0; x < p->input_bitmap->width; x++)
      write_pixel(p, x, y);
    fprintf(p->output_file, "\n");
  }
  fprintf(p->output_file, HTML_END);
  return ;
}
