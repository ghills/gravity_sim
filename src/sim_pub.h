#ifndef _SIM_PUB
#define _SIM_PUB

#include "sim_body_types.h"

void SIM_step(void);

void SIM_get_body_count(void);

void SIM_get_bodies( sim_body_type * bodies, int max_body_count );

#endif