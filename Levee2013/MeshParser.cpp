#include "Vertex.h"
#include "MeshParser.h"
#include "Point.h"
#include "Mesh.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

MeshParser::MeshParser(void)
{
}

MeshParser::~MeshParser(void)
{
}

Mesh* MeshParser::parse(const char *filename) {
	
	Mesh *mesh = new Mesh;
	std::ifstream input(filename);
	//parse header
	std::string dull;	
	getline(input, dull);
	getline(input, dull);
	int numElement, numNode;
	std::stringstream ss(dull);	
	ss >> numElement >> numNode;

	mesh->m_vertices.resize(numNode + 1, 0);

	Point min(1e10, 1e10, 0), max(-1e10, -1e10, 0);
	while(input.good()) {
		std::string line;
		getline(input, line);
		std::stringstream ss(line);
		int id;
		double x, y, depth;
		ss >> id >> x >> y >> depth;
		
		if (x < min[0]) { min[0] = x;}
		if (x > max[0]) { max[0] = x;}
		if (y < min[1]) { min[1] = y;}
		if (y > max[1]) { max[1] = y;}

		Vertex *v = new Vertex(id, x, y, depth);
		mesh->m_vertices[id] = v;
		if (id == numNode) {
			break;
		}
	}

	mesh->m_min = min;
	mesh->m_max = max;

	for (int i = 0; i < numElement; ++i) {
		std::string line;
		getline(input, line);
		mesh->m_elementPool.push_back(line);
	}


	//get to the 3rd section
	for (int i = 0; i < numElement; ++i) {

	}


	input.close();
	return mesh;
}