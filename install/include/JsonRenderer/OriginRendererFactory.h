#ifndef ORIGINRENDERERFACTORY_H
#define ORIGINRENDERERFACTORY_H

#include "RendererFactory.h"
#include "OriginRenderer.h"

class OriginRendererFactory :public RendererFactory {
public:
    OriginRendererFactory();
    virtual JsonRenderer* create() override;
    virtual ~OriginRendererFactory();
};



#endif