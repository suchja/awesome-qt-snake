qt_add_library(snakecore STATIC
    game.h
    game.cpp
    snake.h
    snake.cpp
    foodgenerator.h
    foodgenerator.cpp
    snakecore.h
)
target_link_libraries(snakecore PRIVATE Qt6::Core)
target_include_directories(snakecore INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
