#include <cstring>
#include <iostream>
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
    std::cout << std::endl << std::endl;
    for (int i=0;i<countVertices;i++)
    {
        std::cout << "successor (" << VertName(vertices,i) << ")=";
        std::cout << VertName(vertices,successor[i]);
        if (FLT_MAX==d[i])
        {
            std::cout << " distance to t=INFINITY" << std::endl;
        }
        else
        {     
            std::cout << " distance to t=" << d[i] << std::endl;
        }
    }

    // 3) Clean up memory
    CleanUp(vertices, countVertices);
}
