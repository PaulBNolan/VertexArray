#include <Game.h>

bool flip = false;
int current = 1;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{
	m_initialPoints[0] = Vector3D(1.0f, 1.0f, -5.0f);
	m_initialPoints[1] = Vector3D(-1.0f, 1.0f, -5.0f);
	m_initialPoints[2] = Vector3D(-1.0f, -1.0f, -5.0f);
	m_initialPoints[3] = Vector3D(1.0f, -1.0f, -5.0f);
	m_initialPoints[4] = Vector3D(1.0f, 1.0f, -15.0f);
	m_initialPoints[5] = Vector3D(-1.0f, 1.0f, -15.0f);
	m_initialPoints[6] = Vector3D(-1.0f, -1.0f, -15.0f);
	m_initialPoints[7] = Vector3D(1.0f, -1.0f, -15.0f);

	rotationMatrixX = rotationMatrixX.RotationX(rotationAngleX);
	rotationMatrixY = rotationMatrixY.RotationY(rotationAngleY);

	scaleMatrix = scaleMatrix.Scale3D(scaleFactor);

	translationMatrix = translationMatrix.Translate(translationFactorX, translationFactorY);
}

Game::~Game() {}

float vertices[] =
{
 1.0f, 1.0f, -5.0f,
-1.0f, 1.0f,  -5.0f,
-1.0f, -1.0f,  -5.0f,
 1.0f, -1.0f,  -5.0f,

 1.0f, 1.0f, -15.0f,
-1.0f, 1.0f, -15.0f,
-1.0f, -1.0f, -15.0f,
 1.0f, -1.0f, -15.0f
};

float colors[] =
{ 1.0f, 0.0f, 0.0f, 
0.0f, 1.0f, 0.0f, 
0.0f, 0.0f, 1.0f,
1.0f, 0.0f, 1.0f,
1.0f, 1.0f, 0.0f,
0.0f, 1.0f, 1.0f };

unsigned int vertex_index[] = {
                                4, 5, 6,  6, 7, 4,

                                0, 1, 5,  5, 4, 0,

	                            2, 3, 7,  7, 6, 2, 

	                            1, 5, 6,  6, 2, 1,

	                            4, 0, 3,  3, 7, 4,

								0, 1, 2,  2, 3, 0
};

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		//cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				rotationAngleX += 1.0f;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				rotationAngleX -= 1.0f;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				rotationAngleY += 1.0f;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				rotationAngleY -= 1.0f;
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				translationFactorY -= 1;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				translationFactorY += 1;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				translationFactorX -= 1;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				translationFactorX += 1;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				scaleFactor += 10.0f;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				scaleFactor -= 10.0f;
			}
		}
		update();
		render();
	}

}

void Game::initialize()
{
	isRunning = true;

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	rotationMatrixX = rotationMatrixX.RotationX(rotationAngleX);
	rotationMatrixY = rotationMatrixY.RotationY(rotationAngleY);

	scaleMatrix = scaleMatrix.Scale3D(scaleFactor);

	translationMatrix = translationMatrix.Translate(translationFactorX, translationFactorY);
	for (int index = 0; index < 8; index++)
	{
		m_currentPoints[index] = m_initialPoints[index];
		m_currentPoints[index] = rotationMatrixX * m_currentPoints[index];
		m_currentPoints[index] = rotationMatrixY * m_currentPoints[index];

		m_currentPoints[index] = translationMatrix * m_currentPoints[index];

		m_currentPoints[index] = scaleMatrix * m_currentPoints[index];

		vertices[index * 3] = m_currentPoints[index].x;
		vertices[index * 3 + 1] = m_currentPoints[index].y;
		vertices[index * 3 + 2] = m_currentPoints[index].z;

	}

	//cout << "Update up" << endl;
}

void Game::render()
{
	//cout << "Drawing" << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &vertices);
	glColorPointer(3, GL_FLOAT, 0, &colors);

	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &vertex_index);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	window.display();

}

void Game::unload()
{
	//cout << "Cleaning up" << endl;
}

