cmake_minimum_required(VERSION 3.23)
project(Geo23d)

include_directories(libgraphics simpleGUI Headers BackGeobj Evic)

aux_source_directory(libgraphics SRC_L)
aux_source_directory(simpleGUI SRC_S)
aux_source_directory(SourceFiles SRC_M)
aux_source_directory(BackGeobj SRC_G)
aux_source_directory(Evic SRC_E)

add_executable(geo23d ${SRC_M} ${SRC_S} ${SRC_L} ${SRC_G} ${SRC_E})