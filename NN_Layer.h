#ifndef NN_LAYRE_H
#define NN_LAYRE_H

#include "NN_Type.h"


NN_Object NN_LayerAllocInit( size_t inputNum, size_t nodeNum, NN_ActiveFunc activeFunc, NN_DerivActive derivFunc );

size_t NN_LayerGetNodeNum( NN_Object obj );

void NN_LayerRun( NN_Object obj, const NN_Var *befoLayer );

const NN_Var* NN_LayerBefoOut( NN_Object obj );

void NN_LayerLearn( NN_Object obj, NN_Object aftLayer, const NN_Var *befoLayer, NN_Var learnRate );
void NN_LayerLearnTeacher(NN_Object obj, const NN_Var *aftLayer, const NN_Var *befoLayer, NN_Var learnRate);

NN_Var NN_LayerCulcErSum( NN_Object obj, size_t weightIndex );

#endif NN_LAYRE_H