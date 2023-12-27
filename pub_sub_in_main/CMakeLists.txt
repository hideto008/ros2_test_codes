cmake_minimum_required(VERSION 3.8)
project(pub_sub_in_main)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)

add_executable(pub_sub_in_main src/main.cpp)
ament_target_dependencies(pub_sub_in_main
rclcpp example_interfaces
)

install(TARGETS
  pub_sub_in_main
  DESTINATION lib/${PROJECT_NAME}
)


ament_package()
