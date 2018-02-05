#ifndef YK_FONT_H
#define YK_FONT_H
#include <QPainterPath>
#include "glwidget.h"
//#include <QList>
//
#include <QVector3D>
typedef QList<QVector3D> vector_list;


class YkFont
{
public:
    YkFont();
    YkFont(QString string);
    YkFont(QStringList string_list);
    void Render(int mode, int rotx,int roty, int rotz ,QList<vector_list> *path, QStringList *text_list);

    int Control_size();
    QString Control_font();
    GLfloat* Control_pos();
    GLfloat* Control_color();

    void Control_size(int num);
    void Control_font(QString ch_font);
    void Control_pos(GLfloat x,GLfloat y,GLfloat z);
    void Control_color(GLfloat r,GLfloat g,GLfloat b);
    void rander_outline(int rotx,int roty, int rotz,QList<vector_list> *path_list,QStringList *text_list);
    void rander_paragraph();
    void rander_line(int rotx,int roty, int rotz);
    void savePoint(float x1,float y1,float z1,float x2,float y2,float z2);

   // void move_line(float x1, float y1, float x2, float y2);
    //void linePathAppend(float x1, float y1, float x2, float y2);
   // float calc_distance(float x1,float y1,float x2,float y2);
   // void move_curve(float x1,float y1, float x2,float y2);
   // void create_path_list(QList<vectorlist> list_of_list, QList<QVector3D> path);
    GLfloat color[3];

private:
    QPainterPath *path;
    QList<QVector3D> linePath;
    int size;
    GLfloat disPos[3];
    GLfloat pos[3];
    QString font;
    QString text;
    QStringList paragraph;
    float equation[3];
    float bezier_function[3];
};

#endif // YK_FONT_H
