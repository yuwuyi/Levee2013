#pragma once

#include "Point.h"

class Vertex
{
public:
	Vertex(int id, double x, double y, double depth) : m_id(id), m_point(x, y, 0), m_depth(depth) {}
	~Vertex(void) {}

	int id() const { return m_id; }
	double depth()  const { return m_depth; }	
	const Point& pos() const { return m_point; } 
    operator double*() { return m_point.v; }
private:
	int m_id;
	double m_depth;
	Point m_point;
};
