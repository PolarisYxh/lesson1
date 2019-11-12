/*处理文件，获取信息*/
#include <info_get.h>
#include <string>
using namespace std;
Infohandle::Infohandle(ifstream &infile,string name):modelname(name)//正则表达式查找
{
    string str((std::istreambuf_iterator<char>(infile)),std::istreambuf_iterator<char>());//读取整个文件放到str中
    /*stringstream str1;
    str1 << infile.rdbuf();
    string str2(str1.str());读取整个文件放到str2中*/
    size_t pos = str.find("*/");
    if(pos!=str.npos)
    str=str.substr(0, pos);
    string pattern("\\d{2}\\.\\d{2}\\.\\d{2}");
    regex r(pattern);
    //smatch result;
    //size_t pos;
    Info x;
    //regex_search(str,result , r);
    for (sregex_iterator it(str.begin(), str.end(), r), end; it != end; it++)
    {
        //cout<<it->position()<<endl;
        //cout<<it->str()<<endl;
        pos=it->suffix().str().find('*');
        if (pos == it->suffix().str().npos)pos = it->suffix().str().length();
        string str1 = str.substr(it->position(), pos+it->str().length());
        istringstream f(str1);
        string tem1,tem2;
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
            case 4:getline(f, tem2); x.description = tem1 + tem2; infc.push_back(x); break;
            }
        }
    }
}
Info & Infohandle::infoquery(size_t y)
{
    Info *in=new Info;
    if (y==0||y > infc.size())return *in;
    else
    {
        return *(infc.begin()+y-1);
    }
}
Info & Infohandle::getend()
{
    return infoquery(infc.size());
}
fstream & Infohandle::Infoinsert(fstream &outfile,Info &x)
{
    outfile.seekp(0,ios::end);
    if (int(outfile.tellp()) == 0)//如果release note文件为空
    {
        outfile << "ModelName\tVersion\tDate\tInitials\tCR#\tDescription" << endl;
        outfile << '*' <<" "<< "------" << "\t" << "------" << "\t" << "------" << endl;
    }
    outfile << '*'<<" "<<modelname<<"\t"<<x.version <<"\t"<< x.date <<"\t"<< x.initials <<"\t"<< x.CR <<"\t"<< x.description<< endl ;
    outfile.close();
    return outfile;
}
fstream & Infohandle::Infoinsert(fstream &outfile,string &x)
{
    outfile.seekp(0,ios::end);
    if (int(outfile.tellp()) == 0)//如果release note文件为空
    {
        outfile << "ModelName\tVersion\tDate\tInitials\tCR#\tDescription" << endl;
        outfile << '*' <<" "<< "------" << "\t" << "------" << "\t" << "------" << endl;
    }
    outfile << endl<<endl<<'*'<<" "<<x<<endl ;
    outfile.close();
    return outfile;
}
