cmake_minimum_required(VERSION 3.25)

project(cpp_studies LANGUAGES CXX)

include(CTest)

# Global C++ settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Put all executables into one clean bin directory inside the build tree.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Helper function for study chapters.
#
# It automatically creates one executable target for every:
#
#   ex_*.cpp
#   demo_*.cpp
#
# in the current directory.
#
# Other .cpp files are ignored by this function, so they can later be used
# as implementation/support files without accidentally becoming executables.
function(add_cpp_study_examples target_prefix)
    set(options)
    set(one_value_args)
    set(multi_value_args LINK_LIBRARIES INCLUDE_DIRS SOURCES)

    cmake_parse_arguments(ARG
        "${options}"
        "${one_value_args}"
        "${multi_value_args}"
        ${ARGN}
    )

    file(GLOB example_sources CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/ex_*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/demo_*.cpp"
    )

    foreach(source_file IN LISTS example_sources)
        get_filename_component(source_name "${source_file}" NAME_WE)

        set(target_name "${target_prefix}_${source_name}")

        add_executable(${target_name}
            "${source_file}"
            ${ARG_SOURCES}
        )

        target_compile_features(${target_name} PRIVATE cxx_std_20)

        if(ARG_INCLUDE_DIRS)
            target_include_directories(${target_name}
                PRIVATE
                    ${ARG_INCLUDE_DIRS}
            )
        endif()

        if(ARG_LINK_LIBRARIES)
            target_link_libraries(${target_name}
                PRIVATE
                    ${ARG_LINK_LIBRARIES}
            )
        endif()

        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(${target_name}
                PRIVATE
                    -Wall
                    -Wextra
                    -Wpedantic
            )
        elseif(MSVC)
            target_compile_options(${target_name}
                PRIVATE
                    /W4
            )
        endif()
    endforeach()
endfunction()

# Create and register CTest tests from all test_*.cpp files
# in the current directory.
#
# Each file becomes a target named:
#
#   <target_prefix>_<filename_without_extension>
#
# Optional arguments:
#   LINK_LIBRARIES, INCLUDE_DIRS, SOURCES
#
# Requires include(CTest) at the project root.
function(add_cpp_study_tests target_prefix)
    set(options)
    set(one_value_args)
    set(multi_value_args LINK_LIBRARIES INCLUDE_DIRS SOURCES)

    cmake_parse_arguments(ARG
        "${options}"
        "${one_value_args}"
        "${multi_value_args}"
        ${ARGN}
    )

    file(GLOB test_sources CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/test_*.cpp"
    )

    foreach(source_file IN LISTS test_sources)
        get_filename_component(source_name "${source_file}" NAME_WE)

        set(target_name "${target_prefix}_${source_name}")

        add_executable(${target_name}
            "${source_file}"
            ${ARG_SOURCES}
        )

        target_compile_features(${target_name} PRIVATE cxx_std_20)

        if(ARG_INCLUDE_DIRS)
            target_include_directories(${target_name}
                PRIVATE
                    ${ARG_INCLUDE_DIRS}
            )
        endif()

        if(ARG_LINK_LIBRARIES)
            target_link_libraries(${target_name}
                PRIVATE
                    ${ARG_LINK_LIBRARIES}
            )
        endif()

        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(${target_name}
                PRIVATE
                    -Wall
                    -Wextra
                    -Wpedantic
            )
        elseif(MSVC)
            target_compile_options(${target_name}
                PRIVATE
                    /W4
            )
        endif()

        add_test(
            NAME ${target_name}
            COMMAND ${target_name}
        )
    endforeach()
endfunction()

# Books / book groups
add_subdirectory(learning-cpp/stroustrup)