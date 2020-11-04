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
#FLAGS = 	-c -g -MMD -MP -Wall -Wextra -Werror -O3#
FLAGS = 	-c -g -MMD -MP -O3

LIB = 		-L$(LIB_PATH) -lft

SRC = blur_v4.c brezenham.c clear.c draw_ants.c draw_buff.c draw_circle.c draw_filled_circle.c \
draw_map.c drawing_tests_delete_me.c duplicate_values.c error_manager.c init_sdl.c main.c modify_levels.c \
music.c prepare_data.c pulse_map.c read_ants.c read_links.c read_links_helper.c \
read_rooms.c read_steps.c read_steps_helper.c set_levels_for_view.c utils.c \
valid.c zoom.c

OBJ = $(SRC:.c=.o)

OBJ_A = $(addprefix $(OBJ_PATH),$(OBJ))

SRC_A = $(addprefix $(SRC_PATH),$(SRC))
DEP_A = $(OBJ_A:.o=.d)

all: $(NAME)

$(NAME): $(OBJ_A)
	Make -C $(LIB_PATH)
	clang $(OBJ_A) $(INC) $(LIB) $(FRAME) -o $(NAME)
#	gcc $(OBJ_A) $(INC) $(LIB) $(FRAME) -o $(NAME)

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