// ResourceUtils.h
#ifndef RESOURCEUTILS_H_
#define RESOURCEUTILS_H_

// Qt includes
#include <QString>
#include <QIcon>
#include <QFile>
#include <QDebug>

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

public:
    static bool isResourcePathValid(const QString& resourcePath)
    {
        QFile file(resourcePath);
        return file.exists();
    }
};

#endif // RESOURCEUTILS_H_
