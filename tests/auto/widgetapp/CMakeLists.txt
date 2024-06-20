set(TEST_SOURCES
    test_gameviewmodel.cpp
)

foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_executable(${test_name} ${test_source})
    target_link_libraries(${test_name}
        Qt6::Test
        snakecore
        AwesomeQtSnakeLib
    )
    target_include_directories(${test_name} PRIVATE
        ${CMAKE_SOURCE_DIR}/../../../src/snakecore
        ${CMAKE_SOURCE_DIR}/../../../src/widgetapp
    )
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
