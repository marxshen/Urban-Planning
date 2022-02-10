//
//  finder.hpp
//  Urban-Planning
//
//  Created by Max Shen on 2/7/22.
//

#ifndef finder_hpp
#define finder_hpp

#include <string>
#include <vector>
#include <unordered_map>
#include "graph.hpp"

using caches = std::vector<int>;

class Finder {
    int _nCol, _src, _dst, _inf, _vMin, _vIdx;
    std::string _vAlgo, _eAlgo;
    
    caches *_vDist, *_eDist, *_vTrace, *_eTrace;
    const Graph *_g;
    
    void _DPAlgorithm();
    void _DPBestRoute() const;
    
    void _DijkstraAlgorithm();
    void _DijkstraBestRoute() const;
    
    public:
        Finder(int src, int dst, const Graph *const g);
        ~Finder();
    
        const caches& getVtxDist() const;
        const caches& getEdgeDist() const;
        const caches& getVtxTraces() const;
        const caches& getEdgeTraces() const;
    
        void runVtxAlgo(const std::string& vAlgo="DP");
        void runEdgeAlgo(const std::string& eAlgo="Dijkstra");
    
        void printVtxDist() const;
        void printEdgeDist() const;
    
        void printVtxBestRoute() const;
        void printEdgeBestRoute() const;
};

#endif /* finder_hpp */
