#ifndef NN_NODE_H
#define NN_NODE_H

#include "NN_Type.h"

NN_Object NN_NodeAllocInit( size_t inputNum, NN_ActiveFunc activeFunc, NN_DerivActive derivFunc );

NN_Var NN_NodeRun( NN_Object obj, const NN_Var *befoOut );

void NN_NodeLearn( NN_Object obj, NN_Var erSum, const NN_Var *befoOut, NN_Var learnRate );

NN_Var NN_NodeCulcEr( NN_Object obj, size_t weightIndex );

#endif /*NN_NODE_H*/