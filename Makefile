NAME = ready_set_boole

#########
RM = rm -f
CC = c++
CFLAGS = -Werror -Wextra -Wall
#########

#########
# FILES = main RPN

# SRC = $(addsuffix .cpp, $(FILES))
SRC := $(wildcard src/*.cpp) main.cpp
#########

#########
OBJ_DIR = OBJ
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))
DEP = $(addsuffix .d, $(basename $(OBJ)))
#########

#########
$(OBJ_DIR)/%.o: %.cpp 
	@mkdir -p $(@D)
	@${CC} $(CFLAGS) -MMD -c $< -o $@

all:
	$(MAKE) $(NAME) --no-print-directory

$(NAME):: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "EVERYTHING DONE   "⠀⠀⠀⠀⠀⠀⠀


clean:
	$(RM) $(OBJ) $(DEP) 
	$(RM) -r $(OBJ_DIR) 
	@echo "OBJECTS REMOVED   "

fclean: clean
	$(RM) $(NAME) 
	@echo "EVERYTHING REMOVED   "

re:	fclean all

.PHONY: all clean fclean re

-include $(DEP)
