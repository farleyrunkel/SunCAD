// Copyright [2024] SunCAD

#ifndef COMM_LIST_H_
#define COMM_LIST_H_

#include <NCollection_Vector.hxx>

namespace sun 
{

template <class TheItemType>
class List : public NCollection_Vector<TheItemType>
{
public:
    using NCollection_Vector<TheItemType>::NCollection_Vector;

    TheItemType FirstOrDefault() {
        if (this->IsEmpty()) {
            return TheItemType();  // ����Ĭ�Ϲ����ֵ
        }
        try {
            return this->First();  // ���� First() ���׳��쳣
        }
        catch (const std::exception& e) {
            // �����쳣���
            return TheItemType();  // ����Ĭ��ֵ
        }
    }

};


}  // namespace sun

#endif  // COMM_LIST_H_
