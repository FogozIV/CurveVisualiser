cmake_minimum_required(VERSION 3.20)
project(CurveVisualiser)

set(CMAKE_CXX_STANDARD 20)
set(CURVE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/CurveLibrary)
# Add CurveLibrary subdirectory
add_subdirectory(${CURVE_LIB_DIR})

# Python Auto-Detection with improved library finding
find_package(Python REQUIRED COMPONENTS Interpreter Development)
execute_process(
        COMMAND ${Python_EXECUTABLE} -c "import numpy; print(numpy.get_include())"
        OUTPUT_VARIABLE NUMPY_INCLUDE_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# MinGW-specific fixes
if(MINGW)
    add_compile_definitions(
            NPY_NO_DEPRECATED_API=NPY_1_7_API_VERSION
            PY_SSIZE_T_CLEAN
    )

    # Workaround for MinGW Python library naming
    set(PYTHON_LIB_NAME "python${Python_VERSION_MAJOR}${Python_VERSION_MINOR}")
    find_library(PYTHON_LIB
            NAMES ${PYTHON_LIB_NAME}
            PATHS "${Python_LIBRARY_DIRS}"
            REQUIRED
    )
endif()

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${Python_INCLUDE_DIRS}
        ${NUMPY_INCLUDE_DIR}
        ${CURVE_LIB_DIR}/include
)

add_executable(CurveVisualiser main.cpp)
# Platform-specific linking
if(WIN32)
    if(MINGW)
        # MinGW-specific linking
        target_link_libraries(CurveVisualiser
                CurveLibrary
                EurobotCoreMath  # Explicitly link the math library
                ${PYTHON_LIB}  # Use the library we found
                -Wl,--as-needed
        )
        # Add MinGW-specific link options
        target_link_options(CurveVisualiser PRIVATE
                -static-libgcc
                -static-libstdc++
        )
    else()
        # MSVC linking
        target_link_libraries(CurveVisualiser
                CurveLibrary
                EurobotCoreMath  # Explicitly link the math library
                ${Python_LIBRARIES}
        )
    endif()
endif()