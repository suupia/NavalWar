cmake_minimum_required(VERSION 3.12)
project(NavalWar CXX)

# Linux build of the NavalWar2 tree (OpenSiv3D v0.6.16, NavalWar2.sln).
# Install Siv3D first (Linux/ configure, build, cmake --install), then:
#   cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
#   cmake --build build

if (NOT CMAKE_CONFIGURATION_TYPES AND
	NOT CMAKE_NO_BUILD_TYPE AND
	NOT CMAKE_BUILD_TYPE AND
	CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
	message(STATUS "[!] Setting build type to 'Release' as none was specified.")
	set(CMAKE_BUILD_TYPE Release)
endif()

set(GAME_DIR ${CMAKE_CURRENT_SOURCE_DIR}/NavalWar2)

add_executable(NavalWar
	${GAME_DIR}/Main.cpp
	${GAME_DIR}/GameManager.cpp
	${GAME_DIR}/Font/FontSize.cpp
	${GAME_DIR}/GameObjects/Currency.cpp
	${GAME_DIR}/GameObjects/GameObject.cpp
	${GAME_DIR}/GameObjects/Ship.cpp
	${GAME_DIR}/GameObjects/ShipContainer.cpp
	${GAME_DIR}/GameObjects/SortieButton.cpp
)

target_include_directories(NavalWar PRIVATE ${GAME_DIR})
# Linux headers take the real SSE path only when __SSE4_2__ is defined.
target_compile_options(NavalWar PRIVATE -include stdafx.h -msse4.2)
target_compile_features(NavalWar PRIVATE cxx_std_20)

find_package(Siv3D REQUIRED)
target_link_libraries(NavalWar PUBLIC Siv3D::Siv3D)
