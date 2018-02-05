#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
typedef QList<QVector3D> vector_list;

///****************************/
class SlippyMap;
class YkFont;
class YkFile;
class QVector3D;
class YkPath;
///****************************/

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();
    ///****************************/
    void setCenter(qreal lat, qreal lng);
    void drew_path();
    ///****************************/






public slots:
    ///****************************/
    void updateMap(const QRect &r);
    void size_slot(int f_size);
    void font_slot(QString f_font);
    void path_slot(QString path_num);
    void r_slot(int r);
    void g_slot(int g);
    void b_slot(int b);
    void opacity_slot(int o);
   void itimer_slot();
    ///****************************/

    signals:
        void size_signal(int f_size);
        void font_signal(QString f_font);
        void path_signal(QString path_num);
        void r_signal(int r);
        void g_signal(int g);
        void b_signal(int b);
        void opacity_signal(int o);

protected:

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void drawCube(GLfloat sx, GLfloat sy, GLfloat sz, GLfloat width, GLfloat height, GLfloat depth);
    void CalculateVectorNormal(	GLfloat fVert1[], GLfloat fVert2[], GLfloat fVert3[], GLfloat *fNormalX, GLfloat *fNormalY, GLfloat *fNormalZ);
    ///****************************/
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *event);
    ///****************************/

private:
    QPoint lastPos;
    QColor defaultColor;


///****************************/
    SlippyMap *m_normalMap;
    bool left_button;
    bool right_button;
    bool middle_button;

    bool pressed;
    bool snapped;

    QTimer *itimer;
    QPoint pressPos;
    QPoint dragPos;

    int disx;
    int disy;
    int rotx;
    int roty;
    int rotz;
    int transx;
    int transy;
    int posx;
    int posy;
   float ani_time;

   QList<vector_list> *path;
   QStringList text_list;

    GLfloat opacity;

    bool invert;
    bool zoomed;
    int fSize;
    QImage MapImage;
///****************************/
    YkFont *YKFont;
    YkFile *YKFile;
    YkPath *YKPath;
    YkPath *YKPath2;
    YkPath *YKPath3;
 //   QList<vector_list> list_path;
///****************************/
};


#endif
