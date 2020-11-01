.PHONY: all, $(NAME), clean, fclean, re

NAME = vizuals

SRC_PATH = ./src/
OBJ_PATH = ./objects/
INC_PATH = ./includes/
LIB_PATH = ./libft

INC = -I .  -I $(INC_PATH) -I $(LIB_PATH) -I ./ \
    		-I src/ \
			-I SDL2/SDL2.framework/Headers \
			-F SDL2/

FRAME = 	-F SDL2/ -framework SDL2 -rpath SDL2/
FLAGS = 	-c -g -MMD -MP -Wall -Wextra -Werror

LIB = 		-L$(LIB_PATH) -lft

SRC = ///LIST OF FILES GO HERE///

OBJ = $(SRC:.c=.o)

OBJ_A = $(addprefix $(OBJ_PATH),$(OBJ))

SRC_A = $(addprefix $(SRC_PATH),$(SRC))
DEP_A = $(OBJ_A:.o=.d)

all: $(NAME)

$(NAME): $(OBJ_A)
	Make -C $(LIB_PATH)
	gcc $(OBJ_A) $(INC) $(LIB) $(FRAME) -o $(NAME)

-include $(DEP_A)
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	gcc $(FLAGS) $(INC) $< -o $@

clean:
	@clear
	@Make -C $(LIB_PATH) clean
	@rm -rf $(OBJ_PATH)

fclean: clean
	@Make -C $(LIB_PATH) fclean
	@rm -f $(NAME)

re: fclean all