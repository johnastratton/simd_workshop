#include "transform.h"

//
//  transform.c
//
//  functions: int transform( float p_matrix[ 4 ][ 4 ], 
//      float p_vectors[][ 4 ], float p_outputs[][ 4 ], int length )
//      arguments:
//          p_matrix: a quaterion transformation matrix, row first.
//          p_vectors: a list of vectors to transform using the
//              given matrix.
//          p_outputs: a list of vectors to store the transformed
//              vectors into.
//          int length: The length of each array.
//      function:
//          The function shall transform each vector in p_vectors
//          with the corresponding transformation matrix in
//          p_matrix via dotting each vector on the left by
//          the matrix in question and place each output produced
//          in the corresponding index in p_outputs.
//
//  implement the functions in this file using appropriate vector
//  instructions as directed in the lab instructions.
//

typedef float float4 __attribute__((vector_size(16)));

int transform( float p_matrix[ 4 ][ 4 ], 
	       float p_vectors[][ 4 ], 
	       float p_outputs[][ 4 ], int length )
{
    int i = 0;
    for(; i < length; i++ )
    {
        int j = 0;
        float4 vector = *((float4*)p_vectors[ i ]);
        for(; j < 4; j++ )
        {
            float4 row = *((float4*)p_matrix[j]);
            float4 product = row * vector;
            p_outputs[i][j] = product[0] + product[1] + product[2] + product[3];
        }
    }

    return 0;
}

