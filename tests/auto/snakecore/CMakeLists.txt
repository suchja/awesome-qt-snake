set(TEST_SOURCES
    test_game.cpp
    test_snake.cpp
    test_foodgenerator.cpp
)

foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_executable(${test_name} ${test_source})
    target_link_libraries(${test_name} Qt6::Test snakecore)
    target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR}/../../../src/snakecore)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
