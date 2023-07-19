#pragma once
#include "string"
#include "vector"
#include "map"

using namespace std;

namespace yazi {
namespace json {
class Json {
  public:
    enum Type {
        json_null = 0,
        json_bool,
        json_int,
        json_double,
        json_string,
        json_array,
        json_object
    };
    // 基本构造
    Json();
    ~Json();
    Json(bool value);
    Json(int value);
    Json(double value);
    Json(const char* value);
    Json(const std::string& value);
    Json(Type type);
    Json(const Json& other);

    //数组的中括号操作和添加新元素
    Json &operator[] (int idx);
    void append(const Json & other);

    //对象的中括号操作
    Json &operator[](const char* key);
    Json &operator[](const string &key);

    // 运算符重载
    operator bool();
    operator int();
    operator double ();
    operator string();

    //对象赋值
    Json& operator= (const Json &other);
    //判断相等
    bool operator== (const Json &other);
    bool operator!=(const Json &other);

    //遍历操作，先定义迭代器
    typedef std::vector<Json>::iterator iterator;
    iterator  begin() {
        return m_value.m_array->begin();
    }
    iterator end() {
        return m_value.m_array->end();
    }
    //判断类型
    Type type() const;
    bool isNull() const {return m_type == json_null;}
    bool isBoll() const {return m_type == json_bool;}
    bool isInt() const {return m_type == json_int;}
    bool isDouble() const {return m_type == json_double;}
    bool isString() const {return m_type == json_string;}
    bool isArray() const {return m_type == json_array;}
    bool isObject() const {return m_type == json_object;}

    bool asBool() const;
    int asInt() const;
    double asDouble() const;
    string asString() const;

    bool has(int idx);
    bool has(const char* key);
    bool has(string& key);

    //parse
    void parse(const string& str);
    //str()
    string str() const;
    void clear();
    void remove(int idx);
    void remove(const char* key);
    void remove(string& key);
  private:
    void copy(const Json &other);
  private:
    union Value {
        bool m_bool;
        int m_int;
        double m_double;
        std::string *m_string;
        std::vector<Json> *m_array;
        std::map<std::string, Json> *m_object;
    };
    Type m_type;
    Value m_value{};
};
} // namespace json
} // namespace yazi
