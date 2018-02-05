
#include "javascriptobject.h"
#include "mainwindow.h"

JavascriptObject::JavascriptObject(QWidget *parent)
{
    myMainWindow = (MainWindow *)parent;
}

QPointF JavascriptObject::getLatLng() {
    return mVar;
}

void JavascriptObject::set(float lat, float lng){
    mVar.setX(lat);
    mVar.setY(lng);
}
