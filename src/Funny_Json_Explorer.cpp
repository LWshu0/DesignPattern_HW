#include <iostream>
#include <string>

#include "JsonIcon/JsonIcon.h"
#include "JsonRenderer/TreeRendererFactory.h"
#include "JsonRenderer/RectRendererFactory.h"
#include "JsonRenderer/OriginRendererFactory.h"
#include "JsonLoader/JsonLoader.h"

int main()
{
    JsonLoader loader;
    loader.load("test.json");

    TreeRendererFactory tree_factory;
    RectRendererFactory rect_factory;
    OriginRendererFactory origin_factory;

    std::string result = loader.draw(&tree_factory);
    std::cout << result << std::endl;

    result = loader.draw(&rect_factory);
    std::cout << result << std::endl;

    result = loader.draw(&origin_factory);
    std::cout << result << std::endl;

    loader.load("test2.json");

    result = loader.draw(&tree_factory);
    std::cout << result << std::endl;

    result = loader.draw(&rect_factory);
    std::cout << result << std::endl;

    result = loader.draw(&origin_factory);
    std::cout << result << std::endl;

}