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
        Head = NULL;    //����������ʼ��ַ
        Student *p, *pEnd;
        p = new Student; //����һ����̬����
        if((fp=fopen("Student.txt","r"))==NULL)
        {
            cout << "can not open file!" << endl;
            exit(0);
        }
        fscanf(fp,"%ld%s%s%f%f%f",&p->num,p->name,p->sex,&p->Chinese,&p->Maths,&p->English); //����ָ��pָ��Ķ�������ݳ�Ա��ֵ
        pEnd = Head;                          // ��ŵ�ǰ����ĵ�ַ
        while(!feof(fp))
        {
            // 0 ����������ı�־
            if(NULL == Head)
                Head = p;                     // ֻ�ڵ�һ��ִ�д����
            else
                pEnd->Next = p;               // �����һ������ĵ�ַ
            pEnd = p;
            p = new Student;                  //��̬������һ������
            fscanf(fp,"%ld%s%s%f%f%f",&p->num,p->name,p->sex,&p->Chinese,&p->Maths,&p->English); //������һ���������ݳ�Ա��ֵ
        }

        pEnd->Next = NULL;

        return 0;
    }
    int Add()
    {
        //----��׷�ӵķ�ʽ¼����Ϣ��ֱ�ӽ���Ϣ׷�ӵ���ǰ�ļ���ĩβ----
        ofstream outfile;
        outfile.open("Student.txt",ios::out|ios::app|ios::ate);   //----���ļ�----
        if(!outfile)
        {
            cerr<<" open error"<<endl;
            exit(1);
        }

        //----����������Ӧ�����ݣ�����׷�ӵ�֮ǰ���ļ���ȥ---
        cout<<"�������ѧ����ѧ�ţ�"<<endl;
        cin>>num;
        outfile<<num<<"  ";
        cout<<"�������ѧ����������"<<endl;
        cin>>name;
        outfile<<name<<"  ";
        do
        {
            cout<<"�������ѧ�����Ա�(��/Ů)��"<<endl;
            cin>>sex;
            if(!strcmp(sex,"��")&&!strcmp(sex,"Ů"))
            {
                cout<<"������������Ҫ�������䣡"<<endl;
            }
        }
        while(!strcmp(sex,"��")&&!strcmp(sex,"Ů"));
        outfile<<sex<<"  ";
        cout<<"�������ѧ�������ĳɼ���"<<endl;
        cin>>Chinese;
        outfile<<Chinese<<"  ";
        cout<<"�������ѧ������ѧ�ɼ���"<<endl;
        cin>>Maths;
        outfile<<Maths<<"  ";
        cout<<"�������ѧ����Ӣ��ɼ���"<<endl;
        cin>>English;
        outfile<<English<<"  "<<endl;
        outfile.close();
        cout<<"����ӳɹ���"<<endl;
        return 0;
    }
    void display()
    {
        Student *p;
        Creat();
        cout << "����ѧ�������б�����" << endl;
        p=Head;
        while(p != NULL)
        {
            cout<<" ѧ�� "<<p->num<<endl;
            cout<<" ���� "<<p->name<<endl;
            cout<<" �Ա� "<<p->sex<<endl;
            cout<<" ���ĳɼ� "<<p->Chinese<<endl;
            cout<<" ��ѧ�ɼ� "<<p->Maths<<endl;
            cout<<" Ӣ��ɼ� "<<p->English<<endl;
            cout<<" ƽ���ɼ� "<<((p->Chinese+p->Maths+p->English)/3)<<endl<<endl;
            p = p->Next;
        }
        cout<<"������ѧ����������"<<endl;
        p=Head;
        while(p != NULL)
        {
            if(p->Chinese<60||p->Maths<60||p->English<60)
            {
                cout<<" ѧ�� "<<p->num<<endl;
                cout<<" ���� "<<p->name<<endl;
                cout<<" �Ա� "<<p->sex<<endl;
                cout<<" ���ĳɼ� "<<p->Chinese<<endl;
                cout<<" ��ѧ�ɼ� "<<p->Maths<<endl;
                cout<<" Ӣ��ɼ� "<<p->English<<endl;
                cout<<" ƽ���ɼ� "<<((p->Chinese+p->Maths+p->English)/3)<<endl<<endl;

            }
            p = p->Next;
        }
    }
    int Del()//****************************************ɾ��
    {
        FILE *fp;
        Student *p,*p1;
        char namer[30];
        long numr;
        int x;
        Creat();
        do
        {
            cout << "������Ҫɾ����ѧ��������(1)��ѧ��(2):";
            cin>>x;
            if(x==1)
            {
                cout<<"������";
                cin >> namer;
            }
            if(x==2)
            {
                cout<<"ѧ�ţ�";
                cin >>numr;
            }
            else
                cout<<"����������Ҫ�������䣡"<<endl;
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
                cout << "��Ҫɾ����ѧ���������Ϣ����:" << endl;
                cout << "  ѧ��  : " << p->num<< endl;
                cout << "  ����  : " << p->name<< endl;
                cout << "  �Ա�  : " << p->sex << endl;
                cout << "  ���ĳɼ�  : " << p->Chinese<< endl;
                cout << "  ��ѧ�ɼ�  : " << p->Maths<< endl;
                cout << "  Ӣ��ɼ�  : " << p->English<< endl;
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
                cout << "��ѧ����������Ϣ�ѱ�ɾ��!" << endl;
            }

            else
                cout << "û���ҵ�����Ҫɾ����ѧ������Ϣ" <<endl;
        }
        else
            cout << "�ļ��л�û���κ�ѧ������Ϣ"<<endl;
        return 0;
    }
    int search()//***************************************��ѯ�γ������Ŀ
    {

        Student *p,*p1;
        char namer[30];
        long numr;
        int x;
        Creat();
        cout << "����ѧ�������б�����" << endl;
        p=Head;
        while(p != NULL)
        {

            cout<<" ѧ�� "<<p->num<<endl;
            cout<<" ���� "<<p->name<<endl;
            cout<<" �Ա� "<<p->sex<<endl;
            cout<<" ���ĳɼ� "<<p->Chinese<<endl;
            cout<<" ��ѧ�ɼ� "<<p->Maths<<endl;
            cout<<" Ӣ��ɼ� "<<p->English<<endl;
            p = p->Next;
        }
        do
        {

            cout << "������Ҫ���ҵ�ѧ��������(1)��ѧ��(2):";
            cin>>x;
            if(x==1)
            {
                cout<<"������";
                cin >> namer;
            }
            if(x==2)
            {
                cout<<"ѧ�ţ�";
                cin >>numr;
            }
            else
                cout<<"����������Ҫ�������䣡"<<endl;
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
                cout << "��Ҫ���ҵ�ѧ���������Ϣ����:" << endl;
                cout << "  ѧ�� : " << p->num<< endl;
                cout << "  ���� : " << p->name<< endl;
                cout << "  �Ա�  : " << p->sex << endl;
                cout << "  ���ĳɼ�  : " << p->Chinese<< endl;
                cout << "  ��ѧ�ɼ�  : " << p->Maths<< endl;
                cout << "  Ӣ��ɼ�  : " << p->English<< endl;
            }
            else
                cout << "û���ҵ�����Ҫ���ҵ�ѧ������Ϣ" <<endl;
        }
        else
            cout << "�ļ��л�û���κ�ѧ����Ϣ"<<endl;
        return 0;
    }
    int Modify()//*****************************�޸�
    {
        FILE *fp;
        Student *p;
        char namer[20];
        long numr;
        int x;
        Creat();
        do
        {
            cout << "������Ҫ�޸ĵ�ѧ��������(1)��ѧ��(2):";
            cin>>x;
            if(x==1)
            {
                cout<<"������";
                cin >> namer;
            }
            if(x==2)
            {
                cout<<"ѧ�ţ�";
                cin >> numr;
            }
            else
                cout<<"����������Ҫ�������䣡"<<endl;
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
                cout << "��Ҫ�޸ĵ�ѧ���������Ϣ����:" << endl;
                cout << "  ѧ��  : " << p->num<< endl;
                cout << "  ����  : " << p->name << endl;
                cout << "  �Ա�  : " << p->sex << endl;
                cout << "  ���ĳɼ�  : " << p->Chinese<< endl;
                cout << "  ��ѧ�ɼ�  : " << p->Maths<< endl;
                cout << "  Ӣ��ɼ�  : " << p->English<< endl;
                cout << "�������޸ĺ��ѧ����ѧ��: ";
                cin >> p->num;
                cout << endl;
                cout << "�������޸ĺ������: ";
                cin >> p->name;
                cout << endl;
                cout << "�������޸ĺ���Ա�: ";
                cin >> p->sex;
                cout << endl;
                cout << "�������޸ĺ�����ĳɼ�: ";
                cin >> p->Chinese;
                cout << endl;
                cout << "�������޸ĺ����ѧ�ɼ�: ";
                cin >> p->Maths;
                cout << endl;
                cout << "�������޸ĺ��Ӣ��ɼ�: ";
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
                cout << "û���ҵ�����Ҫ�޸ĵ�ѧ������Ϣ" <<endl;
        }
        else
            cout << "�ļ��л�û���κ�ѧ����Ϣ"<<endl;

        return 0;
    }
    void credit()//ͳ������
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
        cout<<"��ѧ�ִӴ�С����Ϊ"<<endl;
        for(j=0; j<i; j++)
        {
            cout<<" ѧ�� "<<m[j]->num<<endl;
            cout<<" ���� "<<m[j]->name<<endl;
            cout<<" �Ա� "<<m[j]->sex<<endl;
            cout<<" ���ĳɼ� "<<m[j]->Chinese<<endl;
            cout<<" ��ѧ�ɼ� "<<m[j]->Maths<<endl;
            cout<<" Ӣ��ɼ� "<<m[j]->English<<endl;
            cout<<" ƽ���ɼ� "<<((m[j]->Chinese+m[j]->Maths+m[j]->English)/3)<<endl<<endl;
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
            cout<<" ѧ�� "<<p->num<<endl;
            cout<<" ���� "<<p->name<<endl;
            cout<<" �Ա� "<<p->sex<<endl;
            cout<<" ���ĳɼ� "<<p->Chinese<<endl;
            cout<<" ��ѧ�ɼ� "<<p->Maths<<endl;
            cout<<" Ӣ��ɼ� "<<p->English<<endl;
            cout<<" ƽ���ɼ� "<<((p->Chinese+p->Maths+p->English)/3)<<endl<<endl;
        }
        outfile.close();
        cout<<"����ɹ���";

    }
};
int main()
{
    system("color 1d");
    char  choice;
    int j=1;
    Student std;
    cout<<"\n\n\t        �ﻶӭʹ��ѧ���ɼ�����ϵͳ��\n\n";
    cout<<"\t.��������������\n";
    cout<<"\t1.********���ѧ����¼******************\n";
    cout<<"\t2.�������ʾ����ѧ����¼��������\n";
    cout<<"\t3.********��ѧ�Ż�����ɾ����¼********\n";
    cout<<"\t4.����ﰴѧ�Ż�������ѯ��¼����������\n";
    cout<<"\t5.********��ѧ�Ż������޸ļ�¼**************\n";
    cout<<"\t6.�����ͳ�������������\n";
    cout<<"\t7.********����**************\n";
    cout<<"\t0.������˳�������������\n\n\n";
    cout<<"����������ѡ��";
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
            cout<<"���벻����Ҫ�������䣡";
            system("pause");
            break;
        }
        cout<<"����������ѡ��";
    }
    while(j==1);

    return 0;
}
