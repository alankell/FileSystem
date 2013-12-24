#include<iostream>
#include<string.h>
#include<string>
#include<iomanip>
#include <stdlib.h>
#include<stdio.h>
#include<windows.h>
#include<iomanip>
#include"FileSystem.h"
using namespace std;
string error[] = {"/","\\", ":","<",">","|","*","&"} ;  //命名中的非法字符
FileSystem::FileSystem() {   
    
    currentDir = NULL;
    tempfile = NULL;
    tempdir = NULL;
}
FileSystem::~FileSystem() {      //析构
    

    MyDir *d = root;        //指向根目录的指针
    MyFile *f = currentDir->fileChain; //当前目录下的文件链表指针
    while (f != 0) {               //清理文件，释放资源
        if (f->nextFile == 0) {
            this->deleteFile(f);
            f = 0;     
            break;    //如果下一个文件为空，则删除这个文件 ，回收内存
        }
        while (f->nextFile->nextFile != 0)
            f = f->nextFile;   
        this->deleteFile(f->nextFile);
        f->nextFile = 0;
        f = currentDir->fileChain;//如果下下一个文件不为空，则删除下个文件，回收内存
    }
    while (d != 0) {      //清理文件夹，释放资源
        if (d->nextDir == 0) {
            this->deleteDir(d);
            d = 0;
            break;
        }
        while (d->nextDir->nextDir != 0)
            d = d->nextDir;
        this->deleteDir(d->nextDir);
        d->nextDir = 0;
        d = root;
    }
}

int FileSystem::newFile() {

    MyFile *p = NULL;
    p = new MyFile;

    if (p == 0) {
        cout << "CREATE           -FALSE";
        return 0;
    }
    cin>>p->name;
    /*命名检测*/
    string tempname(p->name) ;
    for(int i = 0 ;i< 8 ;++i)
    {
        if(tempname.find(error[i],0)!=string::npos)//从字符串的下标为0处开始查找error[i],如果没找到，返回一个特别的标志c++中用npos表示
        {
            cout << "RENAME            -FALSE"<<endl;
            return 0 ;
        }
    }

    /*创建时候情况如下
     * 1. 目录下没有文件
     * 2. 目录下有文件，新文件命名冲突
     * 3. 目录下有文件，新文件无命名冲突
     * */
    /*检测有无同名函数*/
    if (currentDir->fileChain == NULL) {
        p->nextFile = currentDir->fileChain;
        currentDir->fileChain = p;
    } else {
        MyFile *q = new MyFile;
        q = currentDir->fileChain;
        while (q != NULL) {
            if (strcmp(p->name, q->name)==0) {
                cout << "FILE EXISTS             -FALSE" << endl;
                return 0;
            }
            q = q->nextFile;
        }

        /*重置链表结构*/
        p->nextFile = currentDir->fileChain;
        currentDir->fileChain = p;
        MyDir *h = currentDir;

       
    }
    
    cout <<"CREATE             -OK" << endl;
    return 1;
}

int FileSystem::newDir() {
    MyDir *p, *h;
    p = new MyDir;
    cin >> p->name;

    /*命名检测*/
    string tempname(p->name) ;
    for(int i = 0 ;i< 8 ;++i)
    {
        if(tempname.find(error[i],0)!=string::npos)
        {
            cout << "RENAME              -FALSE"<<endl;
            return 0 ;
        }
    }


    p->dirChain = NULL;
    p->fileChain = NULL;
    p->nextDir = NULL;
    if (currentDir->dirChain == NULL)
        h = NULL;
    else
        h = currentDir->dirChain;

    /*创建时候情况如下
     * 1. 目录下没有子目录
     * 2. 目录下有子目录，命名冲突
     * 3. 目录下有子目录，无命名冲突
     * */
    /*检测有无同名目录*/

    while (h != NULL) {
        if (strcmp(h->name, p->name)==0) {
            cout << "DIR EXISTS           -FALSE" << endl;
            return 0;
        }
        h = h->nextDir;
    }

    /*重置链表结构*/
    p->preDir = currentDir;
    p->nextDir = currentDir->dirChain;
    currentDir->dirChain = p;

    cout << "CREATE                -OK" << endl;
    return 1;
}
int FileSystem::deleteFile(MyFile *f) {
    delete f;
    f = NULL;
    return 1;
}

int FileSystem::deletefileJudge() {
    char temp[MAX_NUM];

    cin >> temp;   //输入要删除的文件的名称
    MyFile *f;
    MyFile *above = NULL;
    f = currentDir->fileChain;

    /*
     * 判断该目录下有无需要删除的文件
     * */

    while (f != NULL) {
        if (!strcmp(f->name, temp))  
            break;  
        above = f;
        f = f->nextFile;
    }           //查询要删除的文件
    if (f == NULL) {
        cout << "NO FILE              -FALSE" << endl;
        return 0;
    }
    
    MyDir *d = currentDir;
    
    /*
     * 删除时考虑
     * 1. 需要删除的文件恰好是目录文件链表中的头节点
     * 2. 需要删除的文件在链表中间
     * */

    if (f == currentDir->fileChain)//删除文件结点
        currentDir->fileChain = currentDir->fileChain->nextFile;
    else
        above->nextFile = f->nextFile;
    delete f;
    f = NULL;
    cout << "DELETE             -OK" << endl;
    return 1;
}
int FileSystem::deleteDir(MyDir *d) {
    delete d;
    d = NULL;
    return 1;
}

int FileSystem::deletedirJudge() {
    char n[MAX_NUM];

    MyDir *p, *pre = NULL;
    p = root;
    p = currentDir->dirChain;
    cin >> n; //删除的文件名

    /*查找所需要删除的目录*/
    while (p != NULL) {
        if (strcmp(p->name, n)==0)
            {pre = p;break;}
        p = p->nextDir;
    }

    if (p == NULL) {
        cout << "DELETE            -FALSE" << endl;
        return 0;
    }

    /*删除目录时需要考虑
     * 1. 该目录处于父目录的目录链表的位置
     * 2. 该目录下是否有子目录或者子文件
     * */
    
    if (p == currentDir->dirChain)
        currentDir->dirChain = currentDir->dirChain->nextDir;
    else
        p->preDir->nextDir = p->nextDir;

    pre = currentDir;
    while (pre != NULL) //修改删除目录后各级目录大小
    {
       
        pre = pre->preDir;
    }
    
    MyDir *d = p->dirChain;
    MyFile *f = p->fileChain;
    if (f != 0) {
        while (p->fileChain->nextFile != NULL)//删除此目录下的文件
        {
            f = p->fileChain;
            while (f->nextFile->nextFile != NULL)//寻找最后一个文件结点
                f = f->nextFile;
            this->deleteFile(f->nextFile);
            f->nextFile = NULL;
        }
        if (p->fileChain->nextFile == NULL) {
            this->deleteFile(p->fileChain);
            p->fileChain = NULL;
        }
    }
    if (d != NULL) {
        while (p->dirChain->nextDir != NULL)//删除此目录下的目录
        {
            d = p->dirChain;
            while (d->nextDir->nextDir != NULL)//寻找最后一个文件结点
                d = d->nextDir;
            this->deleteDir(d->nextDir);//递归调用此函数
            d->nextDir = NULL;
        }
        if (p->dirChain->nextDir == NULL) {
            this->deleteDir(p->dirChain);
            p->dirChain = NULL;
        }
    }
    delete p,d,f;

    cout << "DELETE           -OK" << endl;
    return 1;

}

int FileSystem::openDir() {
    char name[MAX_NUM];
    MyDir *p;
    p = currentDir->dirChain;

    cin >> name;
    while (p != NULL) {
        if (strcmp(p->name, name) == 0) {
            currentDir = p;
            return 1;
        }
        p = p->nextDir;
    }
    cout << "NO DIR             -FALSE" << endl;
    return 0;
}


int FileSystem::renameDir() {
    MyDir *h;
    char n1[MAX_NUM], n2[MAX_NUM];
    cin >> n1;
    cin >> n2;
    h = currentDir->dirChain;
    while (h != NULL) {
        if (strcmp(h->name, n2)==0) {
            cout << "DIR EXIST        -FALSE" << endl;
            return 0;
        }
        h = h->nextDir;
    }
    h = currentDir->dirChain;
    while (h != NULL) {
        if (strcmp(h->name, n1)==0)
            break;
        h = h->nextDir;
    }
    if (h == NULL) {
        cout << "NO DIR         -FALSE" << endl;
        return 0;
    }
    strcpy(h->name, n2);
    cout << "RENAME            -OK" << endl;
    return 1;
}

int FileSystem::renameFile() {
    MyFile *h;
    char n1[MAX_NUM], n2[MAX_NUM];
    cin >> n1;
    cin >> n2;
    h = currentDir->fileChain;
    while (h != NULL) {
        if (!strcmp(h->name, n2)) {
            cout << "FILE EXISTS           -FALSE" << endl;
            return 0;
        }
        h = h->nextFile;
    }
    h = currentDir->fileChain;
    while (h != NULL) {
        if (!strcmp(h->name, n1))
            break;
        h = h->nextFile;
    }
    if (h == NULL) {
        cout << "NO FILE            -FALSE" << endl;
        return 0;
    }
    strcpy(h->name, n2);
    cout << "RENAME             -OK" << endl;
    return 1;
}

MyDir *FileSystem::copyDir(MyDir *d) {
    MyFile *fh;
    MyDir *dh, *dir;
    dir = new MyDir;
    dir->dirChain = NULL;
    dir->fileChain = NULL;
    dir->nextDir = NULL;
    dir->preDir = NULL;
    fh = d->fileChain;
    dh = d->dirChain;

    while (fh != NULL) {
        MyFile *f;
        f = copyFile(fh);
        f->nextFile = dir->fileChain;
        dir->fileChain = f;
        fh = fh->nextFile;
    }

    while (dh != NULL) {
        MyDir *d1, *d2;
        d1 = copyDir(dh);
        d1->preDir = dir;
        dir->dirChain = d1;
        d2 = dh->nextDir;
        while (d2 != NULL) {
            d1->nextDir = copyDir(d2);

            d2 = d2->nextDir;
            d1 = d1->nextDir;
            d1->preDir = dir;
        }

        dh = dh->dirChain;
    }

    strcpy(dir->name, d->name);
    return dir;
}

MyDir *FileSystem::copydirJudge() {
    MyDir *h;
    char n[MAX_NUM];
    cin >> n;
    h = currentDir->dirChain;
    while (h != NULL) {
        if (!strcmp(h->name, n))
            break;
        h = h->nextDir;
    }
    if (h == NULL) {
        cout << "NO DIR            -FALSE" << endl;
        return 0;
    }
    tempdir = copyDir(h);
    cout << "COPY           -OK" << endl;
    return tempdir;
}

MyFile *FileSystem::copyFile(MyFile *h) {
    MyFile *f;
    f = new MyFile;
    strcpy(f->name, h->name);
    f->content = h->content;
    return f;
}

MyFile *FileSystem::copyfileJudge() {
    MyFile *h;
    char n[MAX_NUM];
    cin >> n;
    h = currentDir->fileChain;

    while (h != NULL) {
        if (!strcmp(h->name, n))
            break;
        h = h->nextFile;
    }
    if (h == NULL) {
        cout << "NO FILE             -FALSE" << endl;
        return NULL;
    }
    tempfile = copyFile(h);
    cout << "COPY             -OK" << endl;
    return tempfile;
}

int FileSystem::pasteDir() {
    MyDir *h, *d1;
    h = currentDir->dirChain;

    if (tempdir == NULL) 
	{
        cout << "NO SOURCE            -FALSE" << endl;
        return 0;
    }
    else if (h == NULL)
	   {
        cout << "PASTE              -OK" << endl;
        return 1;
        
        d1 = copyDir(tempdir);
        currentDir->dirChain = d1;
        d1->preDir = currentDir;
        }
        else  {
        while (h != NULL) {
            if (!strcmp(h->name, tempdir->name))
                break;
            h = h->nextDir;
                          }
        
            cout << "DIR EXISTS          -FALSE" << endl;
            return 0;
       
            d1 = copyDir(tempdir);
            d1->nextDir = currentDir->dirChain;
            currentDir->dirChain = d1;
            d1->preDir = currentDir;
            
             }
    
    cout << "PASTE              -OK" << endl;
    return 1;
}

int FileSystem::pasteFile() {
    MyFile *h = currentDir->fileChain;
	MyFile *pTemp = h;
    if (tempfile == NULL) {
        cout << "NO SOURCE              -FALSE" << endl;
        return 0;
    }
    /*如果当前目录没有文件*/
    if (h == NULL) {
        currentDir->fileChain = copyFile(tempfile);
		 cout << "PASTE                -OK" << endl;
    }
	else {
        while (h != NULL) {          //检查是否存在和复制文件重名
            if (!strcmp(h->name, tempfile->name)) {   
                cout << "FILE EXISTS                -FALSE" << endl;
                return 0;
            }
            //break;
            h = h->nextFile;
        }
	      /*无重名则粘贴*/              
        currentDir->fileChain = copyFile(tempfile);
		currentDir->fileChain->nextFile = pTemp;
        //currentDir->fileChain->nextFile = h;
		 cout << "PASTE                -OK" << endl;
    return 1;
    }
return 0;
   
}



int FileSystem::show_path(MyDir *d)//实现显示当前路径的函数
{
    if (d->preDir == NULL)
        cout << root->name;
    if (d->preDir != NULL) {
        this->show_path(d->preDir);//递归调用此函数
        cout << d->name;
    }
    cout << "/";
    return 1;
}

int FileSystem::showCurrentDir() {
    MyDir *d = currentDir->dirChain;
    MyFile *f = currentDir->fileChain;
    if (d == NULL && f == NULL) { 
        cout << "EMPTY" << endl;
        return 0;
    }
    cout << "CONTENT:" << endl;

    if (d != NULL) {       //显示文件夹列表
        cout << "\t" << "D_NAME" << "\t" << endl;
        while (d != NULL) {                         
            cout << "\t" << d->name << "\t" << endl;
            d = d->nextDir;
        }
        cout << endl;
    }

    if (f != NULL) {                    //显示文件列表
        cout << "\t" << "F_NAME" << "\t" <<  endl;
        while (f != NULL) {
            cout << "\t" << f->name << "\t"  <<  endl;
            f = f->nextFile;
        }
    }
    return 1;
}

int FileSystem::showPath()//显示当前文件夹路径
{
	 
     show_path(currentDir);
     return 1;
}

int FileSystem::goback() {
    if (currentDir->preDir == NULL) {
        cout << "ROOT DIR          -FALSE" << endl;
        return 0;
    }
    currentDir = currentDir->preDir;
    return 1;
}

int FileSystem::setUser(char *n, char *c) { //用户设定
    MyDir *root = new MyDir;
    strcpy(root->name, n);
    strcpy(password, c);

    this->root = root;  //文件系统初始化
    currentDir = root;
    currentDir->preDir = NULL;
    currentDir->dirChain = NULL;
    currentDir->fileChain = NULL;
    currentDir->nextDir = NULL;
    return 1;
}

int FileSystem::changePass() {
	//char newname[30];
	char newpass[30];
	 FILE *passwd;//文件指针
    if ((passwd = fopen("user.ini", "w+")) == NULL) {
        printf("File client.txt could not be opened\n");
        fclose(passwd);
        return 0;
    } else {
            
			cout << "请输入新密码："<<endl;
			cin>>newpass;
			fprintf(passwd, "%s %s\n",root->name, newpass);
            fclose(passwd);
        return 1;

       }
}


MyDir *FileSystem::getCurrentdir() {  //获取当前目录
    return currentDir;
}