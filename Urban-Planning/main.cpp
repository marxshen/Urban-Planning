//
//  main.cpp
//  Urban-Planning
//
//  Created by Max Shen on 2/6/22.
//

#include <random>
#include <iostream>
#include "graph.hpp"
#include "finder.hpp"

int main() {
    int nVtx = 49, nCol = 7;
    Graph *g = new Graph {nVtx, nCol};
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);
    
    int nRow = std::ceil(static_cast<double>(nVtx) / nCol);
    
    for (int i = 0, j = 1; i < nVtx; ++i) {
        g->iniVtxes(i, std::abs(dist(gen)));
        
        if (j < nRow) {
            g->addEdges(i, i+nCol, dist(gen));
            
            if (j % 2) {
                if (i % (nCol * 2) != 0)
                    g->addEdges(i, i+nCol-1, dist(gen));
            } else {
                if (i % (nCol * 2 - 1) != 0)
                    g->addEdges(i, i+nCol+1, dist(gen));
            }
            
            (i + 1) % nCol ?: ++j;
        }
    }
    
    g->printVtxes();
    std::cout << std::endl << std::endl;
    g->printEdges();
    std::cout << std::endl << std::endl;
    
    int src = 0, dst = 48;
    Finder *f = new Finder {src < nVtx-nCol ? src : nVtx-nCol-1, dst < nVtx ? dst : nVtx-1, g};
    
    f->runVtxAlgo();
    
    f->printVtxDist();
    std::cout << std::endl << std::endl;
    f->printVtxBestRoute();
    std::cout << std::endl << std::endl;
    
    f->runEdgeAlgo();
    
    f->printEdgeDist();
    std::cout << std::endl << std::endl;
    f->printEdgeBestRoute();
    std::cout << std::endl << std::endl;
}
