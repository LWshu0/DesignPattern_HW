#ifndef RENDERERFACTORY_H
#define RENDERERFACTORY_H

#include "JsonRenderer.h"
#include "JsonIcon/JsonIcon.h"

class RendererFactory {
protected:
    JsonIcon m_icon;
public:
    RendererFactory(const std::string& icon_file) : m_icon(icon_file) {}
    virtual JsonRenderer* create() = 0;
    virtual ~RendererFactory() = default;
};

#endif