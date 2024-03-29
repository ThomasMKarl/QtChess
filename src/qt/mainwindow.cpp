#include "qt/mainwindow.h"

qtc::qt::MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
  Board board = Board::newgame();
  
  setWindowTitle("QtChess Board");

  scene = std::make_shared<QGraphicsScene>();
  const QPen blackPen("black");
  QBrush blackBrush("black");
  QBrush whiteBrush("white");
    
  resize(50 + offset.x + 8*fieldSize,
	 50 + offset.y + 8*fieldSize);
    
  for(unsigned short int i = 0; i < 64; i++)
  {
    if(i%8 == 0) std::swap(blackBrush, whiteBrush);
	
    if(i%2 == 0)
      scene->addRect(offset.x + i%8*fieldSize,
		     offset.y + i/8*fieldSize,
		     fieldSize, fieldSize,
		     blackPen, blackBrush);
    else
      scene->addRect(offset.x + i%8*fieldSize,
		     offset.y + i/8*fieldSize,
		     fieldSize, fieldSize,
		     blackPen, whiteBrush);
  }
  
  refresh(board);
}

std::array<std::string,12> pieceImages = {
  "img/bbishop.png",
  "img/bking.png",
  "img/bknight.png",
  "img/bpawn.png",
  "img/bqueen.png",
  "img/brook.png",

  "img/wbishop.png",
  "img/wking.png",
  "img/wknight.png",
  "img/wpawn.png",
  "img/wqueen.png",
  "img/wrook.png"
};

void qtc::qt::MainWindow::refresh(const Board &board)
{
  Pixel coordinate{};
  std::unique_ptr<QImage> imageObject = std::make_unique<QImage>();
  std::string pathToImage{};
  for(const auto& [position, piece] : board.pieces)
  {
    auto help1 = mpark::get_if<qtc::pc::Bishop>(&piece);
    if(help1)
    {
      if(help1->isWhite()) pathToImage = pieceImages[6];
      else                 pathToImage = pieceImages[0];
      break;
    }
    auto help2 = mpark::get_if<qtc::pc::King>(&piece);
    if(help2)
    {
      if(help2->isWhite()) pathToImage = pieceImages[7];
      else                 pathToImage = pieceImages[1];
      break;
    }
    auto help3 = mpark::get_if<qtc::pc::Knight>(&piece);
    if(help3)
    {
      if(help3->isWhite()) pathToImage = pieceImages[8];
      else                 pathToImage = pieceImages[2];
      break;
    }
    auto help4 = mpark::get_if<qtc::pc::Pawn>(&piece);
    if(help4)
    {
      if(help4->isWhite()) pathToImage = pieceImages[9];
      else                 pathToImage = pieceImages[3];
      break;
    }
    auto help5 = mpark::get_if<qtc::pc::Queen>(&piece);
    if(help5)
    {
      if(help5->isWhite()) pathToImage = pieceImages[10];
      else                 pathToImage = pieceImages[4];
      break;
    }
    auto help6 = mpark::get_if<qtc::pc::Rook>(&piece);
    if(help6)
    {
      if(help6->isWhite()) pathToImage = pieceImages[11];
      else                 pathToImage = pieceImages[5];
      break;
    }
    
    imageObject->load(QString::fromStdString(pathToImage));
    coordinate = PosToPix(position, offset, fieldSize);
    
    QPixmap temp = QPixmap::fromImage(*imageObject.get());
    temp = temp.scaled(fieldSize/2,fieldSize/2);

    std::unique_ptr<QGraphicsItem> temp2(scene->addPixmap(temp));
    temp2->setPos(coordinate.x,coordinate.y);
  }

  QGraphicsView view(scene.get(),this);
  setCentralWidget(&view);
}

void qtc::qt::MainWindow::mousePressEvent(Board &board, const QMouseEvent *event)
{
  const Pixel clickedCoordinate{event->x(),event->y()};

  trafo = QTransform();

  std::string originFieldString, destinationFieldString;

  if(!clicked)
  {
    originField = PixToPos(clickedCoordinate, offset, fieldSize);
    
    if(originField > 63) return;
    
    originFieldString = getFieldName(originField);
    std::cout << ">" << getFieldName(originField);
	
    clicked = true;
  }
  else
  {   
    destinationField = PixToPos(clickedCoordinate, offset, fieldSize);
    
    clicked = false;
    
    if(destinationField > 63) return;
    
    destinationFieldString = getFieldName(destinationField);
    std::cout << "-" << getFieldName(destinationField) << "\n";

    originFieldString += destinationFieldString;
    qtc::move(board, originFieldString);
    refresh(board);
  }
}

unsigned short int qtc::qt::PixToPos(const Pixel &pixel, const Pixel &offset, const double fieldSize)
{
    for(unsigned short int i = 0; i < 64; i++)
    {
      if((pixel.x > offset.x + i%8*fieldSize &&
	  pixel.x < offset.x + (i%8+1)*fieldSize) &&
	 (pixel.y > offset.y + i/8*fieldSize &&
	  pixel.y < offset.y + (i/8+1)*fieldSize))
	return i;
    }
    return 64;
}

qtc::qt::Pixel qtc::qt::PosToPix(const unsigned short int position, const Pixel &offset, const double fieldSize)
{
  qtc::qt::Pixel pixel;

  pixel.x = offset.x + (position%8*4+1)*fieldSize/4;
  pixel.y = offset.y + (position/8*4+1)*fieldSize/4;

  return pixel;
}

std::string qtc::qt::getFieldName(const unsigned short int position)
{
  return fieldMap.at(position);
}
