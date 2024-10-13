cmake_minimum_required(VERSION 3.22)

# Название проекта
project(Game VERSION 1.0)

# Устанавливаем стандарт C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем исполняемый файл для клиента
add_executable(client client.cpp
                       Player.cpp
                       GameField.cpp
                       ConnectionManager.cpp)

# Подключаем библиотеку ncurses
find_package(Curses REQUIRED)
target_link_libraries(client ${CURSES_LIBRARIES})

# Включаем поддержку клавиш-стрелок в ncurses
target_compile_definitions(client PRIVATE _XOPEN_SOURCE_EXTENDED)

# Устанавливаем опции для режимов сборки
set(CMAKE_DEBUG_POSTFIX d)  # Добавляем суффикс 'd' для отладочных версий
set(CMAKE_RELEASE_POSTFIX r) # Добавляем суффикс 'r' для релизных версий

# # Устанавливаем флаги компиляции для разных режимов
# # Режим Debug
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
# # Режим Release
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# # # # # # Сервер
# # Добавляем исполняемый файл для сервера
# add_executable(server server.cpp
#                        Player.cpp
#                        GameField.cpp)