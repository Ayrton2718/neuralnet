#include "NN_Node.h"
#include "SC_Random.h"

struct NN_Node {
	size_t inputNum;

	NN_ActiveFunc active;
	NN_DerivActive deriv;

	NN_Var	*w;
	NN_Var	b;
	NN_Var	z;
	NN_Var	a;
	NN_Var	e;
};


NN_Object NN_NodeAllocInit( size_t inputNum, NN_ActiveFunc activeFunc, NN_DerivActive derivFunc )
{
	struct NN_Node *_obj = (struct NN_Node*)malloc(sizeof(struct NN_Node));
	_obj->inputNum = inputNum;
	_obj->active = activeFunc;
	_obj->deriv = derivFunc;

	_obj->w = (NN_Var*)malloc( sizeof( NN_Var )*_obj->inputNum);
	for ( size_t weightIndex=0; weightIndex<_obj->inputNum; weightIndex++ )
	{
		_obj->w[weightIndex] = SC_RandomOut();
	}
	_obj->b = SC_RandomOut();
	return (NN_Object)_obj;
}


NN_Var NN_NodeRun( NN_Object obj, const NN_Var *befoOut )
{
	struct NN_Node *_obj = (struct NN_Node*)obj;
	
	_obj->z = _obj->b;
	for ( size_t weightIndex=0; weightIndex<_obj->inputNum; weightIndex++ )
	{
		_obj->z += befoOut[weightIndex] * _obj->w[weightIndex];
	}

	_obj->a = _obj->active( _obj->z );

	return _obj->a;
}


void NN_NodeLearn( NN_Object obj, NN_Var erSum, const NN_Var *befoOut, NN_Var learnRate )
{
	struct NN_Node *_obj = (struct NN_Node*)obj;

	_obj->e = erSum*_obj->deriv(_obj->z);

	for ( size_t weightIndex = 0; weightIndex<_obj->inputNum; weightIndex++ )
	{
		_obj->w[weightIndex] -= learnRate * _obj->e * befoOut[weightIndex];
	}

	_obj->b -= learnRate*_obj->e;
}

NN_Var NN_NodeCulcEr(NN_Object obj, size_t weightIndex)
{
	struct NN_Node *_obj = (struct NN_Node*)obj;

	return _obj->e*_obj->w[weightIndex];
}