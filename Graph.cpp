#include "Graph.h"
#include <sstream>
#include <limits>
#include <ios>
#include <queue>

Graph::Graph(ifstream& ifs ) {
	string line;
	int vertex;
	int edge;
	int vertex1=0;
	int vertex2=0;

	
	ifs >> vertex;
	ifs >> edge;
	//cout << vertex << " " << edge;
	//ifs.ignore(numeric_limits<streamsize>::max(), '\n');
	
	
	for(int i = 0; i < vertex; ++i) {
		ifs >> line;
		vertices.push_back(Vertex(line));
	}
	for(int i = 0; i < edge; ++i) {
		ifs >> line;
		
		for(unsigned j = 0; j < vertices.size(); ++j) {
			if(vertices.at(j).label == line) {
				vertex1 = j;
				break;
			}
		}
		
		ifs >> line;
	
		for(unsigned j = 0; j < vertices.size(); ++j) {
			if(vertices.at(j).label == line) {
				vertex2 = j;
				break;
			}
		}		
		ifs >> line;

		
		vertices.at(vertex1).neighbors.push_back(std::pair<int,int>(vertex2,1));
	}
}

void Graph::bfs() {
	if(vertices.empty()) {
		return;
	}
	queue <Vertex> vertex;
	int j = 0;
	
	vertex.push(vertices.at(0));
	vertices.at(0).distance = 0;
	vertices.at(0).color = "GREY";
	
	while(!vertex.empty()) {
		Vertex current = vertex.front();
		vertex.pop();
		
	for(unsigned i = 0; i < vertices.size(); ++i) {
		if(current.label == vertices.at(i).label) {
			j = i;
		}
	}
	
		list<pair<int,int> >::iterator i;
		for(i = current.neighbors.begin(); i != current.neighbors.end(); ++i) {
			if(vertices.at(i->first).color == "WHITE") {
				vertices.at(i->first).color = "GREY";
				vertices.at(i->first).distance = vertices.at(j).distance + 1;
				vertices.at(i->first).prev = &vertices.at(j);
				vertex.push(vertices.at(i->first));
			}
		}
		vertices.at(j).color= "BLACK";
	}
}

void Graph::output_graph(const string& input) {
	for(unsigned i = 0; i < vertices.size(); ++i) {
		cout << "Node: "  << vertices.at(i).label << " distance: " << vertices.at(i).distance;
		if(vertices.at(i).prev != NULL) {
			cout << " previous: " << vertices.at(i).prev->label;
		} 
		cout << " color: " << vertices.at(i).color;
		cout << endl;
	}

}
Graph::~Graph() {
	vertices.clear();
}

