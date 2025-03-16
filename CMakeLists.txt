cmake_minimum_required(VERSION 3.14)
project(FAKApp)

# Настройка Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Поиск необходимых модулей Qt
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Добавление исходных файлов
set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
)

# Создание исполняемого файла
add_executable(FAKApp ${SOURCES})

# Подключение библиотек Qt
target_link_libraries(FAKApp PRIVATE Qt6::Core Qt6::Widgets)
