//
//  graph.hpp
//  Urban-Planning
//
//  Created by Max Shen on 2/6/22.
//

#ifndef graph_hpp
#define graph_hpp

#include <vector>

using vtxes = std::vector<int>;
using edges = std::vector<std::pair<int, int>>;
using ul = unsigned long;

class Graph {
    int _nVtx, _nCol, _maxV, _maxE, _maxVWt, _maxEWt;
    
    vtxes *_mat;
    edges *_adj;
    
    void _printVtxes(const vtxes *const mat, ul wdV, ul wdVWt) const;
    void _printEdges(const edges *const adj, ul wdV, ul wdE, ul wdEWt) const;
    
    public:
        Graph(int nVtx, int nCol);
        ~Graph();
    
        void iniVtxes(int src, int wt);
        void addEdges(int src, int dst, int wt);
    
        int getVtxNum() const;
        int getColNum() const;
        
        const vtxes *const getVtxes() const;
        const edges *const getEdges() const;
    
        ul getVtxWidth() const;
        ul getEdgeWidth() const;
        ul getVtxWtWidth() const;
        ul getEdgeWtWidth() const;

        void printVtxes(const vtxes *const mat=nullptr, ul wdV=0, ul wdVWt=0) const;
        void printEdges(const edges *const adj=nullptr, ul wdV=0, ul wdE=0, ul wdEWt=0) const;
};

#endif /* graph_hpp */
