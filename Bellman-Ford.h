#ifndef _BFS_H
#define _BFS_H

#include "cs4050.h"

#ifdef __cplusplus
extern "C" 
{
#endif
void ShortestPaths( Vertex * V, int countV, 
                    Edge * E, int countE, 
                    int t,
                    float distances[],
                    int successor[]);
#ifdef __cplusplus
}
#endif

#endif
