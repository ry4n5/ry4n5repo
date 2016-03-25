//
//  NeuralNetwork.hpp
//  Bio
//
//  Created by Ryan Schmitz on 2016-03-24.
//  Copyright © 2016 Ryan Schmitz. All rights reserved.
//

#ifndef NeuralNetwork_hpp
#define NeuralNetwork_hpp

#include <stdio.h>
#include <vector>
#include <cassert>
#include <cmath>

class NeuralNetwork {
    
public:
    
    typedef float InputType;
    typedef float HiddenType;
    typedef float OutputType;
    typedef float WeightType;
    
    typedef std::vector<InputType> InputsType;
    typedef std::vector<HiddenType> HiddensType;
    typedef std::vector<OutputType> OutputsType;
    typedef std::vector<WeightType> WeightsType;
    
    
    NeuralNetwork(int numInputs, int numHiddens, int numOutputs) {
        mInputs.resize(numInputs);
        mHiddens.resize(numHiddens);
        mOutputs.resize(numOutputs);
        mInputWeights.resize(numInputs * numHiddens);
        mOutputWeights.resize(numOutputs * numHiddens);
        mPrevInputChanges.resize(numInputs * numHiddens);
        mPrevOutputChanges.resize(numOutputs * numHiddens);
        Randomize(mInputWeights);
        Randomize(mOutputWeights);
    }
    
    
    void FeedForward(InputsType& rInputs) {
        assert(rInputs.size() == mInputs.size());
        mInputs = rInputs;
        WeightsType::iterator in_weight_it = mInputWeights.begin();
        for(HiddensType::iterator hidden_it = mHiddens.begin(); hidden_it!= mHiddens.end(); ++hidden_it) {
            float sum = 0.f;
            for(InputsType::iterator input_it = mInputs.begin(); input_it!= mInputs.end(); ++input_it) {
                sum += (*input_it) * (*in_weight_it++);
            }
            *hidden_it = ApplySigmoid(sum);
        }
        
        WeightsType::iterator out_weight_it = mOutputWeights.begin();
        for(OutputsType::iterator output_it = mOutputs.begin(); output_it!= mOutputs.end(); ++output_it) {
            float sum = 0.f;
            for(HiddensType::iterator hidden_it = mHiddens.begin(); hidden_it!= mHiddens.end(); ++hidden_it) {
                sum += (*hidden_it) * (*out_weight_it++);
            }
            *output_it = ApplySigmoid(sum);
        }
    }
    
    float PropagateBackwards(OutputsType& rTargetOutputs, float N, float M) { // wtf are these variables?
        assert(rTargetOutputs.size() == mOutputs.size());
        // calculate output deltas
        std::vector<OutputType> output_deltas(mOutputs.size());
        OutputsType::iterator target_it = rTargetOutputs.begin();
        for(OutputsType::iterator output_it = mOutputs.begin(); output_it!= mOutputs.end(); ++output_it) {
            OutputType error_val = (*target_it++) - (*output_it);
            output_deltas.push_back(error_val * ApplyDerivativeSigmoid(*output_it++));
        }
        
        // update output weights
        WeightsType::iterator out_weight_it = mOutputWeights.begin();
        WeightsType::iterator prev_out_change_it = mPrevOutputChanges.begin();
        for(OutputsType::iterator output_it = output_deltas.begin(); output_it!= output_deltas.end(); ++output_it) {
            for(HiddensType::iterator hidden_it = mHiddens.begin(); hidden_it!= mHiddens.end(); ++hidden_it) {
                WeightType change = (*output_it) * (*hidden_it);
                *out_weight_it++ += N * change + M * (*prev_out_change_it);
                *prev_out_change_it++ = change;
            }
        }
        
        // calc hidden deltas
        std::vector<HiddenType> hidden_deltas(mHiddens.size());
        out_weight_it = mOutputWeights.begin();
        for(OutputsType::iterator output_it = output_deltas.begin(); output_it!= output_deltas.end(); ++output_it) {
            for(HiddensType::iterator hidden_it = hidden_deltas.begin(); hidden_it!= hidden_deltas.end(); ++hidden_it) {
                *hidden_it += (*output_it) * (*out_weight_it++);
            }
        }
        HiddensType::iterator hiddens_it = mHiddens.begin();
        for(HiddensType::iterator hidden_it = hidden_deltas.begin(); hidden_it!= hidden_deltas.end(); ++hidden_it) {
            *hidden_it *= ApplyDerivativeSigmoid(*hiddens_it++);
        }
        
        // update input weights
        WeightsType::iterator in_weight_it = mInputWeights.begin();
        WeightsType::iterator prev_in_change_it = mPrevInputChanges.begin();
        for(HiddensType::iterator hidden_it = hidden_deltas.begin(); hidden_it!= hidden_deltas.end(); ++hidden_it) {
            for(InputsType::iterator input_it = mInputs.begin(); input_it!= mInputs.end(); ++input_it) {
                float change = (*hidden_it) * (*input_it);
                (*in_weight_it++) = N * change + M * (*prev_in_change_it);
                (*prev_in_change_it++) = change;
            }
        }
        
        // calc combined error
        // 1/2 for differential convenience & **2 for modulus
        float error_val(0.f);
        OutputsType::iterator output_it = mOutputs.begin();
        for(OutputsType::iterator target_it = rTargetOutputs.begin(); target_it!= rTargetOutputs.end(); ++target_it) {
            error_val += 0.5f * powf((*target_it) - (*output_it++), 2);
        }
        
        return error_val;
    }
    
    void Randomize(std::vector<float>& rBuffer) {
        for(std::vector<float>::iterator it = rBuffer.begin(); it!= rBuffer.end(); ++it) {
            *it = (float)rand() / RAND_MAX;
        }
    }
    
    
private:
    float ApplySigmoid(float value) {
        return tanh(value);
    }
    
    float ApplyDerivativeSigmoid(float value) {
        return (1 - pow(value, 2));
    }
    
    InputsType  mInputs;
    HiddensType mHiddens;
    OutputsType mOutputs;
    WeightsType mInputWeights;
    WeightsType mOutputWeights;
    WeightsType mPrevInputChanges;
    WeightsType mPrevOutputChanges;
};

#endif /* NeuralNetwork_hpp */
