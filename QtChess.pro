#-------------------------------------------------
#
# Project created by QtCreator 2018-03-30T23:00:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtChess
TEMPLATE = app
CONFIG += c++17 O3 Wall Wextra

SOURCES +=  main.cpp           \
            src/mainwindow.cpp \
            src/board.cpp      \
            src/pawn.cpp       \
            src/knight.cpp     \
            src/bishop.cpp     \
            src/rook.cpp       \
            src/queen.cpp      \
            src/king.cpp       \

HEADERS  += include/mainwindow.h \
            include/board.h      \        
            include/piece.h      \
            include/pawn.h       \
            include/knight.h     \
            include/bishop.h     \
            include/rook.h       \
            include/queen.h      \
            include/king.h       \
