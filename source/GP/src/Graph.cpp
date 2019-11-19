

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "Graph.h"
#include "List.h"

using namespace std;

Graph::Graph(int n)
{
	List<int> L;
	vertices = n;
	edges = 0;
	for (int i=0; i <= vertices; i++)
	{
		color.push_back('W');
		parent.push_back(0);
		distance.push_back(-1);
		adj.push_back(L);
	}
}

int Graph::getNumEdges() const
{
	return edges;
}

int Graph::getNumVertices() const
{
	return vertices;
}

bool Graph::isEmpty() const
{
	return (edges == 0);
}

int Graph::getDistance(int v) const
{
	assert(v <= getNumVertices());
	return distance[v];
}

int Graph::getParent(int v) const
{
	assert(v <= getNumVertices());
	return parent[v];
}

char Graph::getColor(int v) const
{
	assert(v <= getNumVertices());
	return color[v];
}

void Graph::addEdge(int u, int v)
{
	assert(u <= getNumVertices() && v <= getNumVertices());
    if(u==v)
    {
        return;
    }

    adj[u].insertLast(v);

    edges = edges + 0.5;
}

void Graph::addEdge1(int u , int v)
{
    assert(u <= getNumVertices() && v <= getNumVertices());
    if(u==v)
    {
        return;
    }

    adj[u].insertLast(v);
    adj[v].insertLast(u);

    edges++;
}

void Graph::printGraph(ostream& out)
{
	for (int i = 1; i < adj.size(); i++)
	{
        out << i << ": " ;
        adj[i].printList(out);
    }
   out << endl;
}

void Graph::printBFS(ostream& out)
{
	out << "v	c  	p  	d" << endl;
	for (int i = 1; i <= getNumVertices(); i++)
	{
		out << i << " 	" << color[i] << " 	" << parent[i] << " 	" << distance[i] << endl;
	}
}

List<int> Graph::BFS(int source)
{
	assert(source <= getNumVertices() && source >= 0);
	assert(getNumVertices() > 0);
    List<int> friendreccomnd;

	int x;
	List<int> Q;
	for(int i = 1; i < getNumVertices(); i++)
	{
		color[i] = 'W';
		distance[i] = -1;
		parent[i] = 0;
	}
	color[source] = 'G';
	distance[source] = 0;
	Q.insertLast(source);

	while(!Q.isEmpty())
	{
		x = Q.getFirst();
		Q.removeFirst();
		adj[x].startIterator();
		for(int j = 1; j <= adj[x].getLength(); j++)
		{
			if ( color[adj[x].getIterator()] == 'W')
			{
				color[adj[x].getIterator()] = 'G';
				distance[adj[x].getIterator()] = distance[x] +1;

                if(distance[adj[x].getIterator()] > 1)
                {
                    friendreccomnd.insertFirst(adj[x].getIterator());
                }
				parent[adj[x].getIterator()] = x;
				Q.insertLast(adj[x].getIterator());
			}
			adj[x].advanceIterator();
		}
		color[x] = 'B';
	}
    return friendreccomnd;
}

void Graph::printPath(int source, int destination, ostream& out)
{
	if (destination == source)
	{
		out << source << " ";
	}
	else if(parent[destination] == 0)
	{
		out<< "No path from " << source << " to " << destination << " exits" << endl;
	}
		else
	{
		printPath(source, parent[destination], out);
		out<< destination << " ";
	}
}
List<int> Graph::seeFriends(int s)
{
    List<int> seef;
    adj[s].startIterator();
    while(!adj[s].offend())
    {
        seef.insertLast(adj[s].getIterator());
        adj[s].advanceIterator();
    }
    return seef;
}

void Graph::removeFriend(int s, int r)
{
    adj[s].startIterator();
    while(adj[s].getIterator()!= r)
    {
        adj[s].advanceIterator();
    }
    adj[s].removeIterator();
    adj[r].startIterator();
    while(adj[r].getIterator()!=s)
    {
        adj[r].advanceIterator();
    }
    adj[r].removeIterator();
    edges--;
}

