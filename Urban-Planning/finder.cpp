//
//  finder.cpp
//  Urban-Planning
//
//  Created by Max Shen on 2/7/22.
//

#include <iostream>
#include <limits>
#include <functional>
#include <stack>
#include <queue>
#include "finder.hpp"

using edge = std::pair<int, int>;
using edges = std::vector<edge>;

Finder::Finder(int src, int dst, const Graph *const g)
    : _src(src), _dst(dst), _inf(std::numeric_limits<int>::max()), _vMin(_inf), _vIdx(_inf),
      _vAlgo("Default"), _eAlgo("Default"), _g(g)
{
    _vDist = new caches (g->getVtxNum(), 0);
    _eDist = new caches (g->getVtxNum(), _inf);
    _vTrace = new caches (g->getVtxNum(), -1);
    _eTrace = new caches (g->getVtxNum(), -1);
}

Finder::~Finder() {
    delete _vDist;
    delete _eDist;
    delete _vTrace;
    delete _eTrace;
}

const caches& Finder::getVtxDist() const {
    return *_vDist;
}

const caches& Finder::getEdgeDist() const {
    return *_eDist;
}

const caches& Finder::getVtxTraces() const {
    return *_vTrace;
}

const caches& Finder::getEdgeTraces() const {
    return *_eTrace;
}

void Finder::runVtxAlgo(const std::string& vAlgo) {
    this->_vAlgo = vAlgo;
    
    for (int &i : *_vDist)
         i = 0;

    if (vAlgo == "DP")
        _DPAlgorithm();
    else
        std::cout << "Erred algorithm: " + vAlgo << std::endl;
}

void Finder::runEdgeAlgo(const std::string& eAlgo) {
    this->_eAlgo = eAlgo;
    
    for (int &i : *_eDist)
         i = _inf;
    
    if (eAlgo == "Dijkstra")
        _DijkstraAlgorithm();
    else
        std::cout << "Erred algorithm: " + eAlgo << std::endl;
}

void Finder::printVtxDist() const {
    ul sz = _vDist->size();
    int nCol = _g->getColNum();
    
    for (int i = 0; i < sz; ++i) {
        std::cout << (*_vDist)[i] << " ";
        
        if (i % nCol == nCol - 1 && i < sz - 1)
            std::cout << std::endl;
    }
}

void Finder::printEdgeDist() const {
    ul sz = _eDist->size();
    int nCol = _g->getColNum();
    
    for (int i = 0; i < sz; ++i) {
        std::cout << (*_eDist)[i] << " ";
        
        if (i % nCol == nCol - 1 && i < sz - 1)
            std::cout << std::endl;
    }
}

void Finder::printVtxBestRoute() const {
    if (_vAlgo == "DP")
        _DPBestRoute();
    else
        std::cout << "Erred algorithm: " + _vAlgo << std::endl;
}

void Finder::printEdgeBestRoute() const {
    if (_eAlgo == "Dijkstra")
        _DijkstraBestRoute();
    else
        std::cout << "Erred algorithm: "  + _vAlgo << std::endl;
}

void Finder::_DPAlgorithm() {
    int nVtx = _g->getVtxNum(), nCol = _g->getColNum();
    const caches *const vtxes = _g->getVtxes();
    
    for (int i = 0; i < nCol; ++i)
        (*_vDist)[i] = (*vtxes)[i];
    
    for (int i = nCol; i < nVtx; ++i) {
        int row = static_cast<int>(std::floor(static_cast<double>(i) / nCol)) + 1;

        if (row % 2 == 0)
            if (i == nCol * row - 1) {
                (*_vTrace)[i] = i - 5;
                (*_vDist)[i] = (*_vDist)[i-5] + (*vtxes)[i];
            } else {
                if ((*_vDist)[i-4] + (*vtxes)[i] < (*_vDist)[i-5] + (*vtxes)[i]) {
                    (*_vTrace)[i] = i - 4;
                    (*_vDist)[i] = (*_vDist)[i-4] + (*vtxes)[i];
                } else {
                    (*_vTrace)[i] = i - 5;
                    (*_vDist)[i] = (*_vDist)[i-5] + (*vtxes)[i];
                }
            }
        else
            if (i == nCol * (row - 1)) {
                (*_vTrace)[i] = i - 5;
                (*_vDist)[i] = (*_vDist)[i-5] + (*vtxes)[i];
            } else {
                if ((*_vDist)[i-5] + (*vtxes)[i] < (*_vDist)[i-6] + (*vtxes)[i]) {
                    (*_vTrace)[i] = i - 5;
                    (*_vDist)[i] = (*_vDist)[i-5] + (*vtxes)[i];
                } else {
                    (*_vTrace)[i] = i - 6;
                    (*_vDist)[i] = (*_vDist)[i-6] + (*vtxes)[i];
                }
            }
    }
    
    for (int i = 0; i < nCol; ++i)
        if ((*_vDist)[i] < _vMin) {
            _vMin = (*_vDist)[i];
            _vIdx = i;
        }
}

void Finder::_DPBestRoute() const {
    std::stack<int> route;
    
    for (int i = _dst; i != -1; i = (*_vTrace)[i])
        route.push(i);
    
    while (!route.empty()) {
        int vtx = route.top();
        route.pop();
        
        if (vtx == _dst)
            std::cout << vtx << " (" << (*_vDist)[vtx] << ")";
        else
            std::cout << vtx << " (" << (*_vDist)[vtx] << ") -> ";
    }
}

void Finder::_DijkstraAlgorithm() {
    std::priority_queue<edge, edges, std::greater<edge>> pq;
    
    pq.push({0, _src});
    (*_eDist)[_src] = 0;
    
    std::vector<bool> visited(_g->getVtxNum(), false);
    const edges *const adj = _g->getEdges();
    
    while(!pq.empty()) {
        int src = pq.top().second;
        pq.pop();
        
        visited[src] = true;
        edges* dsts = const_cast<edges*>(&adj[src]);
        
        for (edges::iterator edge = dsts->begin(); edge != dsts->end(); ++edge) {
            int dst = edge->first, weight = edge->second;
            
            if (visited[dst] == false && (*_eDist)[dst] > (*_eDist)[src] + weight) {
                (*_eTrace)[dst] = src;
                (*_eDist)[dst] = (*_eDist)[src] + weight;
                pq.push({(*_eDist)[dst], dst});
            }
        }
    }
}

void Finder::_DijkstraBestRoute() const {
    std::stack<int> route;
    
    for (int i = _dst; i != -1; i = (*_eTrace)[i])
        route.push(i);
    
    while (!route.empty()) {
        int vtx = route.top();
        route.pop();
        
        if (vtx == _dst)
            std::cout << vtx << " (" << (*_eDist)[vtx] << ")";
        else
            std::cout << vtx << " (" << (*_eDist)[vtx] << ") -> ";
    }
}
