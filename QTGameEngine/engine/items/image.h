#ifndef IMAGE_H
#define IMAGE_H
#include <QObject>
#include <QImage>

class Image : public QObject, public QImage
{
    Q_OBJECT
public:
    explicit Image(QObject *parent = 0):QObject(parent){}
    Image(const QString& imgName):QImage(imgName){}

signals:

public slots:

};

#endif // IMAGE_H
