#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include <stdlib.h>
using namespace std;
class Student
{
private:
    long num;
    char name[20];
    char sex[2];
    float Chinese;
    float Maths;
    float English;
    Student *Next;
    Student *Head;
public:
    int Creat()
    {
        FILE *fp;
        Head = NULL;    //存放链表的起始地址
        Student *p, *pEnd;
        p = new Student; //创建一个动态对象
        if((fp=fopen("Student.txt","r"))==NULL)
        {
            cout << "can not open file!" << endl;
            exit(0);
        }
        fscanf(fp,"%ld%s%s%f%f%f",&p->num,p->name,p->sex,&p->Chinese,&p->Maths,&p->English); //输入指针p指向的对象的数据成员的值
        pEnd = Head;                          // 存放当前对象的地址
        while(!feof(fp))
        {
            // 0 是输入结束的标志
            if(NULL == Head)
                Head = p;                     // 只在第一次执行此语句
            else
                pEnd->Next = p;               // 存放下一个对象的地址
            pEnd = p;
            p = new Student;                  //动态创建下一个对象
            fscanf(fp,"%ld%s%s%f%f%f",&p->num,p->name,p->sex,&p->Chinese,&p->Maths,&p->English); //输入下一个对象数据成员的值
        }

        pEnd->Next = NULL;

        return 0;
    }
    int Add()
    {
        //----以追加的方式录入信息，直接将信息追加到以前文件的末尾----
        ofstream outfile;
        outfile.open("Student.txt",ios::out|ios::app|ios::ate);   //----打开文件----
        if(!outfile)
        {
            cerr<<" open error"<<endl;
            exit(1);
        }

        //----依次输入相应的数据，并且追加到之前的文件中去---
        cout<<"请输入该学生的学号："<<endl;
        cin>>num;
        outfile<<num<<"  ";
        cout<<"请输入该学生的姓名："<<endl;
        cin>>name;
        outfile<<name<<"  ";
        do
        {
            cout<<"请输入该学生的性别(男/女)："<<endl;
            cin>>sex;
            if(!strcmp(sex,"男")&&!strcmp(sex,"女"))
            {
                cout<<"输出结果不符合要求，请重输！"<<endl;
            }
        }
        while(!strcmp(sex,"男")&&!strcmp(sex,"女"));
        outfile<<sex<<"  ";
        cout<<"请输入该学生的语文成绩："<<endl;
        cin>>Chinese;
        outfile<<Chinese<<"  ";
        cout<<"请输入该学生的数学成绩："<<endl;
        cin>>Maths;
        outfile<<Maths<<"  ";
        cout<<"请输入该学生的英语成绩："<<endl;
        cin>>English;
        outfile<<English<<"  "<<endl;
        outfile.close();
        cout<<"已添加成功！"<<endl;
        return 0;
    }
    void display()
    {
        Student *p;
        Creat();
        cout << "所有学生数据列表如下" << endl;
        p=Head;
        while(p != NULL)
        {
            cout<<" 学号 "<<p->num<<endl;
            cout<<" 姓名 "<<p->name<<endl;
            cout<<" 性别 "<<p->sex<<endl;
            cout<<" 语文成绩 "<<p->Chinese<<endl;
            cout<<" 数学成绩 "<<p->Maths<<endl;
            cout<<" 英语成绩 "<<p->English<<endl;
            cout<<" 平均成绩 "<<((p->Chinese+p->Maths+p->English)/3)<<endl<<endl;
            p = p->Next;
        }
        cout<<"不及格学生的名单："<<endl;
        p=Head;
        while(p != NULL)
        {
            if(p->Chinese<60||p->Maths<60||p->English<60)
            {
                cout<<" 学号 "<<p->num<<endl;
                cout<<" 姓名 "<<p->name<<endl;
                cout<<" 性别 "<<p->sex<<endl;
                cout<<" 语文成绩 "<<p->Chinese<<endl;
                cout<<" 数学成绩 "<<p->Maths<<endl;
                cout<<" 英语成绩 "<<p->English<<endl;
                cout<<" 平均成绩 "<<((p->Chinese+p->Maths+p->English)/3)<<endl<<endl;

            }
            p = p->Next;
        }
    }
    int Del()//****************************************删除
    {
        FILE *fp;
        Student *p,*p1;
        char namer[30];
        long numr;
        int x;
        Creat();
        do
        {
            cout << "请输入要删除的学生的姓名(1)或学号(2):";
            cin>>x;
            if(x==1)
            {
                cout<<"姓名：";
                cin >> namer;
            }
            if(x==2)
            {
                cout<<"学号：";
                cin >>numr;
            }
            else
                cout<<"输出结果不合要求请重输！"<<endl;
        }
        while(x!=1&&x!=2);
        cout << endl;
        if(Head!=NULL)
        {
            p=Head;
            if(x==1)
            {
                while(strcmp(namer,p->name))
                {
                    p1=p;
                    p=p->Next;
                    if(p==NULL)
                        break;
                }
            }
            if(x==2)
            {
                while(numr!=p->num)
                {
                    p1=p;
                    p=p->Next;
                    if(p==NULL)
                        break;
                }
            }

            if(p!=NULL)
            {
                cout << "你要删除的学生的相关信息如下:" << endl;
                cout << "  学号  : " << p->num<< endl;
                cout << "  姓名  : " << p->name<< endl;
                cout << "  性别  : " << p->sex << endl;
                cout << "  语文成绩  : " << p->Chinese<< endl;
                cout << "  数学成绩  : " << p->Maths<< endl;
                cout << "  英语成绩  : " << p->English<< endl;
                system("pause");
                if(p==Head)Head=p->Next;
                else
                    p1->Next=p->Next;
                if((fp=fopen("Student.txt","w"))==NULL)
                {
                    cout << "can not open file!" << endl;
                    exit(0);
                }
                p=Head;
                if(Head!=NULL)
                    do
                    {
                        fprintf(fp,"%ld %s %s %f %f %f\n",p->num,p->name,p->sex,p->Chinese,p->Maths,p->English);
                        p=p->Next;
                    }
                    while(p!=NULL);
                fclose (fp);
                cout << "该学生的所有信息已被删除!" << endl;
            }

            else
                cout << "没有找到你想要删除的学生的信息" <<endl;
        }
        else
            cout << "文件中还没有任何学生的信息"<<endl;
        return 0;
    }
    int search()//***************************************查询课程设计题目
    {

        Student *p,*p1;
        char namer[30];
        long numr;
        int x;
        Creat();
        cout << "所有学生数据列表如下" << endl;
        p=Head;
        while(p != NULL)
        {

            cout<<" 学号 "<<p->num<<endl;
            cout<<" 姓名 "<<p->name<<endl;
            cout<<" 性别 "<<p->sex<<endl;
            cout<<" 语文成绩 "<<p->Chinese<<endl;
            cout<<" 数学成绩 "<<p->Maths<<endl;
            cout<<" 英语成绩 "<<p->English<<endl;
            p = p->Next;
        }
        do
        {

            cout << "请输入要查找的学生的姓名(1)或学号(2):";
            cin>>x;
            if(x==1)
            {
                cout<<"姓名：";
                cin >> namer;
            }
            if(x==2)
            {
                cout<<"学号：";
                cin >>numr;
            }
            else
                cout<<"输出结果不合要求请重输！"<<endl;
        }
        while(x!=1&&x!=2);
        cout << endl;
        if(Head!=NULL)
        {
            p=Head;
            if(x==1)
            {
                while(strcmp(namer,p->name))
                {
                    p1=p;
                    p=p->Next;
                    if(p==NULL)
                        break;
                }
            }
            if(x==2)
            {
                while(numr!=p->num)
                {
                    p1=p;
                    p=p->Next;
                    if(p==NULL)
                        break;
                }
            }

            if(p!=NULL)
            {
                cout << "你要查找的学生的相关信息如下:" << endl;
                cout << "  学号 : " << p->num<< endl;
                cout << "  姓名 : " << p->name<< endl;
                cout << "  性别  : " << p->sex << endl;
                cout << "  语文成绩  : " << p->Chinese<< endl;
                cout << "  数学成绩  : " << p->Maths<< endl;
                cout << "  英语成绩  : " << p->English<< endl;
            }
            else
                cout << "没有找到你想要查找的学生的信息" <<endl;
        }
        else
            cout << "文件中还没有任何学生信息"<<endl;
        return 0;
    }
    int Modify()//*****************************修改
    {
        FILE *fp;
        Student *p;
        char namer[20];
        long numr;
        int x;
        Creat();
        do
        {
            cout << "请输入要修改的学生的姓名(1)或学号(2):";
            cin>>x;
            if(x==1)
            {
                cout<<"姓名：";
                cin >> namer;
            }
            if(x==2)
            {
                cout<<"学号：";
                cin >> numr;
            }
            else
                cout<<"输出结果不合要求请重输！"<<endl;
        }
        while(x!=1&&x!=2);
        cout << endl;
        if(Head!=NULL)
        {
            p=Head;
            if(x==1)
            {
                while(strcmp(namer,p->name))
                {
                    p=p->Next;
                    if(p==NULL)
                        break;
                }
            }
            if(x==2)
            {
                while(numr!=p->num)
                {
                    p=p->Next;
                    if(p==NULL)
                        break;
                }
            }


            if(p!=NULL)
            {
                cout << "你要修改的学生的相关信息如下:" << endl;
                cout << "  学号  : " << p->num<< endl;
                cout << "  姓名  : " << p->name << endl;
                cout << "  性别  : " << p->sex << endl;
                cout << "  语文成绩  : " << p->Chinese<< endl;
                cout << "  数学成绩  : " << p->Maths<< endl;
                cout << "  英语成绩  : " << p->English<< endl;
                cout << "请输入修改后的学生的学号: ";
                cin >> p->num;
                cout << endl;
                cout << "请输入修改后的姓名: ";
                cin >> p->name;
                cout << endl;
                cout << "请输入修改后的性别: ";
                cin >> p->sex;
                cout << endl;
                cout << "请输入修改后的语文成绩: ";
                cin >> p->Chinese;
                cout << endl;
                cout << "请输入修改后的数学成绩: ";
                cin >> p->Maths;
                cout << endl;
                cout << "请输入修改后的英语成绩: ";
                cin >> p->English;
                cout << endl;
                if((fp=fopen("Student.txt","w"))==NULL)
                {
                    cout << "can not open file!" << endl;
                    exit(0);
                }
                p=Head;
                if(Head!=NULL)
                    do
                    {
                        fprintf(fp,"%ld %s %s %f %f %f\n",p->num,p->name,p->sex,p->Chinese,p->Maths,p->English);
                        p=p->Next;
                    }
                    while(p!=NULL);
                fclose (fp);

            }
            else
                cout << "没有找到你想要修改的学生的信息" <<endl;
        }
        else
            cout << "文件中还没有任何学生信息"<<endl;

        return 0;
    }
    void credit()//统计排序
    {
        Student *p=Head;
        Student *m[90],*t;
        Creat();
        int i,j,k;
        for(i=0; p->Next!=NULL; i++)
        {
            m[i]=p;
            p=p->Next;
        }
        for(j=0; j<i; j++)
            for(k=j; k<i; k++)
            {
                if((m[j]->Chinese+m[j]->Maths+m[j]->English)<(m[k]->Chinese+m[k]->Maths+m[k]->English))
                {
                    t=m[j];
                    m[j]=m[k];
                    m[k]=t;
                }
            }
        cout<<"按学分从大到小排序为"<<endl;
        for(j=0; j<i; j++)
        {
            cout<<" 学号 "<<m[j]->num<<endl;
            cout<<" 姓名 "<<m[j]->name<<endl;
            cout<<" 性别 "<<m[j]->sex<<endl;
            cout<<" 语文成绩 "<<m[j]->Chinese<<endl;
            cout<<" 数学成绩 "<<m[j]->Maths<<endl;
            cout<<" 英语成绩 "<<m[j]->English<<endl;
            cout<<" 平均成绩 "<<((m[j]->Chinese+m[j]->Maths+m[j]->English)/3)<<endl<<endl;
        }

    }
    void save()
    {
        ofstream outfile;
        Student *p=Head;
        Creat();
        outfile.open("Student.txt",ios::out|ios::app|ios::ate);
        for(; p->Next!=NULL; p=p->Next)
        {
            cout<<" 学号 "<<p->num<<endl;
            cout<<" 姓名 "<<p->name<<endl;
            cout<<" 性别 "<<p->sex<<endl;
            cout<<" 语文成绩 "<<p->Chinese<<endl;
            cout<<" 数学成绩 "<<p->Maths<<endl;
            cout<<" 英语成绩 "<<p->English<<endl;
            cout<<" 平均成绩 "<<((p->Chinese+p->Maths+p->English)/3)<<endl<<endl;
        }
        outfile.close();
        cout<<"保存成功！";

    }
};
int main()
{
    system("color 1d");
    char  choice;
    int j=1;
    Student std;
    cout<<"\n\n\t        ★欢迎使用学生成绩管理系统★\n\n";
    cout<<"\t.★★★★★★★★★★★★★\n";
    cout<<"\t1.********添加学生记录******************\n";
    cout<<"\t2.★★★★显示所有学生记录★★★★★★★\n";
    cout<<"\t3.********按学号或姓名删除记录********\n";
    cout<<"\t4.★★★★按学号或姓名查询记录★★★★★★★★★\n";
    cout<<"\t5.********按学号或姓名修改记录**************\n";
    cout<<"\t6.★★★★统计排序★★★★★★★\n";
    cout<<"\t7.********保存**************\n";
    cout<<"\t0.★★★★退出★★★★★★★★★★★\n\n\n";
    cout<<"请输入您的选择：";
    std.Creat();
    do
    {
        cin>>choice;
        switch(choice)
        {
        case '1':
            std.Add();
            system("pause");
            break;
        case '2':
            std.display();
            system("pause");
            break;
        case '3':
            std.Del();
            system("pause");
            break;
        case '4':
            std.search();
            system("pause");
            break;
        case '5':
            std.Modify();
            system("pause");
            break;
        case '6':
            std.credit();
            system("pause");
            break;
        case '7':
            std.save();
            system("pause");
            break;
        case '0':
            j=0;
            break;
        default:
            cout<<"输入不符合要求请重输！";
            system("pause");
            break;
        }
        cout<<"请输入您的选择：";
    }
    while(j==1);

    return 0;
}
