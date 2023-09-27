//
// Created by 丁麓然 on 9/22/23.
//

#ifndef STRING_OPERATION_FRONTEND_H
#define STRING_OPERATION_FRONTEND_H

#include "../datastructure/customlist.h"

namespace interface {
void Welcome();
void Help();
void ShowPage(const custom::list<int> &to_highlight = custom::list<int>());
void SearchWord(const wchar_t *const);
char GetUserInput();
void SwitchInterface(const char);
} // namespace interface

#endif // STRING_OPERATION_FRONTEND_H
