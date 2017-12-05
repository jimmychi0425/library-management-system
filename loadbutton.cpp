#include "loadbutton.h"

loadButton::loadButton(QWidget *parent)
{
    setText(QString::fromLocal8Bit("管理员登入"));
    load=false;
}
void loadButton::updateButton(bool root)
{
    load=root;
    if(load)
    {
        setText(QString::fromLocal8Bit("退出管理员"));
    }
    else
    {
        setText(QString::fromLocal8Bit("管理员登入"));
    }
}
bool loadButton::loadRoot()
{
    return load;
}
loadButton::~loadButton(){}
