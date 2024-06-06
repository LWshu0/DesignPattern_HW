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

    TreeRendererFactory tree_factory_noicon;
    RectRendererFactory rect_factory_noicon;
    TreeRendererFactory tree_factory("icon.config");
    RectRendererFactory rect_factory("icon_ext.config");
    OriginRendererFactory origin_factory;

    // 风格 1
    std::string result = loader.draw(&tree_factory_noicon);
    std::cout << result << std::endl;
    // 风格 2
    result = loader.draw(&rect_factory_noicon);
    std::cout << result << std::endl;
    // 图标 1
    result = loader.draw(&tree_factory);
    std::cout << result << std::endl;
    // 图标 2
    result = loader.draw(&rect_factory);
    std::cout << result << std::endl;

    loader.load("test2.json");
    // 短文件测试
    result = loader.draw(&tree_factory);
    std::cout << result << std::endl;
    // 短文件测试
    result = loader.draw(&rect_factory);
    std::cout << result << std::endl;
    // 短文件测试
    result = loader.draw(&origin_factory);
    std::cout << result << std::endl;
}