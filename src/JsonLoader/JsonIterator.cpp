#include "JsonLoader/JsonIterator.h"
#include "JsonLoader/JsonNode.h"

JsonIterator::JsonIterator(JsonNode* node, int i) :m_node(node), m_idx(i) {}

JsonLeafIterator::JsonLeafIterator(JsonLeaf* leaf, int idx) :
    JsonIterator(leaf, idx)
{}

bool JsonLeafIterator::hasMore()
{
    return false;
}
bool JsonLeafIterator::atEnd()
{
    return m_idx != 0;
}
bool JsonLeafIterator::atLast()
{
    return m_idx == 0;
}

void JsonLeafIterator::getNext()
{
    if (!atEnd())
        m_idx += 1;
}

JsonNode* JsonLeafIterator::get()
{
    return m_node->at(0);
}

JsonLeafIterator::~JsonLeafIterator()
{}


JsonContainerIterator::JsonContainerIterator(JsonContainer* container, int idx) :
    JsonIterator(container, idx)
{}

bool JsonContainerIterator::hasMore()
{
    return m_node->size() > 0 && m_idx < (m_node->size() - 1);
}

bool JsonContainerIterator::atEnd()
{
    return m_idx == m_node->size();
}

bool JsonContainerIterator::atLast()
{
    return m_idx == (m_node->size() - 1);
}

void JsonContainerIterator::getNext()
{
    if (!atEnd())
        m_idx += 1;
}

JsonNode* JsonContainerIterator::get()
{
    return m_node->at(m_idx);
}

JsonContainerIterator::~JsonContainerIterator()
{}