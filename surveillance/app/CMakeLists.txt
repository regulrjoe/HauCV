cmake_minimum_required(VERSION 3.13)

project(Surveillance CXX)

set(OPENCV_VERSION 4.0.1)
set(CPPZMQ_VERSION 4.3)

#------------------------
# Create library
add_library(srvlib
	SHARED
		src/motion_detector.cc
		src/utils/rcode.cc

		src/alarm/alarm.cc
		src/alarm/alarm_commands.cc
		src/alarm/alarm_states.cc
		src/alarm/alarm_facade.cc

		src/alert/alert.cc

		src/srv/builder.cc
		src/srv/system.cc
		src/srv/timer.cc
		src/srv/states.cc

)


# Find dependencies
find_package(OpenCV ${OPENCV_VERSION} REQUIRED)
find_package(cppzmq ${CPPZMQ_VERSION} REQUIRED)

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
		cppzmq
)

# Add compile opetions
target_compile_options(srvlib PRIVATE -Werror -g)

# Add compile features
target_compile_features(srvlib PRIVATE cxx_std_17)

#Add compile definitions
target_compile_definitions(srvlib 
	PUBLIC 
		#DBG_MACRO_DISABLE #flag to disable the dbg(…) macro (i.e. to make it a no-op)
		DBG_MACRO_NO_WARNING # flag to disable the "'dbg.h' header is included in your code base" warnings.
		#PRINT_INFO_MACRO_DISABLE #flag to disable the printINFO(_) macro.
		#PRINT_ERROR__MACRO_DISABLE #flag to disable the printERROR(_) macro.
) 

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
	cppzmq
)

# Add compile options
target_compile_options(surveillance PRIVATE -g)

