cmake_minimum_required(VERSION 3.16)
project(SmartAttendanceSystem VERSION 1.0 LANGUAGES CXX)

# ─────────────────────────────────────────────
#  C++ Standard
# ─────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ─────────────────────────────────────────────
#  Qt Setup
#  Required for Qt's code-generation tools
#  (MOC = Meta-Object Compiler, for signals/slots)
# ─────────────────────────────────────────────
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# ─────────────────────────────────────────────
#  Find Qt
#  Tries Qt6 first, falls back to Qt5.
#  Components we need:
#    Widgets  → windows, buttons, layouts
#    Core     → signals/slots, threading
#    Gui      → image display
# ─────────────────────────────────────────────
find_package(Qt6 COMPONENTS Widgets Core Gui QUIET)
if(NOT Qt6_FOUND)
    message(STATUS "Qt6 not found, trying Qt5...")
    find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)
    set(QT_VERSION_MAJOR 5)
else()
    set(QT_VERSION_MAJOR 6)
endif()
message(STATUS "Using Qt${QT_VERSION_MAJOR}")

# ─────────────────────────────────────────────
#  Find OpenCV
#  Components we need:
#    core       → basic data structures (Mat, etc.)
#    imgproc    → image processing (resize, colour convert)
#    highgui    → window display (imshow)
#    videoio    → webcam / VideoCapture
#    objdetect  → Haar Cascade face detection
#    face       → LBPH face recognizer
#               ↑ this is in opencv_contrib — see README
# ─────────────────────────────────────────────
find_package(OpenCV REQUIRED COMPONENTS
    core
    imgproc
    highgui
    videoio
    objdetect
    face        # From opencv_contrib — LBPH recognizer lives here
)
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")

# ─────────────────────────────────────────────
#  Find SQLite3
#  On Linux/macOS: sudo apt install libsqlite3-dev
#                  brew install sqlite
#  On Windows:     download sqlite3.h + sqlite3.c from
#                  https://www.sqlite.org/download.html
#                  and place them in a "sqlite/" folder
#                  (see the fallback block below)
# ─────────────────────────────────────────────
find_package(SQLite3 QUIET)

if(NOT SQLite3_FOUND)
    message(STATUS "SQLite3 system package not found.")
    message(STATUS "Looking for bundled sqlite/ folder...")

    if(EXISTS "${CMAKE_SOURCE_DIR}/sqlite/sqlite3.h")
        message(STATUS "Found bundled SQLite — using sqlite/sqlite3.c")
        # We compile SQLite directly from its single .c source file.
        # This is perfectly normal and is the "amalgamation" approach
        # recommended by the SQLite team for embedding.
        add_library(sqlite3_bundled STATIC
            sqlite/sqlite3.c
        )
        target_include_directories(sqlite3_bundled PUBLIC
            ${CMAKE_SOURCE_DIR}/sqlite
        )
        set(SQLITE3_LIBRARIES sqlite3_bundled)
        set(SQLITE3_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/sqlite")
    else()
        message(FATAL_ERROR
            "SQLite3 not found.\n"
            "Option A (Linux/macOS): sudo apt install libsqlite3-dev  OR  brew install sqlite\n"
            "Option B (all OS):      Download sqlite-amalgamation from https://www.sqlite.org/download.html\n"
            "                        Extract sqlite3.h and sqlite3.c into a 'sqlite/' folder in the project root."
        )
    endif()
else()
    message(STATUS "SQLite3 found: ${SQLite3_VERSION}")
    set(SQLITE3_LIBRARIES SQLite::SQLite3)
    set(SQLITE3_INCLUDE_DIRS "")   # Already handled by the imported target
endif()

# ─────────────────────────────────────────────
#  Source Files
#  Add your .cpp files here as the project grows.
#  Keep main.cpp small — it should just launch the app.
# ─────────────────────────────────────────────
set(SOURCES
    src/main.cpp

    # Uncomment these as you create each module:
    # src/database/DatabaseManager.cpp
    # src/auth/LoginWindow.cpp
    # src/registration/FaceRegistration.cpp
    # src/attendance/AttendanceMarker.cpp
    # src/records/RecordsViewer.cpp
)

# ─────────────────────────────────────────────
#  Webcam Test Executable
#  A standalone test — lets each team member verify
#  that OpenCV + webcam works before touching Qt or SQLite.
#  Build it with:  cmake --build . --target webcam_test
# ─────────────────────────────────────────────
add_executable(webcam_test
    tests/webcam_test.cpp
)
target_link_libraries(webcam_test PRIVATE
    ${OpenCV_LIBS}
)
target_include_directories(webcam_test PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)

# ─────────────────────────────────────────────
#  Main Application Executable
# ─────────────────────────────────────────────
add_executable(${PROJECT_NAME}
    ${SOURCES}
)

# Link all three libraries to the main app
target_link_libraries(${PROJECT_NAME} PRIVATE
    # Qt
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui

    # OpenCV
    ${OpenCV_LIBS}

    # SQLite
    ${SQLITE3_LIBRARIES}
)

# Make headers findable via #include "..."
target_include_directories(${PROJECT_NAME} PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ${SQLITE3_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src   # So you can do #include "database/DatabaseManager.h" etc.
)

# ─────────────────────────────────────────────
#  Windows-specific: Copy Qt DLLs next to the .exe
#  Without this, the .exe won't run on Windows
#  because it can't find the Qt runtime DLLs.
# ─────────────────────────────────────────────
if(WIN32 AND QT_VERSION_MAJOR EQUAL 6)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND Qt6::windeployqt
        ARGS "$<TARGET_FILE:${PROJECT_NAME}>"
        COMMENT "Running windeployqt to copy Qt DLLs..."
    )
elseif(WIN32 AND QT_VERSION_MAJOR EQUAL 5)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND Qt5::windeployqt
        ARGS "$<TARGET_FILE:${PROJECT_NAME}>"
        COMMENT "Running windeployqt to copy Qt DLLs..."
    )
endif()

# ─────────────────────────────────────────────
#  Print a summary so you know everything was found
# ─────────────────────────────────────────────
message(STATUS "")
message(STATUS "======= Smart Attendance System — Build Summary =======")
message(STATUS "  C++ Standard : C++${CMAKE_CXX_STANDARD}")
message(STATUS "  Qt Version   : ${QT_VERSION_MAJOR}")
message(STATUS "  OpenCV       : ${OpenCV_VERSION}")
message(STATUS "  Build Type   : ${CMAKE_BUILD_TYPE}")
message(STATUS "=======================================================")
message(STATUS "")
