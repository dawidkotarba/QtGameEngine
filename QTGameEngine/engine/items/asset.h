#ifndef ASSET_H
#define ASSET_H
#include <QString>

class Asset {

public:
    Asset(const QString& assetPath):
        path(assetPath),
        imgPattern(""),
        imgCount(1),
        imgExtension(".png"){
        qDebug() << "Asset path: " << assetPath;
    }

    Asset(const QString& assetPath, int assetImgCount):
        Asset(assetPath){
        imgCount = assetImgCount;

        if (assetImgCount > 1)
            imgPattern = "img";

        qDebug() << "Updated asset img count: " << assetImgCount;
    }

    Asset(const QString& assetPath, const QString& assetImgPattern, const QString& assetImgExtension, int assetImgCount):
        Asset(assetPath, assetImgCount){
        imgExtension = assetImgExtension;
        imgPattern = assetImgPattern;
        qDebug() << "Updated asset path: " << assetPath << assetImgPattern << assetImgExtension;
    }

    QString getPath(){return path;}
    QString getImgPattern(){return imgPattern;}
    int getImgCount(){return imgCount;}
    QString getImgExtension(){return imgExtension;}

private:
    QString path;
    QString imgPattern;
    int imgCount;
    QString imgExtension;
};

#endif // ASSET_H
