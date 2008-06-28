#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ascurpic.h"

extern char	*optarg;
extern int	optind;
extern int	optopt;
extern int	opterr;
extern int	optreset;

static int	open_bmp(t_bitmap **bmp, char *arg)
{
  int		fd;

  if ((fd = open(arg, O_RDONLY)) < 0)
  {
    fprintf(stderr, ERR_OPEN, arg);
    return (-1);
  }
  *bmp = load_bitmap(fd);
  if (*bmp == NULL)
  {
    fprintf(stderr, ERR_BMP);
    return (-1);
  }
  return (0);
}

static int	open_file(FILE **f, char *fname, char *perm)
{
  *f = fopen(fname, perm);
  if(*f == NULL)
  {
    fprintf(stderr, ERR_OPEN, fname);
    return (-1);
  }
  return (0);
}

static void	load_def_values(param_t *p)
{
  memset(p, 0, sizeof(*p));
  p->fontsize = DEF_FONTSIZE;
  p->nbcharpx = DEF_NBCHARPX;
  p->bgcolor = DEF_BGCOLOR;
  return ;
}

static int	check_input(param_t *p)
{
  if (!p->input_bitmap || !p->input_text || !p->output_file)
    return (-1);
  return (0);
}

int		parse_opts(param_t *p, int ac, char **av)
{
  int		option;

  load_def_values(p);
  while ((option = getopt(ac, av, "f:t:o:c:n:s:")) != -1)
  {
    switch (option)
    {
      case 'f':
	if (open_bmp(&(p->input_bitmap), optarg) < 0)
	  return (-1);
	break;

      case 't':
	if (open_file(&(p->input_text), optarg, "r") < 0)
	  return (-1);
	break;

      case 'o':
	if (open_file(&(p->output_file), optarg, "w") < 0)
	  return (-1);
	break;

      case 'c':
	p->bgcolor = atoi(optarg);
	break;

      case 'n':
	p->nbcharpx = atoi(optarg);
	break;

      case 's':
	p->fontsize = atoi(optarg);
	break;

      default:
	abort();
    }
  }
  return (check_input(p));
}
