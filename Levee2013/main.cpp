#include <vector>
#include <iomanip>
#include <iostream>
#include <set>
#include "levee2013.h"
#include "Octree.h"
#include "Vertex.h"
#include "Mesh.h"
#include "MeshParser.h"
#include <QtGui/QApplication>

#define NUM_PARTICLES 10000000
#define R 0.005f
#define EPSILON 0.0001f

struct Node
{
	std::vector<Vertex*> particles;
};

class CallbackTraverse: public Octree<Node>::Callback
{
public:
    int count;
    Vertex* p0;
	std::set<Vertex*> vertices;
    virtual bool operator()(const double min[3], const double max[3], Node& n)
    {
        Point pmin(min), pmax(max);
        double cellSizeSq = (pmax - pmin).norm2();
        double maxDist = (sqrtf(cellSizeSq) * 0.5f) + R + EPSILON;
        
        Point center = (pmin + pmax) * 0.5f;
        Point vectCenter = center - p0->pos();
        double distCenterSq = vectCenter.norm2();
        if (distCenterSq > maxDist * maxDist)
            return false; // Too far; don't subdivide cell.
        
        // Iterate through particles in this cell.
		std::vector<Vertex*>::const_iterator it = n.particles.begin();
        for (; it != n.particles.end(); it++)
        {
            Vertex* p = *it;
            if (p == p0)
                continue;
            double dsq = (p->pos() - p0->pos()).norm2();
            // If particle is within the radius, increment counter.
			if (dsq <= R * R) {
				vertices.insert(p);
                count++;
			}
        }
        // Subdivide cell if needed.
        return true;
    }
};

int main(int argc, char *argv[])
{

	MeshParser mparser;
	
	Mesh *mesh = mparser.parse(argv[1]);
	
	std::cout << "load done!\n";
	double *min = mesh->minPt().v;
	double *max = mesh->maxPt().v;

	std::cout << "building octree!\n";
	double cellSize[3] = {(max[0] - min[0])/10.0, (max[1] - min[1]) /10.0, 0.01};
	Octree<Node> octree(min, max, cellSize);

	std::vector<Vertex*> vers = mesh->vertices();
	for (int i = 1; i < vers.size(); i++)
	{
		Node& n = octree.getCell( vers[i]->pos().v );
		n.particles.push_back( vers[i] );
	}
	std::cout << "building done!\n";

    for (int i = 1; i < 120; i++)
    {
		std::cout << std::setw(3) << i << ": ";
        // Prepare the callback class.
        CallbackTraverse ct;
        ct.count = 0;
        ct.p0 = vers[i];
        // Invoke the traversal.
        octree.traverse(&ct);
		std::cout << ct.count << "  ";
        if (i % 8 == 7)
			std::cout << std::endl;
    }
//	Vertex v(1, 0.5, 0.4, 0.2);
//	double *fv = (double*)v;
//	std::cout << fv[0] << " " << fv[1] << " " << fv[2] << "\n";

//	delete mesh;
	return 0;
/*
	QApplication a(argc, argv);
	Levee2013 w;
	w.show();
	return a.exec();
	*/
}
