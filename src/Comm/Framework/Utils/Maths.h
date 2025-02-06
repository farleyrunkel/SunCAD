#ifndef COMM_FRAMEWORK_UTILS_MATHS_H_
#define COMM_FRAMEWORK_UTILS_MATHS_H_

// stl includes
#include <cmath>

// Qt includes
#include <QtGlobal>
#include <QString>
#include <QDebug>

class Maths 
{
public:
    // �ǶȺͻ�����س���
    static constexpr double DoublePI = M_PI * 2.0;
    static constexpr double HalfPI = M_PI / 2.0;
    static constexpr double PI = M_PI;
    static constexpr double DegRadMultiplier = 180.0 / M_PI;

    // ��ȡ�����þ���
    static int precision() {
        return _precision;
    }
    static void setPrecision(int value) {
        _precision = value;
        _precisionFormatString = QString("F%1").arg(_precision);
    }

    static QString precisionFormatString() {
        return _precisionFormatString;
    }

    // �Ƕȹ�һ������λ���ȣ�
    static double normalizeAngleDegree(double value) {
        if (value >= 360.0)
            return std::fmod(value, 360.0);
        if (value < 0.0) {
            value = std::fmod(value, 360.0);
            if (value < 0.0)
                value += 360.0;
        }
        return value;
    }

    static double normalizeAngleDegree(double value, double min, double max) {
        Q_ASSERT(max - min >= 360.0);

        while (value >= max)
            value -= 360.0;
        while (value < min)
            value += 360.0;
        return value;
    }

    // �Ƕȹ�һ������λ�����ȣ�
    static double normalizeAngleRad(double value) {
        if (value >= DoublePI)
            return std::fmod(value, DoublePI);
        if (value < 0.0) {
            value = std::fmod(value, DoublePI);
            if (value < 0.0)
                value += DoublePI;
        }
        return value;
    }

    static double normalizeAngleRad(double value, double min, double max) {
        Q_ASSERT(max - min >= DoublePI);

        while (value >= max)
            value -= DoublePI;
        while (value < min)
            value += DoublePI;
        return value;
    }

    // ȡ��ӽ���ָ�����ֵ
    static double roundToNearest(double value, double divider) {
        return std::round(value / divider) * divider;
    }

private:
    static inline int _precision = 3;
    static inline QString _precisionFormatString = "F3";
};

#endif  // COMM_FRAMEWORK_UTILS_MATHS_H_