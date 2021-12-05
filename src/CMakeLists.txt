add_executable(opt opt.cpp)

target_include_directories(opt PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(opt PRIVATE KALIEDOSCOPE_LIB)
