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
            return TheItemType();  // 返回默认构造的值
        }
        try {
            return this->First();  // 假设 First() 不抛出异常
        }
        catch (const std::exception& e) {
            // 处理异常情况
            return TheItemType();  // 返回默认值
        }
    }

};


}  // namespace sun

#endif  // COMM_LIST_H_
