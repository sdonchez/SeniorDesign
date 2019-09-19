# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("PrintCheck3D")

# Include sub-projects.
add_subdirectory ("vendor/openCV")
add_subdirectory ("vendor/raspicam")