#include "include/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{  
  //this.board = new Board();
    
    //////////////////////////////////////////////////////////////////////
    this->setWindowTitle("QtChess Board");

    scene = new QGraphicsScene();
    QPen r_pen("red");
    QPen b_pen("black");
    QBrush b_brush("black");
    QBrush w_brush("white");
    QBrush help("white");
    
    this->resize(50+this->offset_x+8*this->field_size, 50+this->offset_y+8*this->field_size);
    for(int i = 0; i < 64; i++)
    {
        if(i%8 == 0)
        {
            help    = w_brush;
            w_brush = b_brush;
            b_brush = help;
        }
	
        if(i%2 == 0)
	  scene->addRect(this->offset_x+i%8*this->field_size, this->offset_y+i/8*this->field_size, this->field_size, this->field_size, b_pen, b_brush);
        else
	  scene->addRect(this->offset_x+i%8*this->field_size, this->offset_y+i/8*this->field_size, this->field_size, this->field_size, b_pen, w_brush);
    }


    
    int *cord = new int[2];
    imageObject = new QImage();
    imageObject->load("img/wpawn.png");
    for(unsigned short int i = 0; i < board.wpawn.size(); i++)
    {
      cord = PosToPix(63-board.wpawn[i].get_pos());

      image_wpawn.push_back(QPixmap::fromImage(*imageObject));
      image_wpawn[image_wpawn.size()-1] = image_wpawn[image_wpawn.size()-1].scaled(field_size/2,field_size/2);
      image_wpawn_it.push_back(scene->addPixmap(image_wpawn[image_wpawn.size()-1]));
      image_wpawn_it[image_wpawn_it.size()-1]->setPos(cord[0],cord[1]);
    }
    /*imageObject->load("img/wbishop.png");
    for(unsigned short int i = 0; i < board.wbishop.size(); i++)
    {
      cord = PosToPix(63-board.wbishop[i].get_pos());

      image_wbishop.push_back(QPixmap::fromImage(*imageObject));
      image_wbishop[image_wbishop.size()-1] = image_wbishop[image_wbishop.size()-1].scaled(field_size/2,field_size/2);
      image_wbishop_it.push_back(scene->addPixmap(image_wbishop[image_wbishop.size()-1]));
      image_wbishop_it[image_wbishop_it.size()-1]->setPos(cord[0],cord[1]);
      }*/
    //////////////////////////////////////////////////////////////////////
    imageObject->load("img/bpawn.png");
    for(unsigned int i = 0; i < board.bpawn.size(); i++)
    {
      cord = PosToPix(31-board.bpawn[i].get_pos());

      image_bpawn.push_back(QPixmap::fromImage(*imageObject));
      image_bpawn[image_bpawn.size()-1] = image_bpawn[image_bpawn.size()-1].scaled(field_size/2,field_size/2);
      image_bpawn_it.push_back(scene->addPixmap(image_bpawn[image_bpawn.size()-1]));
      image_bpawn_it[image_bpawn_it.size()-1]->setPos(cord[0],cord[1]);
    }


    QGraphicsView* view = new QGraphicsView(scene);
    setCentralWidget(view);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    this->trafo = QTransform();

    QGraphicsItem *it1, *it2;
    int n1, n2;

    if(!clicked)
    {
        this->field1 = PixToPos(x,y);
	std::cout << ":" << get_field(this->field1) << std::endl;
	
        this->clicked = true;
        it1 = get_item(this->field1,n1);

	if(it1 == NULL)
	{
	  this->clicked = false;
	}
    }
    else
    {   
        this->field2 = PixToPos(x,y);
	std::cout << "-" << get_field(this->field2) << std::endl;
	
	it1 = get_item(this->field1,n1);
	it2 = get_item(this->field2,n2);
	this->clicked = false;
	
	it1->setPos(PosToPix(PixToPos(x,y))[0], PosToPix(PixToPos(x,y))[1]);
	wpawn[n1].set_pos(63-PixToPos(x,y));
	
	if(it2 != NULL && this->field2 != this->field1)
	{
	  this->clicked = false;
	  rem_item(it2,n2);
	}
    }

}

int MainWindow::PixToPos(int x, int y)
{
    for(int i = 0; i < 64; i++)
    {
      if((x > this->offset_x+i%8*this->field_size && x < this->offset_x+(i%8+1)*this->field_size) && (y > this->offset_y+i/8*this->field_size && y < this->offset_y+(i/8+1)*this->field_size))
        {
            return i;
        }
    }
    exit(1);
}

int* MainWindow::PosToPix(int i)
{
    int *pos = new int[2];

    pos[0] = this->offset_x+(i%8*4+1)*this->field_size/4;
    pos[1] = this->offset_y+(i/8*4+1)*this->field_size/4;

    return pos;
}


QGraphicsItem* MainWindow::get_item(int j, int &pos)
{
    for(unsigned int i = 0; i < wpawn.size(); i++)
    {
      if(wpawn[i].get_pos() == 63-j)
      {
        pos = i;
	return image_wpawn_it[i];
      }
    }
    return NULL;
}

void MainWindow::rem_item(QGraphicsItem* pos, int x)
{
  scene->removeItem(pos);
    
  image_wpawn.erase(image_wpawn.begin()+x);
  image_wpawn_it.erase(image_wpawn_it.begin()+x);
  wpawn.erase(wpawn.begin()+x);
}

std::string MainWindow::get_field(int pos)
{
  std::string line;
  std::string row;

  if(pos/8 == 0) row  = "8";
  if(pos%8 == 0) line = "a";

  if(pos/8 == 1) row  = "7";
  if(pos%8 == 1) line = "b";

  if(pos/8 == 2) row  = "6";
  if(pos%8 == 2) line = "c";

  if(pos/8 == 3) row  = "5";
  if(pos%8 == 3) line = "d";

  if(pos/8 == 4) row  = "4";
  if(pos%8 == 4) line = "e";

  if(pos/8 == 5) row  = "3";
  if(pos%8 == 5) line = "f";

  if(pos/8 == 6) row  = "2";
  if(pos%8 == 6) line = "g";

  if(pos/8 == 7) row  = "1";
  if(pos%8 == 7) line = "h";

  
  return line+row;
}
