QT += core concurrent
QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = console_app

SOURCES += main.cpp

QMAKE_CXXFLAGS += -Wall
