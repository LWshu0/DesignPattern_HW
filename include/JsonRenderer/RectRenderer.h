#ifndef RECTRENDERER_H
#define RECTRENDERER_H

#include "JsonRenderer.h"
#include <vector>

class RectRenderer :public JsonRenderer
{
private:
    JsonIcon* m_icon;
    std::vector<std::string> m_prefix;
    size_t m_length;
public:
    RectRenderer(JsonIcon* icon = nullptr);
    virtual void render(JsonLeaf* leaf, int level) override;
    virtual void render(JsonContainer* container, int level) override;
    virtual ~RectRenderer();
private:
    void shrinkPrefix(int num);
    std::string getPrefix();
    size_t count_u8(const std::string& str);
};




#endif