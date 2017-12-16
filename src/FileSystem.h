#ifndef _FILESYSTEM_
#define _FILESYSTEM_

//------- Inclusion ----------------------------------
#include<iostream>
#include<string.h>
#include<string>
#include<vector>
#include<iomanip>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

//--------- Macro --------------------------------------
#define MAX_NAME  20

//--------- Prototype ----------------------------------
struct MyDir ;
//-------- Global Var ----------------------------------
extern int disk_empty ;
//-------- Function ------------------------------------
vector<string> stringsplie( string line ) ;
string         tab_level( int layer ) ;
int            DirCount( MyDir *currentDir );
//-------- Structure Definition ------------------------
typedef struct UserInfo
{
    string name   ;//User name
    string passwd ;//User password
    UserInfo( string u, string p):name(u), passwd(p){}
}UserInfo;
//-------- Structure Definition ------------------------
typedef struct MyFile
{
    string name    ;
    int    size    ;
    int    fid     ;
    struct MyFile *nextFile;
    string content ;
    MyFile( int fid ):fid(fid)
    { size = 0 ; content = "" ; nextFile = NULL; };
} MyFile;
//-------- Structure Definition ------------------------
typedef struct MyDir
{
    string  name        ;
    int size;
    MyDir   *nextDir    ;//The next dir, which is on the same layer
    MyDir   *preDir     ;
    MyFile  *filePtr    ;
    MyDir   *dirPtr     ;//The first dir on next layer
    MyDir( MyDir* nD, MyDir* pD, MyFile* fptr, MyDir* sD, int s ):nextDir(nD),preDir(pD),filePtr(fptr),dirPtr(sD), size(s)
    { name = "" ; }
}MyDir;
//-------- Structure Definition ------------------------
class FileSystem
{
private:
    vector<UserInfo> vUser  ;
    MyDir   *currentDir     ;
    MyFile  *copytempfile   ;
    MyDir   *copytempdir    ;
    MyDir   *root           ; //root directory
    char    password[MAX_NAME];
    char    name[MAX_NAME]  ;
    int     size            ;
    int     filenumber      ;

public:
    //----- Memeber Access ---------------------------------
    vector< UserInfo > &getUserVector( void ){ return vUser ; }
    void setFileNumber( int n ){ filenumber = n    ; }
    int  getFileNumber( )      { return filenumber ; }
    //----- Function ---------------------------------------
    void   run() ;
    void   readUserInfo();
    void   readDirTree() ;
    void   BuildFile( string FileName, MyDir *currentDir, int fid );
    void   BuildDirFile( ifstream & token, vector<string> strspl, MyDir *currentDir );
    void   dumpDirContent( FILE* f, MyDir* currentDir, int layer );
    void   dumpDirTree() ;
    int    login( string, string ) ;
    int    fsOperate( string, string );
    int    regist( string, string );
    int    setUser( string, string);
    MyDir* BuildDir( string DirName, MyDir *currentDir ) ;
    
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
