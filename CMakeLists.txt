# 指定 cmake 最低要求版本
cmake_minimum_required(VERSION 3.17)

# 设置项目名称及版本
project(my_c_study VERSION 1.0)

# 设置 C 标准
set(CMAKE_C_STANDARD 99)

# 添加可执行文件
add_executable(my_c_study main.c)

# 添加 库
add_subdirectory(
        math-function
        c-primer-plus-study
)
add_subdirectory(
        c-primer-plus-study/three-chapter
)
add_subdirectory(
        leetcode-study
)
add_subdirectory(
        my-test-code
)

# 指定编译目标(my_c_study)时包含的路径
# 这样才能找到 .h 文件
target_include_directories(my_c_study PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/math-function"
        "${PROJECT_SOURCE_DIR}/c-primer-plus-study"
        "${PROJECT_SOURCE_DIR}/c-primer-plus-study/three-chapter"
        )