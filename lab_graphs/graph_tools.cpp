/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
    //set label and edges unvisited
    vector<Vertex> all_vertices = graph.getVertices();
    vector<Edge> all_edges = graph.getEdges();
    for(size_t i = 0; i < all_vertices.size(); i++){
        graph.setVertexLabel(all_vertices[i],"UNVISITED");
    }
    for(size_t i = 0; i < all_edges.size(); i++){
        graph.setEdgeLabel(all_edges[i].source,all_edges[i].dest,"UNVISITED");
    }
    //start to traverse
    Vertex start = graph.getStartingVertex();
    queue<Vertex> q;
    q.push(start);
    graph.setVertexLabel(start,"VISITED");
    vector<Vertex> MinEdge_source, MinEdge_dest;
    int MinWeight = -1;
    while(!q.empty()){
        Vertex u = q.front();
        q.pop();
        vector<Vertex> neighb = graph.getAdjacent(u);
        for(size_t i = 0; i < neighb.size(); i++){
            Vertex v = neighb[i];
            if(graph.getEdgeLabel(u,v)=="VISITED") continue;
            graph.setEdgeLabel(u,v,"VISITED");
            if(MinWeight==-1||graph.getEdgeWeight(u,v)<MinWeight){
                MinEdge_source.resize(1);
                MinEdge_dest.resize(1);
                MinEdge_source[0] = u;
                MinEdge_dest[0] = v;
                MinWeight = graph.getEdgeWeight(u,v);
            }
            if(graph.getEdgeWeight(u,v)==MinWeight){
                MinEdge_source.push_back(u);
                MinEdge_dest.push_back(v);
            }
            if(graph.getVertexLabel(v)=="VISITED") continue;
            graph.setVertexLabel(v,"VISITED");
            q.push(v);
        }
    }
    for(size_t i = 0; i<MinEdge_source.size(); i++){
        graph.setEdgeLabel(MinEdge_source[i],MinEdge_dest[i],"MIN");
    }
    return MinWeight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    if(start==end) return 0;
    vector<Edge> all_edges = graph.getEdges();
    for(size_t i = 0; i < all_edges.size(); i++){
        graph.setEdgeLabel(all_edges[i].source,all_edges[i].dest,"NOTMIN");
    }
    unordered_map<Vertex,Vertex> parent;
    unordered_map<Vertex,int> pathlength;
    queue<Vertex> q;
    q.push(start);
    pathlength.insert(std::make_pair(start,0));
    while(!q.empty()){
        Vertex u = q.front();
        q.pop();
        int ulength = pathlength.find(u)->second;
        int indicator = 0;
        vector<Vertex> neighb = graph.getAdjacent(u);
        for(size_t i = 0; i < neighb.size(); i++){
            Vertex v = neighb[i];
            if(pathlength.find(v)==pathlength.end()){
                q.push(v);
                pathlength.insert(std::make_pair(v,ulength+1));
                parent.insert(std::make_pair(v,u));
            }
        }
        if(indicator) break;
    }
    Vertex parentvt;
    Vertex thisvt = end;
    while(thisvt!=start){
        if(parent.find(thisvt)==parent.end()) return -1;
        parentvt = parent.find(thisvt)->second;
        graph.setEdgeLabel(parentvt,thisvt,"MINPATH");
        thisvt = parentvt;
    }
    return pathlength.find(end)->second;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    //initial set and sort
    DisjointSets DS;
    vector<Edge> all_edges = graph.getEdges();
    vector<Vertex> all_vertices = graph.getVertices();
    for(size_t i = 0; i < all_edges.size(); i++){
        graph.setEdgeLabel(all_edges[i].source,all_edges[i].dest,"NOTMST");
    }
    //unordered_map<Vertex,int> find_index;
    //for(size_t i = 0; i<all_vertices.size(); i++){
    //    find_index.insert(std::make_pair(all_vertices[i],i));
    //}
    DS.addelements(all_vertices.size());
    std::sort(all_edges.begin(),all_edges.end());
    int count = 0;
    //add edges
    for(size_t i = 0; i<all_edges.size(); i++){
        //int idxs = find_index.find(all_edges[i].source)->second;
        //int idxd = find_index.find(all_edges[i].dest)->second;
        if(DS.find(all_edges[i].source)!=DS.find(all_edges[i].dest)){
            DS.setunion(all_edges[i].source,all_edges[i].dest);
            graph.setEdgeLabel(all_edges[i].source,all_edges[i].dest,"MST");
            count++;
            if(count==(int)all_vertices.size()) break;
        }
    }
}

