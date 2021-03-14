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

#include "qtchess.h"

namespace qtc {
namespace qt {

class Pixel
{
 public:
  Pixel() = default;
  Pixel(int a, int b) : x(a), y(b) {};
  int x{0};
  int y{0};
};

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = 0);
  void mousePressEvent(Board &board, const QMouseEvent *event);
  void refresh(const Board& board);

 private:
  bool clicked = false;
  unsigned short int originField, destinationField;

  Pixel offset{20,20};
  double fieldSize{80};
  
  //std::shared_ptr<QLabel> label;
  std::shared_ptr<QGraphicsScene> scene;

  QTransform trafo;
};

unsigned short int PixToPos(const Pixel &pixel, const Pixel &offset, const double fieldSize);
Pixel PosToPix(const unsigned short int position, const Pixel &offset, const double fieldSize);
std::string getFieldName(const unsigned short int position);

};};

#endif // MAINWINDOW_H
