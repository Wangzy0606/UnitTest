#include "tasks.h"
#include <iostream>
#include <string>
#include <cctype> // for isdigit

//pair函数是本程序的辅助函数，负责解析线性表达式，返回x的系数和常数项
std::pair<int, int> parse(std::string expr) {
    int a = 0; //a是x的系数
    int b = 0; //b是常数项
    int sign = 1; //sign是当前的符号
    
    int i = 0, n = expr.size(); //i是用于循环遍历的索引，n是字符串或者说表达式的长度
    // 处理符号
    while (i < n) {
        if (expr[i] == '+') {
            sign = 1; //遍历字符串，遇到加号，更新为1
            i++; 
        } else if (expr[i] == '-') {
            sign = -1; //遍历字符串，遇到减号，更新为-1
            i++;
        } //如果数字在开头，例如3x+4,中的3，会使用默认值sign=1，也为正

        int num = 0; //用于储存解析出的整数数值，初始化为零，因为我们要从零开始构建
        bool hasNum = false; //标志位，表示是否解析到了数字，初始化为false，因为还没有开始解析

        while (i < n && std::isdigit(expr[i])) { //isdigit(expr[i])用于检查当前数字是否为0-9
            num = num * 10 + (expr[i] - '0'); //将数字字符转化为相应的整数数值，通过ASCII表
            i++;
            hasNum = true;
        }

        if (i < n && expr[i] == 'x') {
            if (hasNum) {
                a += sign * num;  // 如果有数字，使用num值
            } else {
                a += sign * 1;    // 如果没有数字，默认为1，例如x+234
            }
            i++;
        } else {
            b += sign * num;
        }
    }

    return {a, b};
}

std::string solveEquation(std::string equation) {
    std::size_t eqPos = equation.find('=');
    std::string left = equation.substr(0, eqPos);
    std::string right = equation.substr(eqPos + 1);

    // 左边为 ax + b
    std::pair<int, int> leftRes = parse(left);
    int a = leftRes.first;
    int b = leftRes.second;

    std::pair<int, int> rightRes = parse(right);
    int c = rightRes.first;
    int d = rightRes.second;

    //Ax=B
    int A = a - c;
    int B = d - b;

    if (A == 0) {
        if (B == 0) return "Infinite"; //0x=0，无穷解
        else return "NO"; //0x=constant，无解
    }

    int x = B / A;
    return "x=" + std::to_string(x); //to_string将数值类型转化为字符串
}
