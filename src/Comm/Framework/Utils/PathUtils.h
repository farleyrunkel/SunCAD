#ifndef COMM_FRAMEWORK_UTILS_PATHUTILS_H_
#define COMM_FRAMEWORK_UTILS_PATHUTILS_H_

#include <QString>
#include <QStringList>
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>
#include <QTextStream>
#include <QCoreApplication>
#include <QFileInfoList>
#include <QFile>

class PathUtils {
public:
    //--------------------------------------------------------------------------------------------------

    /// <summary>
    /// Creates a relative path from one file or folder to another.
    /// </summary>
    static QString MakePathRelative(const QString& fromDirectory, const QString& toPath) {
        if (fromDirectory.isEmpty() || toPath.isEmpty()) {
            return toPath;  // or throw exception based on the application needs
        }

        bool isRooted = QDir::isAbsolutePath(fromDirectory) && QDir::isAbsolutePath(toPath);
        if (isRooted) {
            QString fromRoot = QFileInfo(fromDirectory).absolutePath();
            QString toRoot = QFileInfo(toPath).absolutePath();

            if (fromRoot != toRoot)
                return toPath; // Paths have different roots, return the original target path
        }

        QStringList fromDirs = fromDirectory.split(QDir::separator(), Qt::SkipEmptyParts);
        QStringList toDirs = toPath.split(QDir::separator(), Qt::SkipEmptyParts);

        int commonRootIndex = -1;

        // Find common root
        int length = std::min(fromDirs.size(), toDirs.size());
        for (int i = 0; i < length; ++i) {
            if (fromDirs[i].compare(toDirs[i], Qt::CaseInsensitive) != 0)
                break;

            commonRootIndex = i;
        }

        if (commonRootIndex == -1)
            return toPath; // No common root, return the full target path

        QStringList relativePath;

        // Add ".." for each directory in the from path after the common root
        for (int i = commonRootIndex + 1; i < fromDirs.size(); ++i) {
            relativePath.append("..");
        }

        // Add the remaining directories from the to path
        for (int i = commonRootIndex + 1; i < toDirs.size(); ++i) {
            relativePath.append(toDirs[i]);
        }

        // Join the relative parts
        return relativePath.join(QDir::separator());
    }

    //--------------------------------------------------------------------------------------------------

    /// <summary>
    /// Converts a relative path to an absolute path based on the root directory.
    /// </summary>
    static QString MakePathAbsolute(const QString& rootDirectory, const QString& relativePath) {
        if (QDir::isAbsolutePath(relativePath)) {
            return relativePath;
        }
        return QDir(rootDirectory).absoluteFilePath(relativePath);
    }

    //--------------------------------------------------------------------------------------------------

    /// <summary>
    /// Returns the directory where the application executable is located.
    /// </summary>
    static QString GetAppExecutableDirectory() {
        return QCoreApplication::applicationDirPath();
    }

    //--------------------------------------------------------------------------------------------------

    /// <summary>
    /// Returns the local application data directory for the current user.
    /// </summary>
    static QString GetLocalAppDataDirectory() {
        return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + QDir::separator() + "Macad" + QDir::separator();
    }

    //--------------------------------------------------------------------------------------------------

    /// <summary>
    /// Extracts the file extension without the dot.
    /// </summary>
    static QString GetExtensionWithoutPoint(const QString& path) {
        QString ext = QFileInfo(path).suffix();
        return ext;
    }

    //--------------------------------------------------------------------------------------------------

    /// <summary>
    /// Extracts the filename without extension and without a trailing dot.
    /// </summary>
    static QString GetFilenameWithoutExtensionAndPoint(const QString& path, bool fullPath) {
        QFileInfo fileInfo(path);
        QString filename = fileInfo.completeBaseName();  // Base name without extension

        if (fullPath) {
            filename = fileInfo.dir().absolutePath() + QDir::separator() + filename;
        }

        if (!filename.isEmpty() && filename.endsWith('.')) {
            filename.chop(1);  // Remove trailing dot if present
        }

        return filename;
    }

    //--------------------------------------------------------------------------------------------------

    /// <summary>
    /// Splits a path into individual directories.
    /// </summary>
    static QStringList SplitPath(const QString& path) {
        return path.split(QDir::separator(), Qt::SkipEmptyParts);
    }

    //--------------------------------------------------------------------------------------------------

    /// <summary>
    /// Checks if a path is a subpath of the specified base directory.
    /// </summary>
    static bool IsSubPathOf(const QString& path, const QString& baseDirPath) {
        QString normalizedPath = WithTrailingDirectorySeparator(QDir::toNativeSeparators(QFileInfo(path).absoluteFilePath()));
        QString normalizedBaseDirPath = WithTrailingDirectorySeparator(QDir::toNativeSeparators(QFileInfo(baseDirPath).absoluteFilePath()));

        return normalizedPath.startsWith(normalizedBaseDirPath, Qt::CaseInsensitive);
    }

    //--------------------------------------------------------------------------------------------------

    /// <summary>
    /// Ensures the path has a trailing directory separator.
    /// </summary>
    static QString WithTrailingDirectorySeparator(const QString& path) {
        if (path.isEmpty()) {
            return path;
        }

        if (!path.endsWith(QDir::separator())) {
            return path + QDir::separator();
        }

        return path;
    }
};

#endif // COMM_FRAMEWORK_UTILS_PATHUTILS_H_
