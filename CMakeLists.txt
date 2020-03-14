cmake_minimum_required(VERSION 3.15)
project(viz4lem C)

set(CMAKE_C_STANDARD 11)

link_directories(
        SDL2/
        libft)
include_directories(
        SDL2/SDL2.framework/Headers
        libft)


add_executable(viz4lem
        lem_viz.h
        main.c
        utils.c
        read_ants.c
        read_rooms.c
        read_links.c
        read_steps.c
        valid.c
        delete_me_im_a_debug.c
        duplicate_values.c
        init_sdl.c
        prepare_data.c
        draw_ants.c
        draw_map.c
        music.c
        clear.c
        drawing_tests_delete_me.c)


target_link_libraries(viz4lem
        "ft"
        "-F ${PROJECT_SOURCE_DIR}/SDL2 -framework SDL2"
        )