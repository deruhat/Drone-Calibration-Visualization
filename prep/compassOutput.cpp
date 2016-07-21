#include <iostream>
#include <SDL/SDL.h>
#include "SDL_rotozoom.h"
#include <ros/ros.h>
#include "std_msgs/Int32.h"
#include <string>
#include <sstream>

using namespace std;

SDL_Surface *screen, *image, *needle;
        
void chatterCallback(const std_msgs::Int32::ConstPtr& msg) {
	SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Surface *screen, *image, *needle;
	SDL_Surface* compatibleCompassNeedle = NULL;
        screen = SDL_SetVideoMode(309, 400, 32, SDL_SWSURFACE);
	SDL_FillRect(screen, NULL, 0x000000); // 0xFFFFFF = white in RGB, NULL = full window
	SDL_Flip(screen);
        bool running = true;
	const int FPS = 40;	
	Uint32 start;
	int angle = 0;    

	
	image = SDL_DisplayFormat(SDL_LoadBMP("OuterRing.bmp"));
	SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 255, 255, 255));
	needle = SDL_DisplayFormat(SDL_LoadBMP("CompassNeedle.bmp"));
	compatibleCompassNeedle = SDL_DisplayFormatAlpha(needle);
	SDL_SetColorKey(needle, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 255, 255, 255));
  	ROS_INFO("Moved needle: [%d] degrees.", -msg->data);
        //while(running) {
		start = SDL_GetTicks();
                SDL_Event event;
                while(SDL_PollEvent(&event)) {
                        switch(event.type) {
                                case SDL_QUIT:
                                        running = false;
                                        break;
                        }
                }
                //logic && render
		SDL_Rect location;
		location.x = 139.5;
		location.y = 18;
		angle = msg->data;
		SDL_Surface* rotatedneedle = rotozoomSurface(needle, angle, 1.0, 0);
		//recenter pivote for rotation
       	 	location.x -= rotatedneedle->w/2-compatibleCompassNeedle->w/2;
        	location.y -= rotatedneedle->h/2-compatibleCompassNeedle->h/2;
		SDL_FillRect(screen, NULL, 0);
		SDL_BlitSurface(image, NULL, screen, NULL);
		SDL_BlitSurface(rotatedneedle, NULL, screen, &location);
 
                SDL_Flip(screen);
		if(1000/FPS > SDL_GetTicks()-start)
		{
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));	
		}
        //}
        //SDL_FreeSurface(image);
        //SDL_Quit();
}

int main(int argc, char** argv){
	ros::init(argc, argv, "compassOutput");
	ros::start();
	ros::NodeHandle n;
	ROS_INFO_STREAM("Compass started . . .");
	ros::Subscriber sub = n.subscribe("data", 1000, chatterCallback);
	ros::spin();
	ros::shutdown();
        return 0;
}
