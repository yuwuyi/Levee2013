#include "viewport.h"
#include <QPointF>
#include <QMouseEvent>
#include "Renderer.h"

typedef Vector3f vec3;
typedef Vector3d vec3d;
typedef Quatf quat;

ViewPort::ViewPort(QWidget *parent)
	: QGLWidget(parent)
{

}

ViewPort::~ViewPort()
{

}



void ViewPort::initializeGL () {
	GLfloat	light0_Ka[] = {0.1f,0.1f,0.1f,1.0f};
	GLfloat	light0_Kd[] = {1.0f,1.0f,1.0f,1.0f};
	GLfloat light0_Ks[] = {1.0f,1.0f,1.0f,1.0f};
	GLfloat light0_Pos[] = {5.0f, 5.0f, 5.0f, 0.0f};
	GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_Ka);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_Kd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_Ks);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_Pos);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);


	InitCamera();

}

void ViewPort::resizeGL ( int width , int height ) {

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat x = GLfloat(width) / height;
	glFrustum(-x, +x, -1.0, +1.0, 4.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
}

void ViewPort::paintGL () {
	
}


void ViewPort::InitCamera() {
	vec3 homepos, homerotaxis;

	// Since the model is always normalized, constants suffice
	homepos.x = 0;
	homepos.y = 0;
	homepos.z = 6.0;

	homerotaxis = vec3(0, 0, 1);

	theCamera.SetHome(homepos, 0, homerotaxis, DEFAULT_FOV);
	view_dist = 6.0;
	rotate_dist = 6.0;

	theCamera.GoHome();
}



void ViewPort::mousePressEvent(QMouseEvent *event)
{
	float nx, ny;
	Mousei2f(event->pos().x(), event->pos().y(), &nx, &ny);
	bool isClick = true;

	lastPos = QPointF(nx, ny);

	updateGL();

}


void ViewPort::mouseReleaseEvent(QMouseEvent *event) {
	bool isClick = false;

	isClick = (event->pos() - pressPos).manhattanLength() < 0.001;
	updateGL();

}


void ViewPort::mouseMoveEvent(QMouseEvent *event)
{
	float cur_mouse_x, cur_mouse_y;
	float delta_x, delta_y;




	Mousei2f(event->pos().x(), event->pos().y(), &cur_mouse_x, &cur_mouse_y);

	delta_x = cur_mouse_x - lastPos.x();
	delta_y = cur_mouse_y - lastPos.y();
	
	if (event->buttons() & Qt::LeftButton) {
		Rotate(lastPos.x(), lastPos.y(), cur_mouse_x, cur_mouse_y);
	} else if (event->buttons() & Qt::RightButton) {
		Translate(delta_x, delta_y, 0);
	}

	lastPos = QPointF(cur_mouse_x, cur_mouse_y);
	updateGL();
}    

void ViewPort::wheelEvent ( QWheelEvent * event )  {
	Translate(0, 0, ((GLfloat)event->delta()) / 360);
	updateGL();
}


// Mouse event helper function - rotate
void ViewPort::Rotate(float ox, float oy, float nx, float ny)
{
	quat q;
	Camera::Arc2Quaternion(ox, oy, nx, ny, q);

	if (rotate_dist == 0) {
		q[1] = -q[1];
		q[2] = -q[2];
	}

	theCamera.Rotate(q, rotate_dist);
}


// Mouse event helper function - translate
void ViewPort::Translate(float dx, float dy, float dz)
{
	// some auto param ajustment to be refined later
	float scalefactor = 0.5f*view_dist;
	dx *= scalefactor*theCamera.fov;
	dy *= scalefactor*theCamera.fov;
	dz = view_dist * (exp(-0.5f * dz) - 1.0f);

	// moving the camera in the opposite direction to
	// the direction we want the object to move
	theCamera.Move(-dx, -dy, -dz);
	UpdateDist(-dx, -dy, -dz);
}

// Mouse event helper function - update distance
void ViewPort::UpdateDist(float dx, float dy, float dz)
{
	vec3 viewdir(0, 0, -view_dist);
	vec3 delta(-dx, -dy, -dz);

	vec3 newviewdir = viewdir + delta;

	view_dist = -newviewdir.z;
	// Always rotate around the center of the object
	// which is assumed to be place at the origin of the world coordinate
	rotate_dist = view_dist;

}


// Helper function - convert integer coordinates of mouse position to
// normalized floats
void ViewPort::Mousei2f(int x, int y, float *xf, float *yf)
{
	int screenwidth = width();
	int screenheight = height();

	float r = (float)screenwidth/screenheight;
	if (r > 1.0) {
		*xf = r * (2.0f * x / screenwidth - 1.0f);
		*yf = 1.0f - 2.0f * y / screenheight;
	} else {
		*xf = 2.0f * x / screenwidth - 1.0f;
		*yf = (1.0f - 2.0f * y / screenheight) / r;
	}
}