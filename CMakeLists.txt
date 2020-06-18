cmake_minimum_required(VERSION 2.8.7)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
include(FindPkgConfig)

PKG_SEARCH_MODULE(AUDACIOUS REQUIRED audacious>=3.9)
PKG_SEARCH_MODULE(GTK REQUIRED gtk+-3.0>=3.0.0)
add_definitions(${AUDACIOUS_CFLAGS} ${GTK_CFLAGS})
add_library(audacious-plugin-rpc SHARED audacious-plugin-rpc.cc)
target_link_libraries(audacious-plugin-rpc ${CMAKE_SOURCE_DIR}/libdiscord-rpc.a)

PKG_GET_VARIABLE(AUDACIOUS_PLUGIN_DIR audacious plugin_dir)
set(INSTALL_DIR "${AUDACIOUS_PLUGIN_DIR}/General")

install(TARGETS audacious-plugin-rpc LIBRARY DESTINATION ${INSTALL_DIR})
