#include "JsonRenderer/OriginRendererFactory.h"

OriginRendererFactory::OriginRendererFactory() :RendererFactory("")
{}

JsonRenderer* OriginRendererFactory::create()
{
    return new OriginRenderer();
}

OriginRendererFactory::~OriginRendererFactory()
{}
