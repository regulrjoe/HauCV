cmake_minimum_required(VERSION 3.13)

project(FrontDoor CXX)

set(OPENCV_VERSION 4.0.1)

#------------------------
# Create library
add_library(fdlib
	STATIC
		src/body_detector.cc
		src/fd_builder.cc
		src/fd_state.cc
		src/fd_system.cc
		src/fd_timers.cc
)


# Find dependencies
find_package(OpenCV ${OPENCV_VERSION} REQUIRED)

# Add headers
target_include_directories(fdlib
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
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

#------------------------
# Create executable
add_executable(front_door main.cc)

# Add headers
target_include_directories(front_door
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link library
target_link_libraries(front_door 
	fdlib
)

# Add compile options
target_compile_options(front_door PRIVATE -g)

