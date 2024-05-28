aux_source_directory(JsonIcon JSONICON_SRC)
add_library(jsonicon OBJECT ${JSONICON_SRC})

aux_source_directory(JsonRenderer JSONRENDERER_SRC)
add_library(jsonrenderer OBJECT ${JSONRENDERER_SRC})

# 输出为静态库
aux_source_directory(JsonLoader JSONLOADER_SRC)
add_library(jsonloader STATIC ${JSONLOADER_SRC})
target_link_libraries(jsonloader PUBLIC jsonicon jsonrenderer)

add_executable(Funny_Json_Explorer Funny_Json_Explorer.cpp)

target_link_libraries(Funny_Json_Explorer PUBLIC jsonloader)

install(TARGETS jsonloader
        ARCHIVE DESTINATION lib)
install(DIRECTORY ${PROJECT_DIR}/include/
        DESTINATION include)