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
    cout << "* 6.mkdir + <string>                      新建目录,目录名为<string>       *" << endl;
    cout << "* 7.rmdir + <string>                      删除目录,目录名为<string>       *" << endl;
    cout << "* 8.renamedir + <string> + <string>       重命名目录,第二个string是新名字 *" << endl;
    cout << "* 9.cpdir + <string>                      复制目录,目录名为<string>       *" << endl;
    cout << "* 10.pastedir                             粘贴目录                        *" << endl;
    cout << "* 11.ls                                   显示目录下所有内容              *" << endl;
    cout << "* 12.cd +<string>                         打开目录上一个目录或下一个目录  *" << endl;
    cout << "* 13.cd..                                 返回上一级目录                  *" << endl;
	cout << "* 14.pwd                                  显示当前目录                    *" << endl;
	cout << "* 15.passwd                               修改用户口令                    *" << endl;
    cout << "* 16.clear                                清屏                            *" << endl;
    cout << "* 17.exit                                 注销                            *" << endl;
    cout << "***************************************************************************" << endl
        << endl;

}


/*用户名字密码检验（与文件内数据比较）*/
int login(char username[30], char password[30]) {
    char name[30];
    char pass[30];
    FILE *Verify;//文件指针
    if ((Verify = fopen("user.ini", "r")) == NULL) {
        printf("File client.txt could not be opened\n");
        fclose(Verify);
        return 0;
    } else {
        while (!feof(Verify)) {
            fscanf(Verify, "%s%s", name, pass);
            if ((strcmp(username, name) == 0) && (strcmp(password, pass) == 0)) {
                fclose(Verify);
                return 1;
            }
        }
    }
    fclose(Verify);
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
                fs.deletedirJudge();
            else if (choice == "rm")
                fs.deletefileJudge();
            else if (choice == "renamedir")
                fs.renameDir();
            else if (choice == "rename")
                fs.renameFile();
            else if (choice == "cd")
                fs.openDir();
            else if (choice == "ls")
                fs.showCurrentDir();
            else if (choice == "cpdir")
                fs.copydirJudge();
            else if (choice == "cp")
                fs.copyfileJudge();
            else if (choice == "pastedir")
                fs.pasteDir();
            else if (choice == "paste") 
                fs.pasteFile();
			else if (choice=="pwd")
				fs.getCurrentdir();
			else if (choice=="passwd")
				fs.changePass();
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
            else if (choice == "cd..?")
                cout << "返回当前目录的上一级目录" << endl;
			else if (choice == "pwd?")
				cout << "显示当前目录"<<endl;
			else if (choice == "passwd?")
				cout << "修改用户口令"<<endl;
            else if (choice == "exit?")
                cout << "注销文件系统" << endl;
            else
                cout << "命令无效！" << endl;
        }
    }

}
void run(){
    int choice = 0;
    char name[30], pass[30];
    system("CLS");
    Sleep(2);
    while (true) {
        system("CLS");
        cout << "\t\t*****************************************\t" << endl;
        cout << "\t\t*             文  件  系  统          \t*" << endl;
        cout << "\t\t*               1. 登录               \t*" << endl;
        cout << "\t\t*               2. 帮助              \t*" << endl;
        cout << "\t\t*               3. 退出               \t*" << endl;
        cout << "\t\t*****************************************\t" << endl;
        cout << "\t\t请选择: " ;
        cin >> choice;
        switch (choice) {

                    /*选择登录*/
            case 1: {
                        cout << "请输入用户名:";
                        cin >> name;
                        cout << "请输入密码:";
                        cin >> pass;
                        if (login(name, pass) == 1) {
                            cout << "       --登录成功.." << endl;
                            fsOperate(name, pass);

                        } else{
                            cout << "           --登录失败，请向开发者索要账号密码..." << endl;
                             Sleep(2000);

                        }}
                        break;
						/*选择帮助*/
            case 2:{
            	      system("CLS");
                        cout << "\t\t*********************************************************" << endl;
                        cout << "\t\t*                        帮助文档                     \t*" << endl;
                        cout << "\t\t*   如何使用该系统，输入help时显示所有命令的帮助文档；\t*" << endl;
                        cout << "\t\t*        输入某个命令+？时显示该条命令的使用说明      \t*" << endl;
                        cout << "\t\t*********************************************************" << endl;
                        system("Pause");
            	     }break;
                      /*选择退出*/
            case 3: {
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