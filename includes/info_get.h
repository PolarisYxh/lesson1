/*处理.c文件版本号和release note更新*/
#ifndef INFO_GET_H
#define INFO_GET_H
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include <vector>
struct Info
{
    int numX;
    int numY;
    int numZ;
    std::string CR;
    std::string description;
};
class Infohandle
{
    std::vector<Info> infc;
public:
    Infohandle(std::ifstream &infile,std::string name="");//处理.c文件的初始化
    Infohandle()=default;//处理加入日期时间的初始化
    std::fstream & Infoinsert(std::fstream &outfile, Info &x);//插入信息
    std::fstream & Infoinsert(std::fstream &outfile,std::string &x);//插入日期
    Info & infoquery(size_t y);
    Info & getend();
private:
    std::string modelname;
};
/*Infohandle::Infohandle(ifstream &infile)//普通查找
{
    string tem,tem1,tem2;
    Info x;
    int flag = 0;
    //infile.seekg(50, ios_base::beg);
    while (infile >> tem)
    {
        if (tem == "Version"&&flag == 0)
        {
            flag = 1;
            break;
        }
    }
    if (flag ==1)
    {
        while (getline(infile, tem, '*'))
        {
            flag++;
            if (tem.empty())break;
            if (flag >= 4)//进入处理一行信息
            {
                //f.seekg(0, ios::beg);
                istringstream f(tem);
                int i = -1;
                while (f >> tem1)
                {
                    i++;
                    switch (i)
                    {
                    case 0:x.version = tem1; break;
                    case 1:x.date = tem1; break;
                    case 2:x.initials = tem1; break;
                    case 3:x.CR = tem1; break;
                    case 4:getline(f, tem2); x.description = tem1+tem2; infc.push_back(x); break;
                    }
                }
            }
        }
    }
}*/

#endif // INFO_GET_H
