
SRCS	=		get_next_line.c

SRCH	=		get_next_line.h

OBJS	=		$(SRCS:.c=.o)

CC		=		gcc

RM		=		rm -f

AR		=		ar rcs

CFLAGS	=		-Wall -Werror -Wextra

NAME	=		get_next_line.a


all: $(NAME)

$(NAME): $(OBJS) $(SRCH)
	$(AR) $(NAME) $(OBJS)

clean:
	${RM} ${OBJS} ${OBJB}

fclean: clean
	${RM} ${NAME}



re: fclean all

rebonus: fclean bonus

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS) $(SRCBONUS)
	gcc -nostartfiles -shared -o get_next_line.so $(OBJS) $(OBJB)

.PHONY: all clean fclean bonus re rebonus

