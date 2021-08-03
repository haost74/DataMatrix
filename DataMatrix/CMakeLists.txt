# CMakeList.txt: проект CMake для DataMatrix; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (DataMatrix "DataMatrix.cpp" "DataMatrix.h" 
							"src/Raizen.h" "src/Stream.h" "src/Stream.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
