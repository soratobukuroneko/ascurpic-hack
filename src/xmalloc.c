#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "ascurpic.h"

void		*xmalloc(int size)
{
  void		*ptr;

  if ((ptr = malloc(size)) == NULL)
  {
    fprintf(stderr, ERR_MALLOC, size);
    exit(EXIT_FAILURE);
  }
  return (ptr);
}
