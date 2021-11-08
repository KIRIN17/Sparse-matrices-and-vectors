#pragma once



template<typename T>
void sqr(tree_elem <T> *curr) {//(äëÿ Map)
    curr->DATA = curr->DATA * curr->DATA;
}

template<typename T>
bool is_more_than_25(tree_elem <T> *curr) {
    if (curr->DATA >= 25)
        return true;
    return false;
}

template<typename T>
T sum(tree_elem <T> *curr, T curr_sum) {
    return curr_sum + curr->DATA;
}

void MapRecursivelyFunction(void(*func)(tree_elem <T> *), tree_elem <T> *curr) {
    if (curr) {
        MapRecursivelyFunction(func, curr->M_LEFT);
        func(curr);
        MapRecursivelyFunction(func, curr->M_RIGHT);
    }
}

void WhereRecursivelyFunction(bool(*func)(tree_elem <T> *), tree_elem <T> *curr) {
    if (curr) {
        WhereRecursivelyFunction(func, curr->M_LEFT);

        if (func(curr)) {
            delete_elem(curr->DATA);
        }

        WhereRecursivelyFunction(func, curr->M_RIGHT);
    }
}

void ReduceRecursivelyFunction(T(*func)(tree_elem <T> *, T), tree_elem <T> *curr, T &curr_sum) {
    if (curr) {
        ReduceRecursivelyFunction(func, curr->M_LEFT, curr_sum);
        curr_sum = func(curr, curr_sum);
        ReduceRecursivelyFunction(func, curr->M_RIGHT, curr_sum);
    }
}

//map,where,reduce
void Map(void(*func)(tree_elem <T> *)) {//íåîáõîäèìî çàäàòü curr,ïîýòîìó ñîçäàíà âñïîìîãàòåëüíàÿ ôóíêöèÿ
    tree_elem <T> *curr = m_root;
    MapRecursivelyFunction(func, curr);
}

void Where(bool(*func)(tree_elem <T> *)) {//íåîáõîäèìî çàäàòü curr,ïîýòîìó ñîçäàíà âñïîìîãàòåëüíàÿ ôóíêöèÿ
    tree_elem <T> *curr = m_root;
    WhereRecursivelyFunction(func, curr);
}

T Reduce(T(*func)(tree_elem <T> *, T)) {
    tree_elem <T> *curr = m_root;
    T curr_sum = 0;
    ReduceRecursivelyFunction(func, curr, curr_sum);
    return curr_sum;
}