#include"Interface.h"
#include<iostream>
#include<string>
#include<fstream>
#include"FileSystem.h"
#include<unistd.h>

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
void FileSystem::run()
{
    int  choice = 0 ;
    string name, pass, pass1 ;
    system("clear");//clean the screen
    sleep( 1 );
    
    this->readUserInfo() ;
    
    
    
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
