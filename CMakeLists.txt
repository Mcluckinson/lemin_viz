cmake_minimum_required(VERSION 3.15)
project(visualizer C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)

include_directories(.)
include_directories(libft/includes
        ${SDL2_INCLUDE_DIR})

add_executable(visualizer
        libft/includes/get_next_line.h
        libft/includes/libft.h
        libft/srcs/ft_abs.c
        libft/srcs/ft_atoi.c
        libft/srcs/ft_atoi_base.c
        libft/srcs/ft_bzero.c
        libft/srcs/ft_isalnum.c
        libft/srcs/ft_isalpha.c
        libft/srcs/ft_isascii.c
        libft/srcs/ft_isdigit.c
        libft/srcs/ft_isprint.c
        libft/srcs/ft_itoa.c
        libft/srcs/ft_itoa_base.c
        libft/srcs/ft_lstadd.c
        libft/srcs/ft_lstaddback.c
        libft/srcs/ft_lstdel.c
        libft/srcs/ft_lstdelone.c
        libft/srcs/ft_lstiter.c
        libft/srcs/ft_lstmap.c
        libft/srcs/ft_lstnew.c
        libft/srcs/ft_memalloc.c
        libft/srcs/ft_memccpy.c
        libft/srcs/ft_memchr.c
        libft/srcs/ft_memcmp.c
        libft/srcs/ft_memcpy.c
        libft/srcs/ft_memdel.c
        libft/srcs/ft_memmove.c
        libft/srcs/ft_memset.c
        libft/srcs/ft_power.c
        libft/srcs/ft_putchar.c
        libft/srcs/ft_putchar_fd.c
        libft/srcs/ft_putendl.c
        libft/srcs/ft_putendl_fd.c
        libft/srcs/ft_putnbr.c
        libft/srcs/ft_putnbr_fd.c
        libft/srcs/ft_putstr.c
        libft/srcs/ft_putstr_fd.c
        libft/srcs/ft_revmemcpy.c
        libft/srcs/ft_strcat.c
        libft/srcs/ft_strchr.c
        libft/srcs/ft_strclr.c
        libft/srcs/ft_strcmp.c
        libft/srcs/ft_strcpy.c
        libft/srcs/ft_strdel.c
        libft/srcs/ft_strdup.c
        libft/srcs/ft_strequ.c
        libft/srcs/ft_striter.c
        libft/srcs/ft_striteri.c
        libft/srcs/ft_strjoin.c
        libft/srcs/ft_strlcat.c
        libft/srcs/ft_strlen.c
        libft/srcs/ft_strmap.c
        libft/srcs/ft_strmapi.c
        libft/srcs/ft_strncat.c
        libft/srcs/ft_strncmp.c
        libft/srcs/ft_strncpy.c
        libft/srcs/ft_strndup.c
        libft/srcs/ft_strnequ.c
        libft/srcs/ft_strnew.c
        libft/srcs/ft_strnjoin.c
        libft/srcs/ft_strnstr.c
        libft/srcs/ft_strrchr.c
        libft/srcs/ft_strsplit.c
        libft/srcs/ft_strstr.c
        libft/srcs/ft_strsub.c
        libft/srcs/ft_strtrim.c
        libft/srcs/ft_tolower.c
        libft/srcs/ft_toupper.c
        libft/srcs/get_next_line.c
        clear.c
        delete_me_im_a_debug.c
        draw_ants.c
        draw_map.c
        drawing_tests_delete_me.c
        duplicate_values.c
        init_sdl.c
        lem_viz.h
        main.c
        music.c
        prepare_data.c
        read_ants.c
        read_links.c
        read_rooms.c
        read_steps.c
        utils.c
        valid.c)

target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_LIBRARY} -lmingw32  -lSDL2main -lSDL2 -mwindows)