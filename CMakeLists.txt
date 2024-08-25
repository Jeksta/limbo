cmake_minimum_required(VERSION 3.5.0)

set(project_name rumba)

project(${project_name} 
VERSION 0.1.0 
LANGUAGES CXX
)

set(lib_path ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(includes_path ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(src_path ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable( ${project_name} ${src_path}/main.cpp)

# <includes>
function(include_dir dir)
    file(GLOB_RECURSE cpps ${src_path}/${dir}/*.cpp)
    target_sources(${project_name} PRIVATE ${cpps})
    target_include_directories(${project_name} PUBLIC ${includes_path}/${dir})
endfunction()
    
list(APPEND include_dirs utils)
list(APPEND include_dirs scanner)
list(APPEND include_dirs lexer)
list(APPEND include_dirs parser)
list(APPEND include_dirs parser/expression)
list(APPEND include_dirs parser/expression/unary)
list(APPEND include_dirs parser/expression/binary)
list(APPEND include_dirs parser/expression/literal)
list(APPEND include_dirs interpreter)
list(APPEND include_dirs interpreter/logic)
list(APPEND include_dirs interpreter/visitor)

foreach(dir IN LISTS include_dirs)
    include_dir(${dir})
endforeach()
# </includes>

# <libs>
target_include_directories(${project_name} PRIVATE ${lib_path}/magic_enum/include/magic_enum)
# </libs>

include(CTest)
enable_testing()

