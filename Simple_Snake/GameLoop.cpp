#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <list>
#include "GameState.h"
#include "Snake.h"
#include "Wall.h"
#include "Fruit.h"
#include <gl/gl.h>
#include <gl/glu.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

// Structure to store the required globals
struct Globals
{
	HINSTANCE hInstance;    // window app instance
	HWND hwnd;				// handle for the window
	HDC   hdc;				// handle to device context
	HGLRC hglrc;			// handle to OpenGL rendering context
	int width, height;      // the desired width and height of the CLIENT AREA (DRAWABLE REGION in Window)
};

// Declare a structure to hold globals
Globals g;

// Other globals
GameState gameState = GameState::RUNNING;
GLfloat playWidth = 1.9f;
GLfloat playHeight = 1.8f;
GLfloat goalSize = 0.05f;
GLfloat standardSize = 0.02f;
GLfloat speed = 0.005f;
// Create walls
Wall goalWall = Wall(0, (playHeight / 2) - (standardSize / 2), standardSize, goalSize);
Wall leftWall = Wall((-playWidth / 2) + (standardSize / 2), 0, playHeight, standardSize);
Wall rightWall = Wall((playWidth / 2) + (standardSize / 2), 0, playHeight, standardSize);
Wall bottomWall = Wall(0, (-playHeight / 2) + (standardSize / 2), standardSize, playWidth);
Wall topLeftWall = Wall((-playWidth / 4) - (goalSize / 2) + (standardSize / 2),
	(playHeight / 2) - (standardSize / 2),
	standardSize,
	(playWidth / 2) - (goalSize / 2));
Wall topRightWall = Wall((playWidth / 4) + (goalSize / 2) - (standardSize / 2),
	(playHeight / 2) - (standardSize / 2),
	standardSize,
	(playWidth / 2) - (goalSize / 2));
std::list<Wall> walls = { goalWall, leftWall, rightWall, bottomWall, topLeftWall, topRightWall };

// Create fruit
Fruit fruit = Fruit(5, 0.0f, 0.0f, standardSize, standardSize);

// Create snake
Snake snake = Snake(Direction::RIGHT, Point(0.0f, 0.0f), standardSize, standardSize);

std::clock_t start;

// Function prototypes.
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow);
void draw();
void drawSplash();
void drawMenu();
void drawWalls();
void drawHud();
void drawFruit();
void drawSnake();
void drawWin();
void drawGameOver();
void drawCredits();
void checkCollisions();
void keyboardControls(WPARAM wparam);

/*
 * Main loop sets up the OpenGL window and draw loop
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
	g.hInstance = hInstance;

	// Describe the window to create
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("Snake");
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	// Register that class with the Windows O/S..
	RegisterClass(&wc);

	// Setup the rectangle for the screen
	RECT rect;
	SetRect(&rect, 50, 50, 850, 650);
	// Save width and height off.
	g.width = rect.right - rect.left;
	g.height = rect.bottom - rect.top;

	// Adjust the rect for the window
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// Create window using adjusted RECT structure to specify the width and height of the window.
	g.hwnd = CreateWindow(TEXT("Snake"),
			 TEXT("Simple Snake"),
			 WS_OVERLAPPEDWINDOW,
			 rect.left, rect.top,								// adjusted x, y positions
			 rect.right - rect.left, rect.bottom - rect.top,	// adjusted width and height
			 NULL, NULL,
			 hInstance, NULL);

	// Show the window if it was created correctly or exit
	if (g.hwnd == NULL)
	{
		FatalAppExit(NULL, TEXT("CreateWindow() failed!"));
	}
	ShowWindow(g.hwnd, iCmdShow);

	// Store DC in structure
	g.hdc = GetDC(g.hwnd);

	// Set up the Pixel Format Descriptor
	PIXELFORMATDESCRIPTOR pfd = { 0 };			// Create the pfd, and start it out with ALL ZEROs in ALL of its fields
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);  // Size of PFD
	pfd.nVersion = 1;							// Always 1

	pfd.dwFlags = PFD_SUPPORT_OPENGL |			// OpenGL support - not DirectDraw
				  PFD_DOUBLEBUFFER |			// double buffering support
				  PFD_DRAW_TO_WINDOW;			// draw to the app window, not to a bitmap image

	pfd.iPixelType = PFD_TYPE_RGBA;		// red, green, blue, alpha for each pixel
	pfd.cColorBits = 24;                // 8 bits for red, 8 for green, 8 for blue.
	pfd.cDepthBits = 32;                // 32 bits to measure pixel depth.  That's accurate!

	// Get a Pixel Format that is close to the specs above
	int chosenPixelFormat = ChoosePixelFormat(g.hdc, &pfd);
	// If 0 returned, then there was an error.
	if (chosenPixelFormat == 0)
	{
		FatalAppExit(NULL, TEXT("ChoosePixelFormat() failed!"));
	}
	// Set the format
	int result = SetPixelFormat(g.hdc, chosenPixelFormat, &pfd);
	if (result == NULL)
	{
		FatalAppExit(NULL, TEXT("SetPixelFormat() failed!"));
	}
	
	// Create Rendering context (Drawing surface)
	g.hglrc = wglCreateContext(g.hdc);
	// Connect the render context(HGLRC0 with the device context (HDC) of the window
	wglMakeCurrent(g.hdc, g.hglrc);

	// Message loop
	MSG msg;
	start = std::clock();

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			checkCollisions();
			draw();
		}
	}

	// Clean up when done
	// UNmake your rendering context (make it 'uncurrent')
	wglMakeCurrent(NULL, NULL);

	// Delete the rendering context, we no longer need it.
	wglDeleteContext(g.hglrc);

	// release your window's DC
	ReleaseDC(g.hwnd, g.hdc);

	// and a cheesy fade exit
	AnimateWindow(g.hwnd, 200, AW_HIDE | AW_BLEND);

	return msg.wParam;
}


/*
 * Handles messages and sends user controls to keyboardControls()
 */
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_CREATE:
		Beep(50, 10);
		return 0;
		break;

	case WM_PAINT:
	{
		HDC hdc;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
	}
	return 0;
	break;

	case WM_KEYDOWN:
		keyboardControls(wparam);
		return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	}

	return DefWindowProc(hwnd, message, wparam, lparam);
}


/*
*
*/
void checkCollisions()
{
	if (snake.checkWallCollisions(walls))
	{
		snake.setDirection(Direction::NONE);
		gameState = GAME_OVER;
	}
	if (snake.checkFruitCollisions(fruit)) fruit.move();
}

/*
 * Draw the screen
 */
void draw()
{
	// Set up the viewport
	glViewport(0, 0, g.width, g.height);

	// Viewing transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Modelling transformation and drawing
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static clock_t animStart = std::clock();
	double dt = std::clock() - animStart;
	switch (gameState)
	{
	case SPLASH:
		break;
	case MENU:
		break;
	case RUNNING:
		if (dt > 60)
		{
			snake.move(speed);
			checkCollisions();
			animStart = std::clock();
		}
		drawWalls();
		drawFruit();
		drawSnake();
		break;
	case PAUSE:
		break;
	case GAME_OVER:
		break;
	case WIN:
		break;
	case CREDITS:
		break;
	}


	// Swap buffers
	SwapBuffers(g.hdc);
}

/*
 *
 */
void drawSplash()
{

}

void drawMenu()
{
}

/*
*
*/
void drawWalls()
{
	glColor3f(255, 255, 255);
	for (Wall w : walls) {
		glRectf(w.getLeft(), w.getTop(), w.getRight(), w.getBottom());
	}
}

void drawHud()
{
	//glRasterPos2f(0.0f, 0.0f);
	//glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	//printText2D();
}

void drawFruit()
{
	glColor3f(0.0f, 255.0f, 0.0f);
	glRectf(fruit.getLeft(), fruit.getTop(), fruit.getRight(), fruit.getBottom());
}

void drawWin()
{
}

/*
 * 
 */
void drawSnake()
{
	glColor3f(0.0f, 0.0f, 255.0f);
	glRectf(snake.getLeft(), snake.getTop(), snake.getRight(), snake.getBottom());
}

/*
*
*/
void drawGameOver()
{
	glBegin(GL_LINES);
	glColor3f(255.0f, 0.0f, 0.0f);

	glVertex3f(-0.7f, 0.7f, 0.0f);
	glVertex3f(-0.7f, -0.7f, 0.0f);
	glVertex3f(-0.7f, -0.7f, 0.0f);
	glVertex3f(-0.5f, -0.7f, 0.0f);

	glEnd();
}

/*
 * 
 */
void drawCredits()
{

}

/*
 * 
 */
void keyboardControls(WPARAM wparam)
{
	switch (gameState)
	{
	case SPLASH:
		break;
	case MENU:
		break;
	case RUNNING:
		switch (wparam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case VK_LEFT:
			snake.setDirection(Direction::LEFT);
			break;
		case VK_RIGHT:
			snake.setDirection(Direction::RIGHT);
			break;
		case VK_UP:
			snake.setDirection(Direction::UP);
			break;
		case VK_DOWN:
			snake.setDirection(Direction::DOWN);
			break;
			//case VK_P:
			//	
			//	break;
		default:
			break;
		}
	case PAUSE:
		break;
	case GAME_OVER:
		break;
	case WIN:
		break;
	case CREDITS:
		break;
	default:
		break;
	}

}