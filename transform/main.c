#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "transform.h"

#define LENGTH 100
#define RAND_MOD 100

#define DEBUG_PRINTS

//
//  main.c
//
//  Note: the testing subject will not receive a copy of this file
//

int serial_transform( float p_matrices[ 4 ][ 4 ], float p_vectors[][ 4 ], float p_outputs[][ 4 ], int length );
void printMatrix( float p_matrix[][ 4 ] );
void printVector( float p_vector[] );

int main( void )
{
    srand( time( NULL ) );

    //An approximate quaternion rotation matrix
    float __attribute__(( aligned( 16 ) )) matrix[ 4 ][ 4 ] = 
        {{0.36f, 0.48f, -0.8f, 0.0f},
         {-0.8f, 0.6f, 0.0f, 0.0f},
         {0.48f, 0.64f, 0.60f, 0.0f},
         {0.0f, 0.0f, 0.0f, 0.0f}};
    float __attribute__(( aligned( 16 ) )) vectors[ LENGTH ][ 4 ];
    float __attribute__(( aligned( 16 ) )) serial_outputs[ LENGTH ][ 4 ];
    float __attribute__(( aligned( 16 ) )) outputs[ LENGTH ][ 4 ];

    int i = 0;
    for(; i < LENGTH; i++ )
    {
        int j = 0;
        for(; j < 4; j++ )
        {
            vectors[ i ][ j ] = rand() % RAND_MOD;
        }
    }

    serial_transform( matrix, vectors, serial_outputs, LENGTH );
    transform( matrix, vectors, outputs, LENGTH );

    int cmp = 0;
    for (i = 0; i < LENGTH; i++) {
        int j = 0;
        for (j = 0; j < 4; j++) {
	    if (fabs(serial_outputs[i][j] - outputs[i][j]) > 0.001) {
                cmp++;
#ifdef DEBUG_PRINTS
                printf( "Element [%d][%d]: given %f, computed %f\n", i, j, 
                         serial_outputs[i][j], outputs[i][j] );
#endif
            }
                
        }
    }

    if( cmp == 0 )
    {
        printf( "Your solution is functionally correct!\n" );
    }
    else
    {
        printf( "Badness of your solution: %d\n", cmp );

#ifdef DEBUG_PRINTS
        printf( "Additional information:\nThis is the first matrix multiplication in the queue.\nMatrix:\n" );
        printMatrix( matrix[ 0 ] );
        printf( "Vector:\n" );
        printVector( vectors[ 0 ] );
        printf( "Output vector:\n" );
        printVector( outputs[ 0 ] );
        printf( "What you should have gotten:\n" );
        printVector( serial_outputs[ 0 ] );
        printf( "Did you flip which was a column and row?\n" );
#endif
    }

    return 0;
}

int serial_transform( float p_matrix[ 4 ][ 4 ], float p_vectors[][ 4 ], float p_outputs[][ 4 ], int length )
{
    int i = 0;
    for(; i < length; i++ )
    {
        int j = 0;
        for(; j < 4; j++ )
        {
            p_outputs[ i ][ j ] = 0.0f;
            int k = 0;
            for(; k < 4; k++ )
            {
                p_outputs[ i ][ j ] += p_matrix[ j ][ k ] * p_vectors[ i ][ k ];
            }
        }
    }

    return 0;
}

//
//  Makes assumption that the matrix is 4 x 4
//

void printMatrix( float p_matrix[][ 4 ] )
{ 
    printf( "{ " );
    int i = 0;
    for(; i < 4; i++ )
    {
        printf( "{ " );
        int j = 0;
        for(; j < 4; j++ )
        {
            printf( "%.3f", p_matrix[ i ][ j ] );
            if( j < 3 ) printf( ", " );
        }
        printf( " }" );
        if( i < 3 ) printf( ",\n" );
    }
    printf( " }\n" );
}

//
//  Naively assumes 4-vector
//

void printVector( float p_vector[] )
{
    printf( "{ " );
    int i = 0;
    for(; i < 4; i++ )
    {
        printf( "%.3f", p_vector[ i ] );
        if( i < 3 ) printf( ", " );
    }
    printf( " }\n" );
}

