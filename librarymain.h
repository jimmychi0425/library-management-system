#ifndef LIBRARYMAIN_H
#define LIBRARYMAIN_H

#include <QMainWindow>
#include <QLineEdit>
#include<QLayout>
#include<QPushButton>
#include<QLineEdit>
#include<QLabel>
#include<QTabWidget>
#include<QStackedLayout>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QMessageBox>
#include<QComboBox>
#include<QStandardItemModel>
#include<QTextStream>
#include<QTableView>
#include<QHBoxLayout>
#include <QtWidgets>
#include<QIODevice>
#include<QDateTime>
#include<QTableWidget>
#include<QFileDialog>
#include"windfont.h"
class libraryMain : public QObject
{
    Q_OBJECT

public:
    libraryMain(QObject *parent = 0);
    ~libraryMain();
    void setLibraryPage();
    void perpareLoadPage();
private slots:
    void click_load();
    void clickLoadCancel();
    void clickLoadConfirm();
    void process();
    void changeSearchbook();
    void clearSearchbook();
    void findBorrowBook();
    void addBorrowBook();
    void findreturnBook();
    void addreturnBook();
    void addLibraryCard();
    void deleteLibraryCard();
    void addBook();
    void deleteBook();
    void addBookList();
private:
	void update();
	int FID;
	bool lastroot;
	bool change;
	void deleteTable(QTableWidget* tablewidget);
    windFont*windfont;
    QGridLayout *layout_1;
    QVBoxLayout *layout_2;
    QPushButton *button;
    bool root;
    //登入界面
    QWidget* loadPage;
    QPushButton*loadbutton;
    QLabel*loadLabel;
    QLineEdit*loadLineEdit;
    QSqlDatabase dbLibrary;
    QTabWidget *visited;
    QTabWidget *adminer;
    QStackedLayout* stacklayout;
	void initLibraryPage();
    QVBoxLayout* VBSearchbook;
    QGridLayout* GrSearchbook;
    QLineEdit *LiSearchbook;
    QLabel* LaSearchbook;
    QTableWidget* TaSearchbook;
    QPushButton* PbSearchbook;
    QComboBox* CoSearchbook;
    QSqlQuery query;
	QTableWidgetItem*searchBook_1;
	QStringList searchBook_2;
    int maxYear,minYear;
    void initSearPage();
    void setComSearch();
    void setTable();

    QHBoxLayout*borrowBook_1;
	QLabel* borrowBook_7;
    QLineEdit*borrowBook_2;
    QPushButton*borrowBook_3;
    QVBoxLayout*borrowBook_4;
    QTableWidget*borrowBook_5;
    QTableWidgetItem*borrowBook_6;
    QStringList borrowBook_8;
    void borrowBookPage();

    QHBoxLayout*returnBook_1;
    QLineEdit*returnBook_2;
    QPushButton*returnBook_3;
    QVBoxLayout*returnBook_4;
    QTableWidget*returnBook_5;
    QTableWidgetItem*returnBook_6;
	QLabel*returnBook_7;
    QStringList returnBook_8;
    void returnBookPage();

    QGridLayout*libraryCard_1;
    QVBoxLayout*libraryCard_2;
    QLabel*libraryCard_3;
    QLineEdit*libraryCard_4;
    QTableWidget*libraryCard_5;
    QTableWidgetItem*libraryCard_6;
    QStringList libraryCard_7;
    QPushButton*libraryCard_8;
    void libraryCardPage();
    void showLibraryCard();

    QGridLayout*inputBook_1;
    QVBoxLayout*inputBook_2;
    QLabel*inputBook_3;
    QLineEdit*inputBook_4;
    QTableWidget*inputBook_5;
    QTableWidgetItem*inputBook_6;
    QStringList inputBook_7;
    QPushButton*inputBook_8;
    void InputBookPage();
    void showInputBook();
    bool addBookString(QString src);
    bool isDigitStr(QString src);
	QWidget* widget_1;
	QWidget* widget_2;
	QWidget* widget_3;
	QWidget* widget_4;
	QWidget* widget_5;
	QGroupBox* widget_6;
	QGroupBox* widget_7;
	QGroupBox* widget_8;
	QGroupBox*widget_9;
	QGroupBox*widget_10;
	QWidget* windows;
	QWidget* title;
};

#endif // LIBRARYMAIN_H
