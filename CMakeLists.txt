cmake_minimum_required(VERSION 3.10)
project(Physics)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(
        "$<$<CONFIG:RELEASE>:-O3>"
        "$<$<CONFIG:DEBUG>:-O0>"
)

set(CMAKE_AUTOMOC ON) # Enable Qt MOC compiler
set(CMAKE_AUTORCC ON) # Enable Qt resources compiler
set(CMAKE_AUTOUIC ON) # Enable Qt UI compiler

set(CMAKE_PREFIX_PATH ${Qt_DIR})

# Set Qt version
set(QT_VERSION 5)
# Set necessary Qt modules
set(REQUIRED_LIBS Core Multimedia Network WebSockets Widgets)
# Set corresponding Qt libraries
set(REQUIRED_LIBS_QUALIFIED
        Qt5::Core
        Qt5::Multimedia
        Qt5::Network
        Qt5::WebSockets
        Qt5::Widgets)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall")

# ThreadSanitizer
set(TSAN_FLAGS
        "-fsanitize=thread"
        CACHE STRING "Flags used by the C++ compiler during ThreadSanitizer builds."
        FORCE)

# AddressSanitize
set(ASAN_FLAGS
        "-fsanitize=address -fno-optimize-sibling-calls -fsanitize-address-use-after-scope -fno-omit-frame-pointer"
        CACHE STRING "Flags used by the C++ compiler during AddressSanitizer builds."
        FORCE)

# LeakSanitizer
set(LSAN_FLAGS
        "-fsanitize=leak -fno-omit-frame-pointer"
        CACHE STRING "Flags used by the C++ compiler during LeakSanitizer builds."
        FORCE)

# MemorySanitizer
set(MSAN_FLAGS
        "-fsanitize=memory -fno-optimize-sibling-calls -fsanitize-memory-track-origins=2 -fno-omit-frame-pointer"
        CACHE STRING "Flags used by the C++ compiler during MemorySanitizer builds."
        FORCE)

# UndefinedBehaviour
set(UBSAN_FLAGS
        "-fsanitize=undefined"
        CACHE STRING "Flags used by the C++ compiler during UndefinedBehaviourSanitizer builds."
        FORCE)

# Build Types
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ${UBSAN_FLAGS}")

# Add code files
set(SOURCES
        main.cpp
#        PhysicsObject/physics_object.cpp
#        PhysicsObject/physics_object.h
#        PhysicsObject/StaticObject/StaticObject.cpp
#        PhysicsObject/StaticObject/StaticObject.h
#        PhysicsObject/RectangleObject/rectangle_object.cpp
#        PhysicsObject/RectangleObject/rectangle_object.h
        GUI/MainWindow/main_window.cpp GUI/MainWindow/main_window.h
        Constants/constants.cpp Constants/constants.h
        Painter/painter.cpp Painter/painter.h
        Geometry/Line/line.h Geometry/Line/line.cpp
        Geometry/Point/point.cpp Geometry/Point/point.h
        Math/math.cpp Math/math.h
        Geometry/Segment/segment.cpp
        Geometry/Segment/segment.h
        Geometry/Polygon/polygon.cpp
        Geometry/Polygon/polygon.h
        Geometry/Circle/circle.cpp Geometry/Circle/circle.h)

# If necessary, add resources files
qt5_add_big_resources(RESOURCES_COMMON)

add_executable(Physics ${SOURCES} ${RESOURCES_COMMON})

target_link_libraries(Physics ${REQUIRED_LIBS_QUALIFIED})

