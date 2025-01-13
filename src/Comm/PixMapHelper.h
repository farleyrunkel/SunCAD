// Copyright [2024] SunCAD

#ifndef SRC_COMM_PIXMAPHELPER_H_
#define SRC_COMM_PIXMAPHELPER_H_

#include <QImage>
#include <Image_PixMap.hxx>

class PixMapHelper {

 public: 
	static Handle(Image_PixMap) convertFromBitmap(const QImage& bitmap);
};

#endif  // SRC_COMM_PIXMAPHELPER_H_
