#pragma once

#include "Point.h"

#include <vector>

class Vertex;

class Mesh
{
public:
	Mesh(void);
	~Mesh(void);

	Point minPt() const { return m_min; }
	Point maxPt() const { return m_max; }
	
	std::vector<Vertex *>& vertices() { return m_vertices; }

private:
	Point m_min, m_max;
	std::vector<Vertex *> m_vertices;
	std::vector<std::string> m_elementPool;
	friend class MeshParser;
};
