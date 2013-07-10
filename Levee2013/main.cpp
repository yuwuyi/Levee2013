#include "levee2013.h"
#include "Mesh.h"
#include "MeshParser.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{

	MeshParser mparser;
	
	Mesh *mesh = mparser.parse(argv[1]);
	delete mesh;

	return 0;
/*
	QApplication a(argc, argv);
	Levee2013 w;
	w.show();
	return a.exec();
	*/
}
