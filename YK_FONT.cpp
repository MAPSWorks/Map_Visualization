
#include <QStringList>
#include "YK_FONT.h"
#include <math.h>
//#include <gl/glut.h>


YkFont::YkFont()
{
    size = 30;
    font = "Arial";
    text = "hello world!";
    for(int i=0; i<3; i++)
    {
        color[i]=0;
        pos[i]=0;
    }
}

YkFont::YkFont(QString string)
{

    size = 30;
    font = "Arial";
    text = string;
    for(int i=0; i<3; i++)
    {
        color[i]=0;
        pos[i]=0;
    }
}

YkFont::YkFont(QStringList string_list)
{

    size = 30;
    font = "Arial";
    paragraph = string_list;
    for(int i=0; i<3; i++)
    {
        color[i]=0;
        pos[i]=0;
    }

}

int YkFont::Control_size()
{
    return size;
}

QString YkFont::Control_font()
{
   return font;
}
GLfloat* YkFont::Control_pos()
{
    return pos;
}

GLfloat* YkFont::Control_color()
{
    return color;
}


void YkFont::Control_size(int num)
{
    size = num;
}

void YkFont::Control_font(QString ch_font)
{
    font = ch_font;
}
void YkFont::Control_pos(GLfloat x,GLfloat y,GLfloat z)
{
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
}

void YkFont::Control_color(GLfloat r,GLfloat g,GLfloat b)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
}
/*
void YkFont::savePoint(float x1,float y1,float z1,float x2,float y2,float z2)
{
    disPos[0] = (x2-x1)*3/(size);
    disPos[1] = (y2-y1)*3/(size);
    disPos[2] = (z2-z1)*3/(size);
}
*/
void YkFont::rander_outline(int rotx,int roty, int rotz ,QList<vector_list> *path_list,QStringList *text_list)
{
    static int index=0;
    static int prescaler=0;
    static int path_index=0;

    int str_len, cur_path_len, last_point; //Index Checking Variables
    QString spilt_text;

   // prescaler++;
   // if(prescaler>=7)
   // {
   //     index++;
   //     prescaler=0;
   // }
    cur_path_len = path_list->value(path_index).length();
    str_len = text_list->value(path_index).length();
    last_point = cur_path_len-str_len;
    if(index  >=  last_point)
    {
      index=0;
       path_index++;
       if(path_index >= path_list->length())
           path_index = 0;
    }
    spilt_text = text_list->value(path_index);

    for(int i=0;i<spilt_text.length();i++)
    {

        path = new QPainterPath;
        path->addText(QPointF(0,0),QFont(font,size),QString(spilt_text.data()[i]));

        pos[0]=path_list->value(path_index).value(index+i).x();
        pos[1]=path_list->value(path_index).value(index+i).y();
        pos[2]=path_list->value(path_index).value(index+i).z();

        glPushMatrix();
        glTranslatef(pos[0],pos[1],pos[2]);

        glPushMatrix();
        glRotatef(rotx/6, 1.0f, 0.0f, 0.0f);

        glPushMatrix();
        glRotatef(-rotz/6, 0.0f, 1.0f, 0.0f);
        // glRotatef(rotz/6, 0.0f, 0.0f, 1.0f);

        glColor3f(color[0],color[1],color[2]);

        QList<QPolygonF> poly = path->toSubpathPolygons();

        for(QList<QPolygonF>::iterator i = poly.begin(); i != poly.end(); i++)//한글자씩
        {
            glBegin(GL_LINE_LOOP);
            for(QPolygonF::iterator p = (*i).begin(); p != (*i).end();p++)//선하나씩
            {
                glVertex3f(p->rx()*1.0f,-p->ry()*1.0f,0);
            }
            glEnd();
        }
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();
    }
    glPopMatrix();



    spilt_text = text_list->value(path_index+1);

    for(int i=0;i<spilt_text.length();i++)
    {

        path = new QPainterPath;
        path->addText(QPointF(0,0),QFont(font,size),QString(spilt_text.data()[i]));

        pos[0]=path_list->value(path_index+1).value(index+i).x();
        pos[1]=path_list->value(path_index+1).value(index+i).y();
        pos[2]=path_list->value(path_index+1).value(index+i).z();

        glPushMatrix();
        glTranslatef(pos[0],pos[1],pos[2]);

        glPushMatrix();
        glRotatef(rotx/6, 1.0f, 0.0f, 0.0f);

        glPushMatrix();
        glRotatef(-rotz/6, 0.0f, 1.0f, 0.0f);
        // glRotatef(rotz/6, 0.0f, 0.0f, 1.0f);

        glColor3f(color[0],color[1],color[2]);

        QList<QPolygonF> poly = path->toSubpathPolygons();

        for(QList<QPolygonF>::iterator i = poly.begin(); i != poly.end(); i++)//한글자씩
        {
            glBegin(GL_LINE_LOOP);
            for(QPolygonF::iterator p = (*i).begin(); p != (*i).end();p++)//선하나씩
            {
                glVertex3f(p->rx()*1.0f,-p->ry()*1.0f,0);
            }
            glEnd();
        }
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();
    }
    glPopMatrix();



    spilt_text = text_list->value(path_index+2);

    for(int i=0;i<spilt_text.length();i++)
    {

        path = new QPainterPath;
        path->addText(QPointF(0,0),QFont(font,size),QString(spilt_text.data()[i]));

        pos[0]=path_list->value(path_index+2).value(index+i).x();
        pos[1]=path_list->value(path_index+2).value(index+i).y();
        pos[2]=path_list->value(path_index+2).value(index+i).z();

        glPushMatrix();
        glTranslatef(pos[0],pos[1],pos[2]);

        glPushMatrix();
        glRotatef(rotx/6, 1.0f, 0.0f, 0.0f);

        glPushMatrix();
        glRotatef(-rotz/6, 0.0f, 1.0f, 0.0f);
        // glRotatef(rotz/6, 0.0f, 0.0f, 1.0f);

        glColor3f(color[0],color[1],color[2]);

        QList<QPolygonF> poly = path->toSubpathPolygons();

        for(QList<QPolygonF>::iterator i = poly.begin(); i != poly.end(); i++)//한글자씩
        {
            glBegin(GL_LINE_LOOP);
            for(QPolygonF::iterator p = (*i).begin(); p != (*i).end();p++)//선하나씩
            {
                glVertex3f(p->rx()*1.0f,-p->ry()*1.0f,0);
            }
            glEnd();
        }
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();
    }
    glPopMatrix();



    spilt_text = text_list->value(path_index+3);

    for(int i=0;i<spilt_text.length();i++)
    {

        path = new QPainterPath;
        path->addText(QPointF(0,0),QFont(font,size),QString(spilt_text.data()[i]));

        pos[0]=path_list->value(path_index+3).value(index+i).x();
        pos[1]=path_list->value(path_index+3).value(index+i).y();
        pos[2]=path_list->value(path_index+3).value(index+i).z();

        glPushMatrix();
        glTranslatef(pos[0],pos[1],pos[2]);

        glPushMatrix();
        glRotatef(rotx/6, 1.0f, 0.0f, 0.0f);

        glPushMatrix();
        glRotatef(-rotz/6, 0.0f, 1.0f, 0.0f);
        // glRotatef(rotz/6, 0.0f, 0.0f, 1.0f);

        glColor3f(color[0],color[1],color[2]);

        QList<QPolygonF> poly = path->toSubpathPolygons();

        for(QList<QPolygonF>::iterator i = poly.begin(); i != poly.end(); i++)//한글자씩
        {
            glBegin(GL_LINE_LOOP);
            for(QPolygonF::iterator p = (*i).begin(); p != (*i).end();p++)//선하나씩
            {
                glVertex3f(p->rx()*1.0f,-p->ry()*1.0f,0);
            }
            glEnd();
        }
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();
    }
    glPopMatrix();



    spilt_text = text_list->value(path_index+4);

    for(int i=0;i<spilt_text.length();i++)
    {

        path = new QPainterPath;
        path->addText(QPointF(0,0),QFont(font,size),QString(spilt_text.data()[i]));

        pos[0]=path_list->value(path_index+4).value(index+i).x();
        pos[1]=path_list->value(path_index+4).value(index+i).y();
        pos[2]=path_list->value(path_index+4).value(index+i).z();

        glPushMatrix();
        glTranslatef(pos[0],pos[1],pos[2]);

        glPushMatrix();
        glRotatef(rotx/6, 1.0f, 0.0f, 0.0f);

        glPushMatrix();
        glRotatef(-rotz/6, 0.0f, 1.0f, 0.0f);
        // glRotatef(rotz/6, 0.0f, 0.0f, 1.0f);

        glColor3f(color[0],color[1],color[2]);

        QList<QPolygonF> poly = path->toSubpathPolygons();

        for(QList<QPolygonF>::iterator i = poly.begin(); i != poly.end(); i++)//한글자씩
        {
            glBegin(GL_LINE_LOOP);
            for(QPolygonF::iterator p = (*i).begin(); p != (*i).end();p++)//선하나씩
            {
                glVertex3f(p->rx()*1.0f,-p->ry()*1.0f,0);
            }
            glEnd();
        }
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();
    }
    glPopMatrix();



    spilt_text = text_list->value(path_index);

    for(int i=0;i<spilt_text.length();i++)
    {

        path = new QPainterPath;
        path->addText(QPointF(0,0),QFont(font,size),QString(spilt_text.data()[i]));

        pos[0]=path_list->value(path_index).value(index+i).x();
        pos[1]=path_list->value(path_index).value(index+i).y();
        pos[2]=path_list->value(path_index).value(index+i).z();

        glPushMatrix();
        glTranslatef(pos[0],pos[1],pos[2]);

        glPushMatrix();
        glRotatef(rotx/6, 1.0f, 0.0f, 0.0f);

        glPushMatrix();
        glRotatef(-rotz/6, 0.0f, 1.0f, 0.0f);
        // glRotatef(rotz/6, 0.0f, 0.0f, 1.0f);

        glColor3f(color[0],color[1],color[2]);

        QList<QPolygonF> poly = path->toSubpathPolygons();

        for(QList<QPolygonF>::iterator i = poly.begin(); i != poly.end(); i++)//한글자씩
        {
            glBegin(GL_LINE_LOOP);
            for(QPolygonF::iterator p = (*i).begin(); p != (*i).end();p++)//선하나씩
            {
                glVertex3f(p->rx()*1.0f,-p->ry()*1.0f,0);
            }
            glEnd();
        }
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();
    }
    glPopMatrix();

}

void YkFont::rander_paragraph()
{
    if(paragraph.length()!=0)
    {
        path = new QPainterPath;
        int dis= 0;
        int board_w =0;
        int board_h =0;
        int shift_w = 0;
        int shift_h = paragraph.length()*size;

        for(int i=0; i<paragraph.length(); i++,dis+=size*1.5)
        {
            if(i==0)
            {
                shift_w = paragraph[i].length();
            }
            else
            {
                if(paragraph[i].length()>shift_w)
                    shift_w=paragraph[i].length();
            }
        path->addText(QPointF(0,dis),QFont(font,size),QString(paragraph[i]));
        }
        shift_w = shift_w*size;

        glPushMatrix();
        glColor3f(color[0],color[1],color[2]);
        glTranslatef(-(shift_w/4),shift_h,0);
        glTranslatef(pos[0],pos[1],pos[2]);
        QList<QPolygonF> poly = path->toSubpathPolygons();

        for(QList<QPolygonF>::iterator i = poly.begin(); i != poly.end(); i++)
        {
            glLineWidth(1);
            glBegin(GL_LINE_LOOP);
            for(QPolygonF::iterator p = (*i).begin(); p != (*i).end();p++)
            {
                glVertex3f(p->rx()*1.0f,-p->ry()*1.0f,0);

                if(p ==(*i).begin())
                {
                   board_w = p->rx()*1.0f;
                   board_h = -p->ry()*1.0f;
                }
                else
                {
                    if(board_w < p->rx()*1.0f)
                        board_w = p->rx()*1.0f;//max
                    if(board_h > -p->ry()*1.0f)
                        board_h = -p->ry()*1.0f;//min
                }
            }
            glEnd();
        }
        glColor4f(255,255,255,1);
        glBegin(GL_POLYGON);//board
        glNormal3f(0,0,-1);
        glVertex3f(-board_w/10,-(board_h/10),0);
        glVertex3f(-(board_w/10),board_h+(board_h/10),0);
         glVertex3f(board_w+(board_w/10),board_h+(board_h/10),0);
        glVertex3f(board_w+(board_w/10),-(board_h/10),0);
        glEnd();
        glPopMatrix();
    }

}

void YkFont::rander_line(int rotx,int roty, int rotz)
{
    QString spilt_text = QString(text);
    spilt_text.toUtf8();

        glScalef(size*0.02,size*0.02,size*0.02);
        glColor3f(color[0],color[1],color[2]);
        glTranslatef(pos[0],pos[1],pos[2]);

        for(int i=0;i<spilt_text.length();i++)
        {
            glTranslatef(size*2,0,0);

            glPushMatrix();
            glRotatef(rotx/6, 1.0f, 0.0f, 0.0f);

           glPushMatrix();
           // glRotatef(rotz/6, 0.0f, 0.0f, 1.0f);

            glPushMatrix();
             glRotatef(-rotz/6, 0.0f, 1.0f, 0.0f);

           // glutStrokeCharacter(GLUT_STROKE_ROMAN,spilt_text.toAscii().data()[i]);

            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
        }
}
void YkFont::Render(int mode, int rotx,int roty, int rotz,QList<vector_list> *path, QStringList *text_list)
{
    switch(mode)
    {
    case 0 :
        rander_outline(rotx,roty,rotz,path,text_list);
        break;
    case 1 :
        rander_line(rotx,roty, rotz);
         break;
    case 2 :
        rander_paragraph();
         break;
    }

}


