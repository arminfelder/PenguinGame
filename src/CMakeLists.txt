project(game)
add_executable(game penguinGame.cpp penguinGame.h entity.cpp entity.h eventHandler.cpp eventHandler.h world.cpp world.h res_path.h position.cpp position.h dimension.cpp dimension.h entityController.cpp entityController.h TXTParser.cpp TXTParser.h)
target_link_libraries(game ${SDL2_LIBRARIES})