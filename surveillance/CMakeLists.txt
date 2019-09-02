cmake_minimum_required(VERSION 3.13)

project(Surveillance CXX)

set(OPENCV_VERSION 4.0.1)

#------------------------
# Create library
add_library(srvlib
	STATIC
		src/body_detector.cc
		src/notifier.cc
		src/retval.cc
		src/sound_controller.cc
		src/video_recorder.cc

		src/srv/builder.cc
		src/srv/state.cc
		src/srv/system.cc
		src/srv/timer.cc
)


# Find dependencies
find_package(OpenCV ${OPENCV_VERSION} REQUIRED)

# Add headers
target_include_directories(srvlib
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		${OpenCV_INCLUDE_DIRS}
)

# Link dependencies
target_link_libraries(srvlib
	PRIVATE
		${OpenCV_LIBS}
)

# Add compile opetions
target_compile_options(srvlib PRIVATE -Werror)

# Add compile features
target_compile_features(srvlib PRIVATE cxx_std_17)

#Add compile definitions
target_compile_definitions(srvlib PUBLIC NDEBUG) #Comment to print. Uncomment to not print.

#------------------------
# Create executable
add_executable(surveillance main.cc)

# Add headers
target_include_directories(surveillance
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link library
target_link_libraries(surveillance 
	srvlib
)

# Add compile options
target_compile_options(surveillance PRIVATE -g)

