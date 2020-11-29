cmake_minimum_required(VERSION 3.17)
project(lem_in_vizuals C)

set(CMAKE_C_STANDARD 11)

link_directories(
        SDL2/
        libft)
include_directories(
        SDL2/SDL2.framework/Headers
        includes
        libft)

add_executable(lem_in_vizuals
        includes/lem_viz.h
        src/blur_v4.c
        src/clear.c
        src/draw_ants.c
        src/draw_buff.c
        src/draw_filled_circle.c
        src/draw_map.c
        src/duplicate_values.c
        src/error_manager.c
        src/init_sdl.c
        src/main.c
        src/modify_levels.c
        src/music.c
        src/prepare_data.c
        src/read_ants.c
        src/read_links.c
        src/read_links_helper.c
        src/read_rooms.c
        src/read_steps.c
        src/read_steps_helper.c
        src/set_levels_for_view.c
        src/utils.c
        src/valid.c
        src/zoom.c
        src/delete_unused.c
        src/loopz.c
        src/general_drawing.c
        src/draw_texture.c src/draw_ants_steps.c src/draw_ants_helper.c src/clear_data.c src/draw_buff_2.c)


target_link_libraries(lem_in_vizuals
        "ft"
        "-F ${PROJECT_SOURCE_DIR}/SDL2 -framework SDL2"
        "-F ${PROJECT_SOURCE_DIR}/SDL2 -framework SDL2_image"
        )
