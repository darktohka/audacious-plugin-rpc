cmake_minimum_required(VERSION 2.8.12)
project(audacious-rpc)

# General options
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Finding Audacious
include(FindPkgConfig)
PKG_SEARCH_MODULE(AUDACIOUS REQUIRED audacious>=3.9)
add_definitions(${AUDACIOUS_CFLAGS})

# Building discord-rpc
include(FetchContent)

option(BUILD_EXAMPLES "Build examples for discord-rpc" OFF)
FetchContent_Declare(
  discord-rpc
  URL https://github.com/discord/discord-rpc/archive/refs/heads/master.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP ON
)

FetchContent_MakeAvailable(discord-rpc)

if(IS_DIRECTORY "${discord-rpc_SOURCE_DIR}")
  set_property(DIRECTORY ${discord-rpc_SOURCE_DIR} PROPERTY EXCLUDE_FROM_ALL YES)
endif()

# Creating RPC plugin
add_library(audacious-plugin-rpc SHARED audacious-plugin-rpc.cc)
target_link_libraries(audacious-plugin-rpc discord-rpc)
message("${discord-rpc_SOURCE_DIR}/include")
target_include_directories(audacious-plugin-rpc PRIVATE "${discord-rpc_SOURCE_DIR}/include")

# Installing RPC plugin
PKG_GET_VARIABLE(AUDACIOUS_PLUGIN_DIR audacious plugin_dir)
set(INSTALL_DIR "${AUDACIOUS_PLUGIN_DIR}/General")

install(TARGETS audacious-plugin-rpc LIBRARY DESTINATION ${INSTALL_DIR})
