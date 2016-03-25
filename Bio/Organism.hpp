//
//  Organism.hpp
//  Bio
//
//  Created by Ryan Schmitz on 2016-03-24.
//  Copyright © 2016 Ryan Schmitz. All rights reserved.
//

#ifndef Organism_hpp
#define Organism_hpp

#include <stdio.h>
#include "Object.hpp"
#include "NeuralNetwork.hpp"

class Organism : public virtual Object {
public:
    
    Organism() : mNeuralNetwork(3, 20, 2) { }
    
    virtual void Update(ObjectsType& rObjects) {
        AssessObjects(rObjects);
    }
    
    void AssessObjects(ObjectsType& rObjects) {
        for(ObjectsType::iterator it = rObjects.begin(); it!= rObjects.end(); ++it) {
            AssessObject(**it);
        }
        MakeDecision();
    }
    
    void AssessObject(Object& rObject) {
        std::vector<float> 
        mNeuralNetwork.SetInput(0, rObject.Type());
        mNeuralNetwork.SetInput(1, rObject.Position().X());
        mNeuralNetwork.SetInput(2, rObject.Position().Y());
        mNeuralNetwork.Run();
    }
    
private:
    void SetupNN () {
        
    }
    
    
    NeuralNetwork   mNeuralNetwork;
    
};


#endif /* Organism_hpp */
