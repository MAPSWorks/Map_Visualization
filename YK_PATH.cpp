#include "YK_PATH.h"
#include "glwidget.h"
YkPath::YkPath()
{
    list_of_list = new QList<vector_list>;
   // vector_list vector;
    // path_append(0,0,100,0,&vector);
   // create_path_list(list_of_list,vector);
}

YkPath::YkPath(float x1, float y1, float x2, float y2, vector_list path)
{
    list_of_list = new QList<vector_list>;
    path_append(x1,y1,x2,y2,&path);
    create_path_list(list_of_list,path);
}

float YkPath::calc_distance(float x1,float y1,float x2,float y2)
{
     float dis_points = float(sqrt(pow(x2-x1,2)+pow(y2-y1,2)));
     return dis_points;
}

void YkPath::path_append(float x1, float y1, float x2, float y2,vector_list *linepath)
{
    float equation[3];
    float dis_points = calc_distance(x1,y1,x2,y2);
    float v_x = (x2-x1)/dis_points;
    float v_y = (y2-y1)/dis_points;


  //클리어
    for(float t=0; t<dis_points; t+=35)
    {
        equation[0] = x1+(t*v_x);
        equation[1] = y1+(t*v_y);
        equation[2] = 0;

        linepath->append(QVector3D(equation[0],equation[1],equation[2]));
    }
    linepath->append(QVector3D(x2,y2,0));
    //오차값 생김 : dis_points 바로 전에 좌표값이 잡혀서 equation계산할때 t을 곱한값이 x2,x2를 넘길때
}
void YkPath::create_path_list(QList<vector_list> *list_of_list, vector_list path)
{
    list_of_list->append(path);
}


/*
void YkPath::move_curve(float x1, float y1, float x2, float y2)
{

    float dis_points = calc_distance(x1,y1,x2,y2);
    float ctrlpoint[2][2] = {{x1+(dis_points/4),dis_points/2}
                             ,{x2-(dis_points/4),dis_points/2}};
    int wordSpace=0;
    int tempSize=wordSpace;//fSize+wordSpace;

    for(float i =0; i<=1; i+=(1/dis_points)*tempSize)
    {
        bezier_function[0] = pow(1-i,3)*x1 + 3*i*pow(1-i,2)*ctrlpoint[0][0] +
                3*(1-i)*pow(i,2)*ctrlpoint[1][0] + pow(i,3)*x2;
        bezier_function[1]=0;
        bezier_function[2] = pow(1-i,3)*y1 + 3*i*pow(1-i,2)*ctrlpoint[0][1] +
                3*(1-i)*pow(i,2)*ctrlpoint[1][1] + pow(i,3)*y2;
        linePath.append(QVector3D(bezier_function[0],bezier_function[1],-bezier_function[2]));
    }

}
*/
