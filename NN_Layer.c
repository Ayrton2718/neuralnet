#include "NN_Layer.h"
#include "NN_Node.h"

struct NN_Layer {
	size_t		nodeNum;
	NN_Object	*nodes;

	NN_Var		*befoOut;
};

NN_Object NN_LayerAllocInit( size_t inputNum, size_t nodeNum, NN_ActiveFunc activeFunc, NN_DerivActive derivFunc )
{
	struct NN_Layer *_obj = (struct NN_Layer*)malloc( sizeof( struct NN_Layer ) );

	_obj->nodeNum = nodeNum;
	_obj->nodes = (NN_Object*)malloc(sizeof(NN_Object)*_obj->nodeNum);
	for ( size_t nodeIndex=0; nodeIndex<_obj->nodeNum; nodeIndex++ )
	{
		_obj->nodes[nodeIndex] = NN_NodeAllocInit( inputNum, activeFunc, derivFunc );
	}

	_obj->befoOut = (NN_Var*)malloc( sizeof( NN_Var )*_obj->nodeNum );

	return _obj;
}


size_t NN_LayerGetNodeNum(NN_Object obj)
{
	struct NN_Layer *_obj = (struct NN_Layer*)obj;

	return _obj->nodeNum;
}


void NN_LayerRun( NN_Object obj, const NN_Var *befoLayer )
{
	struct NN_Layer *_obj = (struct NN_Layer*)obj;

	for ( size_t nodeIndex=0; nodeIndex<_obj->nodeNum; nodeIndex++ )
	{
		_obj->befoOut[nodeIndex] = NN_NodeRun( _obj->nodes[nodeIndex], befoLayer );
	}
}

const NN_Var* NN_LayerBefoOut( NN_Object obj )
{
	struct NN_Layer *_obj = (struct NN_Layer*)obj;
	return (const NN_Var*)_obj->befoOut;
}

void NN_LayerLearn( NN_Object obj, NN_Object aftLayer, const NN_Var *befoLayer, NN_Var learnRate )
{
	struct NN_Layer *_obj = (struct NN_Layer*)obj;
	
	for ( size_t nodeIndex = 0; nodeIndex<_obj->nodeNum; nodeIndex++ )
	{
		NN_NodeLearn(_obj->nodes[nodeIndex], NN_LayerCulcErSum(aftLayer, nodeIndex), befoLayer, learnRate );
	}
}


void NN_LayerLearnTeacher( NN_Object obj, const NN_Var *aftLayer, const NN_Var *befoLayer, NN_Var learnRate )
{
	struct NN_Layer *_obj = (struct NN_Layer*)obj;

	for (size_t nodeIndex = 0; nodeIndex<_obj->nodeNum; nodeIndex++)
	{
		NN_NodeLearn(_obj->nodes[nodeIndex], (NN_Node), befoLayer, learnRate);
	}
}


NN_Var NN_LayerCulcErSum( NN_Object obj, size_t weightIndex )
{
	struct NN_Layer *_obj = (struct NN_Layer*)obj;

	NN_Var erSum = (NN_Var)0;

	for ( size_t nodeIndex = 0; nodeIndex<_obj->nodeNum; nodeIndex++ )
	{
		erSum += NN_NodeCulcEr( _obj->nodes[nodeIndex], weightIndex );
	}

	return erSum;
}