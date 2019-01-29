//
//  main.cpp
//  testing
//
//  Created by Zui Chen on 1/29/19.
//  Copyright © 2019 Zui Chen. All rights reserved.
//

#include <iostream>
//using namespace std
int main() {
    // all even numbers from 1 to 100 backwards
    for (int i=100; i>1; i-=2) {
        // print except 44
        if (i != 44){
            std::cout << i << std::endl;
        }
    }
    return 0; // return object matches the type declared in front of main 
    //void main doesn't return anything
}

