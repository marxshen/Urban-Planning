# Urban-Planning

Designers plan a graph with edges and vertices connected in a grid pattern.<br/>
Vertices exist at each intersection.<br/>
Also, vertices and edges have specific weights.<br/>
There are precisely n * n vertices.<br/>

A variable vDist[i] stores the weight of each vertex.<br/>
Also, a variable eDist[i] stores the weight of each edge.<br/>

The planners can denote its source in any of the lots, L<sub>1</sub> to L<sub>n</sub>,<br/>
which are adjacent to vertices in the first column.<br/>
On the other side of the graph are their n targets, R<sub>1</sub> to R<sub>n</sub>.<br/>

The planners would like to denote their sources to allow for paths to targets with minimum weights.<br/>
The goal is to determine the locations of their sources and the best routes to the targets.<br/>
