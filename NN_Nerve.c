#include "NN_Nerve.h"
#include "NN_Layer.h"

struct NN_Nerve {
	size_t inputDataNum;
	
	size_t layerNum;
	size_t layerAppendCount;
	NN_Object *layers;
};

NN_Object NN_NerveAllocInit( size_t inputDataNum, size_t layerNum )
{
	struct NN_Nerve *_obj = (struct NN_Nerve*)malloc( sizeof( struct NN_Nerve ) );

	_obj->inputDataNum = inputDataNum;
	_obj->layerNum = layerNum;
	_obj->layerAppendCount = 0;
	_obj->layers = (NN_Object*)malloc( sizeof( NN_Object )*_obj->layerNum);
}

void NN_NerveAppendLayer( NN_Object obj, size_t nodeNum, NN_ActiveFunc activeFunc, NN_DerivActive derivFunc )
{
	struct NN_Nerve *_obj = (struct NN_Nerve*)obj;

	size_t inputNum = 0;
	if ( _obj->layerAppendCount == 0 )
	{
		inputNum = _obj->inputDataNum;
	}else {
		inputNum = NN_LayerGetNodeNum( _obj->layers[_obj->layerAppendCount-1] );
	}

	_obj->layers[_obj->layerAppendCount] = NN_LayerAllocInit( inputNum, nodeNum, activeFunc, derivFunc );
	_obj->layerAppendCount++;
}


size_t NN_NerveRun( NN_Object obj, const NN_Var *inputData, NN_Var *output )
{
	struct NN_Nerve *_obj = (struct NN_Nerve*)obj;

	NN_LayerRun( _obj->layers[0], inputData );

	for ( size_t layerIndex=1; layerIndex<_obj->layerNum; layerIndex++ )
	{
		NN_LayerRun( _obj->layers[layerIndex], NN_LayerBefoOut( _obj->layers[layerIndex-1] ) );
	}
	
	size_t outputNum = NN_LayerGetNodeNum(_obj->layers[_obj->layerNum]);
	memcpy( output, NN_LayerBefoOut( _obj->layers[_obj->layerNum] ), sizeof( NN_Var )*outputNum);
	return outputNum;
}


void NN_NerveLearn( NN_Object obj, const NN_Var *teacher)
{
	struct NN_Nerve *_obj = (struct NN_Nerve*)obj;

	for ( size_t layerIndex = _obj->layerNum;  0<=layerIndex; layerIndex-- )
	{
		NN_LayerLearn( _obj->layers[layerIndex],  );
	}
}