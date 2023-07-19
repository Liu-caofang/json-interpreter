//
// Created by 刘芃 on 2023/7/18.
//
#include <sstream>
#include "json.h"
#include "string"
#include "Parse.h"


using namespace yazi::json;
//基本构造函数
Json::Json() : m_type(json_null){

}
Json::Json(Json::Type type) : m_type(type){
    switch (m_type) {
        case json_null:
            break;
        case json_bool:
            m_value.m_bool = false;
            break;
        case json_int:
            m_value.m_int = 0;
            break;
        case json_double:
            m_value.m_double = 0.0;
            break;
        case json_string:
            m_value.m_string = new std::string("");
            break;
        case json_array:
            m_value.m_array = new std::vector<Json>();
            break;
        case json_object:
            m_value.m_object = new std::map<string, Json>();
        default:
            break;
    }
}
Json::Json(bool value) : m_type(json_bool){
    m_value.m_bool = value;
}
Json::Json(int value) : m_type(json_int){
    m_value.m_int = value;
}
Json::Json(double value) : m_type(json_double){
    m_value.m_double = value;
}
Json::Json(const char *value) : m_type(json_string){
    m_value.m_string = new std::string (value);
}

Json::Json(const string &value) : m_type(json_string){
    m_value.m_string = new std::string (value);
}

Json::Json(const Json &other) : m_type(json_null) {
    copy(other);
}
Json::~Json() = default;

//判断类型
Json::Type Json::type() const {
    return m_type;
}

//运算符重载
Json::operator bool(){
    if(m_type != json_bool){
        throw std::logic_error("type error, not bool value");
    }
    return m_value.m_bool;
}
Json::operator int(){
    if(m_type != json_int){
        throw std::logic_error("type error, not int value");
    }
    return m_value.m_int;
}
Json::operator double (){
    if(m_type != json_double){
        throw std::logic_error("type error, not double value");
    }
    return m_value.m_double;
}
Json::operator string(){
    if(m_type != json_string){
        throw std::logic_error("type error, not string value");
    }
    return *(m_value.m_string);
}

Json & Json::operator[] (int idx){
    if(idx < 0)
        throw std::logic_error("index out of range, idx < 0");
    if(m_type != json_array){
        clear();
        m_type = json_array;
        m_value.m_array = new std::vector<Json>();
    }
    int size = (m_value.m_array)->size();
    if(idx >= size){
        for(int i = size; i <= idx; i++){
            m_value.m_array->push_back(Json());
        }
    }
    return (m_value.m_array)->at(idx);
}
//对象操作
Json &Json::operator[](const char* key){
    string name(key);
    return (*this)[name];//调用下一个函数
}
Json &Json::operator[](const string &key){
    //如果为空，则先清理再创建一个新的Json对象
    if(m_type != json_object){
        clear();
        m_type = json_object;
        m_value.m_object = new std::map<string, Json>();
    }
    return (*(m_value.m_object))[key];
}
Json& Json::operator= (const Json &other){
    clear();
    copy(other);
    return *this;
}
bool Json::operator == (const Json &other){
    if(this->m_type != other.type()) return false;
    switch (m_type) {
        case json_null:
            return true;
        case json_bool:
            return m_value.m_bool == other.m_value.m_bool;
        case json_int:
            return m_value.m_int == other.m_value.m_int;
        case json_double:
            return m_value.m_double == other.m_value.m_double;
        case json_string:
            return *(m_value.m_string) == *(other.m_value.m_string);
        case json_array:
            return m_value.m_array == other.m_value.m_array; //判断指针是否一样就可以了
            break;
        case json_object:
            return m_value.m_object == other.m_value.m_object; //判断指针是否一样就可以了
        default:
            break;
    }
    return false;
}
bool Json::operator!= (const Json &other) {
    return !(*this == other);
}

void Json::append(const Json & other){
    if(m_type != json_array){
        clear();
        m_type = json_array;
        m_value.m_array = new std::vector<Json>();
    }
    (m_value.m_array)->push_back(other);
}

void Json::copy(const Json &other){
    m_type = other.m_type;
    switch (m_type) {
        case json_null:
            break;
        case json_bool:
            m_value.m_bool = other.m_value.m_bool;
            break;
        case json_int:
            m_value.m_int = other.m_value.m_int;
            break;
        case json_double:
            m_value.m_double = other.m_value.m_double;
            break;
        case json_string:
            m_value.m_string = other.m_value.m_string;
            break;
        case json_array:
            m_value.m_array = other.m_value.m_array;
            break;
        case json_object:
            m_value.m_object = other.m_value.m_object;
        default:
            break;
    }
}
void Json::clear() {
    switch (m_type) {
        case json_null:
            break;
        case json_bool:
            m_value.m_bool = false;
            break;
        case json_int:
            m_value.m_int = 0;
            break;
        case json_double:
            m_value.m_double = 0.0;
            break;
        case json_string:
            delete m_value.m_string;
            break;
        case json_array:
            //先释放数组里面的元素，在释放自身
            for(auto & it : *m_value.m_array){
                it.clear();
            }
            delete m_value.m_array;
            break;
        case json_object:
            for(auto & it : *m_value.m_object){
                it.second.clear();
            }
            delete m_value.m_object;
            break;
        default:
            break;
    }
    m_type = json_null;
}
//parse()
void Json::parse(const string &str) {
    Parser parser;
    parser.load(str);
    *this = parser.parse();
}

//输出str
string Json::str() const {
    stringstream ss;
    switch (m_type) {
        case json_null:
            ss << "null";
            break;
        case json_bool:
            if(m_value.m_bool){
                ss << "true";
            }else ss << "false";
            break;
        case json_int:
            ss << m_value.m_int;
            break;
        case json_double:
            ss << m_value.m_double;
            break;
        case json_string:
            ss << "\"" << *(m_value.m_string) << "\"";
            break;
        case json_array:
            ss << "[";
            for(auto it = m_value.m_array->begin(); it != m_value.m_array->end();it++){
                if(it != m_value.m_array->begin()) ss << ',';
                ss << it->str();
            }
            ss << "]";
            break;
        case json_object:
            ss << "{";
            for(auto it = m_value.m_object->begin(); it != m_value.m_object->end();it++){
                if(it != m_value.m_object->begin()) ss << ',';
                ss << "\"" << it->first << '\"' << ':' << it->second.str();
            }
            ss << "}";
            break;
        default:
            break;
    }
    return ss.str();
}

bool Json::asBool() const{
    if(m_type != json_bool)
        throw std::logic_error("type error, not bool value");
    return m_value.m_bool;
}
int Json::asInt() const{
    if(m_type != json_int)
        throw std::logic_error("type error, not int value");
    return m_value.m_int;
}
double Json::asDouble() const{
    if(m_type != json_double)
        throw std::logic_error("type error, not double value");
    return m_value.m_double;
}
string Json::asString() const{
    if(m_type != json_string)
        throw std::logic_error("type error, not string value");
    return *(m_value.m_string);
}

bool Json::has(int idx){
    if(m_type != json_array)
        return false;
    return idx >=0 && m_value.m_array->size() > idx;
}
bool Json::has(const char* key){
    string name(key);
    return has(name);
}
bool Json::has(string& key){
    if(m_type != json_object)
        return false;
    return m_value.m_object->count(key);
}

void Json::remove(int idx){
    if(m_type != json_array || !has(idx))
        return;
    (m_value.m_array)->at(idx).clear();
    (m_value.m_array)->erase((m_value.m_array)->begin() + idx);

}
void Json::remove(const char* key){
    string name(key);
    remove(name);
}
void Json::remove(string& key){
    if(m_type != json_object || !has(key))
        return;
    (*(m_value.m_object))[key].clear();
    (m_value.m_object)->erase(key);
}
