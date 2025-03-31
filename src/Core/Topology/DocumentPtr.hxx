// Copyright [2024] SunCAD

#ifndef DocumentPtr_H_
#define DocumentPtr_H_

#include <TDocStd_Document.hxx>
#include "Comm/OccHandle.hxx"

class Document;
DEFINE_STANDARD_HANDLE(Document, TDocStd_Document)
using DocumentPtr = OccHandle<Document>;

#endif  // DocumentPtr_H_
