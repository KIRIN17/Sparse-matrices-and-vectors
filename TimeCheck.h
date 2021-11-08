#include <time.h>
#include <fstream>
#include "Map.h"

void TestSum(){
    int Size = 100;

    std::fstream out;
    out.open("Multiplication.txt");

    for (int i = 1; i <= 10; i += 1) {

        int* data1 = new int[i * i];
        for (int j = 0; j < i * i; ++j) {
            data1[i] = rand() % 1000;
        }

        binary_tree<int> a(Size,Size);
        int index = 0;
        for (int j = 0; j < i * i; ++j) {
            for (int k = 0; k < i * i; ++k) {
                a.insert({j % i,k % i},data1[index]);
                ++index;
                if(index >= i * i)
                    index = 0;
            }
        }

        binary_tree<int> b(Size,Size);
        index = 0;
        for (int j = 0; j < i * i; ++j) {
            for (int k = 0; k < i * i; ++k) {
                b.insert({j % i,k % i},data1[index]);
                ++index;
                if(index >= i * i)
                    index = 0;
            }
        }

        unsigned int start = clock();
        binary_tree<int> c = a * b;
        unsigned int finish = clock();
        out << finish - start << ' ';
        std::cout << i;
    }
}
