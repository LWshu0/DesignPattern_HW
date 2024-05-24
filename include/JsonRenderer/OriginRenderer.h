#ifndef ORIGINRENDERER_H
#define ORIGINRENDERER_H

#include "JsonRenderer.h"

class OriginRenderer :public JsonRenderer {
public:
    OriginRenderer();
    virtual void renderLeaf(JsonLeaf* leaf, int level) override;
    virtual void renderContainer(JsonContainer* container, int level) override;
    virtual ~OriginRenderer();
};


#endif