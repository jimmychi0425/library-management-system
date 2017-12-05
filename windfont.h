#ifndef WINDFONT_H
#define WINDFONT_H
#include<QBasicTimer>
#include<QWidget>
#include<QString>
#include<QFont>
class windFont:public QWidget
{
public:
    windFont(QWidget *parent=0);
protected:
    void paintEvent(QPaintEvent *event)Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event)Q_DECL_OVERRIDE;
private:
    QBasicTimer timer;
    QString text;
    int step;
};

#endif // WINDFONT_H
