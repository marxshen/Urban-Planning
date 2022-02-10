//
//  graph.cpp
//  Urban-Planning
//
//  Created by Max Shen on 2/6/22.
//

#include <iostream>
#include <iomanip>
#include <type_traits>
#include "graph.hpp"

Graph::Graph(int nVtx, int nCol)
    : _nVtx(nVtx), _nCol(nCol), _maxV(0), _maxE(0), _maxVWt(0), _maxEWt(0)
{
    _mat = new vtxes (nVtx);
    _adj = new edges [nVtx];
}

Graph::~Graph() {
    delete _mat;
    delete [] _adj;
    
    _mat = nullptr;
    _adj = nullptr;
}

void Graph::iniVtxes(int src, int wt) {
    (*_mat)[src] = wt;
    _maxV = std::max(src, _maxV);
    _maxVWt = std::max(wt, _maxVWt);
}

void Graph::addEdges(int src, int dst, int wt) {
    if (dst < _nVtx) {
        _adj[src].insert(_adj[src].end(), {dst, wt});
        _adj[dst].insert(_adj[dst].end(), {src, wt});
        
        _maxE = std::max({src, dst, _maxE});
        _maxEWt = std::max(wt, _maxEWt);
    }
}

int Graph::getVtxNum() const {
    return _nVtx;
}

int Graph::getColNum() const {
    return _nCol;
}

const vtxes *const Graph::getVtxes() const {
    return _mat;
}

const edges *const Graph::getEdges() const {
    return _adj;
}

ul Graph::getVtxWidth() const {
    return std::to_string(_maxV).size();
}

ul Graph::getEdgeWidth() const {
    return std::to_string(_maxE).size();
}

ul Graph::getVtxWtWidth() const {
    return std::to_string(_maxVWt).size();
}

ul Graph::getEdgeWtWidth() const {
    return std::to_string(_maxEWt).size();
}

void Graph::printVtxes(const vtxes *const mat, ul wdV, ul wdVWt) const {
    if (mat == nullptr)
        _printVtxes(this->_mat, getVtxWidth(), getVtxWtWidth());
    else
        _printVtxes(mat, wdV, wdVWt);
}

void Graph::printEdges(const edges *const adj, ul wdV, ul wdE, ul wdEWt) const {
    if (adj == nullptr)
        _printEdges(this->_adj, getVtxWidth(), getEdgeWidth(), getEdgeWtWidth());
    else
        _printEdges(adj, wdV, wdE, wdEWt);
}

void Graph::_printVtxes(const vtxes *const mat, ul wdV, ul wdVWt) const {
    for (int src = 0; src < _nVtx; ++src) {
        std::cout << std::setw(static_cast<int>(wdV)) << std::to_string(src) << " (" \
                  << std::setw(static_cast<int>(wdVWt)) << std::to_string((*mat)[src]) << ") ";
        
        if (src % _nCol == _nCol - 1 && src < _nVtx - 1)
            std::cout << std::endl;
    }
}

void Graph::_printEdges(const edges *const adj, ul wdV, ul wdE, ul wdEWt) const {
    for (int src = 0; src < _nVtx; ++src) {
        edges* srces = const_cast<edges*>(&adj[src]);
        
        for (edges::iterator edge = srces->begin(); edge != srces->end(); ++edge)
            std::cout << std::setw(static_cast<int>(wdV)) << src << "->" \
                      << std::setw(static_cast<int>(wdE)) << edge->first << " (" \
                      << std::setw(static_cast<int>(wdEWt)) << edge->second << ") ";
        
        if (src < _nVtx - 1)
            std::cout << std::endl;
    }
}
