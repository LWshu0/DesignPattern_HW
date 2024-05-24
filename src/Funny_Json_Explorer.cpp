#include <iostream>
#include <string>

#include "JsonLoader/JsonLoader.h"
#include "JsonRenderer/TreeRenderer.h"
#include "JsonRenderer/RectRenderer.h"
#include "JsonIcon/PokerIcon.h"
int main()
{
    JsonLoader loader;
    PokerIcon icon;
    TreeRenderer tree_renderer(&icon);
    RectRenderer rect_renderer(&icon);
    loader.load("test.json");
    // loader.output("test_output.json");
    std::string result = loader.draw(&rect_renderer);
    // std::string result = loader.draw(&tree_renderer);
    std::cout << result;
    
}