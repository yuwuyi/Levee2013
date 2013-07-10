#include "Mesh.h"
#include "Vertex.h"

Mesh::Mesh(void)
{
}

Mesh::~Mesh(void)
{
	for (size_t i = 0; i < m_vertices.size(); ++i) {
		delete m_vertices[i];
	}
	m_vertices.clear();
}
