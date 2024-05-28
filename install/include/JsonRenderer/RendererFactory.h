#ifndef RENDERERFACTORY_H
#define RENDERERFACTORY_H

#include "JsonRenderer.h"
#include "JsonIcon/JsonIcon.h"

class RendererFactory {
protected:
    JsonIcon* m_icon;
public:
    RendererFactory(const std::string& icon_file = "") :m_icon(nullptr)
    {
        if (icon_file != "")
        {
            m_icon = new JsonIcon(icon_file);
        }
    }
    virtual JsonRenderer* create() = 0;
    virtual ~RendererFactory()
    {
        if (m_icon != nullptr) delete m_icon;
    };
};

#endif