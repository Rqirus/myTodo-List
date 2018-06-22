#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralWidget->setMouseTracking(true);
    setMouseTracking(true);
    brushOfPlus = QBrush(QColor(135,206,250,255));
    scrollColor = QColor(255,99,71);
    scrollLength = this->height();
    drawScrollPen.setWidth(5);
    drawScrollPen.setColor(scrollColor);
    del=0;
    selectedItem=-1;
    scrollIsDrag = false;
    centerPoint.setX(this->width() - 68);
    centerPoint.setY(this->height() - 53);
    r = 20;
    openItem=-1;
    deleteItem-1;
    plusRect = QRect(centerPoint.x()-r,centerPoint.y()-r,2*r,2*r);
    closeLabel = new QLabel(this);
    closeLabel->setMouseTracking(true);
    closeLabel->setText("×");
    inputBox = new QPlainTextEdit(this);
    inputBox->setVisible(false);
    inputBox->setGeometry(20,60,this->width()-40,this->height()-40);
    inputBox->setStyleSheet("background-color:rgb(127,255,170,0)");

    this->setMaximumWidth(this->width());
    this->setMinimumWidth(this->width());
    this->setMaximumHeight(this->height());
    this->setMinimumHeight(this->height());
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete closeLabel;
    delete inputBox;
}

void MainWindow::paintEvent(QPaintEvent *e)
{    
    /*绘制背景图*/
    QPainter painter(this);
    QPixmap pix(":/image/image/todolist2.jpg");
    painter.drawPixmap(0,0,pix);
    int h = painter.fontMetrics().height();
    /*绘制展开后的便签*/
    if(openItem!=-1)
    {
        painter.setBrush(QBrush(QColor(127,255,170,150)));
        int x1 = 20 , x2 = this->width() - 40;
        int y1 = 20 , y2 = this->height()- 40;
        painter.drawRoundRect(x1,y1,x2,y2,15,15);
        closeLabel->setGeometry(x2-30,y1-5,closeLabel->fontMetrics().width("×"),closeLabel->fontMetrics().height()-15);
        closeLabel->show();
    }
    else
    {
        /*绘制便签框*/
        painter.translate(0,del);
        QVector<QRect> v=Item.getAllItem();
        QVector<QRect> sign = Item.getcloseSign();
        for(int i=0;i<v.size();i++)
        {
            int cnt=0;
            if(selectedItem==i)
                painter.setBrush(QBrush(QColor(123,123,123,150))),painter.setPen(Qt::red);
            else
                painter.setBrush(QBrush(QColor(127,255,170,150))),painter.setPen(Qt::black);
            painter.drawRoundRect(v[i],5,5);


            if(deleteItem==i)painter.setPen(Qt::red);
            else painter.setPen(Qt::black);
            // topright close
            painter.drawText(sign[i],tr("×"));
            // topleft id
            painter.setPen(Qt::black);
            painter.drawText(v[i].x()+10,v[i].y()+15,tr("%1.").arg(i+1));
            QFile file(tr("item/myFile_%1").arg(i));
            bool f=file.open(QIODevice::ReadWrite|QIODevice::Text);
            QTextStream ts(&file);
            while(!ts.atEnd()&&cnt<=2)
            {
                painter.drawText(v[i].x()+10,v[i].y()+cnt*h+15,v[i].width(),
                                 v[i].height(),Qt::TextLongestVariant,ts.readLine());
                cnt++;
            }
            file.close();
        }

        painter.translate(0,-del);



        /*绘制滚动条*/
        qreal ratio = this->height()*1.0/Item.getCanvasLength();
        if(ratio<=1)
        scrollLength = ratio*this->height();
        double l = this->height() - scrollLength;
        double k = l*1.0/(Item.getCanvasLength()-this->height());
        int Y = k*(-del);
        drawScrollPen.setColor(scrollColor);
        painter.setPen(drawScrollPen);
        scrollRect = QRect(this->width()-5,Y,5,scrollLength);
        painter.drawRoundRect(scrollRect,25,25);


        /*绘制加号按钮*/
        int x =centerPoint.x();
        int y =centerPoint.y();
        painter.setBrush(brushOfPlus);
        painter.setPen(Qt::white);
        painter.drawEllipse(plusRect);
        painter.drawLine(x,y,x-2*r/3,y);
        painter.drawLine(x,y,x+2*r/3,y);
        painter.drawLine(x,y,x,y-2*r/3);
        painter.drawLine(x,y,x,y+2*r/3);
    }
}


void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    QPoint p = e->pos();
    selectedItem=deleteItem=-1;

    if(openItem!=-1)
    {
         if(closeLabel->geometry().contains(p))
         {
             closeLabel->setStyleSheet("color: red");
         }
         else closeLabel->setStyleSheet("color: black");
    }
    else
    {
        if(cursorInPlus(p))
        {
            brushOfPlus = QBrush(QColor(30,144,255,255));
            update();
            return;
        }
        else
            brushOfPlus = QBrush(QColor(135,206,250,255));



        QVector<QRect> v=Item.getAllItem();
        QVector<QRect> sign=Item.getcloseSign();
        for(int i=v.size()-1;i>=0;i--)
        {
            int x = v[i].x();
            int y = v[i].y();
            y += del;
            if(p.x()>=x&&p.x()<=x+v[i].width()&&p.y()>=y&&p.y()<=y+v[i].height())
                selectedItem=i;
            x = sign[i].x();
            y = sign[i].y();
            y += del;
            if(p.x()>=x&&p.x()<=x+v[i].width()&&p.y()>=y&&p.y()<=y+v[i].height())
                deleteItem = i;

        }

        if(cursorInScroll(p))
            scrollColor = QColor(205,38,38);
        else
            scrollColor = QColor(255,99,71);
        if(scrollIsDrag)
        {
            scrollColor = QColor(205,38,38);

            int delta = p.y() - lastPoint.y();
            int h = Item.getCanvasLength()-this->height();
            lastPoint = p;

            if(h<0)return;
            del -= delta*3;
            if(del>0)del=0;
            if(-del>h&&h>0)del = -h;
        }
    }

    update();

}


void MainWindow::mousePressEvent(QMouseEvent *e)
{
    QPoint p = e->pos();
    if(openItem!=-1)
    {
        if(closeLabel->geometry().contains(p))      //close and save
        {
            closeLabel->setVisible(false);
            QFile file(tr("item/myFile_%1").arg(openItem));
            file.open(QIODevice::ReadWrite|QIODevice::Text);
            file.write(inputBox->toPlainText().toLocal8Bit());
            file.close();
            inputBox->setEnabled(false);
            inputBox->setVisible(false);
            openItem=-1;
        }
    }
    else
    {
        if(cursorInPlus(p))
            Item.addItem(this->width());
        else if(cursorInScroll(p))
        {
            lastPoint=p;
            scrollIsDrag=true;
        }
        else if(selectedItem!=-1)
        {
            QVector<QRect> v=Item.getAllItem();
            QVector<QRect> sign = Item.getcloseSign();
            if(deleteItem==-1)//open
            {
                openItem = selectedItem;
                QFont ft;
                ft.setPointSize(25);
                closeLabel->setFont(ft);
                closeLabel->setStyleSheet("color: black");
                QFile file(tr("item/myFile_%1").arg(openItem));
                file.open(QIODevice::ReadWrite|QIODevice::Text);
                inputBox->setEnabled(true);
                inputBox->show();
                inputBox->setPlainText(file.readAll());
                file.close();
            }
            else               //remove
            {
                QFile file(tr("item/myFile_%1").arg(deleteItem));
                file.open(QIODevice::ReadWrite);
                if(file.remove())
                    qDebug()<<"remove sucess!!";
                else
                    qDebug()<<file.errorString();


                qDebug()<<v.size()<<sign.size();

                file.close();
                for(int i=deleteItem+1;i<v.size();i++)
                {
                    QFile file(tr("item/myFile_%1").arg(i));
                    file.open(QIODevice::ReadWrite);
                    file.rename(tr("item/myFile_%1").arg(i-1));
                    file.close();
                }
                Item.removeItem();

                int h = Item.getCanvasLength() - this->height();
                if(-del>h&&h>0)del=-h;

            }
        }
        else
        {
        }
    }
    update();
}
void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    scrollIsDrag=false;
}

void MainWindow::wheelEvent(QWheelEvent *e)
{
    int f=e->delta();
    int h = Item.getCanvasLength() - this->height();
    if(h<0)return;

    int w = Item.getWidth();
    if(f>0)del += w;
    else del -= w;
    if(del>0)del=0;
    if(-del>h)del=-h;

    update();
}

bool MainWindow::cursorInScroll(QPoint p)
{
    return scrollRect.contains(p);
}

bool MainWindow::cursorInPlus(QPoint p)
{
    if(p.x()>=centerPoint.x()-r&&p.x()<=centerPoint.x()+r
            &&p.y()>=centerPoint.y()-r&&p.y()<=centerPoint.y()+r)
        return true;
    else return false;
}
