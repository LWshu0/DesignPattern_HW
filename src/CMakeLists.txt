aux_source_directory(JsonLoader JSONLOADER_SRC)
add_library(jsonloader OBJECT ${JSONLOADER_SRC})

aux_source_directory(JsonIcon JSONICON_SRC)
add_library(jsonicon OBJECT ${JSONICON_SRC})

aux_source_directory(JsonRenderer JSONRENDERER_SRC)
add_library(jsonrenderer OBJECT ${JSONRENDERER_SRC})

add_executable(Funny_Json_Explorer Funny_Json_Explorer.cpp)

target_link_libraries(Funny_Json_Explorer PUBLIC jsonicon jsonrenderer jsonloader)