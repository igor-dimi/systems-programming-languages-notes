add_library(cpp_learning_stroustrup_ch05_lib
    src/vector.cpp
)

target_include_directories(cpp_learning_stroustrup_ch05_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_cpp_study_examples(cpp_learning_stroustrup_ch05
    LINK_LIBRARIES cpp_learning_stroustrup_ch05_lib
)