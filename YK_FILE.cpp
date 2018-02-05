#include "YK_FILE.h"


YkFile::YkFile()
{
    files = new QFile;
}

YkFile::YkFile(QString &name)
{
   files = new QFile(name);
}

void YkFile::open_text_file(QString &name)
{
   files = new QFile(name);
}

void YkFile::read_line()
{
    if(files->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(files);
        while(!in.atEnd())
        {

           string_line += in.readLine();
        }
    }
    files->close();
}
void YkFile::read_paragraph()
{

    if(files->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(files);
        while(!in.atEnd())
        {

           string_list += in.readLine();
        }
    }
    files->close();

}


//line
//read all while(!EOF)
//chFile - ���ð�����, ����
//fileReset - ������ offset �ʱ�ȭ
//fileOffset(���ڰ�)
