#pragma once

#include <vector>

class Vertex;

class Mesh
{
public:
	Mesh(void);
	~Mesh(void);

private:
	std::vector<Vertex *> m_vertices;
	friend class MeshParser;
};
