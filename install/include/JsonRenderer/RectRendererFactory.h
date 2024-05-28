#ifndef RECTRENDERERFACTORY_H
#define RECTRENDERERFACTORY_H

#include "RendererFactory.h"
#include "RectRenderer.h"

class RectRendererFactory :public RendererFactory {
public:
    RectRendererFactory(const std::string& icon_file = "");
    virtual JsonRenderer* create() override;
    virtual ~RectRendererFactory();
};

#endif