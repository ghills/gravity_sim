#include <assert.h>
#include <math.h>
#include <string.h>

#include "UTL_compare_pub.h"
#include "UTL_types.h"

#include "SIM_pub.h"

#include "sim_body_types.h"
#include "sim_force_types.h"

// MACROS

#define SQR(x) (x * x)

// STATIC FUNCTION DECLARATIONS

static float gravity_between_bodies
	( 
	sim_body_type		*body1, 
	sim_body_type		*body2,
	sim_force_vector	*result_force 
	);

// MODULE VARIABLES



// FUNCTION DEFINITIONS

void SIM_step()
{

}

void SIM_get_body_count(void)
{

}

void SIM_get_bodies( sim_body_type * bodies, int max_body_count )
{

}

static float gravity_between_bodies
	( 
	sim_body_type		*body1, 
	sim_body_type		*body2,
	sim_force_vector	*result_force 
	)
{
	static const float grav_const = 6.6726E-11;

	float force;
	float distance_between;
	float theta;
	
	// check that we don't have any null pointers, that would be a dev mistake!
	assert( body1 );
	assert( body2 );
	assert( result_force );

	// Initialize
	force = 0.0f;
	distance_between = 0.0f;
	theta = 0.0f;
	memset( result_force, 0, sizeof(*result_force) );

	// X direction component
	distance_between = ( body1->posn.x - body2->posn.x );
	if( !UTL_compare_float_eq( distance_between, 0 ) )
	{
		// F = G*m1*m2 / r^2
		force = ( ( grav_const * body1->mass * body2->mass ) / SQR(distance_between) ); 
		result_force->x = force;
	}

	// Y direction component
	distance_between = ( body1->posn.y - body2->posn.y );
	if( !UTL_compare_float_eq( distance_between, 0 ) )
	{
		// F = G*m1*m2 / r^2
		force = ( ( grav_const * body1->mass * body2->mass ) / SQR(distance_between) ); 
		result_force->y = force;
	}

	// Z direction component
	distance_between = ( body1->posn.z - body2->posn.z );
	if( !UTL_compare_float_eq( distance_between, 0 ) )
	{
		// F = G*m1*m2 / r^2
		force = ( ( grav_const * body1->mass * body2->mass ) / SQR(distance_between) ); 
		result_force->z = force;
	}

	result_force->mag = sqrt( SQR(result_force->x) + SQR(result_force->y) + SQR(result_force->z) );

	// THIS SECTION WILL BE REMOVED - JUST TO TEST--------------------------------------------------
	// Euclidean distance in 3D space
	distance_between = sqrt( 
						SQR( body1->posn.x - body2->posn.x ) +
						SQR( body1->posn.y - body2->posn.y ) +
						SQR( body1->posn.z - body2->posn.z )
						);

	//TODO: gmh - replace with epsilon comparison
	if( distance_between != 0 )
	{
		// F = G*m1*m2 / r^2
		force = ( ( grav_const * body1->mass * body2->mass ) / SQR(distance_between) ); 
	}

	assert( UTL_compare_float_eq(result_force->mag,force) );

	// can use Fx = ( Px * |F| ) / |P|

	// |F| = sqrt( Fx^2 + Fy^2 + Fz^2 )
	//---------------------------------------------------------------------------------------------
}