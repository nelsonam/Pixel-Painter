#include "headers/SDL/SDL.h"
#include "headers/SDL/SDL_main.h"
#include "headers/SDL/SDL_opengl.h"
#include <stdio.h>
#include <math.h>

//New defines that we can use inside of mouse input handling to avoid magic numbers
#define WINDOW_WIDTH  500
#define WINDOW_HEIGHT 500
//size of each grid cell
#define GRID_SIZE 25 //50

//Means of the user exiting the main loop
static int user_exit = 0;

//Eventually these will be moved out of here into a "rendering" subsystem, which is why they are prefixed r_.
static void r_init();
static void r_drawFrame();

//Fancy new input declarations - we will also want to move this out of here.
static int keys_down[256];
static void input_update();
static void input_keyDown(SDLKey k);
static void input_keyUp(SDLKey k);
static void input_mouseMove(int xPos, int yPos);

//used to represent color values for the background
static float r;
static float g;
static float b;

//2D array of grid cells - 1 denotes the cell is "on"(clicked), 0 is not "on"
static int cells[20][20]; //10x10
/*
 * SDL_main
 * Program entry point
 */
int SDL_main(int argc, char* argv[])
{
	SDL_Event	event;
	SDL_Surface	*screen;

	r = .4;
	g = .7;
	b = .4;

	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
	{
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	SDL_WM_SetCaption("Pixel Painter", "Pixel Painter");
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_OPENGL);
	if(!screen)
	{
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}

	//Renderer
	r_init();

	while(!user_exit)
	{
		//Handle input
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_KEYDOWN:
				input_keyDown(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				input_keyUp(event.key.keysym.sym);
				break;
			case SDL_MOUSEMOTION:
				input_mouseMove(event.motion.x, event.motion.y);
				break;
			case SDL_MOUSEBUTTONDOWN:
				  if(event.button.button == SDL_BUTTON_LEFT)
				  {
					  int x = event.button.x;
					  int y = event.button.y;
					  int gridCell_X = floor(x/GRID_SIZE);
					  int gridCell_Y = floor(y/GRID_SIZE);
					  if(cells[gridCell_X][gridCell_Y]==0)
						  cells[gridCell_X][gridCell_Y] = 1;
					  else if(cells[gridCell_X][gridCell_Y]==1)
						  cells[gridCell_X][gridCell_Y] = 0;
					  printf("x:%d y:%d gX:%d gY:%d \n",x,y,gridCell_X,gridCell_Y);
				  }
				  break;
			case SDL_QUIT:
				exit(0);
			}
		}

		//Respond to keys being down
		input_update();

		//Draw the scene
		r_drawFrame();
	}

	SDL_Quit();
	return 0;
}

//We simply flag whether a key is up or down when it actually occurs, and then
//do the logic in a single update later on. If you don't do it this way things like
//using input to move the camera ends up being super stuttery, due to whatever reason.
static void input_keyDown(SDLKey k) { keys_down[k] = 1; if(k == SDLK_ESCAPE || k == SDLK_q) user_exit = 1; }
static void input_keyUp  (SDLKey k) { keys_down[k] = 0; }

//Mouse input is more complicated...
//The input event gives you where the mouse is located in screen coordinates.
//In our case, this means xPos will be between 0 and 1024, and yPos between
//0 and 768. Try printing out the values to get an idea of how the coordinates
//are oriented.
//Imagine how a first person camera typically works, and try to think of what is
//occurring in terms of matrix transformations. Since we know that the camera is
//looking down the -Z axis in the default OpenGL setup, and that we typically
//deal with rotations about axes, which rotations correspond to moving the mouse
//up/down or left/right?
//One other problem you will face is how to transform the screen coordinates of
//the mouse movement into a useful form to use inside of a rotation matrix.
//A simple way to achieve this is to reset the cursor to the middle of the window
//after each mouse movement. Then, you can get a delta movement out of the screen
//coordinates by simply subtracting half of the screen width/height. This can
//be translated into an angle of rotation directly, although you may need to scale
//the value (i.e. adjust the sensitivity).
static void input_mouseMove(int xPos, int yPos)
{
	float halfWinWidth, halfWinHeight,
		  dx, dy;

	halfWinWidth  = (float)WINDOW_WIDTH  / 2.0;
	halfWinHeight = (float)WINDOW_HEIGHT / 2.0;

	dx = xPos - halfWinWidth; dy = yPos - halfWinHeight;

	//Do something with deltas.

	//Reset cursor to center
	//SDL_WarpMouse(halfWinWidth, halfWinHeight);
}

//This function is currently being called each time we run through the main loop.
//By the time it is executed, all keys will have been registered as down or up.
//You can use this information inside of a simple check to do things like
//move the camera in a certain direction.
static void input_update()
{
	if(keys_down['1'])
	{
		r = 0.7;
		g = 0.75;
		b = 0.0;
	}
	if(keys_down['2'])
	{
		r = .7;
		g = .25;
		b = 1.0;
	}
	if(keys_down['3'])
	{
		r = 0.75;
		g = 0.0;
		b = 0.0;
	}
	r_drawFrame();
}

/*
 * r_init
 * Initializes rendering state.
 */
static void r_init()
{
	glEnable(GL_DEPTH_TEST);

	//Make lines a little bigger
	glLineWidth(2.0);
}

/*
 * r_drawFrame
 * Produces a final image of the scene.
 */
static void r_drawFrame()
{
	//sets the background color based on what button user presses
	glClearColor(r, g, b, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//this draws the grid
	 glBegin(GL_LINES);
	 glColor3f(0.0,0.0,0.0);
	 float i;
	 //horizontal lines
	 for (i=-1.0; i<=1; i+=.1)
	 {
	      glVertex2f(-1.0, i);
	      glVertex2f(1, i);
	 }
	 //vertical lines
	 for (i=-1.0; i<=1; i+=.1)
	 {
	     glVertex2f(i, -1.0);
	     glVertex2f(i, 1);
	 }
	 glEnd();

	 //checks each cell to see if it was pressed, updates as necessary
	 int j,k;
	 for(j=0; j<(WINDOW_WIDTH/GRID_SIZE); j++)
	 {
		 for(k=0; k<(WINDOW_WIDTH/GRID_SIZE); k++)
		 {
			 if(cells[j][k]==1)
			 {
				 printf("cell %d,%d is on \n", j,k);
				 //GL_QUAD stuff, makes a filled square on top of the grid
				 glBegin(GL_QUADS);
				 	glColor3f(0.0,0.0,0.0);

				 	glVertex2f(-1+(.1*j),1-(.1*k)); //.8, .2
				 	glVertex2f(-.9+(.1*j),1-(.1*k));
				 	glVertex2f(-.9+(.1*j),.9-(.1*k));
				 	glVertex2f(-1+(.1*j),.9-(.1*k));

				 glEnd();
			 }
		 }
	 }


	 SDL_GL_SwapBuffers();
}

