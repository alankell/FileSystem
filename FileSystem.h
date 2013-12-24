#include<iostream>
#include<string.h>
#include<string>
#include<iomanip>
#include <stdlib.h>
#include<stdio.h>
using namespace std;
#define MAX_NUM  20    //文件名或者目录名字最大字节数



typedef struct MyFile         //文件结构体
{
    char name[MAX_NUM];      //文件名 
    struct MyFile *nextFile;  //指向文件列表中下一个文件
    string content;           //文件内容
} MyFile;

typedef struct MyDir          //目录结构体
{
    char name[MAX_NUM];      //目录名字
    MyDir *nextDir;           //后继目录
    MyDir *preDir;            //前继目录
    MyFile *fileChain;          //该目录下的文件链表指针
    MyDir *dirChain;            //该目录下的目录链表指针
} MyDir;


class FileSystem //文件系统类
{
	private:
    MyDir *currentDir; //当前目录
    MyFile *tempfile; //用于拷贝文件时的临时文件
    MyDir *tempdir; //用于拷贝目录时的临时目录
    MyDir *root; //根目录
    char password[MAX_NUM];   //用户密码
    char name[MAX_NUM];   //用户名称
    

 public:
     FileSystem();
    ~FileSystem();

    int newFile(); //创建文件
    int newDir(); //创建目录

    int deleteFile(MyFile *file);//删除文件
    int deletefileJudge(); //删除文件前的逻辑判断
    int deleteDir(MyDir *d); //删除目录
    int deletedirJudge(); //删除目录前的逻辑判断

    int openDir(); //打开目录
    int renameDir(); //重命名目录
    int renameFile(); //重命名文件

    MyDir *copyDir(MyDir *dir);//复制目录
    MyDir *copydirJudge(); //复制目录前的逻辑判断
    MyFile *copyFile(MyFile *h); //复制文件
    MyFile *copyfileJudge(); //复制文件前的逻辑判断

    int pasteDir(); //粘贴目录
    int pasteFile(); //粘贴文件
    int showCurrentDir(); //显示当前目录内容

    int show_path(MyDir *dir); //显示路径的部分实现
    int showPath(); //显示路径

    int goback(); //返回上一级目录
    int changePass();//修改用户口令
    int setUser(char *, char *);//设置用户名与密码

    MyDir *getCurrentdir(); //获得当前目录
};