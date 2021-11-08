#include <iostream>
#include <fstream>
#include <math.h>

#include "Map.h"
#include "TimeCheck.h"

int main() {



    int M,N;
    std::cout << "Enter sizes of the first matrix :\n";
    std::cin >> M >> N;
    binary_tree<int> map1(M,N);

    std::cout << "Enter count of non-zero elements :\n";
    int non_zero_elem_count;
    std::cin >> non_zero_elem_count;

    int* data1 = new int[non_zero_elem_count];

    char answer;
    std::cout << "Generate " << non_zero_elem_count << " elements or do input from keyboard ? (1 / 2)\n";
    std::cin >> answer;

    if(answer == '1'){
        for (int i = 0; i < non_zero_elem_count; ++i) {
            data1[i] = rand() % 1000;
        }
    }
    else{
        for (int i = 0; i < non_zero_elem_count; ++i) {
            int tmp;
            std::cin >> tmp;
            data1[i] = tmp;
        }
    }

    int index = 0;
    int a = std::sqrt(non_zero_elem_count);

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            map1.insert({i % a,j % a},data1[index]);//прямоугольное заполнение
            index++;
            if(index >= non_zero_elem_count)
                index = 0;
        }

    }

    std::cout << "Enter sizes of the second matrix :\n";
    std::cin >> M >> N;
    binary_tree<int> map2(M,N);

    std::cout << "Enter count of non-zero elements :\n";
    std::cin >> non_zero_elem_count;

    int* data2 = new int[non_zero_elem_count];
    std::cout << "Generate " << non_zero_elem_count << " elements or do input from keyboard ? (1 / 2)\n";
    std::cin >> answer;
    if(answer == '1'){
        for (int i = 0; i < non_zero_elem_count; ++i) {
            data2[i] = rand() % 1000;
        }
    }
    else{
        for (int i = 0; i < non_zero_elem_count; ++i) {
            int tmp;
            std::cin >> tmp;
            data2[i] = tmp;
        }
    }
    index = 0;
    a = std::sqrt(non_zero_elem_count);

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            map2.insert({i % a,j % a},data2[index]);
            index++;
            if(index >= non_zero_elem_count)
                index = 0;
        }

    }

    std::cout << "First matrix\n";
    map1.print_matrix();
    std::cout << std::endl;
    std::cout << "Second matrix\n";
    map2.print_matrix();
    std::cout << std::endl;


    binary_tree<int> mult = map1 * map2;
    std::cout << "Multiplication\n";
    mult.print_matrix();
    std::cout << std::endl;

    std::cout << "Sum\n";
    binary_tree<int> summ = map1 + map2;
    summ.print_matrix();
    std::cout << std::endl;

    std::cout << "Difference\n";
    binary_tree<int> diff = map1 - map2;
    diff.print_matrix();
    std::cout << std::endl;

    //демонстрация map - reduce
    map1.Map(sqr);
    std::cout << "First matrix after squaring each element :\n";
    map1.print_matrix();

    std::cout << "The sum of the elements of the modified first matrix = " << map1.Reduce(sum) << std::endl;

    return 0;
}
