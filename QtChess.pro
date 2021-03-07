#-------------------------------------------------
#
# Project created by QtCreator 2018-03-30T23:00:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtchess
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++17 -O3 -I include -pthread -Wl,-rpath -Wl,/usr/lib/openmpi -Wl,--enable-new-dtags
QMAKE_LIBS += -L/usr/lib/openmpi -lmpi_cxx -lmpi

SOURCES +=  qt.cpp           \
            src/mainwindow.cpp \
            src/board.cpp      \
            src/piece/pawn.cpp       \
            src/piece/knight.cpp     \
            src/piece/bishop.cpp     \
            src/piece/rook.cpp       \
            src/piece/queen.cpp      \
            src/piece/king.cpp       \

HEADERS  += include/mainwindow.h \
            include/board.h      \        
            include/piece/piece.h      \
            include/piece/pawn.h       \
            include/piece/knight.h     \
            include/piece/bishop.h     \
            include/piece/rook.h       \
            include/piece/queen.h      \
            include/piece/king.h       \
