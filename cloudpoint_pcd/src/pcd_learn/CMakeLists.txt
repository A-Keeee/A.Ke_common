cmake_minimum_required(VERSION 3.8)
project(pcd_learn)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 查找依赖项
find_package(ament_cmake REQUIRED)
find_package(PCL REQUIRED COMPONENTS io visualization)
find_package(VTK REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread)

# 包含目录
include_directories(${PCL_INCLUDE_DIRS})
include_directories(${VTK_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

# 添加可执行文件
add_executable(pcd_learn src/pcd_learn.cpp)

# 链接库文件
target_link_libraries(pcd_learn ${PCL_LIBRARIES} ${VTK_LIBRARIES} ${Boost_LIBRARIES})

# ament 目标依赖
ament_target_dependencies(pcd_learn)

# 安装可执行文件
install(TARGETS
  pcd_learn
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
