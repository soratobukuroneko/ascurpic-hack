#include <stdio.h>
#include "ascurpic.h"

int		main(int ac, char **av)
{
  param_t	p;
  int		parse_ret;

  if ((parse_ret = parse_opts(&p, ac, av)) < 0)
  {
    fprintf(stderr, USAGE, av[0]);
    if (ac == 1)
      return (EXIT_SUCCESS);
    return (EXIT_FAILURE);
  }
  disp_info_bmp(p.input_bitmap);
  write_page(&p);
  free_bitmap(p.input_bitmap);
  return (EXIT_SUCCESS);
}
