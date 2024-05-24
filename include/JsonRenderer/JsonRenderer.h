#ifndef JSONRENDERER_H
#define JSONRENDERER_H

#include <string>
#include <vector>

class JsonLeaf;
class JsonContainer;
class JsonIcon;
/**
 *@brief Json 渲染器的抽象接口
 * 
 */
class JsonRenderer
{
protected:
    /* each string is one line */
    std::vector<std::string> m_outputBuffer;
public:
    JsonRenderer() = default;
    virtual void renderLeaf(JsonLeaf* leaf, int level) = 0;
    virtual void renderContainer(JsonContainer* container, int level) = 0;
    std::string getResult()
    {
        std::string result = "";
        for (auto& str : m_outputBuffer)
        {
            result += str;
            result += "\n";
        }
        return result;
    }
    virtual ~JsonRenderer() {};
};

#endif