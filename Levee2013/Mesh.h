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
	std::vector<std::string> m_elementPool;
	friend class MeshParser;
};
