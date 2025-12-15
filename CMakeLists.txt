cmake_minimum_required(VERSION 3.0.2)

project(PPUViewer)

INCLUDE_DIRECTORIES (
   D:/Develope/Libs/Glut/include

)

find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5OpenGL)

find_package(OpenGL)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET( PPUViewer_SRCS
   main.cpp   
   PPUViewer.cpp
   PPUViewer.h
   RenderWidget.cpp
   RenderWidget.h
   IO/MeshModel.cpp
   IO/MeshModel.h
   IO/l3ds.cpp
   IO/l3ds.h
)

LINK_LIBRARIES(
   D:/Develope/Libs/Glut/Lib/glut32.lib
   debug      baselib/debug/baselib.lib
   optimized  baselib/release/baselib
   ${OPENGL_glu_LIBRARY}
   ${OPENGL_LIBRARY}
   opengl32.lib
)

SUBDIRS (baselib)

add_executable(PPUViewer ${PPUViewer_SRCS})

qt5_use_modules(PPUViewer Widgets OpenGL)
target_link_libraries(PPUViewer ${QT_LIBRARIES} ${OPENGL_LIBRARIES})