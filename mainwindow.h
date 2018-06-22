#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QPen>
#include <myitem.h>
#include <QColor>
#include <QLabel>
#include <QVector>
#include <QPlainTextEdit>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    bool cursorInScroll(QPoint);
    bool cursorInPlus(QPoint);
private:
    Ui::MainWindow *ui;
    QBrush brushOfPlus;
    QPoint centerPoint;
    QPoint lastPoint;
    myItem Item;
    QColor scrollColor;
    QPen drawScrollPen;
    QRect scrollRect;
    QRect plusRect;
    int scrollLength;
    int r;
    int del;
    int selectedItem;
    int openItem;
    int deleteItem;
    bool scrollIsDrag;
    QLabel *closeLabel;
    QPlainTextEdit *inputBox;
};

#endif // MAINWINDOW_H
