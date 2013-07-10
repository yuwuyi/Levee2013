#include "Vertex.h"
#include "MeshParser.h"
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

	while(input.good()) {
		std::string line;
		getline(input, line);
		std::stringstream ss(line);
		int id, x, y, depth;
		ss >> id >> x >> y >> depth;
		
		Vertex *v = new Vertex(id, x, y, depth);
		mesh->m_vertices[id] = v;
	}

	input.close();
	return mesh;
}