cmake_minimum_required(VERSION 3.13)

project(AlarmSurveillance CXX)

set(OPENCV_VERSION 4.0.1)

#------------------------
# Create library
add_library(asvlib
	STATIC
		src/body_detector.cc
		src/asv_builder.cc
		src/asv_state.cc
		src/asv_system.cc
		src/asv_timer.cc
		src/notifier.cc
		src/retval.cc
		src/sound_controller.cc
		src/video_recorder.cc
)


# Find dependencies
find_package(OpenCV ${OPENCV_VERSION} REQUIRED)

# Add headers
target_include_directories(asvlib
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
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
add_executable(alarm_surveillance main.cc)

# Add headers
target_include_directories(alarm_surveillance
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link library
target_link_libraries(alarm_surveillance 
	asvlib
)

# Add compile options
target_compile_options(alarm_surveillance PRIVATE -g)

