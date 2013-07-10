#pragma once

class Mesh;

class MeshParser
{
public:
	MeshParser(void);
	~MeshParser(void);
	Mesh* parse(const char *filename);
};
