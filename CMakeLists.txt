cmake_minimum_required(VERSION 3.25)

option(BUILD_FOR_DOS "Build ${PROGRAM_NAME} for DOS using DJGPP" off)
option(BUILD_FOR_OLDWIN "Build ${PROGRAM_NAME} using msvcrt20 (Mingw-w64 Required)" off)
option(BUILD_SHARED_LIBS "Build shared version of libFrank" off)
option(BUILD_ONLY_LIBRARY "Build only libFrank" off)

project(FrankC LANGUAGES C VERSION 1.2)

if(BUILD_FOR_DOS)
	set(CMAKE_C_COMPILER "i586-pc-msdosdjgpp-gcc")
elseif(BUILD_FOR_OLDWIN)
	set(CMAKE_C_FLAGS "-mcrtdll=msvcrt20 -march=i586")
endif()

set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
set(CMAKE_C_FLAGS_RELEASE "-s -O2")

if(NOT BUILD_ONLY_LIBRARY)
	file(GLOB SOURCE_FILES "src/*.c")
endif()

if(BUILD_SHARED_LIBS)
	if (BUILD_FOR_DOS)
		message(FATAL_ERROR "You can't build a shared library when compiling for DOS")
	else()
		add_library(Frank SHARED src/libFrank/frank.c)
	endif()
else()
	add_library(Frank STATIC src/libFrank/frank.c)
endif()

if(NOT BUILD_ONLY_LIBRARY)
	configure_file(src/progInfo.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/progInfo.h @ONLY)
endif()

if(NOT BUILD_ONLY_LIBRARY)
	add_executable(${PROJECT_NAME} ${SOURCE_FILES})
	target_link_libraries(${PROJECT_NAME} Frank)
	if(BUILD_FOR_DOS)
		set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".exe")
	endif()
	target_include_directories(${PROJECT_NAME} PRIVATE src/)
endif()