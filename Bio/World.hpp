//
//  World.hpp
//  Bio
//
//  Created by Ryan Schmitz on 2016-03-24.
//  Copyright © 2016 Ryan Schmitz. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <stdio.h>
#include <vector>
#include "Object.hpp"

class World {
public:
    typedef std::vector<Object*> ObjectsType;
    
    World() { }
    
    void Update() {
        for(ObjectsType::iterator it = mObjects.begin(); it!= mObjects.end(); ++it) {
            (*it)->Update(mObjects);
        }
    }
    
private:
    ObjectsType mObjects;
};

#endif /* World_hpp */
