#-------------------------------------------------
#
# Project created by QtCreator 2018-03-30T23:00:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtchess
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++17 -O3 -I include -fopenmp -Wl,-rpath -Wl,/usr/lib/openmpi -Wl,--enable-new-dtags
QMAKE_LIBS += -L/usr/lib/openmpi -lmpi_cxx -lmpi -lgomp

SOURCES +=  qt.cpp                   \
            src/qt/mainwindow.cpp    \ 
            src/board/board.cpp      \
            src/board/fen.cpp        \
            src/board/help.cpp       \
            src/piece/pawn.cpp       \
            src/piece/knight.cpp     \
            src/piece/bishop.cpp     \
            src/piece/rook.cpp       \
            src/piece/queen.cpp      \
            src/piece/king.cpp       \

HEADERS  += include/qt/mainwindow.h    \
            include/board/board.h      \        
            include/piece/piece.h      \
            include/piece/pawn.h       \
            include/piece/knight.h     \
            include/piece/bishop.h     \
            include/piece/rook.h       \
            include/piece/queen.h      \
            include/piece/king.h       \
