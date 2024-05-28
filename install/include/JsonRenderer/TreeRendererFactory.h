#ifndef TREERENDERERFACTORY_H
#define TREERENDERERFACTORY_H

#include "RendererFactory.h"
#include "TreeRenderer.h"

class TreeRendererFactory :public RendererFactory {
public:
    TreeRendererFactory(const std::string& icon_file = "");
    virtual JsonRenderer* create() override;
    virtual ~TreeRendererFactory();
};

#endif