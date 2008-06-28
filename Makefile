CC		=	gcc

NAME		=	ascurpic

SRC		=	./src/main.c		\
			./src/disp_info_bmp.c	\
			./src/free_bitmap.c	\
			./src/get_bmp_color.c	\
			./src/load_bitmap.c	\
			./src/parse_opts.c	\
			./src/write_page.c	\
			./src/xmalloc.c		\

OBJ		=	$(SRC:.c=.o)

INC		=	-I./include/

CFLAGS		+=	-W -Wall -O2

.c.o:
		$(CC) $(INC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME)

all:		$(NAME)

clean:
		rm -f $(OBJ)

distclean:	clean
		rm -f $(NAME)

re:		distclean all
