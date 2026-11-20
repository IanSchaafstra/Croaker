cmake_minimum_required(VERSION 4.3)
project(croaker C)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(${CMAKE_PROJECT_NAME} main.c
        entities/car.h
        entities/car.c
        structs/env_data.h
        entities/player.h
        entities/player.c
        components/aabb.h
        components/aabb.c
        entities/log.h
        components/direction.h
        structs/configs/logconfig.h
        entities/log.c
        lanes/carlane.h
        lanes/carlane.c
        lanes/lanemanager.h
        lanes/lanemanager.c
        lanes/grasslane.h
        lanes/grasslane.c
        structs/config.h
        lanes/waterlane.h
        lanes/waterlane.c
        structs/sprites.h
        util/colors.h
        util/colors.c
        util/array_utils.h
        util/array_utils.c
        entities/scoreboard.h
        entities/scoreboard.c
        util/int_utils.h
        util/int_utils.c
        structs/configs/carconfig.h
        util/time_utils.h
        util/time_utils.c
)
target_link_libraries(${CMAKE_PROJECT_NAME} ${CURSES_LIBRARIES})
