#ifndef JSONNODE_H
#define JSONNODE_H

#include <string>
#include <vector>
#include <memory>
#include <iterator>

class JsonIcon;
class JsonRenderer;

/**
 *@brief Json 节点的抽象基类, 提供一个绘制接口
 *
 */
class JsonNode {
protected:
    std::string m_name;

public:
    JsonNode() :m_name("") {}

    /* 修改 */
    inline void setName(const std::string& name)
    {
        m_name = name;
    }
    virtual void setValue(const std::string& value) = 0;
    
    /* 访问 */
    virtual size_t size() = 0;
    virtual bool empty() = 0;
    virtual JsonNode& at(size_t idx) = 0;
    virtual JsonNode& at(const std::string& name) = 0;
    virtual JsonNode& operator[](size_t idx) = 0;
    virtual JsonNode& operator[](const std::string& name) = 0;
    inline std::string getName()
    {
        return m_name;
    }
    virtual std::string getValue() = 0;
    virtual int getInt() = 0;
    virtual float getFloat() = 0;
    virtual bool getBool() = 0;

    virtual void draw(JsonRenderer* renderer, int level) = 0;
    virtual void clear() = 0;
    virtual ~JsonNode() {}
};


/**
 *@brief Json 树的中间容器节点, 可以有多个子节点, 子节点可以是另一个容器节点也可以是叶子节点.
 *       
 */
class JsonContainer :public JsonNode {
private:
    int m_level;
    std::vector<std::shared_ptr<JsonNode>> m_children;
public:
    /**
     *@brief Construct a new Json Container object
     * 
     * @param level 容器节点的层级, 最外层是第 0 层, 向内依次增加
     */
    JsonContainer(int level);

    virtual void setValue(const std::string& value) override;
    
    // 访问方法
    /**
     *@brief 获取容器节点的子节点数量
     *
     * @return int 容器节点的子节点数量
     */
    virtual size_t size() override;
    /**
     *@brief 判断子节点是否为空
     * 
     * @return true 无子节点
     * @return false 有子节点
     */
    virtual bool empty() override;
    /**
     *@brief 根据下标返回子节点
     * 
     * @param idx 子节点下标
     * @return JsonNode& 子节点
     */
    virtual JsonNode& at(size_t idx) override;
    /**
     * @brief 根据子节点名称获得子节点, 如果不存在该名称的子节点, 将抛出 out_of_range 异常
     * 
     * @param name 子节点名称
     * @return JsonNode& 子节点
     */
    virtual JsonNode& at(const std::string& name) override;
    virtual JsonNode& operator[](size_t idx) override;
    virtual JsonNode& operator[](const std::string& name) override;
    virtual std::string getValue() override;
    virtual int getInt() override;
    virtual float getFloat() override;
    virtual bool getBool() override;

    /**
     *@brief 向容器节点添加一个子节点
     * 
     * @param node 待添加的子节点
     */
    void addChild(std::shared_ptr<JsonNode> node);

    /**
     *@brief 使用指定的渲染器渲染该容器节点到字符串形式
     * 
     * @param renderer 渲染器
     * @param level 渲染的层级, 为该容器的层级
     */
    virtual void draw(JsonRenderer* renderer, int level) override;
    /**
     *@brief 清空子节点
     * 
     */
    virtual void clear() override;
    virtual ~JsonContainer();
};

/**
 *@brief Json 树的叶子节点
 *
 */
class JsonLeaf :public JsonNode {
private:
    std::string m_value;
public:
    JsonLeaf();

    /**
         *@brief 设置叶子节点的值
         *
         * @param value 值
         */
    void setValue(const std::string& value);

    virtual size_t size() override;
    virtual bool empty() override;
    virtual JsonNode& at(size_t idx) override;
    virtual JsonNode& at(const std::string& name) override;
    virtual JsonNode& operator[](size_t idx) override;
    virtual JsonNode& operator[](const std::string& name) override;
    /**
     *@brief 获取叶子节点的值
     *
     * @return std::string 值
     */
    std::string getValue();
    virtual int getInt() override;
    virtual float getFloat() override;
    virtual bool getBool() override;
    
    /**
     *@brief 使用指定的渲染器渲染叶子节点到字符串形式
     * 
     * @param renderer 渲染器
     * @param level 渲染层级, 上一层 container 的层级+1
     */
    virtual  void draw(JsonRenderer* renderer, int level) override;
    /**
     *@brief 将节点的内容置为 null
     * 
     */
    virtual void clear() override;
    virtual ~JsonLeaf();
};

#endif