#include<iostream>
#include<string.h>
#include<string>
#include<vector>
#include<iomanip>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
#define MAX_NAME  20

#ifndef _FILESYSTEM_
#define _FILESYSTEM_

extern int disk_empty ;
vector<string> stringSplit(string input, char *delimiters) ;

typedef struct UserInfo
{
    string name   ;//User name
    string passwd ;//User password
    UserInfo( string u, string p):name(u), passwd(p){}
}UserInfo;

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
    vector<UserInfo> vUser ;
    MyDir *currentDir;
    MyFile *copytempfile;
    MyDir *copytempdir;
    MyDir *root; //root directory
    char password[MAX_NAME];
    char name[MAX_NAME];
    int size;

 public:
    //----- Memeber Access ---------------------------------
    vector< UserInfo > &getUserVector( void ){ return vUser ; }
    
    //----- Function ---------------------------------------
    void run() ;
    void readUserInfo();
    int login( string, string ) ;
    int fsOperate( string, string );
    int regist( string, string );
    int setUser( string, string);
    //----- Destructor --------------------------------------
    FileSystem();
    ~FileSystem();

    //----- Operation ---------------------------------------
    //1
    int newFile();
    int newDir();
    //2
    int dele_file(MyFile *file);
    int deleteFile();
    //3
    int dele_dir(MyDir *d);
    int deleteDir();
    //4
    int readDir();
    int readFile();
    //5
    int renameDir();
    int renameFile();
    //6
    MyDir *copy_dir(MyDir *dir);
    MyDir *copyDir();
    //7
    MyFile *copy_file(MyFile *h);
    MyFile *copyFile();
    //8
    int pasteDir();
    int pasteFile();
    //9
    int edit();
    //10
    int showCurrentDir();
    //11
    int show_path(MyDir *dir); //
    int showPath();//like cmd "pwd"
    //12
    int goback(); //go back to the upper layer directory
    //13
    

    int getSize();//get the size of currrent directory, where the user is
    MyDir *getCurrentdir(); //Obtain the current directory
};
#endif
