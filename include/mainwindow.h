#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGridLayout>
#include <QColor>
#include <QGraphicsPixmapItem>
#include <QTransform>

#include "include/board.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void mousePressEvent(QMouseEvent *event);
    int PixToPos(int,int);
    int* PosToPix(int);
    QGraphicsItem* get_item(int, int &);
    void rem_item(QGraphicsItem*, int);
    std::string get_field(int);

private:
    QLabel* label;
    bool clicked = false;
    int field1, field2;

    double offset_x = 20;
    double offset_y = 20;
    double field_size = 80;

    Board board;

    QImage  *imageObject;
    QTransform trafo;
    QGraphicsScene *scene;

    std::vector<QPixmap> image_wpawn;
    std::vector<QGraphicsItem*> image_wpawn_it;
    std::vector<QPixmap> image_wbishop;
    std::vector<QGraphicsItem*> image_wbishop_it;
    std::vector<QPixmap> image_bpawn;
    std::vector<QGraphicsItem*> image_bpawn_it;
};

#endif // MAINWINDOW_H
