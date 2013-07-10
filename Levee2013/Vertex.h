#pragma once

class Vertex
{
public:
	Vertex(int id, double x, double y, double depth);
	~Vertex(void);

	int id() const { return m_id; }
	
	double x() const { return m_x; }
	double y() const { return m_y; }
	double depth() const { return m_depth; }

private:
	int m_id;
	double m_x, m_y, m_depth;
};
