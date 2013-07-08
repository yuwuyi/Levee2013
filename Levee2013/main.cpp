#include "levee2013.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Levee2013 w;
	w.show();
	return a.exec();
}
