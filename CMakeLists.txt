cmake_minimum_required(VERSION 2.8)

project(nbody)
add_executable(nbody glrender.cpp sample.cpp)

# Найдём OpenGL
find_package(OpenGL REQUIRED)
# Найдём FreeGLUT
find_package(GLUT REQUIRED)

# Теперь можно выставить директории с header-ами
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

# И указать библиотеки для линковки
target_link_libraries(nbody ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})