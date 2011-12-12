#ifndef _SIM_BODY_TYPES
#define _SIM_BODY_TYPES

#include "sim_posn_types.h"
#include "sim_vel_types.h"

typedef enum 
{
	BODY_TYPE_SPHERE,
	BODY_TYPE_CUBE,

	BODY_TYPE_COUNT
} body_type;

typedef struct
{
	sim_posn_type	posn;
	sim_vel_type	vel;
	float			mass;
	float			size;
	body_type		type;
} sim_body_type;

#endif