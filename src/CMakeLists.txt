project(game)
add_executable(game penguinGame.cpp penguinGame.h entity.cpp entity.h)
target_link_libraries(game ${SDL2_LIBRARIES})