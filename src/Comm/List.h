// Copyright [2024] SunCAD

#ifndef COMM_LIST_H_
#define COMM_LIST_H_

#include <NCollection_List.hxx>

namespace sun {

template <class TheItemType>
class List : public NCollection_List<TheItemType> 
{
public:

};


}  // namespace sun

#endif  // COMM_LIST_H_
