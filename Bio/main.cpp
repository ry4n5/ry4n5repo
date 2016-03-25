//
//  main.cpp
//  Bio
//
//  Created by Ryan Schmitz on 2016-03-24.
//  Copyright © 2016 Ryan Schmitz. All rights reserved.
//

#include <iostream>

#include "World.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    World world;
    
    world.Update();
    return 0;
}
