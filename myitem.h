#ifndef MYITEM_H
#define MYITEM_H

#include <QObject>
#include <QPainterPath>
#include <QFont>
#include <QVector>
#include <QRect>
#include <QBrush>
#include <QRegion>
#include <QFile>
class myItem : public QObject
{
private:
    Q_OBJECT

    int width;
    int windowWidth=468;
    int count;
    int canvasLength;
    QPainterPath path;
    QVector<QRect> itemBak;
    QVector<QRect> closeSign;
    QBrush itemBrush;

public:
    explicit myItem(QObject *parent = 0);
    ~myItem();
    void addItem(int);
    QPainterPath getPath();
    int getWidth();
    int getCanvasLength();
    int getCount();
    QVector<QRect> getAllItem();
    QVector<QRect>  getcloseSign();
    QBrush getItemBrush();
    void setItemBrush(QBrush);
    void setWindowWidth(int w);
    void removeItem();
signals:

public slots:



};

#endif // MYITEM_H
