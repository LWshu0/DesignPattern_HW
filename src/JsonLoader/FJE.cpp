#include "JsonLoader/FJE.h"

FJE::FJE() :
    m_icon(nullptr),
    m_factory(nullptr),
    m_loader(nullptr)
{}

void FJE::buildIcon(const std::string& icon_path)
{
    if (m_icon != nullptr) delete m_icon;
    m_icon = new JsonIcon(icon_path);
    if (m_factory != nullptr) m_factory->setIcon(m_icon);
}

void FJE::buildRender(RendererFactory* factory)
{
    if (m_factory != nullptr) delete m_factory;
    m_factory = factory;
    if (m_icon != nullptr) m_factory->setIcon(m_icon);
}

void FJE::buildLoader(const std::string& json_path)
{
    if (m_loader == nullptr)
    {
        m_loader = new JsonLoader;
    }
    m_loader->load(json_path);
}

void FJE::renderJson()
{
    std::string result = m_loader->draw(m_factory);
    std::cout << result << std::endl;
}

FJE::~FJE()
{
    if (m_icon != nullptr) delete m_icon;
    if (m_factory != nullptr) delete m_factory;
    if (m_loader != nullptr) delete m_loader;
}