#ifndef NN_TYPE_H
#define NN_TYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void* NN_Object;

typedef float NN_Var;

typedef NN_Var(*NN_ActiveFunc)(NN_Var);

typedef NN_Var(*NN_DerivActive)(NN_Var);

#endif	/*NN_TYPE_H*/