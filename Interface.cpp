#include"Interface.h"
#include<iostream>
#include<string>
#include"FileSystem.h"
#include<Windows.h>
using namespace std;
void help() {
    cout << "***************************************************************************" << endl;
    cout << "* 1.mk + <string>                         新建一个文件,文件名为<string>   *" << endl;
    cout << "* 2.rm + <string>                         删除文件名为<string>的文件      *" << endl;
    cout << "* 3.rename + <string> + <string>          重命名文件,第二个string是新名字 *" << endl;
    cout << "* 4.cp + <string>                         复制文件,文件名为<string>       *" << endl;
    cout << "* 5.paste                                 粘贴文件                        *" << endl;
    cout << "* 6.read  + <string>                      打开文件,文件名为<string>       *" << endl;
    cout << "* 7.vi + <string>                         编辑文件,文件名为<string>       *" << endl;
    cout << "* 8.mkdir + <string>                      新建目录,目录名为<string>       *" << endl;
    cout << "* 9.rmdir + <string>                      删除目录,目录名为<string>       *" << endl;
    cout << "* 10.renamedir + <string> + <string>      重命名目录,第二个string是新名字 *" << endl;
    cout << "* 11.cpdir + <string>                     复制目录,目录名为<string>       *" << endl;
    cout << "* 12.pastedir                             粘贴目录                        *" << endl;
    cout << "* 13.ls                                   显示目录下所有内容              *" << endl;
    cout << "* 14.cd +<string>                         打开目录上一个目录或下一个目录  *" << endl;
    cout << "* 15.cd..                                 返回上一级目录                  *" << endl;
    cout << "* 16.clear                                清屏                            *" << endl;
    cout << "* 17.exit                                 注销                            *" << endl;
    cout << "***************************************************************************" << endl
        << endl;

}


/*用户注册写入文件函数*/
int regist(char username[30], char password[30]) {

    FILE *cfptr;//文件指针
    if ((cfptr = fopen("users.ini", "a+")) == NULL) {
        printf("File client.txt could not be opened\n");
        fclose(cfptr);
        return 0;
    } else {
        fprintf(cfptr, "%s %s\n", username, password);
        fclose(cfptr);
        return 1;

    }
}
/*用户名字密码检验，是否已经注册（与文件内数据比较）*/
int login(char username[30], char password[30]) {
    char user[30];
    char pass[30];
    FILE *cfptr;//文件指针
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

int fsOperate(char name[30], char pass[30]) {
    FileSystem fs;
    fs.setUser(name, pass);
    while (1) {
        system("CLS");
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
                system("CLS");
                help();
            } else if (choice == "exit") {
                system("CLS");
                cout << "用户: " << name << "正在注销...."
                    << endl;
                 Sleep(3);
                return 0;
            } else if (choice == "help") {
                help();
            } else if (choice == "mkdir?")
                cout << "创建新目录 ，格式为 mkdir [dirname]" << endl;
            else if (choice == "mk?")
                cout << "创建新文件，格式为 mk[filename]" << endl;
            else if (choice == "rmdir?")
                cout << "删除子目录，格式为 rmdir [dirname]" << endl;
            else if (choice == "rm?")
                cout << "删除文件，输入格式为 rm [filename]" << endl;
            else if (choice == "renamedir?")
                cout << "目录重命名 " << endl;
            else if (choice == "rename?")
                cout << "文件重命名 " << endl;
            else if (choice == "cd?")
                cout << "打开子目录，格式为 cd [dirname]" << endl;
            else if (choice == "read?")
                cout << "查看文件内容，格式为 read [filename]" << endl;
            else if (choice == "ls?")
                cout << "显示目录内容列表" << endl;
            else if (choice == "cpdir?")
                cout << "复制子目录, 格式为 cpDir [dirname]" << endl;
            else if (choice == "cy?")
                cout << "复制文件,格式为 cp [filename]" << endl;
            else if (choice == "pastedir?")
                cout << "粘贴已复制的目录" << endl;
            else if (choice == "paste?")
                cout << "粘贴已复制的文件" << endl;
            else if (choice == "clear?")
                cout << "清屏" << endl;
            else if (choice == "vi?")
                cout << "编辑文档，输入格式为 vi[filename]" << endl;
            else if (choice == "cd..?")
                cout << "返回当前目录的上一级目录" << endl;
            else if (choice == "exit?")
                cout << "注销文件系统" << endl;
            else
                cout << "命令无效！" << endl;
        }
    }

}
void run(){
    int choice = 0;
    char name[30], pass[30], pass1[30];
    system("CLS");
    Sleep(2);
    while (true) {
        system("CLS");
        cout << "\t\t*****************************************\t" << endl;
        cout << "\t\t*             文  件  系  统          \t*" << endl;
        cout << "\t\t*               1. 注册新用户         \t*" << endl;
        cout << "\t\t*               2. 登录               \t*" << endl;
        cout << "\t\t*               3. 帮助              \t*" << endl;
        cout << "\t\t*               4. 退出               \t*" << endl;
        cout << "\t\t*****************************************\t" << endl;
        cout << "\t\t请选择: " ;
        cin >> choice;
        switch (choice) {
            /*选择注册*/
            case 1: {
                        cout << "请输入用户名:";
                        cin >> name;
                        cout << "请输入密码: ";
                        cin >> pass;
                        cout << "请确认密码: ";
                        cin >> pass1;
                        while (strcmp(pass, pass1) != 0) {
                            cout << "          --两次密码不一致，请重试.." << endl;
                            cout << "请输入密码: ";
                            cin >> pass;
                            cout << "请确认密码: ";
                            cin >> pass1;
                        }
                        if (regist(name, pass) == 1){
                            cout << "        --注册成功.." << endl;
                             Sleep(2);
                        } 
                        else{
                            cout << "         --注册失败，请重试.." << endl;
                             Sleep(2);
                        }
                    }
                    break;

                    /*选择登录*/
            case 2: {
                        cout << "请输入用户名:";
                        cin >> name;
                        cout << "请输入密码:";
                        cin >> pass;
                        if (login(name, pass) == 1) {
                            cout << "       --登录成功.." << endl;
                            fsOperate(name, pass);

                        } else{
                            cout << "          --登录失败，请检查用户名和密码.." << endl;
                             Sleep(2);

                        }}
                        break;
            case 3:{
            	      system("CLS");
                        cout << "\t\t*********************************************************" << endl;
                        cout << "\t\t*                        帮助文档                     \t*" << endl;
                        cout << "\t\t*   如何使用该系统，输入help时显示所有命令的帮助文档；\t*" << endl;
                        cout << "\t\t*        输入某个命令+？时显示该条命令的使用说明      \t*" << endl;
                        cout << "\t\t*********************************************************" << endl;
                        system("Pause");
            	     }break;
           
            case 4: {
                        system("CLS");
                        cout << "        --退出文件系统.." << endl;
                         Sleep(3);
                        exit(0);
                    }
                    break;
                    /*其他选项*/
            default:
                    
                    break;
        }
    }

}