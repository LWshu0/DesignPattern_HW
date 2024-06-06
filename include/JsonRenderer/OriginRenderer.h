#ifndef ORIGINRENDERER_H
#define ORIGINRENDERER_H

#include "JsonRenderer.h"

class OriginRenderer :public JsonRenderer {
public:
    OriginRenderer();
    virtual void render(JsonLeaf* leaf, int level) override;
    virtual void render(JsonContainer* container, int level) override;
    virtual ~OriginRenderer();
};


#endif