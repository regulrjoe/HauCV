cmake_minimum_required(VERSION 3.13)

project(SoundControllerExperimental CXX)

set(OPENCV_VERSION 4.0.1)
set(CPPZMQ_VERSION 4.3)

#------------------------
# Create library
add_library(sctrl
	SHARED
		src/alarm.cc
)


# Find dependencies
find_package(cppzmq ${CPPZMQ_VERSION} REQUIRED)

# Add headers
target_include_directories(sctrl
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Link dependencies
target_link_libraries(sctrl
	PRIVATE
		cppzmq
)

# Add compile opetions
target_compile_options(sctrl PRIVATE -Werror -g)

# Add compile features
target_compile_features(sctrl PRIVATE cxx_std_17)

#Add compile definitions
#target_compile_definitions(srvlib PUBLIC NDEBUG) #Comment to print. Uncomment to not print.

#------------------------
# Create executable
add_executable(exp main.cc)

# Add headers
target_include_directories(exp
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link library
target_link_libraries(exp 
	sctrl
	cppzmq
)

# Add compile options
target_compile_options(exp PRIVATE -g)

