#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "addvec.h"

#define LENGTH 100
#define RAND_MOD 1000

//
//  main.c
//
//  Note: the testing subject will not receive a copy of this file
//

int serial_addvec( const float* p_a, const float* p_b, float* p_c, int length );

int main( void )
{
    srand( time( NULL ) );

    float __attribute__(( aligned( 16 ) )) p_a[ LENGTH ];
    float __attribute__(( aligned( 16 ) )) p_b[ LENGTH ];
    float __attribute__(( aligned( 16 ) )) p_c[ LENGTH ];
    float __attribute__(( aligned( 16 ) )) p_d[ LENGTH ];

    //
    //  Note we skip memory initialization for p_c.
    //  A correct function should not require that 
    //  there be assumptions on p_c's initial values.
    //  Notice also that we do not allow the user
    //  to control the alignment of the memory space.
    //  This is part of the issue that we are asking
    //  the user to address in this assignment.
    //

    //
    //  initialize garbage data
    //

    int i = 0;
    for(; i < LENGTH; i++ )
    {
        p_a[ i ] = ( float )( rand() % 1000 ) / 100.0f;
        p_b[ i ] = ( float )( rand() % 1000 ) / 100.0f;
    }

    //
    //  call the usre's code
    //

    serial_addvec( p_a, p_b, p_d, LENGTH );
    addvec( p_a, p_b, p_c, LENGTH );

    //
    //  Verify for correctness
    //

    int e = 0;
    for( i = 0; i < LENGTH; i++ )
    {
        if( p_c[ i ] != p_d[ i ] ) e++;
    }

    printf( "Run complete. Errors: %d\n", e );

    return 0;
}

int serial_addvec( const float* p_a, const float* p_b, float* p_c, int length )
{
    if( length <= 0 ) return 1;

    int i = 0;
    for(; i < length; i++ )
    {
        p_c[ i ] = p_a[ i ] + p_b[ i ];
    }

    return 0;
}

