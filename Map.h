#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Balance.h"
#include "Functions.h"
template<typename T>
T sqr(tree_elem <T> *curr) {//(äëÿ Map)
    return curr->DATA * curr->DATA;
}
template<typename T>
T sum(tree_elem<T>* curr,T curr_sum){//(для Reduce)
    return curr_sum + curr->DATA;
}
template<typename T>
class binary_tree {
private:
    tree_elem<T> *m_root;
    int size;

    void Map_help(T(*func)(tree_elem<T>*),tree_elem<T>* curr,binary_tree<T>& res){//для рекурсивного выполнения Map
        if(curr){
            Map_help(func ,curr->M_LEFT,res);
            res.insert(curr->indices,func(curr));
            Map_help(func,curr->M_RIGHT,res);
        }
    }

    void Reduce_help(T(*func)(tree_elem<T>*,T),tree_elem<T>* curr,T& curr_sum){//для рекурсивного выполнения Reduce
        if(curr){
            Reduce_help(func,curr->M_LEFT,curr_sum);
            curr_sum = func(curr,curr_sum);
            Reduce_help(func,curr->M_RIGHT,curr_sum);
        }
    }

    void upgrade_sub_tree(binary_tree<T> *result, tree_elem<T> *curr) {
        if (curr) {
            upgrade_sub_tree(result, curr->M_LEFT);
            result->insert(curr->DATA);
            upgrade_sub_tree(result, curr->M_RIGHT);
        }
    }

    void tree_to_stringRecursivelyFunction(tree_elem<T> *curr, std::vector<std::string> &curr_str) {
        if (curr) {
            tree_to_stringRecursivelyFunction(curr->M_LEFT, curr_str);
            curr_str.push_back(std::to_string(curr->DATA));
            tree_to_stringRecursivelyFunction(curr->M_RIGHT, curr_str);
        }
    }

    void print_tree(tree_elem<T> *curr) {
        if (curr) {
            print_tree(curr->M_LEFT);
            std::cout << curr->indices << " : " << curr->DATA << std::endl;
            print_tree(curr->M_RIGHT);
        }
    }

    void print_matrix_req(T** values,tree_elem<T>* curr){
        if(curr){
            print_matrix_req(values,curr->M_LEFT);
            values[curr->indices.first][curr->indices.second] = curr->DATA;
            print_matrix_req(values,curr->M_RIGHT);
        }
    }

public:
    const int rows_count;
    const int columns_count;

    T get(const Pair<int,int>& indices) const{

        tree_elem<T>* curr = m_root;
        while (curr){
            if(curr->indices != indices){
                if(curr->indices > indices){
                    curr = curr->M_LEFT;
                } else
                    curr = curr->M_RIGHT;
            }else
                return curr->DATA;
        }
        return T();
    }

    void print_matrix(){
        int M = rows_count;
        int N = columns_count;
        T** values = new T*[M];
        for (int i = 0; i < M; ++i) {
            values[i] = new T[N];
            for (int j = 0; j < N; ++j) {
                values[i][j] = T();
            }
        }
        print_matrix_req(values,m_root);
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                std::cout << values[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }

    binary_tree() : rows_count(0),columns_count(0){
        m_root = nullptr;
        size = 0;
    }

    binary_tree(int m,int n) : rows_count(m),columns_count(n){
        m_root = nullptr;
        size = 0;
    }

    binary_tree(const Pair<int,int>& indices,int data,int m,int n) : rows_count(m),columns_count(n){
        m_root = new tree_elem<T>(indices,data);
        size = 1;
    }

    int get_size() { return size; }

    void tree_height() {
        std::cout << height(m_root);
    }

    void print() {
        print_tree(m_root);
        std::cout << std::endl;
    }


    bool find(const Pair<int,int>& indices) {

        tree_elem<T> *curr = m_root;
        while (curr && curr->indices != indices) {
            if (curr->indices > indices)
                curr = curr->M_LEFT;
            else
                curr = curr->M_RIGHT;
        }
        return (bool) curr;
    }


    void insert(const Pair<int,int>& indices,int data) {
        if (m_root == nullptr) {
            m_root = new tree_elem<T>(indices,data);
            size = 1;
        } else {
            tree_elem<T> *curr = m_root;
            while (curr && curr->indices != indices) {
                if (curr->indices > indices) {
                    if (curr->M_LEFT)
                        curr = curr->M_LEFT;
                    else {
                        curr->M_LEFT = new tree_elem<T>(indices,data);
                        m_root = balance(m_root);
                        size++;
                        return;
                    }
                } else {
                    if (curr->M_RIGHT)
                        curr = curr->M_RIGHT;
                    else {
                        curr->M_RIGHT = new tree_elem<T>(indices,data);
                        m_root = balance(m_root);
                        size++;
                        return;
                    }
                }
            }
        }
    }


    void delete_elem(T key) {

        tree_elem<T> *curr = m_root;
        tree_elem<T> *prev = nullptr;

        while (curr && curr->DATA != key) {
            prev = curr;
            if (curr->DATA > key) {
                curr = curr->M_LEFT;
            } else
                curr = curr->M_RIGHT;
        }
        if (!curr)
            return;


        if (prev->M_RIGHT == curr) {
            if (curr->M_RIGHT == nullptr && curr->M_LEFT == nullptr) {
                prev->M_RIGHT = nullptr;
                delete[] curr;
                size--;
                return;
            }
            if (curr->M_LEFT == nullptr) {
                prev->M_RIGHT = curr->M_RIGHT;
                delete[] curr;
                size--;
                return;
            }
            if (curr->M_RIGHT == nullptr) {
                prev->M_RIGHT = curr->M_LEFT;
                delete[] curr;
                size--;
                return;
            }
        }

        if (prev->M_LEFT == curr) {
            if (curr->M_RIGHT == nullptr && curr->M_LEFT == nullptr) {
                prev->M_LEFT = nullptr;
                delete[] curr;
                size--;
                return;
            }
            if (curr->M_LEFT == nullptr) {
                prev->M_LEFT = curr->M_RIGHT;
                delete[] curr;
                size--;
                return;
            }
            if (curr->M_RIGHT == nullptr) {
                prev->M_LEFT = curr->M_LEFT;
                delete[] curr;
                size--;
                return;
            }
        }

        tree_elem<T> *tmp = curr->M_RIGHT;
        while (tmp->M_LEFT)
            tmp = tmp->M_LEFT;

        T minimum = tmp->DATA;


        if (prev->M_LEFT == curr) {
            delete_elem(tmp->DATA);
            prev->M_LEFT = new tree_elem<T>(minimum, curr->M_LEFT, curr->M_RIGHT);
            delete[] curr;
            size--;
            return;
        }
        if (prev->M_RIGHT == curr) {
            delete_elem(tmp->DATA);
            prev->M_RIGHT = new tree_elem<T>(minimum, curr->M_LEFT, curr->M_RIGHT);
            delete[] curr;
            size--;
            return;
        }
    }


    std::string tree_to_string() const{

        tree_elem<T> *curr = m_root;
        std::vector<std::string> result;
        tree_to_stringRecursivelyFunction(curr, result);

        std::string result_str = "";
        for (int i = 0; i < result.size(); ++i) {
            result_str += result[i] + " ";
        }
        return result_str;
    }
    void is_balanced() {

        std::vector<int> h;
        curr_balance(m_root, h);
        for (int i = 0; i < size; ++i) {
            std::cout << h[i] << " ";
        }
        std::cout << std::endl;
    }

    void curr_balance(tree_elem<T> *curr, std::vector<int> &h) {
        if (curr) {
            curr_balance(curr->M_LEFT, h);
            h.push_back(diff(curr));
            curr_balance(curr->M_RIGHT, h);
        }

    }

    T& operator [](const Pair<int,int>& indices){
        return this->get(indices);
    }

    //map, reduce
    binary_tree<T> Map(T(*func)(tree_elem<T>*)){//необходимо задать curr,поэтому создана вспомогательная функция
        tree_elem<T>* curr = m_root;

        binary_tree<T> res(rows_count,columns_count);
        res.insert(curr->indices,func(curr));

        Map_help(func,curr,res);

        return res;
    }

    T Reduce(T(*func)(tree_elem<T>*,T)){
        tree_elem<T>* curr = m_root;
        T curr_sum = 0;
        Reduce_help(func,curr,curr_sum);
        return curr_sum;
    }

    binary_tree<T> operator *(binary_tree<T>& matrix){
        //левая матрица - this
        //правая матрица - matrix

        int M = this->rows_count;
        int K = this->columns_count;
        int N = matrix.columns_count;

        if(K != matrix.rows_count)
            return binary_tree<T>();

        binary_tree<T> res(M,N);
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                T tmp = T();
                for (int k = 0; k < K; ++k) {
                    if(this->find({i,k}) && matrix.find({k,j}))
                        tmp += this->get({i,k}) * matrix.get({k,j});
                }
                if(tmp != T())
                    res.insert({i,j},tmp);
            }
        }
        return res;
    }

    binary_tree<T> operator +(binary_tree<T>& matrix){
        if(matrix.columns_count != this->columns_count || matrix.rows_count != this->rows_count)
            return binary_tree<T>();
        int M = matrix.rows_count;
        int N = matrix.columns_count;
        binary_tree<T> res(M,N);
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                res.insert({i,j},this->get({i,j}) + matrix.get({i,j}));
            }
        }
        return res;
    }

    binary_tree<T> operator -(binary_tree<T>& matrix){
        if(matrix.columns_count != this->columns_count || matrix.rows_count != this->rows_count)
            return binary_tree<T>();
        int M = matrix.rows_count;
        int N = matrix.columns_count;
        binary_tree<T> res(M,N);
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                res.insert({i,j},this->get({i,j}) - matrix.get({i,j}));
            }
        }
        return res;
    }
};





