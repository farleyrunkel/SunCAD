// ResourceUtils.h
#ifndef RESOURCEUTILS_H_
#define RESOURCEUTILS_H_

// Qt includes
#include <QString>
#include <QIcon>
#include <QFile>
#include <QImage>

class ResourceUtils
{
public:
    static constexpr const char* ICON_PATH_PREFIX = "://icons/";

    static QString iconPath(const QString& iconName)
    {
        return QString("%1%2.svg").arg(ICON_PATH_PREFIX, iconName);
    }

    static QIcon icon(const QString& iconName)
    {
        return QIcon(iconPath(iconName));
    }

    static QString GetResourceUri(const QString& filename)
    {
        return assemblyName().append(filename);
    }

    static QImage readBitmapFromResource(const QString& filename)
    {
        return QImage(GetResourceUri(filename));
    }


public:
    static bool isResourcePathValid(const QString& resourcePath)
    {
        QFile file(resourcePath);
        return file.exists();
    }

private:
    static QString assemblyName()
    {
        return ":/";
    };
};

#endif // RESOURCEUTILS_H_
