#include "addvec.h"

//
//  addvec.c
//
//  functions: int addvec( int* p_a, int* p_b, int* p_c, int length )
//      arguments:
//      int* p_a: An array A, one of the arguments to the sum
//      int* p_b: An array B, one of the arguments to the sum
//      int* p_c: An array C, the destination of the componentwise 
//          sum of the vectors A and B.
//      int length: The length of each array.
//      function:
//      addvec shall perform a componentwise addition of vectors
//          A and B of length 'length' and store the result in vector C.
//
//  implement the functions in this file using appropriate vector
//  instructions as directed in the lab instructions.
//

int addvec( const float* p_a, const float* p_b, float* p_c, int length )
{
    if( length <= 0 ) return 1;

    int i = 0;
    for(; i < length; i++ )
    {
        p_c[ i ] = p_a[ i ] + p_b[ i ];
    }

    return 0;
}

