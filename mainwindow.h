#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QWebView>
#include <QWebPage>
#include <QWebFrame>
#include <QFile>
#include <QMessageBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>

#include "javascriptobject.h"

QT_BEGIN_NAMESPACE

class Qlabel;
class QLineEdit;
class QPushButton;

QT_END_INCLUDE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow();
    ~MainWindow();

    QWebView *frame;

    JavascriptObject *myObject;

    QGridLayout *glay;

    QString Start;
    QString End;


private:
    QWidget *widget;
    QLineEdit *StartAddress;
    QLineEdit *EndAddress;
    QPushButton *StartButton;
    QPushButton *EndButton;
    QPushButton *GetDirections;


private slots:
    void StartButtonSlot();
    void EndButtonSlot();
    void GetDirectionsSlot();
};

#endif // MAINWINDOW_H
