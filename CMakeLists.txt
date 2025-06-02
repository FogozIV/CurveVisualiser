cmake_minimum_required(VERSION 3.20)
project(CurveVisualiser)

set(CMAKE_CXX_STANDARD 20)

# Set this before find_package(Python) to prevent debug suffix issues
if(MSVC)
    set(Python_FIND_ABI "OFF" "ANY" "ANY")  # Disable debug library search
endif()

set(CURVE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/CurveLibrary)
add_subdirectory(${CURVE_LIB_DIR})

# Python detection - now won't look for debug versions
find_package(Python REQUIRED COMPONENTS Interpreter Development)

# For MSVC: Explicitly use the release library
if(MSVC)
    # Get the actual library path without _d suffix
    get_filename_component(PYTHON_LIB_DIR ${Python_LIBRARY_RELEASE} DIRECTORY)
    get_filename_component(PYTHON_LIB_NAME ${Python_LIBRARY_RELEASE} NAME)

    # Force this library for all configurations
    set(Python_LIBRARIES "${PYTHON_LIB_DIR}/${PYTHON_LIB_NAME}")
endif()

# NumPy include detection
execute_process(
        COMMAND ${Python_EXECUTABLE} -c "import numpy; print(numpy.get_include())"
        OUTPUT_VARIABLE NUMPY_INCLUDE_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${Python_INCLUDE_DIRS}
        ${NUMPY_INCLUDE_DIR}
        ${CURVE_LIB_DIR}/include
)

add_executable(CurveVisualiser main.cpp)

if(WIN32)
    if(MINGW)
        # MinGW-specific setup
        add_compile_definitions(
                NPY_NO_DEPRECATED_API=NPY_1_7_API_VERSION
                PY_SSIZE_T_CLEAN
        )
        target_link_libraries(CurveVisualiser
                CurveLibrary
                EurobotCoreMath
                "${Python_LIBRARY_RELEASE}"  # Explicitly use release version
        )
        target_link_options(CurveVisualiser PRIVATE
                -static-libgcc
                -static-libstdc++
        )
    else()
        # MSVC linking - uses our forced library path
        target_link_libraries(CurveVisualiser
                CurveLibrary
                EurobotCoreMath
                ${Python_LIBRARIES}
                debug "${Python_LIBRARY_RELEASE}"  # Important override
                optimized "${Python_LIBRARY_RELEASE}"
        )
    endif()
endif()