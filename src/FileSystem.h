#include<iostream>
#include<string.h>
#include<string>
#include<iomanip>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
#define MAX_NAME  20


typedef struct MyFile
{
    char name[MAX_NAME];
    int size;
    struct MyFile *nextFile;
    string content;
} MyFile;

typedef struct MyDir
{
    char name[MAX_NAME];
    int size;
    MyDir *nextDir;
    MyDir *preDir;
    MyFile *filePtr;
    MyDir *dirPtr;
} MyDir;


class FileSystem
{
	private:
    MyDir *currentDir;
    MyFile *copytempfile;
    MyDir *copytempdir;
    MyDir *root; //root directory
    char password[MAX_NAME];
    char name[MAX_NAME];
    int size;

 public:
    FileSystem();
    ~FileSystem();

    int newFile();
    int newDir();

    int dele_file(MyFile *file);
    int deleteFile();
    int dele_dir(MyDir *d);
    int deleteDir();

    int readDir();
    int readFile();

    int renameDir();
    int renameFile();

    MyDir *copy_dir(MyDir *dir);
    MyDir *copyDir();
    MyFile *copy_file(MyFile *h);
    MyFile *copyFile();

    int pasteDir();
    int pasteFile();
    int edit();

    int showCurrentDir();

    int show_path(MyDir *dir); //
    int showPath();//like cmd "pwd"

    int goback(); //go back to the upper layer directory

    int setUser(char *, char *);

    int getSize();//get the size of currrent directory, where the user is
    MyDir *getCurrentdir(); //Obtain the current directory
};
