##
## EPITECH PROJECT, 2025
## Trains-Bridge
## File description:
## Makefile
##

CC	=	gcc

IFLAGS	=	-lpthread -I include/

CFLAGS	=	-W -Wall -Werror -Wextra $(IFLAGS)

SRC	=	$(shell find "./src" -name *.c)

OBJ	=	$(SRC:.c=.o)

EXEC	=	trains.exe

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

clean:
	find "./" -name *.o -delete

fclean: clean
	rm -rf $(EXEC)

re:	fclean all
