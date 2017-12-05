#include "windfont.h"
#include<QtWidgets>
windFont::windFont(QWidget *parent):QWidget(parent)
{
    setBackgroundRole(QPalette::Midlight);
    setAutoFillBackground(true);
    QFont newFont=font();
    newFont.setPointSize(newFont.pointSize()+10);
    setFont(newFont);
    step=0;
    timer.start(60,this);
    text=QString::fromLocal8Bit("图书管理系统");
}
void windFont::paintEvent(QPaintEvent */*event*/)
{
    static const int sinTable[16]={
        0,38,71,92,100,92,71,38,0,-38,-71,-92,-100,-92,-71,-38
    };
    QFontMetrics metric(font());
    int x=(width()-metric.width(text))/2;
    int y=(height()+metric.ascent()-metric.descent())/2;
    QColor color;
    QPainter painter(this);
    for(int i=0;i<text.size();i++)
    {
        int index=(step+1)%16;
        color.setHsv((15-index)*16,255,191);
        painter.setPen(color);
        painter.drawText(x,y-((sinTable[index]*metric.height())/400),QString(text[i]));
        x+=metric.width(text[i]);
    }
}
void windFont::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==timer.timerId()){
        step++;
        update();
    }else{
        QWidget::timerEvent(event);
    }
}
