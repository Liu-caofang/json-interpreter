//
// Created by 刘芃 on 2023/7/18.
//

#ifndef JSON_INTERPRETER_PARSE_H
#define JSON_INTERPRETER_PARSE_H

#endif //JSON_INTERPRETER_PARSE_H

//#pragma once //为了避免同一个头文件被包含（include）多次,或者上面的方式
#include <string>
#include "json.h"

namespace yazi{
namespace json{

class Parser{
public:
    Parser();
    ~Parser();

    void load(const string& str);
    Json parse();
private:
    void skip_white_space();
    char get_next_token();

    Json parse_null();
    Json parse_bool();
    Json parse_number();
    string parse_string();
    Json parse_array();
    Json parse_object();

    static bool in_range(int x, int lower, int upper){
        return x >= lower && x <= upper;
    }
private:
    string m_str;
    size_t m_idx;
};
}
}