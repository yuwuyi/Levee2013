#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGLWidget>
#include "Camera.h"

class Renderer;

class ViewPort : public QGLWidget
{
	Q_OBJECT

public:
	ViewPort(QWidget *parent);
	~ViewPort();

protected:
	void initializeGL ();
	void resizeGL ( int width , int height );
	void paintGL ();

	void InitCamera();


	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

	void wheelEvent( QWheelEvent * event );

private:
	void Rotate(float ox, float oy, float nx, float ny);
	void Translate(float dx, float dy, float dz);
	void UpdateDist(float dx, float dy, float dz);
	void Mousei2f(int x, int y, float *xf, float *yf);


private:
	Renderer *m_renderer;
	Camera theCamera;
	QPointF lastPos;
	QPointF pressPos;
	
	float view_dist;
	float rotate_dist;
};

#endif // VIEWPORT_H
