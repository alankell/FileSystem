#include"Interface.h"
#include<iostream>
#include<string>
#include"FileSystem.h"
#include<unistd.h>

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


/*User register and write the file function*/
int regist( char username[30], char password[30])
{
    FILE *cfptr;//pointer to the file
    if ((cfptr = fopen("users.ini", "a+")) == NULL)
    {
        printf("File client.txt could not be opened\n");
        fclose(cfptr);
        return 0;
    } else {
        fprintf(cfptr, "%s %s\n", username, password);
        fclose(cfptr);
        return 1;

    }
}
/*Check whether the user name/passed has been registered*/
int login(char username[30], char password[30]) {
    char user[30];
    char pass[30];
    FILE *cfptr;//pointer to file
    if ((cfptr = fopen("users.ini", "r")) == NULL) {
        printf("File client.txt could not be opened\n");
        fclose(cfptr);
        return 0;
    } else {
        while (!feof(cfptr)) {
            fscanf(cfptr, "%s%s", user, pass);
            if ((strcmp(username, user) == 0) && (strcmp(password, pass) == 0)) {
                fclose(cfptr);
                return 1;
            }
        }
    }
    fclose(cfptr);
    return 0;
}

int fsOperate( char name[30], char pass[30] )
{
    FileSystem fs;
    fs.setUser(name, pass);
    while (1) {
        system("clear");
        help();
        while (1) {
            cout << endl;
            string choice;

            fs.showPath();
            cin >> choice;
            if (choice == "mkdir")
                fs.newDir();
            else if (choice == "mk")
                fs.newFile();
            else if (choice == "rmdir")
                fs.deleteDir();
            else if (choice == "rm")
                fs.deleteFile();
            else if (choice == "renamedir")
                fs.renameDir();
            else if (choice == "rename")
                fs.renameFile();
            else if (choice == "cd")
                fs.readDir();
            else if (choice == "read")
                fs.readFile();
            else if (choice == "ls")
                fs.showCurrentDir();
            else if (choice == "cpdir")
                fs.copyDir();
            else if (choice == "cp")
                fs.copyFile();
            else if (choice == "pastedir")
                fs.pasteDir();
            else if (choice == "paste") {
                fs.pasteFile();
            } else if (choice == "vi")
                fs.edit();
            else if (choice == "cd..")
                fs.goback();
            else if (choice == "clear") {
                system("clear");
                help();
            } else if (choice == "exit") {
                system("clear");
                cout << "用户: " << name << "正在注销...."
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
                cout << "荂lean file screem" << endl;
            else if (choice == "vi?")
                cout << "Edit an file: vi[filename]" << endl;
            else if (choice == "cd..?")
                cout << "Enter the upper layer directory" << endl;
            else if (choice == "exit?")
                cout << "Exit" << endl;
            else
                cout << "Invalid Command" << endl;
        }
    }

}
void run()
{
    int  choice = 0 ;
    char name[30], pass[30], pass1[30];
    system("clear");//clean the screen
    sleep(2);
    while( true )
    {
        system("clear");
        cout << "\t\t***********************************************************\t" << endl;
        cout << "\t\t*               File System                                \t*" << endl;
        cout << "\t\t*               1. Registration for New User               \t*" << endl;
        cout << "\t\t*               2. Sign in                                 \t*" << endl;
        cout << "\t\t*               3. Help                                    \t*" << endl;
        cout << "\t\t*               4. Exit                                    \t*" << endl;
        cout << "\t\t***********************************************************\t" << endl;
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
                        while( strcmp(pass, pass1) != 0 )
                        {
                            cout << "          --Passwords are inconsistent, please retry..." << endl;
                            cout << "Please type the password: ";
                            cin >> pass;
                            cout << "Retype the password: ";
                            cin >> pass1;
                        }
                        if( regist(name, pass) == 1 )
                        {
                             cout << "        --Successful registration.." << endl;
                             sleep(2);
                        } 
                        else
                        {
                            cout << "         --Failing registration, please retry" << endl;
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
                        if( login(name, pass) == 1 )
                        {
                            cout << "       --Successful Login !" << endl;
                            fsOperate(name, pass);

                        } else{
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
                         sleep(3);
                        exit(0);
                    }
                    break;
                    /*其他选项*/
            default:
                    
                    break;
        }
    }

}
