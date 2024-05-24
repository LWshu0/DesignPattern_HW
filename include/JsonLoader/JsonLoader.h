#ifndef JSONLOADER_H
#define JSONLOADER_H

#include "JsonNode.h"
#include "JsonRenderer/JsonRenderer.h"
#include "JsonRenderer/RendererFactory.h"
#include <string>
#include <fstream>
#include <iostream>
#include <exception>

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

class JsonLoader {
private:
    std::shared_ptr<JsonContainer> m_root;

public:
    JsonLoader();
    int load(const std::string& path);
    std::string draw(RendererFactory* factory);
    void clear();
    ~JsonLoader();

private:
    // 返回是否到达文件结尾
    bool skipSpace(std::string& input_file, size_t& now_pos);

    
    // 获取一个标识符
    // now_pos必须位于左 " 或 第一个字符处
    std::string getIdentifier(std::string& input_file, size_t& now_pos);

    /**
     *@brief parse {...}
     *
     * @param input_file
     * @param now_pos
     * @param level
     * @return JsonContainer*
     */
    std::shared_ptr<JsonContainer> parseContainer(std::string& input_file, size_t& now_pos, int level);

    /**
     *@brief parse value string
     * 
     * @param input_file 
     * @param now_pos 
     * @return std::shared_ptr<JsonLeaf> 
     */
    std::shared_ptr<JsonLeaf> parseLeaf(std::string& input_file, size_t& now_pos);
};



#endif