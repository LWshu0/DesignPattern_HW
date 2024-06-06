#include <iostream>
#include <string>
#include <cstring>

#include "JsonIcon/JsonIcon.h"
#include "JsonRenderer/TreeRendererFactory.h"
#include "JsonRenderer/RectRendererFactory.h"
#include "JsonRenderer/OriginRendererFactory.h"
#include "JsonLoader/JsonLoader.h"
#include "JsonLoader/FJE.h"

int main(int argc, char** argv)
{
    std::string json_path;
    std::string style;
    std::string icon_path;
    for (int i = 1;i < argc;i += 2)
    {
        if (0 == strcmp(argv[i], "-f"))
        {
            json_path = argv[i + 1];
        }
        else if (0 == strcmp(argv[i], "-s"))
        {
            style = argv[i + 1];
        }
        else if (0 == strcmp(argv[i], "-i"))
        {
            icon_path = argv[i + 1];
        }
    }
    FJE fje;
    fje.buildIcon(icon_path);
    if (style == "tree")
    {
        fje.buildRender(new TreeRendererFactory);
    }
    else if (style == "rect")
    {
        fje.buildRender(new RectRendererFactory);
    }
    else if (style == "origin")
    {
        fje.buildRender(new OriginRendererFactory);
    }
    else
    {
        std::cout << "未知风格" << std::endl;
        return -1;
    }
    fje.buildLoader(json_path);
    fje.renderJson();
    return 0;
}