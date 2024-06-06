#ifndef FJE_H
#define FJE_H

#include "JsonIcon/JsonIcon.h"
#include "JsonLoader/JsonLoader.h"
#include "JsonRenderer/RendererFactory.h"
#include "JsonRenderer/TreeRendererFactory.h"
#include "JsonRenderer/RectRendererFactory.h"
#include "JsonRenderer/OriginRendererFactory.h"

class FJE
{
private:
    JsonIcon* m_icon;
    RendererFactory* m_factory;
    JsonLoader* m_loader;
public:
    FJE();
    void buildIcon(const std::string& icon_path);
    void buildRender(RendererFactory* factory);
    void buildLoader(const std::string& json_path);
    void renderJson();
    ~FJE();
};

#endif