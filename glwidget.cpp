
#include <QtGui>
#include <QtOpenGL>
#include <QPainter>
#include <QTimer>
#include <math.h>
#include "glwidget.h"
#include "slippymap.h"
#include "YK_FONT.h"
#include "YK_FILE.h"
#include "YK_PATH.h"
#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent),disx(0),disy(0),rotx(0),roty(0),rotz(0),transx(0),transy(0),posx(0),posy(0),ani_time(0),
      pressed(false), snapped(false), left_button(false),right_button(false),middle_button(false),
      invert(false),fSize(15)
{

    QString a="in.txt";
    YKFile = new YkFile();
    YKFile->open_text_file(a);
    YKFile->read_line();

    YKFont = new YkFont();
    YKFont = new YkFont(YKFile->string_line);


    itimer = new QTimer(this);
    itimer->start(100);
    connect(itimer,SIGNAL(timeout()),this,SLOT(itimer_slot()));



    vector_list path1, path2, path3, path4, path5;

    YKPath = new YkPath(-310,-380,0,-520,path1);
    YKPath->text_list.append(QString::fromLocal8Bit("  아차산로 >>"));
    YKPath->path_append(0,-520,600,-700,&path2);
    YKPath->text_list.append(QString::fromLocal8Bit("아차산로 >> 아차산로 >>"));
    YKPath->path_append(600,-700,580,-520,&path3);
    YKPath->text_list.append(QString::fromLocal8Bit("  자양로"));
    YKPath->path_append(580,-520,680,-220,&path4);
    YKPath->text_list.append(QString::fromLocal8Bit(" ^^  자양로"));
    YKPath->path_append(680,-220,950,70,&path5);
    YKPath->text_list.append(QString::fromLocal8Bit("  ┒┒  자양로"));
    YKPath->create_path_list(YKPath->list_of_list,path2);
    YKPath->create_path_list(YKPath->list_of_list,path3);
    YKPath->create_path_list(YKPath->list_of_list,path4);
    YKPath->create_path_list(YKPath->list_of_list,path5);
   path = YKPath->list_of_list;
   text_list = YKPath->text_list;

    vector_list path6,path7,path8;
    YKPath2 = new YkPath(-310,-380,150,610,path6);
    YKPath2->text_list.append(QString::fromLocal8Bit("  동일로  ^^  동일로  ^^  동일로  ^^"));
    YKPath2->path_append(150,610,830,280,&path7);
    YKPath2->text_list.append(QString::fromLocal8Bit("  천호대로  >>  천호대로  >>  "));
    YKPath2->path_append(830,280,950,70,&path8);
    YKPath2->text_list.append(QString::fromLocal8Bit("  천호대로 "));
    YKPath2->create_path_list(YKPath2->list_of_list,path7);
    YKPath2->create_path_list(YKPath2->list_of_list,path8);
    //path = YKPath2->list_of_list;

    vector_list path9,path10,path11,path12,path13;
    YKPath3 = new YkPath(-310,-380,0,-520,path9);
    YKPath3->text_list.append(QString::fromLocal8Bit("아차산로  >>"));
    YKPath3->path_append(0,-520,170,-90,&path10);
    YKPath3->text_list.append(QString::fromLocal8Bit("   능동로  ^^"));
    YKPath3->path_append(170,-90,400,-190,&path11);
    YKPath3->text_list.append(QString::fromLocal8Bit(" 광나루로 > >"));
    YKPath3->path_append(400,-190,680,-220,&path12);
    YKPath3->text_list.append(QString::fromLocal8Bit("   광나루로"));
    YKPath3->path_append(680,-220,950,70,&path13);
    YKPath3->text_list.append(QString::fromLocal8Bit(">>  자양로"));
    YKPath3->create_path_list(YKPath3->list_of_list,path10);
    YKPath3->create_path_list(YKPath3->list_of_list,path11);
    YKPath3->create_path_list(YKPath3->list_of_list,path12);
    YKPath3->create_path_list(YKPath3->list_of_list,path13);
  // path = YKPath3->list_of_list;
  // text_list = YKPath3->text_list;

    ///****************************/begin
    MapImage = QImage(1680,1050,QImage::Format_RGB32);
    m_normalMap = new SlippyMap(this);
    connect(m_normalMap, SIGNAL(updated(QRect)), SLOT(updateMap(QRect)));
    ///****************************/end
}

///****************************/begin


void GLWidget::path_slot(QString path_num)
{

    if(path_num == "1")
    {
        path = YKPath->list_of_list;
        text_list= YKPath->text_list;
    }
    else if(path_num == "2")
    {
        path = YKPath2->list_of_list;
        text_list= YKPath2->text_list;
    }
    else
    {
        path = YKPath3->list_of_list;
        text_list= YKPath3->text_list;
    }
emit path_signal(path_num);
}
void GLWidget::itimer_slot()
{

    ani_time+=0.05;
    if(ani_time>1)
        ani_time=0;
/*
   move_line(0,0,-100,-100);
   YKFont->Control_pos(equation[0],equation[1],equation[2]);
   */////////////////////////////무브라인함수랑 폰트 함수 바꾸기


/*
    move_curve(0,0,100,0);
    YKFont->Control_pos(bezier_function[0],bezier_function[1],-bezier_function[2]);
    */////////////////////////////////////커브
    updateGL();
}
void GLWidget::drew_path()
{
   GLfloat x1,y1,x2,y2;
   int val;

    int list_len = path->length();

    for(int i = 0; i<=list_len; i++)
    {
     x1 = path->value(i).value(0).x();
     y1 = path->value(i).value(0).y();
     val = path->value(i).length()-1;
     x2 = path->value(i).value(val).x();
     y2 = path->value(i).value(val).y();
     glColor3f(1,1,0);
   glBegin(GL_LINES);
    glVertex3f(x1,y1,0.8);
    glVertex3f(x2,y2,0.8);
    glEnd();
    }

}
void GLWidget::setCenter(qreal lat, qreal lng)
{
    m_normalMap->latitude = lat;
    m_normalMap->longitude = lng;
    m_normalMap->invalidate();
}
void GLWidget::opacity_slot(int o)
{
    opacity = (float)o/10;
    emit opacity_signal(o);
    updateGL();
}
void GLWidget::size_slot(int f_size)
{
    YKFont->Control_size(f_size);
    fSize = f_size;
    emit size_signal(f_size);
    updateGL();
}
void GLWidget::font_slot(QString f_font)
{
    YKFont->Control_font(f_font);
    emit font_signal(f_font);
    updateGL();
}
void GLWidget::r_slot(int r)
{
    float f_r = (float)r/255;
    YKFont->Control_color(f_r,YKFont->color[1],YKFont->color[2]);
    emit r_signal(r);
    updateGL();
}
void GLWidget::g_slot(int g)
{
    float f_g = (float)g/255;
    YKFont->Control_color(YKFont->color[0],f_g,YKFont->color[2]);
    emit g_signal(g);
    updateGL();
}
void GLWidget::b_slot(int b)
{
    float f_b = (float)b/255;
    YKFont->Control_color(YKFont->color[0],YKFont->color[1],f_b);
    emit b_signal(b);
    updateGL();
}
void GLWidget::updateMap(const QRect &r)
{
    update(r);
}

void GLWidget::resizeEvent(QResizeEvent *)
{
    int width0 = width();
    int height0 = height();
    m_normalMap->width = width0;
    m_normalMap->height = height0;
    m_normalMap->invalidate();
    updateGL();

    glViewport(0,0,width0,height0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-width0, +width0, -height0, +height0, 1000, -1000);
#else
    glOrtho(-width0, +width0, -height0, +height0, 1000, -1000);
#endif
    glMatrixMode(GL_MODELVIEW);

    updateGL();
}

void GLWidget::paintEvent(QPaintEvent *event)
{
    QPainter paint;

    paint.begin(&MapImage);
    m_normalMap->render(&paint, event->rect());

    paint.drawRect(0,0,m_normalMap->width,m_normalMap->height);
    paint.end();

    if (invert) {
         paint.begin(&MapImage);
         paint.setCompositionMode(QPainter::CompositionMode_Difference);
         paint.fillRect(event->rect(), Qt::white);
         paint.end();
    }
    MapImage.save("image.bmp");
    updateGL();
}

///****************************/end

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{

    defaultColor.setRgb(255,255,255);
    qglClearColor(defaultColor);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);

}

void GLWidget::paintGL()
{

    GLuint texture;
    if(!MapImage.isNull())
    { texture= bindTexture(MapImage,GL_TEXTURE_2D);
    }
    GLfloat coordX = (GLfloat)((double)(m_normalMap->width)/1680);
    GLfloat coordY = 1.0f-(GLfloat)((double)(m_normalMap->height)/1050);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glPushMatrix();
    glRotatef(-rotx/6, 1.0f, 0.0f, 0.0f);
    glRotatef(-roty/6, 0.0f, 1.0f, 0.0f);
    glRotatef(-rotz/6, 0.0f, 0.0f, 1.0f);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_ONE,GL_ZERO);
   glColor4f(0.8f,0.8f,0.8f,1.0f);
    glBegin(GL_QUADS);//판
        glVertex3f(-(this->width()), (this->height()), 0.9);
        glVertex3f(-(this->width()),-(this->height()), 0.9);
        glVertex3f((this->width()),-(this->height()), 0.9);
        glVertex3f((this->width()),(this->height()), 0.9);
    glEnd();
    glEnable(GL_POLYGON_SMOOTH);
    glLineWidth(10);
    drew_path();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if(!MapImage.isNull())
    {
        glEnable( GL_TEXTURE_2D );
        glBindTexture(GL_TEXTURE_2D,texture);
        glColor4f(1.0,1.0,1.0,opacity);
        glBegin(GL_QUADS);//지도
            glNormal3f(0,0,-1);
            glVertex3f(-(this->width()), (this->height()), 1);	glTexCoord2f(0.0    , coordY );
            glVertex3f(-(this->width()),-(this->height()), 1);	glTexCoord2f(coordX , coordY );
            glVertex3f( (this->width()),-(this->height()), 1);	glTexCoord2f(coordX , 1.0    );
            glVertex3f( (this->width()), (this->height()), 1);	glTexCoord2f(0.0    , 1.0    );
        glEnd();

        glDisable( GL_TEXTURE_2D );
        glEnable(GL_DEPTH_TEST);
    }
    glDisable(GL_BLEND);
    glTranslatef(transx*2,transy*2,0);
    /* draw font START */

    glLineWidth(1);
    YKFont->Render(0,rotx,roty,rotz,path,&text_list);
    /* draw font END */
    glPopMatrix();

}

void GLWidget::resizeGL(int width, int height)
{

}
static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{

    if (event->buttons() == Qt::LeftButton)//x,y
    {
    pressed = snapped = true;
    pressPos = dragPos = event->pos();

    posx = event->x();
    posy = event->y();

    left_button = true;
    right_button = false;
    middle_button = false;

    }
    else if(event->buttons() == Qt::MiddleButton)//x,z
    {
        pressed = snapped = true;
        pressPos = dragPos = event->pos();

        posx = event->x();
        posy = event->y();

        left_button = false;
        right_button = false;
        middle_button = true;
    }

    else if(event->buttons() == Qt::RightButton)//transrate
    {
        pressed = snapped = true;
        pressPos = dragPos = event->pos();
        left_button = false;
        right_button = true;
        middle_button = false;
    }

    posx = event->x();
    posy = event->y();
     return;

}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!pressed || !snapped ) {

        if(left_button)//x,y
        {
            disx = event->x() - posx;
            disy = event->y() - posy;

            rotx += disy;
            roty += disx;
        }
        else if(middle_button)//x,z
        {
            disx = event->x() - posx;
            disy = event->y() - posy;

            rotx += disy;
            rotz += disx;
        }
        else if(right_button)
        {
            QPoint delta = event->pos() - pressPos;
            pressPos = event->pos();
            m_normalMap->pan(delta);

            transx +=(event->x() - posx);
            transy +=(posy - event->y());
        }
        posx = event->x();
        posy = event->y();
        updateGL();
        return;
    }

    else
    {
        const int threshold = 10;
        QPoint delta = event->pos() - pressPos;
        if (snapped) {
            snapped &= delta.x() < threshold;
            snapped &= delta.y() < threshold;
            snapped &= delta.x() > -threshold;
            snapped &= delta.y() > -threshold;
        }
    }
    ///****************************/
}

void GLWidget::drawCube(GLfloat sx, GLfloat sy, GLfloat sz, GLfloat width, GLfloat height, GLfloat depth)
{	GLfloat arr[8][3]=	{	{sx,sy,sz},						//0 좌하앞
                            {sx+width,sy,sz},				//1	우하앞
                            {sx+width,sy+height,sz},		//2 우상앞
                            {sx,sy+height,sz},				//3 좌상앞
                            {sx,sy,sz+depth},				//4 좌하뒤
                            {sx+width,sy,sz+depth},			//5 우하뒤
                            {sx+width,sy+height,sz+depth},	//6 우상뒤
                            {sx,sy+height,sz+depth}			//7 좌상뒤
                        };
    GLfloat vx,vy,vz;

    glBegin(GL_QUADS);
        CalculateVectorNormal(arr[7],arr[6],arr[5],&vx,&vy,&vz);
        glNormal3f(vx,vy,vz);
        glVertex3f(arr[7][0],arr[7][1],arr[7][2]);	glTexCoord2f (0.0, 0.0);
        glVertex3f(arr[6][0],arr[6][1],arr[6][2]);	glTexCoord2f (1.0, 0.0);
        glVertex3f(arr[5][0],arr[5][1],arr[5][2]);	glTexCoord2f (1.0, 1.0);
        glVertex3f(arr[4][0],arr[4][1],arr[4][2]);	glTexCoord2f (0.0, 1.0);

        CalculateVectorNormal(arr[0],arr[1],arr[2],&vx,&vy,&vz);
        glNormal3f(vx,vy,vz);
        glVertex3f(arr[0][0],arr[0][1],arr[0][2]);	glTexCoord2f (0.0, 0.0);
        glVertex3f(arr[1][0],arr[1][1],arr[1][2]);	glTexCoord2f (1.0, 0.0);
        glVertex3f(arr[2][0],arr[2][1],arr[2][2]);	glTexCoord2f (1.0, 1.0);
        glVertex3f(arr[3][0],arr[3][1],arr[3][2]);	glTexCoord2f (0.0, 1.0);

        CalculateVectorNormal(arr[0],arr[3],arr[7],&vx,&vy,&vz);
        glNormal3f(vx,vy,vz);
        glVertex3f(arr[0][0],arr[0][1],arr[0][2]);	glTexCoord2f (0.0, 0.0);
        glVertex3f(arr[3][0],arr[3][1],arr[3][2]);	glTexCoord2f (1.0, 0.0);
        glVertex3f(arr[7][0],arr[7][1],arr[7][2]);	glTexCoord2f (1.0, 1.0);
        glVertex3f(arr[4][0],arr[4][1],arr[4][2]);	glTexCoord2f (0.0, 1.0);

        CalculateVectorNormal(arr[3],arr[2],arr[6],&vx,&vy,&vz);
        glNormal3f(vx,vy,vz);
        glVertex3f(arr[3][0],arr[3][1],arr[3][2]);	glTexCoord2f (0.0, 0.0);
        glVertex3f(arr[2][0],arr[2][1],arr[2][2]);	glTexCoord2f (1.0, 0.0);
        glVertex3f(arr[6][0],arr[6][1],arr[6][2]);	glTexCoord2f (1.0, 1.0);
        glVertex3f(arr[7][0],arr[7][1],arr[7][2]);	glTexCoord2f (0.0, 1.0);

        CalculateVectorNormal(arr[6],arr[2],arr[1],&vx,&vy,&vz);
        glNormal3f(vx,vy,vz);
        glVertex3f(arr[6][0],arr[6][1],arr[6][2]);	glTexCoord2f (0.0, 0.0);
        glVertex3f(arr[2][0],arr[2][1],arr[2][2]);	glTexCoord2f (1.0, 0.0);
        glVertex3f(arr[1][0],arr[1][1],arr[1][2]);	glTexCoord2f (1.0, 1.0);
        glVertex3f(arr[5][0],arr[5][1],arr[5][2]);	glTexCoord2f (0.0, 1.0);

        CalculateVectorNormal(arr[0],arr[4],arr[5],&vx,&vy,&vz);
        glNormal3f(vx,vy,vz);
        glVertex3f(arr[0][0],arr[0][1],arr[0][2]);	glTexCoord2f (0.0, 0.0);
        glVertex3f(arr[4][0],arr[4][1],arr[4][2]);	glTexCoord2f (1.0, 0.0);
        glVertex3f(arr[5][0],arr[5][1],arr[5][2]);	glTexCoord2f (1.0, 1.0);
        glVertex3f(arr[1][0],arr[1][1],arr[1][2]);	glTexCoord2f (0.0, 1.0);
    glEnd();
}

void GLWidget::CalculateVectorNormal(	GLfloat fVert1[], GLfloat fVert2[], GLfloat fVert3[],		//3개의 vertice 입력
                            GLfloat *fNormalX, GLfloat *fNormalY, GLfloat *fNormalZ)	//3개의 벡터값 저장할 위치
{
    GLfloat Qx, Qy, Qz, Px, Py, Pz;

    Qx = fVert2[0]-fVert1[0];
    Qy = fVert2[1]-fVert1[1];
    Qz = fVert2[2]-fVert1[2];
    Px = fVert3[0]-fVert1[0];
    Py = fVert3[1]-fVert1[1];
    Pz = fVert3[2]-fVert1[2];

    *fNormalX = Py*Qz - Pz*Qy;
    *fNormalY = Pz*Qx - Px*Qz;
    *fNormalZ = Px*Qy - Py*Qx;
}
