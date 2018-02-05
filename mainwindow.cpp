#include "mainwindow.h"

MainWindow::MainWindow()
    : QMainWindow(0)
{
    widget = new QWidget;
    setCentralWidget(widget);

    QString content;
    QString fileName = ":/index.html";
    QFile file(fileName);

    if( file.open(QFile::ReadOnly) )
    {
        content = QString(file.readAll());
    }
    else
    {
        QMessageBox::information(this, tr("GPS Mapper"),
                                      tr("Cannot load %1.").arg(fileName));
        qFatal("Error opening index html file.");
    }
    file.close();

    frame = new QWebView();
    frame->setUrl(QUrl::fromLocalFile("index.html"));
    frame->setHtml(content);

    myObject = new JavascriptObject(this);
    frame->page()->mainFrame()->addToJavaScriptWindowObject("myObject",myObject);

    glay = new QGridLayout();

    StartAddress = new QLineEdit();
    EndAddress = new QLineEdit();

    StartButton = new QPushButton(tr("start"));
    connect(StartButton,SIGNAL(clicked()),
           this ,SLOT(StartButtonSlot()));

    EndButton = new QPushButton(tr("end"));
    connect(EndButton,SIGNAL(clicked()),
            this,SLOT(EndButtonSlot()));

    GetDirections  = new QPushButton(tr("Get Directions"));
    connect(GetDirections,SIGNAL(clicked()),
            this,SLOT(GetDirectionsSlot()));


    glay->addWidget(frame,0,5,10,30);
    glay->addWidget(StartAddress,0,0,1,3);
    glay->addWidget(EndAddress,1,0,1,3);
    glay->addWidget(StartButton,0,4,1,1);
    glay->addWidget(EndButton,1,4,1,1);
    glay->addWidget(GetDirections,2,1,1,3);
    widget->setLayout(glay);



}

void MainWindow::StartButtonSlot()
{

    Start = StartAddress->text();
    QString address = QString("codeAddress('%1',1); null")
             .arg(Start);
    frame->page()->mainFrame()->evaluateJavaScript(address);

}

void MainWindow::EndButtonSlot()
{
    End = EndAddress->text();
    QString address = QString("codeAddress('%1',2); null")
             .arg(End);
    frame->page()->mainFrame()->evaluateJavaScript(address);

}

void MainWindow::GetDirectionsSlot()
{
    frame->page()->mainFrame()->evaluateJavaScript("calcRoute(); null");
}

MainWindow::~MainWindow()
{
    
}
