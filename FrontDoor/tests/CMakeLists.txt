cmake_minimum_required(VERSION 3.13)

project(FrontDoor CXX)

set(OPENCV_VERSION 4.0.1)

#------------------------
# Create library
add_library(fdlib
	STATIC
		../src/body_detector.cc
		../src/fd_builder.cc
		../src/fd_state.cc
		../src/fd_system.cc
		../src/fd_timer.cc
		../src/notifier.cc
		../src/retval.cc
)


# Find dependencies
find_package(OpenCV ${OPENCV_VERSION} REQUIRED)

# Add headers
target_include_directories(fdlib
	PUBLIC
		$<INSTALL_INTERFACE:/../include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
		${OpenCV_INCLUDE_DIRS}
)

# Link dependencies
target_link_libraries(fdlib
	PRIVATE
		${OpenCV_LIBS}
)

# Add compile opetions
target_compile_options(fdlib PRIVATE -Werror)

# Add compile features
target_compile_features(fdlib PRIVATE cxx_std_17)
 
#Add compile definitions
target_compile_definitions(fdlib PUBLIC NDEBUG) #Comment to print. Uncomment to not print.

#------------------------
# Create executable
add_executable(tests tests.cc)

# Add headers
target_include_directories(tests
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/../include
		/opt/googletest/include
)

# Add Library paths
target_link_directories(tests
	PRIVATE
		/opt/googletest/lib
)

# Link library
target_link_libraries(tests 
	fdlib
	gtest
	gtest_main
)

# Add compile options
target_compile_options(tests PRIVATE -g)

# Add compile features
target_compile_features(tests PRIVATE cxx_std_17)
