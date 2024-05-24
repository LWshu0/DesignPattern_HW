#include <iostream>
#include <string>

#include "JsonIcon/JsonIcon.h"
#include "JsonRenderer/TreeRendererFactory.h"
#include "JsonRenderer/RectRendererFactory.h"
#include "JsonLoader/JsonLoader.h"

int main()
{
    JsonLoader loader;
    loader.load("test.json");

    TreeRendererFactory tree_factory("icon.config");
    RectRendererFactory rect_factory("icon_ext.config");
    
    // loader.output("test_output.json");
    std::string result = loader.draw(&tree_factory);
    std::cout << result;

    result = loader.draw(&rect_factory);
    std::cout << result;
    
}