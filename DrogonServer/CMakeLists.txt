# CMakeList.txt : CMake project for DrogonServer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (DrogonServer "DrogonServer.cpp" "DrogonServer.h" "pages/Home/HomePageController.cpp" "pages/JSON/JsonController.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DrogonServer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
find_package(Drogon CONFIG REQUIRED)
target_link_libraries(DrogonServer PRIVATE Drogon::Drogon)