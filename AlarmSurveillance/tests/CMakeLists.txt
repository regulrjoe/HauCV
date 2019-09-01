cmake_minimum_required(VERSION 3.13)

project(FrontDoor CXX)

set(OPENCV_VERSION 4.0.1)

#------------------------
# Create library
add_library(asvlib
	STATIC
		../src/body_detector.cc
		../src/asv_builder.cc
		../src/asv_state.cc
		../src/asv_system.cc
		../src/asv_timer.cc
		../src/notifier.cc
		../src/retval.cc
		../src/sound_controller.cc
		../src/video_recorder.cc
)


# Find dependencies
find_package(OpenCV ${OPENCV_VERSION} REQUIRED)

# Add headers
target_include_directories(asvlib
	PUBLIC
		$<INSTALL_INTERFACE:/../include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
		${OpenCV_INCLUDE_DIRS}
)

# Link dependencies
target_link_libraries(asvlib
	PRIVATE
		${OpenCV_LIBS}
)

# Add compile opetions
target_compile_options(asvlib PRIVATE -Werror)

# Add compile features
target_compile_features(asvlib PRIVATE cxx_std_17)
 
#Add compile definitions
target_compile_definitions(asvlib PUBLIC NDEBUG) #Comment to print. Uncomment to not print.

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
	asvlib
	gtest
	gtest_main
)

# Add compile options
target_compile_options(tests PRIVATE -g)

# Add compile features
target_compile_features(tests PRIVATE cxx_std_17)
