#ifndef NN_NERVE_H
#define NN_NERVE_H

#include "NN_Type.h"

NN_Object NN_NerveAllocInit( size_t inputDataNum, size_t layerNum );

void NN_NerveAppendLayer( NN_Object obj, size_t nodeNum, NN_ActiveFunc activeFunc, NN_DerivActive derivFunc);

size_t NN_NerveRun( NN_Object obj, const NN_Var *inputData, NN_Var *output );

void NN_NerveLearn( NN_Object obj, const NN_Var *teacher, NN_Var learn_rate );

#endif /*NN_NERVE_H*/