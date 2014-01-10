#include<iostream>
#include<string.h>
#include<string>
#include<iomanip>
#include <stdlib.h>
#include<stdio.h>
using namespace std;
#define MAX_NAME  20    //文件名或者目录名字最大字节数
extern int disk_empty;


typedef struct MyFile         //文件结构体
{
    char name[MAX_NAME];      //文件名 
    int size;                 //文件大小
    struct MyFile *nextFile;  //指向文件列表中下一个文件
    string content;           //文件内容
} MyFile;

typedef struct MyDir          //目录结构体
{
    char name[MAX_NAME];      //目录名字
    int size;                 //目录大小
    MyDir *nextDir;           //后继目录
    MyDir *preDir;            //前继目录
    MyFile *filePtr;          //该目录下的文件链表指针
    MyDir *dirPtr;            //该目录下的目录链表指针
} MyDir;


class FileSystem //文件系统类
{
	private:
    MyDir *currentDir; //当前目录
    MyFile *copytempfile; //用于拷贝文件时的临时文件
    MyDir *copytempdir; //用于拷贝目录时的临时目录
    MyDir *root; //根目录
    char password[MAX_NAME];   //用户密码
    char name[MAX_NAME];   //用户名称
    int size; //用户所使用空间大小

 public:
    FileSystem();
    ~FileSystem();

    int newFile(); //创建文件
    int newDir(); //创建目录

    int dele_file(MyFile *file);//删除文件
    int deleteFile(); //删除文件前的逻辑判断
    int dele_dir(MyDir *d); //删除目录
    int deleteDir(); //删除目录前的逻辑判断

    int readDir(); //打开目录
    int readFile(); //打开文件

    int renameDir(); //重命名目录
    int renameFile(); //重命名文件

    MyDir *copy_dir(MyDir *dir);//复制目录
    MyDir *copyDir(); //复制目录前的逻辑判断
    MyFile *copy_file(MyFile *h); //复制文件
    MyFile *copyFile(); //复制文件前的逻辑判断

    int pasteDir(); //粘贴目录
    int pasteFile(); //粘贴文件
    int edit(); //编辑文件

    int showCurrentDir(); //显示当前目录内容

    int show_path(MyDir *dir); //显示路径的部分实现
    int showPath(); //显示路径

    int goback(); //返回上一级目录

    int setUser(char *, char *);//设置用户名与密码

    int getSize();//获得用户所在目录大小
    MyDir *getCurrentdir(); //获得当前目录
};