#include "JsonRenderer/TreeRendererFactory.h"
TreeRendererFactory::TreeRendererFactory(const std::string& icon_file) :RendererFactory(icon_file)
{}

JsonRenderer* TreeRendererFactory::create()
{
    return new TreeRenderer(&m_icon);
}

TreeRendererFactory::~TreeRendererFactory()
{}
