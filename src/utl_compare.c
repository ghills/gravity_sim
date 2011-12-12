#include <math.h>

#include "UTL_types.h"

#define EPSILON (0.00001f)

boolean UTL_compare_float_eq( float value1, float value2 )
{
	return ( abs( value1 - value2 ) < EPSILON );
}