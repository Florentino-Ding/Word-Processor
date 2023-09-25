//
// Created by 丁麓然 on 9/22/23.
//

#ifndef STRING_OPERATION_STRINGOPERATION_H
#define STRING_OPERATION_STRINGOPERATION_H

#include "../datastructure/customlist.h"
#include "../datastructure/customstring.h"

namespace custom {
void OpenFile(list<string> &, const string &);
void CreateFile(const string &);
void OverwriteFile(const list<string> &, const string &);
} // namespace custom

#endif // STRING_OPERATION_STRINGOPERATION_H
