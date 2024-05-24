#include "JsonRenderer/OriginRenderer.h"
#include "JsonIcon/JsonIcon.h"
#include "JsonLoader/JsonNode.h"

OriginRenderer::OriginRenderer() :JsonRenderer()
{}

void OriginRenderer::renderLeaf(JsonLeaf* leaf, int level)
{
    std::string spaces(level * 4, ' ');
    m_outputBuffer.back() += (spaces + '\"' + leaf->getName() + "\": ");
    if (leaf->getValue() == "null")
    {
        m_outputBuffer.back() += leaf->getValue();
    }
    else
    {
        m_outputBuffer.back() += ('\"' + leaf->getValue() + '\"');
    }
}

void OriginRenderer::renderContainer(JsonContainer* container, int level)
{
    std::string spaces(level * 4, ' ');
    if (container->getName() != "")
    {
        m_outputBuffer.back() += (spaces + '\"' + container->getName() + "\": ");
    }
    if (!m_outputBuffer.empty()) m_outputBuffer.back() += "{";
    else m_outputBuffer.push_back("{");
    m_outputBuffer.push_back("");
    for (int i = 0;i < container->size();i++)
    {
        container->at(i)->draw(this, level + 1);
        if (i != container->size() - 1) m_outputBuffer.back() += ',';
        m_outputBuffer.push_back("");
    }
    m_outputBuffer.back() += (spaces + "}");
}

OriginRenderer::~OriginRenderer()
{}
