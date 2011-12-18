project( TrigramKata )

cmake_minimum_required( VERSION 2.6 )

set ( CMAKE_BUILD_TYPE Release )

add_definitions ( -Wall )

include_directories (
	${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
	$ENV{GMOCK_ROOT}/include
	$ENV{GTEST_ROOT}/include)

link_directories ( $ENV{GMOCK_ROOT} $ENV{GTEST_ROOT} )

set ( TrigramKata_HDRS
	Trigram.h
	)

set ( TrigramKata_SRCS
	main.cpp
	TrigramTest.cpp
	Trigram.cpp
	)

add_executable ( TrigramKata ${TrigramKata_SRCS} )

target_link_libraries ( TrigramKata gmock gtest pthread )
