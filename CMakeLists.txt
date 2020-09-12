cmake_minimum_required(VERSION 3.17)
project(lemin_vizualizer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
link_directories(
        SDL2/
        libft)
include_directories(
        SDL2/SDL2.framework/Headers
        includes
        libft)

add_executable(lemin_vizualizer
       blur_v4.c
        brezenham.c
        clear.c
        delete_me_im_a_debug.c
        draw_ants.c
        draw_buff.c
        draw_circle.c
        draw_filled_circle.c
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

target_link_libraries(lemin_vizualizer
        "ft"
        "-F ${PROJECT_SOURCE_DIR}/SDL2 -framework SDL2"
        )