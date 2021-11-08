#pragma once
#include "Map.h"



//==============================================
std::string is_balanced_str() {
    std::vector<std::string> h;
    std::string res = "";
    curr_balance_str(m_root, h);
    for (int i = 0; i < size; ++i) {
        res += h[i] + " ";
    }
    return res;
}

void curr_balance_str(tree_elem<T> *curr, std::vector<std::string> &h) {
    if (curr) {
        curr_balance_str(curr->M_LEFT, h);
        h.push_back(std::to_string(diff(curr)));
        curr_balance_str(curr->M_RIGHT, h);
    }

}