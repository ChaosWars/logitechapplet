PROJECT(logitechapplet)

#if you don't want the full compiler output, remove the following line
SET(CMAKE_VERBOSE_MAKEFILE OFF)

#add definitions, compiler switches, etc.
ADD_DEFINITIONS(-Wall -O2)

#So that cmake can find local cmake files
SET( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" )

ADD_SUBDIRECTORY(src)
