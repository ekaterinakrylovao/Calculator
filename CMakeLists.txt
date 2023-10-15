# CMakeList.txt: проект CMake для Calc; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Calc")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Calc   "Token.h" "Token.cpp" "RPN.h" "RPN.cpp" "main.cpp" "Variables.h" "Variables.cpp"  "Vector.cpp" "Vector.h" "MyDLLLoader.h" "MyDLLLoader.cpp")

add_custom_target(watch_plugins ALL)

add_custom_command(
    TARGET watch_plugins
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/plugins
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/plugins ${CMAKE_BINARY_DIR}/plugins
)

add_dependencies("Calc" watch_plugins)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Calc PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.