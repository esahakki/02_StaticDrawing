#include "pch.h"

#pragma region generalDirectives
// SDL libs
#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "SDL2main.lib")

// OpenGL libs
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Glu32.lib")

// SDL and OpenGL Includes
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#pragma endregion generalDirectives

#include <iostream>
#include <string>
#include <ctime>

#pragma region windowInformation
const float g_WindowWidth{ 500.0f };
const float g_WindowHeight{ 300.0f };
const std::string g_WindowTitle{ u8"StaticDrawing - H�kkinen, Esa - 1DAE08" };
bool g_IsVSyncOn{ true };
#pragma endregion windowInformation

#pragma region coreDeclarations
// Functions
void Initialize( );
void Cleanup( );
void QuitOnSDLError( );
void QuitOnOpenGlError( );
// Game functions
void DrawHouse();
void DrawFlag();
void DrawCheckerPattern();
void DrawColorBand();
void DrawPentagram();
void DrawColumnChart();
// Variables
SDL_Window* g_pWindow{ nullptr }; // The window we'll be rendering to
SDL_GLContext g_pContext; // OpenGL context
#pragma endregion coreDeclarations

#pragma region gameDeclarations
// Functions
void Draw( );
void ClearBackground( );

// Variables
#pragma endregion gameDeclarations



int main( int argc, char* args[] )
{
	// seed the pseudo random number generator
	srand(unsigned int(time(nullptr)));
	
	// Initialize SDL and OpenGL
	Initialize( );

	// Draw on the window
	Draw( );

	// Update window
	SDL_GL_SwapWindow( g_pWindow );


	// Wait for user to quit the program
	std::cout << "Press ENTER to quit\n";
	std::cin.get( );


	// Clean up SDL and OpenGL
	Cleanup( );

	return 0;
}

#pragma region gameImplementations
void ClearBackground( )
{
	glClearColor( 44.0f / 255.0f, 21.0f / 255.0f, 45.0f / 255.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Draw( )
{
	ClearBackground( );
	// add your drawing code here

	DrawHouse();
	DrawFlag();
	DrawCheckerPattern();
	DrawColorBand();
	DrawPentagram();
	DrawColumnChart();
}
void DrawHouse()
{
	// Roof triangle
	float basex{ 10.f }, basey{ 250.0f };
	glColor3f(255.f / 255.f, 0.f / 255.f, 0.f / 255.f);
	glLineWidth(0.0f);
	// background solid
	glBegin(GL_POLYGON);
		glVertex2f(basex +   0.0f, basey +   0.0f);
		glVertex2f(basex + 200.0f, basey +   0.0f);
		glVertex2f(basex + 100.0f, basey +  40.0f);
	glEnd();
	
	// foreground line
	glColor3f(255.f / 255.f, 255.f / 255.f, 255.f / 255.f);
	glLineWidth(1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(basex +   0.0f, basey +   0.0f);
	glVertex2f(basex + 200.0f, basey +   0.0f);
	glVertex2f(basex + 100.0f, basey +  40.0f);
	glEnd();

	// Wall square
	glColor3f(255.f / 255.f, 0.f / 255.f, 0.f / 255.f);
	glLineWidth(0.0f);
	// background solid
	glBegin(GL_POLYGON);
	glVertex2f(basex +   0.0f, basey +   0.0f);
	glVertex2f(basex + 200.0f, basey +   0.0f);
	glVertex2f(basex + 200.0f, basey -  40.0f);
	glVertex2f(basex +   0.0f, basey -  40.0f);
	glEnd();

	// foreground line
	glColor3f(255.f / 255.f, 255.f / 255.f, 255.f / 255.f);
	glLineWidth(1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(basex +   0.0f, basey +   0.0f);
	glVertex2f(basex + 200.0f, basey +   0.0f);
	glVertex2f(basex + 200.0f, basey -  40.0f);
	glVertex2f(basex +   0.0f, basey -  40.0f);
	glEnd();

	return;
}

void DrawFlag()
{

}
void DrawCheckerPattern()
{

}
void DrawColorBand()
{

}
void DrawPentagram()
{

}
void DrawColumnChart()
{

}
#pragma endregion gameImplementations

#pragma region coreImplementations
void Initialize( )
{
	//Initialize SDL
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		QuitOnSDLError( );
	}

	//Use OpenGL 2.1
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

	//Create window
	g_pWindow = SDL_CreateWindow(
		g_WindowTitle.c_str( ),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		int( g_WindowWidth ),
		int( g_WindowHeight ),
		SDL_WINDOW_OPENGL );

	if ( g_pWindow == nullptr )
	{
		QuitOnSDLError( );
	}

	// Create an opengl context and attach it to the window 
	g_pContext = SDL_GL_CreateContext( g_pWindow );
	if ( g_pContext == nullptr )
	{
		QuitOnSDLError( );
	}

	// Set the swap interval for the current OpenGL context synchronized with the vertical retrace
	if ( g_IsVSyncOn )
	{
		if ( SDL_GL_SetSwapInterval( 1 ) < 0 )
		{
			QuitOnSDLError( );
		}
	}
	else
	{
		SDL_GL_SetSwapInterval(0);
	}


	// Initialize Projection matrix
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	// Set the clipping (viewing) area's left, right, bottom and top
	gluOrtho2D( 0, g_WindowWidth, 0, g_WindowHeight );

	// The viewport is the rectangular region of the window where the image is drawn.
	// Set it to the entire client area of the created window
	glViewport(0, 0, int(g_WindowWidth), int(g_WindowHeight));

	//Initialize Modelview matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	// Enable color blending and use alpha blending
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void Cleanup( )
{
	SDL_GL_DeleteContext( g_pContext );

	SDL_DestroyWindow( g_pWindow );
	g_pWindow = nullptr;

	SDL_Quit( );
}


void QuitOnSDLError( )
{
	std::cout << "Problem during SDL initialization: ";
	std::cout << SDL_GetError( );
	std::cout << std::endl;
	Cleanup( );
	exit( -1 );
}
void QuitOnOpenGlError( )
{
	std::cout << "Problem during OpenGL initialization: ";
	std::cout << SDL_GetError( );
	std::cout << std::endl;
	Cleanup( );
	exit( -1 );
}

#pragma endregion coreImplementations
