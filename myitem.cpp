#include "myitem.h"
#include <QDebug>
#include <QByteArray>
#include <QLabel>
myItem::myItem(QObject *parent) :width(100),QObject(parent)
{
    itemBrush = QBrush(QColor(127,255,170,150));
    QFile file("itemnumber");
    file.open(QIODevice::ReadWrite|QIODevice::Text);
    QByteArray array = file.readLine();
    count = array.toInt();
    for(int i=0;i<count;i++)
    {
        itemBak.append(QRect(10,10+i*width,windowWidth-20,width*4/5));
        closeSign.append(QRect(windowWidth-25,10+i*width,20,20));
    }
    file.close();
}

myItem::~myItem()
{
    QFile file("itemnumber");
    file.resize(0);
    file.open(QIODevice::ReadWrite|QIODevice::Text);
    char num[10];
    int Index=0,tmp=count;
    while(tmp)
    {
        num[Index++]='0'+tmp%10;
        tmp/=10;
    }
    for(int i=0;i<Index/2;i++)
    {
        tmp=num[i];
        num[i]=num[Index-i-1];
        num[Index-i-1]=tmp;
    }
    num[Index]='\0';
    file.write(num);
    file.close();

}

void myItem::addItem(int windowWidth)
{
    QFont font;
    itemBak.append(QRect(10,10+count*width,windowWidth-20,width*4/5));
    closeSign.append(QRect(windowWidth-25,10+count*width,20,20));
    count++;
}

QPainterPath myItem::getPath()
{
    return this->path;
}


int myItem::getCanvasLength()
{
    return itemBak.count()*width;
}

int myItem::getWidth()
{
    return this->width;
}

int myItem::getCount()
{
    return itemBak.count();
}

QVector<QRect> myItem::getAllItem()
{
    return itemBak;
}

QBrush myItem::getItemBrush()
{
    return this->itemBrush;
}

void myItem::setItemBrush(QBrush brush)
{
    this->itemBrush = brush;
}


void myItem::setWindowWidth(int w)
{
    this->windowWidth=w;
}

void myItem::removeItem()
{
    itemBak.pop_back();
    closeSign.pop_back();
    count = itemBak.size();
}


QVector<QRect> myItem::getcloseSign()
{
    return this->closeSign;
}
