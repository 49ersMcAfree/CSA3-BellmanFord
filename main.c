#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "cs4050.h"
#include "Bellman-Ford.h"

char * VertName(Vertex vertices[], int iVertexIndex)
{
    static char VName[256];
    if (-1==iVertexIndex)
    {
        strcpy(VName,"NULL");
    }
    else
    {
        sprintf(VName,"%d",vertices[iVertexIndex].number);
    }

    return VName;
}


int main(void)
{
    /******************************************************/
    /* Set things up by loading the graph and printing it */
    int countVertices, countEdges;

    //SetDirected(1);
	IsDirected();
    GetCounts(&countVertices,&countEdges);

    Vertex vertices[countVertices];
    Edge edges[countEdges];
    memset(vertices,0,sizeof(vertices));
    memset(edges,0,sizeof(edges));

    GetEdges(edges,countEdges);
    BuildAdjacency(vertices,edges,countVertices,countEdges);
    PrintVertices(vertices,countVertices);
    /******************************************************/


    // Now, we need to do the following:
    // 1) Build the distance and successor matrices
    float d[countVertices];
    int successor[countVertices];

    ShortestPaths(
        vertices, countVertices, 
        edges, countEdges, 
        countVertices-1,  // end - we assume t is the last vertex
        d,successor);

    // 2) Print the distance from each v to each s
    printf("\n\n");
    for (int i=0;i<countVertices;i++)
    {
        printf("successor (%s)=", VertName(vertices,i));
        printf("=%s, ", VertName(vertices,successor[i]));
        if (FLT_MAX==d[i])
        {
            printf(" distance to t=INFINITY\n");
        }
        else
        {     
            printf(" distance to t=%5.2f\n",d[i]);
        }
    }

    // 3) Clean up memory
    CleanUp(vertices,countVertices);
}
