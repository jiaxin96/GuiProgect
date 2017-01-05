#include <QCoreApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString mStr = "666";
    qDebug() << "Hello word\n" << mStr;
    return a.exec();
}
