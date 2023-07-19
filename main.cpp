#include <iostream>
#include <fstream>
#include <sstream>
#include "json.h"

using namespace std;
using namespace yazi::json;

#include "sys/time.h"

int main(){
    // 基本构造
//    Json v1;
//    Json v2 = true;
//    Json v3 = 123;
//    Json v4 = 1.23;
//    Json v5 = "hello, world";
//    // 运算符重载
//    bool b = v2;
//    int i = v3;
//    double f = v4;
//    const std::string &s = v5;

//数组类型
//    Json arr;
//    arr[0] = true;
//    arr[1] = 123;
//    arr.append(1.23);
//    arr.append("hello, world");
//
//    std::cout << arr.str() << std::endl;
//    std::cout << arr[1].str() << std::endl;
//
//    bool b = arr[0];
//    int i = arr[1];
//    double f = arr[2];
//    const std::string &s = arr[3];
//对象类型

//    Json obj;
//    //map
//    obj["bool"] = true;
//    obj["int"] = 123;
//    obj["double"] = 1.23;
//    obj["str"] = "hello, world";
//    //输出对象的内容
//    std::cout << obj.str() << std::endl;

//    Json arr;
//    arr[0] = true;
//    arr[1] = 123;
//    arr[2] = 1.23;
//    arr[3] = "hello, world";
//    std::cout << arr.has(0) << std::endl;
//    std::cout << arr.has(4) << std::endl;
//    std::cout << arr.str() << std::endl;
//    arr.remove(0);
//    std::cout << arr.str() << std::endl;
//    arr.remove(4);
//    std::cout << arr.str() << std::endl;
//    arr.clear()
//    Json obj;
//    obj["bool"] = true;
//    obj["int"] = 123;
//    obj["double"] = 1.23;
//    obj["string"] = "hello, world";
//    obj["arr"] = arr;
//    std::cout << obj.has("bool") << std::endl;
//    std::cout << obj.has("hello") << std::endl;
//    std::cout << obj.str() << std::endl;
//    obj.remove("bool");
//    std::cout << obj.str() << std::endl;
//    obj.remove("hello");
//    std::cout << obj.str() << std::endl;
//    obj.clear();//只需要释放obj
    try
    {
        std::ifstream fin("../main.json"); //要根据exe文件来选择路径，exe是放在cmake文件夹下的
        if (!fin.is_open()) {
            cout << "Error opening file." << endl;
            return 1;
        }
        std::stringstream ss;
        ss << fin.rdbuf();
        const string & data = ss.str();

        struct timeval tv;
        gettimeofday(&tv, NULL);
        int start_sec = tv.tv_sec;
        int start_usec = tv.tv_usec;
        const int max = 1;
        for (int i = 0; i < max; i++)
        {
            Json json;
            json.parse(data);
            std::cout << json.str() << std::endl;
            json.clear();
        }
        gettimeofday(&tv, NULL);
        int end_sec = tv.tv_sec;
        int end_usec = tv.tv_usec;
        double time_diff = (end_sec - start_sec) * 1000000 + (end_usec - start_usec);
        std::cout << time_diff / 1000 / max << "ms" << std::endl;
    }
    catch (std::exception & e)
    {
        std::cout << "catch exception: " << e.what() << std::endl;
    }
    return 0;
}