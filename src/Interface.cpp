#include"Interface.h"
#include<iostream>
#include<string>
#include<string.h>
#include<fstream>
#include"FileSystem.h"
#include<unistd.h>
#include<assert.h>
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

using namespace std;

void help() {
    cout << "************************************************************************************************************" << endl;
    cout << "* 1.mk + <string>                         Construct a file, named <string>                                 *" << endl;
    cout << "* 2.rm + <string>                         Remove a file, named <string>                                    *" << endl;
    cout << "* 3.rename + <string1> + <string2>        Rename the file <string1> with new name <string2>                *" << endl;
    cout << "* 4.cp + <string>                         Copy the file, named <string>                                    *" << endl;
    cout << "* 5.paste                                 Paste                                                            *" << endl;
    cout << "* 6.read  + <string>                      Open the file, named <string>                                    *" << endl;
    cout << "* 7.vi + <string>                         Edit the file, named <string>                                    *" << endl;
    cout << "* 8.mkdir + <string>                      Make a new directory, named <string>                             *" << endl;
    cout << "* 9.rmdir + <string>                      Remove an existing directory, named <string>                     *" << endl;
    cout << "* 10.renamedir + <string1> + <string2>    Rename an existing directory <string1> with new name <string 2>  *" << endl;
    cout << "* 11.cpdir + <string>                     Copy an existing directory, named <string>                       *" << endl;
    cout << "* 12.pastedir                             Paste                                                            *" << endl;
    cout << "* 13.ls                                   List the content in the directory                                *" << endl;
    cout << "* 14.cd +<string>                         Enter the directory, named <string>                              *" << endl;
    cout << "* 15.cd..                                 Leave the current directory                                      *" << endl;
    cout << "* 16.clear                                Clear                                                            *" << endl;
    cout << "* 17.exit                                 Exit                                                             *" << endl;
    cout << "************************************************************************************************************" << endl
        << endl;

}


int FileSystem::regist( string username, string password )
{
    //Check whether the repetition of registration with the same user name.
    for( auto &user:this->getUserVector() )
    {
        if( user.name == username )//Repeated registration!!
        {
            printf( "\t\t--Warning: " RED"Repeated username\n" RESET );
            return 0 ;
        }
    }
    //No repetition
    FILE *adduser = fopen("./user.txt","a") ;
    if( !adduser )
    {
        printf( RED"[Error] " RESET"Cannot open ./user.txt\n");
    }
    fprintf( adduser,"%s\t%s\n", username.c_str(), password.c_str());
    
    this->getUserVector().push_back( UserInfo( username, password ) ) ;
    
    return 1 ;
}
/*Check whether the user name/passed has been registered*/
int FileSystem::login( string username, string password )
{
    
    for( auto &UserInfo:this->getUserVector())
    {
        if( UserInfo.name == username && UserInfo.passwd == password ) return 1 ;
    }
    return 0 ;
}

int FileSystem::fsOperate( string user, string passwd )
{
    this->setUser( user , passwd );
    while( 1 )
    {
        system("clear");
        help();
        while( 1 )
        {
            this->showPath();
            
            string choice;
            cin >> choice ;

            if (choice == "mkdir")
                this->newDir();
            else if (choice == "mk")
                this->newFile();
            else if (choice == "rmdir")
                this->deleteDir();
            else if (choice == "rm")
                this->deleteFile();
            else if (choice == "renamedir")
                this->renameDir();
            else if (choice == "rename")
                this->renameFile();
            else if (choice == "cd")
                this->readDir();
            else if (choice == "read")
                this->readFile();
            else if (choice == "ls")
                this->showCurrentDir();
            else if (choice == "cpdir")
                this->copyDir();
            else if (choice == "cp")
                this->copyFile();
            else if (choice == "pastedir")
                this->pasteDir();
            else if (choice == "paste")
                this->pasteFile();
            else if (choice == "vi")
                this->edit();
            else if (choice == "cd..")
                this->goback();
            else if (choice == "clear") {
                system("clear");
                help();
            } else if (choice == "exit") {
                system("clear");
                cout << "Leave " << name << "...."
                    << endl;
                 sleep(3);
                return 0;
            } else if (choice == "help") {
                help();
            } else if (choice == "mkdir?")
                cout << "Make a new direcotry: mkdir [dirname]" << endl;
            else if (choice == "mk?")
                cout << "Make a new file: mk[filename]" << endl;
            else if (choice == "rmdir?")
                cout << "Remove an existing directory: rmdir [dirname]" << endl;
            else if (choice == "rm?")
                cout << "Remove an existing file: rm [filename]" << endl;
            else if (choice == "renamedir?")
                cout << "Rename an existing directory " << endl;
            else if (choice == "rename?")
                cout << "Rename an existing file " << endl;
            else if (choice == "cd?")
                cout << "Enter an existing file: cd [dirname]" << endl;
            else if (choice == "read?")
                cout << "read file: read [filename]" << endl;
            else if (choice == "ls?")
                cout << "List the content in the directory" << endl;
            else if (choice == "cpdir?")
                cout << "Copy an existing directory: cpDir [dirname]" << endl;
            else if (choice == "cy?")
                cout << "Copt an existing file: cp [filename]" << endl;
            else if (choice == "pastedir?")
                cout << "Paster an existing direcotry" << endl;
            else if (choice == "paste?")
                cout << "Paster an existing file" << endl;
            else if (choice == "clear?")
                cout << "ÇClean file screem" << endl;
            else if (choice == "vi?")
                cout << "Edit an file: vi[filename]" << endl;
            else if (choice == "cd..?")
                cout << "Enter the upper layer directory" << endl;
            else if (choice == "exit?")
                cout << "Exit" << endl;
            else
                cout << RED"[Warning]" RESET"Invalid Command" << endl;
        }
    }

}

//****************************************************************************************
//* Fun Name: readUserInfo                                                               *
//* Work: Read users' information before begining the program                            *
//* Where to be called: run()                                                            *
//* Editor: Tien-Hung Tseng                                                              *
//* **************************************************************************************
void FileSystem::readUserInfo()
{
    ifstream token ;
    token.open( "user.txt", ifstream::in ) ;
    if( !token )
    {
        printf("Error!\n");
    }
    string user ="", password="" ;
    token >> user >> password ;
    while( token >> user >> password )
    {
        this->getUserVector().push_back( UserInfo( user, password ) ) ;
    }
}
//****************************************************************************************
//* Fun Name: stringsplie()                                                              *
//* Work: Splie the string with some characters                                          *
//* Where to be called: readDirTree()                                                    *
//* Editor: Tien-Hung Tseng                                                              *
//****************************************************************************************
vector<string> stringsplit( string line )
{
    vector<string> result         ;
    char           str[1024] = "" ;
    strcpy( str, line.c_str() ) ;
    char *pch = strtok( str, " /");
    while( pch != NULL )
    {
        result.push_back( pch ) ;
        pch = strtok( NULL, "/" );
    }
    return result ;
}
//****************************************************************************************
//* Fun Name: BuildDir()                                                                 *
//* Work: Using Recursive Way to Build directories or files                              *
//* Where to be called: BuildDirFile()                                                   *
//* Editor: Tien-Hung Tseng                                                              *
//****************************************************************************************
MyDir*  FileSystem::BuildDir( string DirName, MyDir *currentDir )
{
    MyDir *newDirptr   = NULL  ;
    MyDir *hdNextLayer = NULL  ;//header of next layer
    newDirptr = new MyDir( NULL, NULL, NULL, NULL, 0 ) ;
    newDirptr->name = DirName ;
    
    if( currentDir->dirPtr == NULL)
        hdNextLayer = NULL;
    else
        hdNextLayer = currentDir->dirPtr;//First dir on next layer
    
    /*Rebuild the Linked List*/
    newDirptr->preDir  = currentDir;
    newDirptr->nextDir = currentDir->dirPtr;
    currentDir->dirPtr = newDirptr ;
    return newDirptr ;
}
//****************************************************************************************
//* Fun Name: BuildFile()                                                                *
//* Work: Using Recursive Way to Build directories or files                              *
//* Where to be called: BuildDirFile()                                                   *
//* Editor: Tien-Hung Tseng                                                              *
//****************************************************************************************
void  FileSystem::BuildFile( string FileName, MyDir *currentDir, int id )
{
    MyFile *newFile = new MyFile( id ) ;
    newFile->name = FileName ;

    if( currentDir->filePtr == NULL )
    {
        newFile->nextFile = currentDir->filePtr;
        currentDir->filePtr = newFile ;
    }
    else
    {
        MyFile *q = currentDir->filePtr;
        while( q != NULL )
        {
            assert( strcmp( newFile->name.c_str(), q->name.c_str() ) != 0 );
            q = q->nextFile ;
        }
        /*Rebuild the Linked List*/
        newFile->nextFile = currentDir->filePtr;
        newFile->size = 0 ;
        currentDir->filePtr = newFile ;
        MyDir *h = currentDir;
        
        /*Resize the size of upper layer direcotory*/
        while( h != NULL )
        {
            h->size += newFile->size;
            h = h->preDir;
        }
        
    }
    currentDir->filePtr->size = 0;
    this->setFileNumber( this->getFileNumber()+1 );
    disk_empty = disk_empty - newFile->size;
    //this->size += newFile->size;
}
//****************************************************************************************
//* Fun Name: BuildDirFile()                                                             *
//* Work: Using Recursive Way to Build directories or files                              *
//* Where to be called: readDirTree()                                                    *
//* Editor: Tien-Hung Tseng                                                              *
//****************************************************************************************
void  FileSystem::BuildDirFile( ifstream & token, vector<string> strspl, MyDir *currentDir )
{
    assert( strspl[1] == "f" || strspl[1] == "d" );
    int size = stoi( strspl[2] );
    //--- File --------------------------------
    if( strspl[1] == "f" )
    {
        BuildFile( strspl[0], currentDir, size );
        return ;
    }
    //--- Directoy ----------------------------
    else if( strspl[1] == "d" )
    {
        MyDir *newDir = NULL ;
        newDir = BuildDir( strspl[0], currentDir );
        for( int i = 0 ; i < size ; i++ )
        {
            string nextline = ""   ;
            token >> nextline      ;
            vector<string> nstrspl = stringsplit( nextline ) ;
            BuildDirFile( token, nstrspl, newDir ) ;
        }
    }
}
//****************************************************************************************
//* Fun Name: readDirTree                                                                *
//* Work: Read preexisting tree strucutre of directories and files                       *
//* Where to be called: run()                                                            *
//* Editor: Tien-Hung Tseng                                                              *
//****************************************************************************************
void FileSystem::readDirTree()
{
    ifstream token ;
    token.open( "tree.txt", ifstream::in ) ;
    assert( token ) ;
    
    string line = " " ;
    //---- For Root ---------------------------------------
    token >> line ;
    vector<string> rootinfo = stringsplit( line ) ;
    assert( rootinfo[0] == "root") ;
    this->root = new MyDir( NULL, NULL, NULL, NULL, 0 ) ;
    this->root->name = rootinfo[0] ;
    while( token >> line )
    {
        vector<string> strsplit = stringsplit(line);
        assert( strsplit.size() == 3 );
        BuildDirFile( token, strsplit, this->root ) ;
    }
}
//****************************************************************************************
//* Fun Name: tab_level()                                                                *
//* Work: calculate the count of the level                                                   *
//* Where to be called: dumpDirContent()                                                 *
//* Editor: Tien-Hung Tseng                                                              *
//****************************************************************************************
string tab_level( int layer )
{
    string tab = "" ;
    for( int i = 0 ; i < layer ; i++ )
    {
        tab += "\t" ;
    }
    return tab ;
}
//****************************************************************************************
//* Fun Name: DirCount()                                                                 *
//* Work: calculate the count of inner dirs in the current dir                           *
//* Where to be called: dumpDirContent()                                                 *
//* Editor: Tien-Hung Tseng                                                              *
//****************************************************************************************
int DirCount( MyDir *currentDir )
{
    assert( currentDir ) ;
    int c = 0 ;
    MyDir *itrDir = currentDir->dirPtr ;//Iterator
    while( itrDir )
    {
        c++ ;
        itrDir = itrDir->nextDir ;
    }
    MyFile *itrFile = currentDir->filePtr ;//Iterator
    while( itrFile )
    {
        c++ ;
        itrFile = itrFile->nextFile ;
    }
    return c ;
}
//****************************************************************************************
//* Fun Name: dumpDirContent()                                                           *
//* Work: dump the content (inner files and dirs) in the current dir                     *
//* Where to be called: dumpDirTree()                                                    *
//* Editor: Tien-Hung Tseng                                                              *
//****************************************************************************************
void FileSystem::dumpDirContent( FILE* f, MyDir* currentDir, int layer )
{
    //---- Check ----------------------------------------------------
    if( !currentDir ) return ;
    assert( f ) ;
    //---- Dump Current Dir Info ---------------------------------./fs
    string tabcount = tab_level( layer ) ;
    int dircount = DirCount( currentDir ) ;
    fprintf( f, "%s%s/d/%d\n", tabcount.c_str(), currentDir->name.c_str(), dircount );
    
    MyDir *itrDir = currentDir->dirPtr ;//Iterator
    //---- Dump Inner Dirs (in Current Dir)  ----------------------
    while( itrDir )
    {
        this->dumpDirContent( f, itrDir, layer+1 ) ;
        itrDir = itrDir->nextDir ;
    }
    //---- Dump Inner Files (in Current Dir) ---------------------
    MyFile *itrFile = currentDir->filePtr ;
    while( itrFile )
    {
        string tabcount2 = tab_level( layer + 1 ) ;
        fprintf( f, "%s%s/f/%d\n", tabcount2.c_str(), itrFile->name.c_str(), itrFile->fid );
        itrFile = itrFile->nextFile ;
    }
}
//****************************************************************************************
//* Fun Name: dumpDirTree()                                                              *
//* Work: dump the tree structure of the file system                                     *
//* Where to be called: run()-choice 4                                                   *
//* Editor: Tien-Hung Tseng                                                              *
//****************************************************************************************
void FileSystem::dumpDirTree()
{
    printf( GREEN"[Info]" RESET "Dump the new tree structure of the filesystem\n" );
    
    FILE *dirtree = fopen("./tree.txt","w") ;
    if( !dirtree )
    {
        assert( dirtree );
        printf( RED"[ERROR]" RESET"Cannot open tree.txt\n" );
    }
    dumpDirContent( dirtree, this->root, 0 ) ;
}
//****************************************************************************************
//* Fun Name: run                                                                        *
//* Work: Read preexisting tree strucutre of directories and files                       *
//* Where to be called: main()                                                           *
//* Editor: Original Author & Tien-Hung Tseng                                            *
//****************************************************************************************
void FileSystem::run()
{
    //------- Var Delcare --------------------------------------------------------------
    int  choice = 0 ;
    string name = "", pass = "", pass1 = "" ;
    system("clear") ;
    //------- Read Setting File --------------------------------------------------------
    this->readUserInfo() ;
    this->readDirTree()  ;
    
    //------- Begin Execution -----------------------------------------------------------
    while( true )
    {
        system("clear");
        cout << "\t\t***********************************************************" << endl;
        cout << "\t\t*               File System                               *" << endl;
        cout << "\t\t*               1. Registration for New User              *" << endl;
        cout << "\t\t*               2. Sign in                                *" << endl;
        cout << "\t\t*               3. Help                                   *" << endl;
        cout << "\t\t*               4. Exit                                   *" << endl;
        cout << "\t\t**********************************************************t" << endl;
        cout << "\t\tPlease choice: " ;
        cin >> choice;
        switch ( choice )
        {
            /*Register*/
            case 1: {
                        cout << "Please type the user name:";
                        cin >> name;
                        cout << "Please type the password: ";
                        cin >> pass;
                        cout << "Retype the password: ";
                        cin >> pass1;
                        while( strcmp( pass.c_str(), pass1.c_str() ) != 0 )
                        {
                            cout << "\t\t--Passwords are inconsistent, please retry..." << endl;
                            cout << "Please type the password: ";
                            cin >> pass;
                            cout << "Retype the password: ";
                            cin >> pass1;
                        }
                        if( regist( name, pass ) == 1 )
                        {
                             cout << "\t\t--Successful registration.." << endl;
                             sleep(2);
                        } 
                        else
                        {
                            cout << "\t\t--Failing registration, please retry" << endl;
                            sleep(2);
                        }
                    }
                    break;

                    /*Sign in*/
            case 2: {
                        cout << "User Name:";
                        cin >> name;
                        cout << "Password:";
                        cin >> pass;
                        if( this->login(name, pass) == 1 )
                        {
                            cout << "       --Successful Login !" << endl;
                            this->fsOperate(name, pass) ;
                        }
                        else
                        {
                            cout << "          --Fail!, Please recheck username and password" << endl;
                            sleep(2);
                        }}
                        break;
            case 3:{
            	        system("clear");
                        cout << "\t\t**********************************************************"  << endl;
                        cout << "\t\t*                        Help                           \t*" << endl;
                        cout << "\t\t*          How do you use the file system ?             \t*" << endl ;
                        cout << "\t\t*                  When typing 'help',                  \t*" << endl;
                        cout << "\t\t*          the helping file will appear                 \t*" << endl;
                        cout << "\t\t*                         OR                            \t*" << endl;
                        cout << "\t\t*      command+?: Instruction of the cmd will appear    \t*" << endl;
                        cout << "\t\t*********************************************************" << endl;
                        system("Pause");
            	     }break;
           
            case 4: {
                        system("clear");
                        this->dumpDirTree() ;
                        cout << "        --Leave the file system.." << endl;
                        sleep(1);
                        exit(0);
                    }
                    break;
            default:
                    printf( RED"[Error] " RESET"The file system can not recognize your choice !\n" );
                    sleep(5);
                    break;
        }
    }

}
