#include <fstream>
#include "Map.h"

void TestAll(){
    int M;
    int N;
    int count_of_nonzero_elements;

    std::ifstream input1("data1.txt");
    input1 >> M >> N >> count_of_nonzero_elements;
    binary_tree<int> left(M,N);

    for (int i = 0; i < count_of_nonzero_elements; ++i) {
        int row_index;
        int col_index;
        int data;
        input1 >> row_index >> col_index >> data;
        left.insert({row_index,col_index},data);
    }


    std::ifstream input2("data2.txt");
    input2 >> M >> N >> count_of_nonzero_elements;
    binary_tree<int> right(M,N);

    for (int i = 0; i < count_of_nonzero_elements; ++i) {
        int row_index;
        int col_index;
        int data;
        input2 >> row_index >> col_index >> data;
        right.insert({row_index,col_index},data);
    }

    bool flag = true;

    for (int i = 0; i < 3; ++i) {
        if(left.get({i,i}) != i + 1)
            flag = false;
    }
    if(!flag){
        std::cerr << "First input wasn't correct !\n";
        std::exit(0);
    }

    for (int i = 0; i < 3; ++i) {
        if(right.get({i,i}) != i + 1)
            flag = false;
    }
    if(!flag){
        std::cerr << "Second input wasn't correct !\n";
        std::exit(0);
    }

    binary_tree<int> sum = left + right;
    for (int i = 0; i < 3; ++i) {
        if(sum.get({i,i}) != 2 * (i + 1))
            flag = false;
    }
    if(!flag){
        std::cerr << "Sum isn't correct !\n";
        std::exit(0);
    }
    binary_tree<int> diff = left - right;
    for (int i = 0; i < 3; ++i) {
        if(diff.get({i,i}) != 0)
            flag = false;
    }
    if(!flag){
        std::cerr << "Difference isn't correct !\n";
        std::exit(0);
    }

    binary_tree<int> multiplication = left * right;
    for (int i = 0; i < 3; ++i) {
        if(multiplication.get({i,i}) != (i + 1) * (i + 1))
            flag = false;
    }
    if(!flag){
        std::cerr << "Multiplication isn't correct !\n";
        std::exit(0);
    }

    std::cerr << "ALL TESTS OK";
}