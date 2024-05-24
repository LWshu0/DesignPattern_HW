#ifndef TREERENDERER_H
#define TREERENDERER_H

#include "JsonRenderer.h"
#include <vector>
class TreeRenderer :public JsonRenderer {
private:
    JsonIcon* m_icon;
    std::vector<std::string> m_prefix;
    bool m_childEnd;
public:
    TreeRenderer(JsonIcon* icon = nullptr);
    virtual void renderLeaf(JsonLeaf* leaf, int level) override;
    virtual void renderContainer(JsonContainer* container, int level) override;
    virtual ~TreeRenderer();
private:
    void shrinkPrefix(int num);
    std::string getPrefix();
};

#endif