PROJECT(logitechapplet)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
FIND_PACKAGE( KDE4 REQUIRED )
#if you don't want the full compiler output, remove the following line
SET(CMAKE_VERBOSE_MAKEFILE OFF)
#So that cmake can find local cmake files
SET( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" )
ADD_SUBDIRECTORY(src)
