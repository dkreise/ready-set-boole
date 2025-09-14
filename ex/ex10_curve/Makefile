NAME = ex10

#########
RM = rm -f
CC = c++
CFLAGS = -Werror -Wextra -Wall -std=c++17
#########

#########
FILES = main ../../rsb
SRC = $(addsuffix .cpp, $(FILES))

OBJ = $(SRC:.cpp=.o)
#########

#########
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "EVERYTHING DONE   "

clean:
	$(RM) $(OBJ)
	@echo "OBJECTS REMOVED   "

fclean: clean
	$(RM) $(NAME) 
	@echo "EVERYTHING REMOVED   "

re:	fclean all

.PHONY: all clean fclean re
