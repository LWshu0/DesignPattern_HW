#include "JsonRenderer/RectRendererFactory.h"

RectRendererFactory::RectRendererFactory(const std::string& icon_file) :RendererFactory(icon_file)
{}

JsonRenderer* RectRendererFactory::create()
{
    return new RectRenderer(m_icon);
}

RectRendererFactory::~RectRendererFactory()
{}