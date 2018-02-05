#ifndef YK_PATH_H
#define YK_PATH_H
#include "math.h"
#include <QList>
#include <QVector3D>
#include <QStringList>


typedef QList<QVector3D> vector_list;

class YkPath
{
    public:
    YkPath();
    YkPath(float x1, float y1, float x2, float y2, vector_list path);
    QList<vector_list> *list_of_list;
    QStringList text_list;


  //  void move_line(float x1, float y1, float x2, float y2);
   //void move_curve(float x1,float y1, float x2,float y2);


    float calc_distance(float x1,float y1,float x2,float y2);
    void path_append(float x1, float y1, float x2, float y2,vector_list *linepath);
    void create_path_list(QList<vector_list> *list_of_list, vector_list path);
private:


};
#endif // YK_PATH_H
