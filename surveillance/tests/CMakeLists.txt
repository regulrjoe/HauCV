cmake_minimum_required(VERSION 3.13)

project(SurveillanceUT CXX)

set(OPENCV_VERSION 4.0.1)

#------------------------
# Create library
add_library(srvlib
	STATIC
		../src/body_detector.cc
		../src/notifier.cc
		../src/retval.cc
		../src/sound_controller.cc
		../src/video_recorder.cc

		../src/srv/builder.cc
		../src/srv/state.cc
		../src/srv/system.cc
		../src/srv/timer.cc
)


# Find dependencies
find_package(OpenCV ${OPENCV_VERSION} REQUIRED)

# Add headers
target_include_directories(srvlib
	PUBLIC
		$<INSTALL_INTERFACE:/../include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
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
add_executable(tests tests.cc)

# Add headers
target_include_directories(tests
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/../include
		${CMAKE_CURRENT_SOURCE_DIR}/include
		/opt/googletest/include
)

# Add Library paths
target_link_directories(tests
	PRIVATE
		/opt/googletest/lib
)

# Link library
target_link_libraries(tests 
	srvlib
	gtest
	gtest_main
)

# Add compile options
target_compile_options(tests PRIVATE -g)

# Add compile features
target_compile_features(tests PRIVATE cxx_std_17)
