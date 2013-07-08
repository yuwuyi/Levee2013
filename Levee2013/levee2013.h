#ifndef LEVEE2013_H
#define LEVEE2013_H

#include <QtGui/QMainWindow>
#include "ui_levee2013.h"

class Levee2013 : public QMainWindow
{
	Q_OBJECT

public:
	Levee2013(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Levee2013();

private:
	Ui::Levee2013Class ui;
};

#endif // LEVEE2013_H
