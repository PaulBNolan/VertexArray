#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <Vector3.h>
#include <Matrix3.h>

using namespace std;
using namespace sf;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();

	Clock clock;
	Time elapsed;

	float rotationAngleX = 0.0f;
	float rotationAngleY = 0.0f;
	float translationFactorX = 0.0f;
	float translationFactorY = 0.0f;
	float scaleFactor = 100.0f;

	Vector3D m_initialPoints[8];
	Vector3D m_currentPoints[8];

	Matrix3 rotationMatrixX;
	Matrix3 rotationMatrixY;
	Matrix3 translationMatrix;
	Matrix3 scaleMatrix;
};