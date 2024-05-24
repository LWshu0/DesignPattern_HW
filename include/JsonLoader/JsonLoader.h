#ifndef JSONLOADER_H
#define JSONLOADER_H

#include "JsonNode.h"
#include "JsonRenderer/JsonRenderer.h"
#include "JsonRenderer/RendererFactory.h"
#include <string>
#include <fstream>
#include <iostream>
#include <exception>

/**
 *@brief json 解析过程中抛出的异常
 *       代表 json 文件中出现了无法解读的内容
 */
class JsonLoaderException :public std::exception {
private:
    std::string m_errorMsg;
public:
    JsonLoaderException(const std::string& msg) :m_errorMsg(msg) {}
    virtual const char* what() const throw()
    {
        return m_errorMsg.c_str();
    }
    ~JsonLoaderException() {}
};

/**
 *@brief json 文件载入器, 完成 json 文件的解析
 *
 */
class JsonLoader {
private:
    std::shared_ptr<JsonContainer> m_root;

public:
    JsonLoader();
    /**
     *@brief 读入并解析一个 json 文件, 如果解析出现问题, 抛出异常
     * 
     * @param path json 文件的路径
     * @return int 0 代表成功, -1 代表失败
     */
    int load(const std::string& path);
    /**
     *@brief 渲染 json 文件到字符串
     * 
     * @param factory 渲染器的工厂
     * @return std::string 渲染得到的字符串
     */
    std::string draw(RendererFactory* factory);
    /**
     *@brief 清空载入器中的 json 文件内容
     * 
     */
    void clear();
    ~JsonLoader();

private:
    /**
     *@brief 从 now_pos 开始跳过读入文件中遇到的空白字符, 修改 now_pos 到第一个非空白字符处
     * 
     * @param input_file 读入的文件内容
     * @param now_pos 目前解析到的字符位置
     * @return true 如果文件到达了结尾
     * @return false 如果文件没有到达结尾
     */
    bool skipSpace(std::string& input_file, size_t& now_pos);

    /**
     *@brief 获取一个标识符, 标识符是被双引号括起来的, 或者裸字符串, 或者 null.
     *       调用该函数时, now_pos 必须位于左 " 处(如果被引号括起来)或标识符第一个字符处(没有引号括起来)
     *       对于 json 的标识符, 在 vscode 中不加引号会报错(null 除外)
     * @param input_file 读入的文件内容
     * @param now_pos 目前解析到的字符位置
     * @return std::string 标识符字符串
     */
    std::string getIdentifier(std::string& input_file, size_t& now_pos);

    /**
     *@brief 解析两个大括号及其中的内容, 即 {...}
     *
     * @param input_file 读入的文件内容
     * @param now_pos 目前解析到的字符位置
     * @param level 目前所处的 json 层级
     * @return std::shared_ptr<JsonContainer> 解析完成的容器节点的指针
     */
    std::shared_ptr<JsonContainer> parseContainer(std::string& input_file, size_t& now_pos, int level);

    /**
     *@brief 解析一个标识符
     *
     * @param input_file 读入的文件内容
     * @param now_pos 目前解析到的字符位置
     * @return std::shared_ptr<JsonLeaf> 解析完成的叶子节点的指针
     */
    std::shared_ptr<JsonLeaf> parseLeaf(std::string& input_file, size_t& now_pos);
};



#endif