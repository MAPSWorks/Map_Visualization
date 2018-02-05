#ifndef YK_FILE_H
#define YK_FILE_H
#include<qstringlist.h>
#include<qfile.h>
#include<qtextstream.h>
#include <QDir>
#include <QCoreApplication>

class YkFile
{
    public:
        QStringList string_list;
        QString string_line;

        YkFile();
        YkFile(QString &name);

        void open_text_file(QString &name);
        void read_line();//���ٷ� ������
        void read_paragraph();//�ܶ� ������

    private:
        QFile *files;
        QDir *testPath;

};


#endif // YK_FILE_H
