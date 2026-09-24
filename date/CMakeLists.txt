add_library(date date.cpp)

target_include_directories(date PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(date PROPERTIES OUTPUT_NAME "util_date")