#include "librarymain.h"
#include"windfont.h"
#include <qlineedit.h>
#include<qsqlerror.h>
libraryMain::libraryMain(QObject *parent)
    : QObject(parent)
{
	FID = 0;
	change = true;
	windows = new QWidget;
	lastroot = false;
    root=false;
    windfont=new windFont;
    layout_1=new QGridLayout;
    layout_2=new QVBoxLayout;
    visited=new QTabWidget;
    adminer=new QTabWidget;
    button=new QPushButton;
    dbLibrary=QSqlDatabase::addDatabase("QMYSQL");
    dbLibrary.setHostName("localhost");
    dbLibrary.setPort(3306);
    dbLibrary.setUserName("root");
    dbLibrary.setPassword("lyz.637631");
	if (!dbLibrary.open())
	{
		QMessageBox::critical(0, QObject::tr("error"), dbLibrary.lastError().text());
	};
    query=QSqlQuery::QSqlQuery(dbLibrary);
	query.exec(tr("create database library;"));
	if (!query.exec(tr("use library;")))
	{
		QMessageBox warnning;
		warnning.setInformativeText(query.lastError().text());
		warnning.setStandardButtons(QMessageBox::Ok);
		warnning.exec();
	}
	QString query_string = tr("select count(*) from libraryRecords;");
	query.exec(query_string);
	query.next();
	FID = query.value(0).toInt();
    connect(button,SIGNAL(clicked()),this,SLOT(click_load()));
    setTable();//建立数据库表
    perpareLoadPage();//登入界面绘制
	initLibraryPage();//设置图书馆界面
}
void libraryMain::setTable()//建立数据库的表
{
	QString query_string;
    QMessageBox warnning;
    warnning.setDefaultButton(QMessageBox::Ok);
    warnning.setText(tr("Database error"));
	query_string =tr( "create table Books( BookNo varchar(50), BookType varchar(50),BookName varchar(50),Publisher varchar(50),Year int(4),Author varchar(50),Pirce double,Total int,Storage int,UpdateTime TIMESTAMP default CURRENT_TIMESTAMP ,primary key(BookNo));");
	query.exec(query_string);
	query_string = tr("create table LibraryCard(CardNo varchar(50), Name varchar(50),Department varchar(50),"
		"CardType varchar(50),UpdateTime TIMESTAMP default CURRENT_TIMESTAMP ,primary key(CardNo));");
	query.exec(query_string);
    query.exec("create table Users(UserID varchar(50),Password varchar(50),Name varchar(50),Contact varchar(50),"
               "primary key(UserID));");
    query.exec("create table LibraryRecords(FID int,CardNo varchar(50),BookNo varchar(50),LentDate datetime,ReturnDate datetime,"
               "Operator varchar(50),primary key(FID));");
}
//登入界面的绘制
void libraryMain::perpareLoadPage()
{
    loadPage=new QWidget();
    QGridLayout *loadpageLayout=new QGridLayout();
    loadLabel=new QLabel[2];
    loadLabel[0].setText(QString::fromLocal8Bit("用户名"));
    loadLabel[1].setText(QString::fromLocal8Bit("密码"));
    loadpageLayout->addWidget(&loadLabel[0],0,0,1,1,0);
    loadpageLayout->addWidget(&loadLabel[1],1,0,1,1,0);
    loadLineEdit=new QLineEdit[2];
    loadLineEdit[0].clear();
    loadLineEdit[1].clear();
    loadLineEdit[1].setEchoMode(QLineEdit::Password);
    loadpageLayout->addWidget(&loadLineEdit[0],0,1,1,3,0);
    loadpageLayout->addWidget(&loadLineEdit[1],1,1,1,3,0);
    loadbutton=new QPushButton[2];
    loadbutton[0].setText(QString::fromLocal8Bit("确定"));
    loadbutton[1].setText(QString::fromLocal8Bit("取消"));
    loadpageLayout->addWidget(&loadbutton[0],2,1,1,1,0);
    loadpageLayout->addWidget(&loadbutton[1],2,2,1,1,0);
    loadPage->setLayout(loadpageLayout);
    loadPage->setWindowTitle(QString::fromLocal8Bit("管理员登入"));
    connect(&loadbutton[0], SIGNAL(clicked()), this, SLOT(clickLoadConfirm()));
    connect(&loadbutton[1], SIGNAL(clicked()), this, SLOT(clickLoadCancel()));
}
void libraryMain::initLibraryPage()
{
	title = new QWidget;
    widget_1=new QWidget;
    widget_2=new QWidget;
    widget_3=new QWidget;
    widget_4=new QWidget;
    widget_5=new QWidget;
	layout_2 = new QVBoxLayout;
	initSearPage();
	InputBookPage();
	borrowBookPage();
	returnBookPage();
	libraryCardPage();
	windows->setWindowTitle(QString::fromLocal8Bit("图书管理系统"));
	windows->resize(1100, 800);
	layout_1->addWidget(windfont, 0, 0, 2, 5, 0);
	layout_1->addWidget(button, 0, 5, 2, 1, 0);
	adminer->addTab(widget_1, QString::fromLocal8Bit("图书查询"));
	title->setLayout(layout_1);
	setLibraryPage();
	layout_2->addWidget(title);
	layout_2->addWidget(adminer);
	windows->setLayout(layout_2);
	windows->show();
}
void libraryMain::setLibraryPage()
{
    if(root)
        button->setText(QString::fromLocal8Bit("退出"));
    else
        button->setText(QString::fromLocal8Bit("管理员登入"));
	if (lastroot != root)
	{
		lastroot = root;
		if (root)
		{
			adminer->addTab(widget_2, QString::fromLocal8Bit("图书导入"));
			adminer->addTab(widget_3, QString::fromLocal8Bit("图书借出"));
			adminer->addTab(widget_4, QString::fromLocal8Bit("图书归还"));
			adminer->addTab(widget_5, QString::fromLocal8Bit("借书证管理"));
		}
		else
		{
			adminer->removeTab(4);
			adminer->removeTab(3);
			adminer->removeTab(2);
			adminer->removeTab(1);
		}
	}
}
void libraryMain::initSearPage()//初始化searchTable
{
	GrSearchbook = new QGridLayout;
    widget_6=new QGroupBox;
	searchBook_1 = NULL;
	VBSearchbook = new QVBoxLayout;
	TaSearchbook = new QTableWidget;
    LaSearchbook=new QLabel[8];
    CoSearchbook=new QComboBox[4];
    setComSearch();
    LaSearchbook[0].setText(QString::fromLocal8Bit("书名"));
    LaSearchbook[1].setText(QString::fromLocal8Bit("类别"));
    LaSearchbook[2].setText(QString::fromLocal8Bit("作者"));
    LaSearchbook[3].setText(QString::fromLocal8Bit("出版社"));
    LaSearchbook[4].setText(QString::fromLocal8Bit("年份"));
    LaSearchbook[5].setText(QString::fromLocal8Bit("——"));
    LaSearchbook[6].setText(QString::fromLocal8Bit("价格范围"));
    LaSearchbook[7].setText(QString::fromLocal8Bit("——"));
    LiSearchbook=new QLineEdit[4];//0:书名 1：作者 2：价格范围1，3：价格范围2
    PbSearchbook=new QPushButton[2];
    PbSearchbook[0].setText(QString::fromLocal8Bit("查询"));
    //此处可以进行设置图标
    PbSearchbook[1].setText(QString::fromLocal8Bit("清空"));
    //第一行控件
    GrSearchbook->addWidget(&LaSearchbook[0],0,0,1,1);
    GrSearchbook->addWidget(&LiSearchbook[0],0,1,1,4);
    GrSearchbook->addWidget(&LaSearchbook[1],0,5,1,1);
    GrSearchbook->addWidget(&CoSearchbook[0],0,6,1,4);
    GrSearchbook->addWidget(&LaSearchbook[2],0,10,1,1);
    GrSearchbook->addWidget(&LiSearchbook[1],0,11,1,6);
    GrSearchbook->addWidget(&PbSearchbook[0],0,17,1,1);
    //第二行控件
    GrSearchbook->addWidget(&LaSearchbook[3],1,0,1,1);
    GrSearchbook->addWidget(&CoSearchbook[1],1,1,1,4);
    GrSearchbook->addWidget(&LaSearchbook[4],1,5,1,1);
    GrSearchbook->addWidget(&CoSearchbook[2],1,6,1,2);
    GrSearchbook->addWidget(&LaSearchbook[5],1,8,1,1);
    GrSearchbook->addWidget(&CoSearchbook[3],1,9,1,2);
    GrSearchbook->addWidget(&LaSearchbook[6],1,11,1,1);
    GrSearchbook->addWidget(&LiSearchbook[2],1,12,1,2);
    GrSearchbook->addWidget(&LaSearchbook[7],1,14,1,1);
    GrSearchbook->addWidget(&LiSearchbook[3],1,15,1,2);
    GrSearchbook->addWidget(&PbSearchbook[1],1,17,1,1);
    connect(&PbSearchbook[0],SIGNAL(clicked(bool)),this,SLOT(changeSearchbook()));
    connect(&PbSearchbook[1],SIGNAL(clicked(bool)),this,SLOT(clearSearchbook()));
	widget_6->setLayout(GrSearchbook);
	//widget_6->setFixedSize(800, 100);
	//TaSearchbook->setFixedSize(800, 700);
	TaSearchbook->setColumnCount(10);
	searchBook_2 << QString::fromLocal8Bit("书号") << QString::fromLocal8Bit("图书类别") << QString::fromLocal8Bit("书名")
		<< QString::fromLocal8Bit("出版社") << QString::fromLocal8Bit("出版年份") << QString::fromLocal8Bit("作者") << QString::fromLocal8Bit("图书单价")
		<< QString::fromLocal8Bit("总藏书量") << QString::fromLocal8Bit("库存数") << QString::fromLocal8Bit("添加时间");
	TaSearchbook->setHorizontalHeaderLabels(searchBook_2);
    changeSearchbook();
    VBSearchbook->addWidget(widget_6);
    VBSearchbook->addWidget(TaSearchbook);
    widget_1->setLayout(VBSearchbook);
}
void libraryMain::changeSearchbook()
{

    QString stringlist[8];
    for(int i=0;i<4;i++)
        stringlist[i]=LiSearchbook[i].text();
    for(int i=4;i<8;i++)
        stringlist[i]=CoSearchbook[i-4].currentText();
    QString string_query;
    string_query="select * from books where 1=1 ";
    if(stringlist[0]!=tr(""))
        string_query+="and bookName like '%"+stringlist[0]+"%'";
    if(stringlist[4]!=tr(""))
        string_query+="and bookType='"+stringlist[4]+"'";
    if(stringlist[1]!=tr(""))
        string_query+="and author like '%"+stringlist[1]+"%' ";
    if(stringlist[5]!=tr(""))
        string_query+="and Publisher='"+stringlist[5]+"' ";
    if(stringlist[6]!=tr(""))
        string_query+="and Year>="+stringlist[6]+" ";
    if(stringlist[7]!=tr(""))
        string_query+="and Year<="+stringlist[7]+" ";
    if(stringlist[2]!=tr(""))
        string_query+="and Pirce>="+stringlist[2]+" ";
    if(stringlist[3]!=tr(""))
        string_query+="and Pirce<="+stringlist[3]+" ";
    string_query+=";";
	if (query.exec(string_query))
	{
		int count = query.size();
		if (searchBook_1 != NULL)
			delete []searchBook_1;
		if (count <= 10)
		{
			TaSearchbook->setRowCount(10);
			searchBook_1 = new QTableWidgetItem[100];
		}
		else
		{
			TaSearchbook->setRowCount(count);
			searchBook_1 = new QTableWidgetItem[count * 10];
		}
		for (int i = 0; i<count; i++)
		{
			query.next();
			for (int j = 0; j<10; j++)
			{
				searchBook_1[i * 10 + j].setText(query.value(j).toString());
				TaSearchbook->setItem(i, j, &searchBook_1[i * 10 + j]);
			}
		}
	}
}
void libraryMain::clearSearchbook()
{
    int count;
    for(int i=0;i<4;i++)
        LiSearchbook[i].clear();
    for(int i=0;i<4;i++)
    {
        count=CoSearchbook[i].findText(tr(""));
        CoSearchbook[i].setCurrentIndex(count);
    }
}
void libraryMain::borrowBookPage()
{
    borrowBook_1=new QHBoxLayout;
    borrowBook_2=new QLineEdit[2];
    borrowBook_3=new QPushButton;
	widget_8 = new QGroupBox;
	borrowBook_7 = new QLabel[2];
    borrowBook_6=NULL;
	borrowBook_7[0].setText(QString::fromLocal8Bit("借书证卡号"));
	borrowBook_7[1].setText(QString::fromLocal8Bit("书号"));
	borrowBook_3->setText(QString::fromLocal8Bit("确定"));
	borrowBook_1->addWidget(&borrowBook_7[0]);
    borrowBook_1->addWidget(&borrowBook_2[0]);
	borrowBook_1->addWidget(&borrowBook_7[1]);
    borrowBook_1->addWidget(&borrowBook_2[1]);
    borrowBook_1->addWidget(borrowBook_3);
    connect(&borrowBook_2[0],SIGNAL(textChanged(QString)),this,SLOT(findBorrowBook()));
    connect(borrowBook_3,SIGNAL(clicked(bool)),this,SLOT(addBorrowBook()));
    borrowBook_4=new QVBoxLayout;
    borrowBook_5=new QTableWidget;
    borrowBook_8<< QString::fromLocal8Bit("书号")<< QString::fromLocal8Bit("类别")<< QString::fromLocal8Bit("书名")<< QString::fromLocal8Bit("出版社")<< QString::fromLocal8Bit("年份")<< QString::fromLocal8Bit(" 作者")<< QString::fromLocal8Bit("价格")<< QString::fromLocal8Bit("总藏书量")<< QString::fromLocal8Bit("库存");
	borrowBook_5->setColumnCount(10);
	borrowBook_5->setHorizontalHeaderLabels(borrowBook_8);
	findBorrowBook();
    widget_8->setLayout(borrowBook_1);
	borrowBook_4->addWidget(widget_8);
    borrowBook_4->addWidget(borrowBook_5);
    widget_3->setLayout(borrowBook_4);
}
void libraryMain::findBorrowBook()
{
    QString query_string;
	query_string = tr("select * from books where BookNo in(select bookNo from libraryRecords where CardNo='") + borrowBook_2[0].text() + tr("'");
    query_string+=tr("and returnDate is null);");
    if(query.exec(query_string))
    {
        int count=query.size();
        if(borrowBook_6!=NULL)
            delete[] borrowBook_6;
        if(count<=10)
        {
           borrowBook_5->setRowCount(10);
           borrowBook_6=new QTableWidgetItem[100];
        }
        else
        {
            borrowBook_5->setRowCount(count);
            borrowBook_6=new QTableWidgetItem[count*10];
        }
        for(int i=0;i<count;i++)
        {
            query.next();
            for(int j=0;j<10;j++)
            {
                borrowBook_6[i*10+j].setText(query.value(j).toString());
                borrowBook_5->setItem(i,j,&borrowBook_6[i*10+j]);
            }
        }
    }
	else
	{
		borrowBook_5->setRowCount(10);
	}
}
void libraryMain::addBorrowBook()
{
    QString query_string;
    query_string=tr("select * from LibraryCard where CardNo='")+borrowBook_2[0].text()+tr("'and returnDate is null;");
    if(query.exec(query_string))
    {
        if(query.size()==1)
        {
            query_string=tr("select * from Books where BookNo='")+borrowBook_2[1].text()+tr("';");
            query.exec(query_string);
            if(query.size()==1)
            {
                query.next();
                int storage=query.value(8).toInt();
                if(storage>0)
                {
                    query_string=tr("update Books set storage=storage-1 where BookNo='")+borrowBook_2[1].text()+tr("';");
                    if(!query.exec(query_string))
                    {
                        QMessageBox::warning(windows,tr("warning"),tr("update the books is not successed!"),QMessageBox::Ok);
                    }
                    query_string=tr("insert into LibraryRecords values( %1").arg(FID)+tr(",'")+borrowBook_2[0].text()+tr("' , '")+borrowBook_2[1].text()+tr("' , '")+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+tr("' , NULL , 'root');");
					FID++;
					if(!query.exec(query_string))
                    {
                        QMessageBox::warning(windows,tr("warning"),/*tr("inset the LibraryRecords is not successed!")*/query.lastError().text(),QMessageBox::Ok);
                    }
					findBorrowBook();
                }
            }
            else
            {
                QMessageBox::warning(windows,tr("warning"),tr("the bookNo is not exist!"),QMessageBox::Ok);
            }
        }
        else
        {
            QMessageBox::warning(windows,tr("warning"),tr("the CardNo is not exist"),QMessageBox::Ok);
        }
    }
}
void libraryMain::returnBookPage()
{
    returnBook_1=new QHBoxLayout;
    returnBook_2=new QLineEdit[2];
    returnBook_3=new QPushButton;
	returnBook_7 = new QLabel[2];
	widget_9 = new QGroupBox;
    returnBook_6=NULL;
	returnBook_7[0].setText(QString::fromLocal8Bit("借书证卡号"));
	returnBook_7[1].setText(QString::fromLocal8Bit("书号"));
    returnBook_3->setText(QString::fromLocal8Bit("确定"));
	returnBook_1->addWidget(&returnBook_7[0]);
	returnBook_1->addWidget(&returnBook_2[0]);
	returnBook_1->addWidget(&returnBook_7[1]);
	returnBook_1->addWidget(&returnBook_2[1]);
    returnBook_1->addWidget(returnBook_3);
	widget_9->setLayout(returnBook_1);
    connect(&returnBook_2[0],SIGNAL(textChanged(QString)),this,SLOT(findreturnBook()));
    connect(returnBook_3,SIGNAL(clicked(bool)),this,SLOT(addreturnBook()));
    returnBook_4=new QVBoxLayout;
    returnBook_5=new QTableWidget;
    returnBook_8<< QString::fromLocal8Bit("书号")<< QString::fromLocal8Bit("类别")<< QString::fromLocal8Bit("书名")<<
		QString::fromLocal8Bit("出版社")<< QString::fromLocal8Bit("年份")<< QString::fromLocal8Bit(" 作者")
		<< QString::fromLocal8Bit("价格")<< QString::fromLocal8Bit("总藏书量")<< QString::fromLocal8Bit("库存");
	returnBook_5->setColumnCount(10);
	returnBook_5->setHorizontalHeaderLabels(returnBook_8);
	findreturnBook();
    returnBook_4->addWidget(widget_9);
    returnBook_4->addWidget(returnBook_5);
    widget_4->setLayout(returnBook_4);
}
void libraryMain::findreturnBook()
{
    QString query_string;
	query_string = tr("select * from books where BookNo in(select bookNo from libraryRecords where CardNo='") + returnBook_2[0].text() + tr("' and returndate is null); ");
    query_string+=tr("and returnDate is null;");
    if(query.exec(query_string))
    {
        int count=query.size();
        if(returnBook_6!=NULL)
            delete[] returnBook_6;
        if(count<=10)
        {
           returnBook_5->setRowCount(10);
           returnBook_6=new QTableWidgetItem[100];
        }
        else
        {
            returnBook_6=new QTableWidgetItem[count*10];
        }
        for(int i=0;i<count;i++)
        {
            query.next();
            for(int j=0;j<10;j++)
            {
                returnBook_6[i*10+j].setText(query.value(j).toString());
                returnBook_5->setItem(i,j,&returnBook_6[i*10+j]);
            }
        }
    }
	else
	{
		returnBook_5->setRowCount(10);
	}
}
void libraryMain::addreturnBook()
{
    QString query_string;
	query_string = tr("select * from LibraryRecords where CardNo='") + returnBook_2[0].text() + tr("' and ReturnDate is NULL and BookNo='") + returnBook_2[1].text() + tr("';");
    if(query.exec(query_string))
    {
        if(query.size()==1)
        {
			query.next();
			int temp = query.value(0).toInt();
            query_string=tr("select * from Books where BookNo=")+returnBook_2[1].text()+tr(";");
            query.exec(query_string);
            if(query.size()==1)
            {
                query.next();
                int storage=query.value(8).toInt();
                if(storage>0)
                {
                    query_string=tr("update Books set storage=storage+1 where BookNo=")+returnBook_2[1].text()+tr(";");
                    if(!query.exec(query_string))
                    {
                        QMessageBox::warning(windows,tr("warning"),tr("update the books is not successed!"),QMessageBox::Ok);
                    }
					query_string= tr("update libraryRecords set ReturnDate='") + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + tr("' where FID=%1").arg(temp) + tr(";");
                    if(!query.exec(query_string))
                    {
                        QMessageBox::warning(windows,tr("warning"),tr("inset the LibraryRecords is not successed!"),QMessageBox::Ok);
                    }
					findreturnBook();
                }
            }
            else
            {
                QMessageBox::warning(windows,tr("warning"),tr("the bookNo is not exist!"),QMessageBox::Ok);
            }
        }
        else
        {
            QMessageBox::warning(windows,tr("warning"),tr("the CardNo is not exist"),QMessageBox::Ok);
        }
    }
}
void libraryMain::libraryCardPage()
{
    libraryCard_1=new QGridLayout;
    libraryCard_2=new QVBoxLayout;
    libraryCard_3=new QLabel[4];
    libraryCard_6=NULL;
	widget_10 = new QGroupBox;
    libraryCard_3[0].setText(QString::fromLocal8Bit("卡号"));
    libraryCard_3[1].setText(QString::fromLocal8Bit("姓名"));
    libraryCard_3[2].setText(QString::fromLocal8Bit("单位"));
    libraryCard_3[3].setText(QString::fromLocal8Bit("类别"));
    libraryCard_8=new QPushButton[2];
    libraryCard_8[0].setText(QString::fromLocal8Bit("添加"));
    libraryCard_8[1].setText(QString::fromLocal8Bit("删除"));
    libraryCard_4=new QLineEdit[4];
    libraryCard_1->addWidget(&libraryCard_3[0],0,0,1,1,0);
    libraryCard_1->addWidget(&libraryCard_4[0],0,1,1,3,0);
    libraryCard_1->addWidget(&libraryCard_3[1],0,4,1,1,0);
    libraryCard_1->addWidget(&libraryCard_4[1],0,5,1,3,0);
    libraryCard_1->addWidget(&libraryCard_8[0],0,8,1,2,0);

    libraryCard_1->addWidget(&libraryCard_3[2],1,0,1,1,0);
    libraryCard_1->addWidget(&libraryCard_4[2],1,1,1,3,0);
    libraryCard_1->addWidget(&libraryCard_3[3],1,4,1,1,0);
    libraryCard_1->addWidget(&libraryCard_4[3],1,5,1,3,0);
    libraryCard_1->addWidget(&libraryCard_8[1],1,8,1,2,0);
	widget_10->setLayout(libraryCard_1);
    connect(&libraryCard_8[0],SIGNAL(clicked(bool)),this,SLOT(addLibraryCard()));
    connect(&libraryCard_8[1],SIGNAL(clicked(bool)),this,SLOT(deleteLibraryCard()));
    libraryCard_5=new QTableWidget;
    libraryCard_7<< QString::fromLocal8Bit("卡号")<< QString::fromLocal8Bit("姓名")<< QString::fromLocal8Bit("所属单位")<< QString::fromLocal8Bit("类别")<< QString::fromLocal8Bit("添加时间");
	libraryCard_5->setColumnCount(5);
	libraryCard_5->setHorizontalHeaderLabels(libraryCard_7);
	showLibraryCard();
	libraryCard_2->addWidget(widget_10);
    libraryCard_2->addWidget(libraryCard_5);
    widget_5->setLayout(libraryCard_2);
}
void libraryMain::showLibraryCard()
{
    QString query_string;
    query_string=tr("select * from LibraryCard;");
    if(query.exec(query_string))
    {
		int count = query.size();
		if (libraryCard_6 != NULL)
			delete [] libraryCard_6;
		libraryCard_5->setRowCount(0);
		if (count <= 10)
		{
			libraryCard_5->setRowCount(10);
			libraryCard_6 = new QTableWidgetItem[count * 5];
		}
		else
		{
			libraryCard_5->setRowCount(count);
			libraryCard_6 = new QTableWidgetItem[count * 5];
		}
        int index=-1;
        while(query.next())
        {
            index++;
            for(int i=0;i<5;i++)
            {
                libraryCard_6[index*5+i].setText(query.value(i).toString());
                libraryCard_5->setItem(index,i,&libraryCard_6[index*5+i]);
            }
        }
    }
    else
    {
        QMessageBox::warning(windows,tr("warning"),tr("select from LibraryCard is not successed!"),QMessageBox::Ok);
    }
}
void libraryMain::addLibraryCard()
{
    if(libraryCard_4[0].text()==tr(""))
    {
        QMessageBox::warning(windows,tr("warning"),QString::fromLocal8Bit("必须输入有效卡号"),QMessageBox::Ok);
        return;
    }
    QString query_string;
    query_string=tr("select *from LibraryCard where CardNo='")+libraryCard_4[0].text()+tr("' ;");
    if(query.exec(query_string))
    {
        if(query.size()!=0)
        {
            QMessageBox::warning(windows,tr("warning"), QString::fromLocal8Bit("此卡号已经存在"),QMessageBox::Ok);
            return;
        }
    }
    else
    {
        QMessageBox::warning(windows,tr("warning"), QString::fromLocal8Bit("查询是否存在次卡号失败"),QMessageBox::Ok);
        return;
    }
    query_string=tr("insert into LibraryCard values( '")+libraryCard_4[0].text()+tr("', '")+libraryCard_4[1].text()+tr("', '")+libraryCard_4[2].text()+tr("', '")+libraryCard_4[3].text()+tr("' ,now());");
    if(!query.exec(query_string))
        QMessageBox::warning(windows,tr("warning"), QString::fromLocal8Bit("借书证导入错误"),QMessageBox::Ok);
	showLibraryCard();
}
void libraryMain::deleteLibraryCard()
{
    if(libraryCard_4[0].text()==tr(""))
    {
        QMessageBox::warning(windows,tr("warning"), QString::fromLocal8Bit("必须输入有效卡号"),QMessageBox::Ok);
        return;
    }
    QString query_string;
    query_string=tr("select *from LibraryCard where CardNo='")+libraryCard_4[0].text()+tr("' ;");
    if(query.exec(query_string))
    {
        if(query.size()==0)
        {
            QMessageBox::warning(windows, QString::fromLocal8Bit("warning"), QString::fromLocal8Bit("此卡号不存在"),QMessageBox::Ok);
            return;
        }
    }
    query_string=tr("delete from LibraryCard where CardNo='")+libraryCard_4[0].text()+tr("';");
    if(!query.exec(query_string))
        QMessageBox::warning(windows, QString::fromLocal8Bit("warning"), QString::fromLocal8Bit("删除该信息失败"),QMessageBox::Ok);
	showLibraryCard();
}
void libraryMain::InputBookPage()
{
    inputBook_1=new QGridLayout;
    inputBook_2=new QVBoxLayout;
    inputBook_3=new QLabel[8];
    inputBook_4=new QLineEdit[8];
    inputBook_8=new QPushButton[3];
	widget_7 = new QGroupBox;
    inputBook_6=NULL;
	widget_2->setLayout(inputBook_2);
    inputBook_3[0].setText(QString::fromLocal8Bit("书号"));
    inputBook_3[1].setText(QString::fromLocal8Bit("类别"));
    inputBook_3[2].setText(QString::fromLocal8Bit("书名"));
    inputBook_3[3].setText(QString::fromLocal8Bit("出版社"));
    inputBook_3[4].setText(QString::fromLocal8Bit("年份"));
    inputBook_3[5].setText(QString::fromLocal8Bit("作者"));
    inputBook_3[6].setText(QString::fromLocal8Bit("价格"));
    inputBook_3[7].setText(QString::fromLocal8Bit("数量"));
    inputBook_8[0].setText(QString::fromLocal8Bit("添加"));
    inputBook_8[1].setText(QString::fromLocal8Bit("删除"));
    inputBook_8[2].setText(QString::fromLocal8Bit("导入"));
    inputBook_1->addWidget(&inputBook_3[0],0,0,1,1,0);
    inputBook_1->addWidget(&inputBook_4[0],0,1,1,3,0);
    inputBook_1->addWidget(&inputBook_3[1],0,4,1,1,0);
    inputBook_1->addWidget(&inputBook_4[1],0,5,1,3,0);
    inputBook_1->addWidget(&inputBook_3[2],0,8,1,1,0);
    inputBook_1->addWidget(&inputBook_4[2],0,9,1,3,0);
    inputBook_1->addWidget(&inputBook_8[0],0,12,1,2,0);

    inputBook_1->addWidget(&inputBook_3[3],1,0,1,1,0);
    inputBook_1->addWidget(&inputBook_4[3],1,1,1,3,0);
    inputBook_1->addWidget(&inputBook_3[4],1,4,1,1,0);
    inputBook_1->addWidget(&inputBook_4[4],1,5,1,3,0);
    inputBook_1->addWidget(&inputBook_3[5],1,8,1,1,0);
    inputBook_1->addWidget(&inputBook_4[5],1,9,1,3,0);
    inputBook_1->addWidget(&inputBook_8[1],1,12,1,2,0);

    inputBook_1->addWidget(&inputBook_3[6],2,0,1,1,0);
    inputBook_1->addWidget(&inputBook_4[6],2,1,1,3,0);
    inputBook_1->addWidget(&inputBook_3[7],2,4,1,1,0);
    inputBook_1->addWidget(&inputBook_4[7],2,5,1,3,0);
    inputBook_1->addWidget(&inputBook_8[2],2,12,1,2,0);
    connect(&inputBook_8[0],SIGNAL(clicked(bool)),this,SLOT(addBook()));
    connect(&inputBook_8[1],SIGNAL(clicked(bool)),this,SLOT(deleteBook()));
    connect(&inputBook_8[2],SIGNAL(clicked(bool)),this,SLOT(addBookList()));
    inputBook_5=new QTableWidget;
	widget_7->setLayout(inputBook_1);
    inputBook_7<< QString::fromLocal8Bit("书号")<< QString::fromLocal8Bit("图书类别")<< QString::fromLocal8Bit("书名")<<
		QString::fromLocal8Bit("出版社")<< QString::fromLocal8Bit("出版年份")<< QString::fromLocal8Bit("作者")<< QString::fromLocal8Bit("图书单价")<<
		QString::fromLocal8Bit("总藏书量")<< QString::fromLocal8Bit("库存数")<< QString::fromLocal8Bit("添加时间");
	inputBook_5->setColumnCount(10);
	inputBook_5->setHorizontalHeaderLabels(inputBook_7);
    showInputBook();
	inputBook_2->addWidget(widget_7);
	inputBook_2->addWidget(inputBook_5);
    widget_2->setLayout(inputBook_2);
}
void libraryMain::showInputBook()
{
    QString query_string;
    query_string=tr("select * from Books;");
    if(query.exec(query_string))
    {
        int count=query.size();
        if(inputBook_6!=NULL)
            delete []inputBook_6;
        if(count<=10)
        {
            inputBook_6=new QTableWidgetItem[10*10];
            inputBook_5->setRowCount(10);
        }
        else
        {
            inputBook_6=new QTableWidgetItem[10*count];
            inputBook_5->setRowCount(count);
        }
        for(int i=0;i<count;i++)
        {
            query.next();
            for(int j=0;j<10;j++)
            {
                inputBook_6[i*10+j].setText(query.value(j).toString());
                inputBook_5->setItem(i,j,&inputBook_6[i*10+j]);
            }
        }
    }
}
bool libraryMain::isDigitStr(QString src)
{
    int count=src.size();
    bool isDigit_src=true;
    for(int i=0;i<count;i++)
    {
        if(!src[i].isDigit())
        {
            isDigit_src=false;
            break;
        }
    }
    return isDigit_src;
}
void libraryMain::addBook()
{
    QString query_string;
    bool complete=true;
    for(int i=0;i<8;i++)
    {
        if(inputBook_4[i].text()==tr(""))
        {
            complete=false;
            break;
        }
    }
    if(complete)
    {
        if(isDigitStr(inputBook_4[4].text())&&isDigitStr(inputBook_4[6].text())&&isDigitStr(inputBook_4[7].text()))
        {
			query_string = tr("insert into Books values ( '") + inputBook_4[0].text() + tr("', '") + inputBook_4[1].text() + tr("', '") + inputBook_4[2].text() + tr("', '") + inputBook_4[3].text() + tr("', ") + inputBook_4[4].text() + tr(" , '") + inputBook_4[5].text() + tr("', ") + inputBook_4[6].text() + tr(" , ") + inputBook_4[7].text() + tr(" , ") + inputBook_4[7].text() + tr(" , now());");
            if(!query.exec(query_string))
                QMessageBox::warning(windows,tr("warning"),tr("添加图书失败!!!"),QMessageBox::Ok);
			else
			{
				showInputBook();
				changeSearchbook();
			}
        }
    }
    else
    {
        QMessageBox::warning(windows,tr("warning"),tr("添加数据信息不完整!!"),QMessageBox::Ok);
    }
}
void libraryMain::deleteBook()
{
    QString query_string;
    query_string=tr("select * from Books where BookNo='")+inputBook_4[0].text()+tr("';");
    if(query.exec(query_string))
    {
        if(query.size()==1)
        {
            query.next();
            if(query.value(7).toInt()==query.value(8).toInt())
            {
                query_string=tr("delete from Books where BookNo='")+inputBook_4[0].text()+tr("';");
                if(!query.exec(query_string))
                {
                    QMessageBox::warning(windows,tr("warning"),QString::fromLocal8Bit("删除图书出现意想不到的错误!!"),QMessageBox::Ok);
                }
                else
                    showInputBook();
            }
            else
            {
                QMessageBox::warning(windows,tr("warning"), QString::fromLocal8Bit("想要删除的图书被借出，请先删除借出记录然后进行删除!!"),QMessageBox::Ok);
            }
        }
    }
}
void libraryMain::addBookList()
{
    QString path=QFileDialog::getOpenFileName(windows,tr("open File"),".",tr("Text Files(*.txt)"));
    if(!path.isEmpty())
    {
        QFile file(path);
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QMessageBox::warning(windows,tr("warning"),tr("文件无法打开"),QMessageBox::Ok);
        }
        else{
            QTextStream textInput(&file);
			textInput.setCodec("utf8");
            QString LineStr;
            while(!textInput.atEnd())
            {
                LineStr=textInput.readLine();
                if(!addBookString(LineStr))
                    QMessageBox::warning(windows,tr("warning"),LineStr+tr(" 为正确添加，请检查是否语法错误!!"),QMessageBox::Ok);
            }
			showInputBook();

        }
   }
}
bool libraryMain::addBookString(QString src)
{
    QString BookInfrom[8];
    int totalCount=src.size();
    int index=0,begin=0;
    for(int i=0;i<=totalCount;i++)
    {
        if(src[i]==' '||i==totalCount)
        {
            BookInfrom[index++]=src.mid(begin,i-begin+1);
			begin = i + 1;
        }
        if(index==8)
            break;
    }
    QString query_string;
    query_string=tr("insert into Books values ('")+BookInfrom[0]+tr("', '")+BookInfrom[1]+tr("', '")+BookInfrom[2]+tr("', '");
    query_string+=BookInfrom[3]+tr("', ")+BookInfrom[4]+tr(" , '")+BookInfrom[5]+tr("' , ")+BookInfrom[6]+tr(" , ")+BookInfrom[7]+tr(" , ")
            +BookInfrom[7]+tr(" , now());");
    if(!query.exec(query_string))
    {
		query_string = query.lastError().text();
        return false;
    }
    else
        return true;
}
void libraryMain::setComSearch()
{
    for(int i=0;i<4;i++)
    {
        CoSearchbook[i].clear();
    }
    query.exec("select distinct BookType from Books");
    CoSearchbook[0].addItem(tr(""));
    while(query.next())
    {
        CoSearchbook[0].addItem(query.value(0).toString());
    }
    query.exec("select distinct Publisher from Books");
    CoSearchbook[1].addItem(tr(""));
    while(query.next())
    {
        CoSearchbook[1].addItem(query.value(0).toString());
    }
	query.exec("select  max(Year) from books");
    while(query.next())
    {
        maxYear=query.value(0).toInt();
    }
    query.exec("select min(Year) from books");
    while(query.next())
    {
        minYear=query.value(0).toInt();
    }
    CoSearchbook[2].addItem(tr(""));
    CoSearchbook[3].addItem(tr(""));
    for(int i=minYear;i<=maxYear;i++)
    {
        CoSearchbook[2].addItem(QString::number(i,10));
        CoSearchbook[3].addItem(QString::number(i,10));
    }
    connect(&CoSearchbook[3],SIGNAL(currentIndexChanged(int)),this,SLOT(process()));
    connect(&CoSearchbook[2],SIGNAL(currentIndexChanged(int)),this,SLOT(process()));
}
void libraryMain::process()
{
	if (!change)
		return;
    int i;
	QString temp;
    QString string1;
    if(sender()==&CoSearchbook[2])
    {
		change = !change;
        string1=CoSearchbook[2].currentText();
		temp = CoSearchbook[3].currentText();
        if(string1==tr(""))
            i=minYear;
        else
            i=string1.toInt();
        CoSearchbook[3].clear();
        CoSearchbook[3].addItem(tr(""));
        for(;i<=maxYear;i++)
        {
            CoSearchbook[3].addItem(QString::number(i));
        }
		CoSearchbook[3].setCurrentIndex((CoSearchbook[3].findText(temp)) >= 0 ? CoSearchbook[3].findText(temp) : 0);
		change = !change;
    }
    else
    {
		temp = CoSearchbook[2].currentText();
		change = !change;
        string1=CoSearchbook[3].currentText();
        if(string1==tr(""))
            i=maxYear;
        else
            i=string1.toInt();
        CoSearchbook[2].clear();
        CoSearchbook[2].addItem(tr(""));
        for(int j=minYear;j<=i;j++)
            CoSearchbook[2].addItem(QString::number(j));
		change = !change;
		CoSearchbook[2].setCurrentIndex((CoSearchbook[2].findText(temp)) >= 0 ? CoSearchbook[2].findText(temp) : 0);
    }
}
//登入界面选择取消
void libraryMain::clickLoadCancel()
{
    loadPage->close();
}
void libraryMain::clickLoadConfirm()
{
	QString query_string = tr("select * from users where UserId='") + loadLineEdit[0].text() + tr("' and Password='") + loadLineEdit[1].text() + tr("';");
	query.exec(query_string);
	if (query.size()!=1)
	{
        QMessageBox::warning(windows,QString::fromLocal8Bit("管理员登入错误"),QString::fromLocal8Bit("用户名或者密码错误"),QMessageBox::Yes,NULL);
		loadLineEdit[0].clear();
		loadLineEdit[1].clear();
	}
    else
    {
        loadPage->close();
		root = true;
        button->setText(QString::fromLocal8Bit("退出"));
		setLibraryPage();
    }
}

void libraryMain::click_load()
{
	if (root)
	{
		root = !root;
		button->setText(QString::fromLocal8Bit("管理员登入"));
		setLibraryPage();
	}
    else
    {
        loadLineEdit[0].clear();
        loadLineEdit[1].clear();
        loadPage->show();
    }
}

libraryMain::~libraryMain()
{

}
