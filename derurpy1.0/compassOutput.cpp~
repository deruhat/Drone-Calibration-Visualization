#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "SDL_rotozoom.h"
#include <ros/ros.h>
#include "std_msgs/Int32.h"
#include <geometry_msgs/Point.h>
#include <string>
#include <sstream>
#define SDL_MAIN_HANDLED

using namespace std;

//FOR ANGLE FETCH:
static float angles [3];
        
void chatterCallback(const geometry_msgs::Point::ConstPtr& msg) {
	//ANGLE DETECTION (ROS TOPIC "data"):
	angles[0] = -msg->x;
	angles[1] = -msg->y;
	angles[2] = -msg->z;
}

int main(int argc, char** argv){
	
	//ROS INITIATION:
	ros::init(argc, argv, "compassOutput");
	ros::start();
	ros::NodeHandle n;
	ROS_INFO_STREAM("Compass started . . .");

	//SDL INITIATION AND SURFACE DECLARATION:
	SDL_Init(SDL_INIT_EVERYTHING); 
	SDL_Surface *screen;
	SDL_Surface* icon;
	screen = SDL_SetVideoMode(941, 410, 32, SDL_SWSURFACE);
	icon = SDL_LoadBMP("icon3.bmp");
	SDL_SetColorKey(icon, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 255, 255, 255));
	SDL_WM_SetIcon(icon,NULL);
	SDL_WM_SetCaption("DeruRPY 1.0", "DeruRPY 1.0");
	SDL_Surface *image, *needle;
	SDL_Surface *image2, *needle2;
	SDL_Surface *image3, *needle3;
	SDL_Surface* compatibleCompassNeedle = NULL;
	SDL_Surface* compatibleCompassNeedle2 = NULL;
	SDL_Surface* compatibleCompassNeedle3 = NULL;
	TTF_Init();
	if (TTF_Init() != 0)
	{
		cerr << "TTF_Init() Failed: " << TTF_GetError() << endl;
		SDL_Quit();
		exit(1);
	}
	TTF_Font *font, *fontRPY;
	font = TTF_OpenFont("Tahoma.ttf", 24);
	fontRPY = TTF_OpenFont("Tahoma.ttf", 12);
	if (font == NULL)
	{
		cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;
		TTF_Quit();
		SDL_Quit();
		exit(1);
	}
	SDL_Surface *text;
	SDL_Surface *text2;
	SDL_Surface *text3;
	SDL_Surface *detailsYAW, *detailsPITCH, *detailsROLL, *angleYAW, *anglePITCH, *angleROLL;
	SDL_Color text_color = {225, 225, 225};
	text = TTF_RenderText_Blended(font, "X", text_color);
	text2 = TTF_RenderText_Blended(font, "Y", text_color);
	text3 = TTF_RenderText_Blended(font, "Z", text_color);
	detailsYAW = TTF_RenderText_Blended(fontRPY, "Yaw (X) angle:", text_color);
	detailsPITCH = TTF_RenderText_Blended(fontRPY, "Pitch (Y) angle:", text_color);
	detailsROLL = TTF_RenderText_Blended(fontRPY, "Roll (Z) angle:", text_color);
	if (text == NULL)
	{
		cerr << "TTF_RenderText_Blended() Failed: " << TTF_GetError() << endl;
		TTF_Quit();
		SDL_Quit();
		exit(1);
	}
	
	//IMAGE LOADING AND SETTING:
	image = SDL_DisplayFormat(SDL_LoadBMP("OuterRing.bmp"));
	image2 = SDL_DisplayFormat(SDL_LoadBMP("OuterRing.bmp"));
	image3 = SDL_DisplayFormat(SDL_LoadBMP("OuterRing.bmp"));
	SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 255, 255, 255));
	SDL_SetColorKey(image2, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 255, 255, 255));
	SDL_SetColorKey(image3, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 255, 255, 255));
	needle = SDL_DisplayFormat(SDL_LoadBMP("CompassNeedle.bmp"));
	needle2 = SDL_DisplayFormat(SDL_LoadBMP("CompassNeedle.bmp"));
	needle3 = SDL_DisplayFormat(SDL_LoadBMP("CompassNeedle.bmp"));
	compatibleCompassNeedle = SDL_DisplayFormatAlpha(needle);
	compatibleCompassNeedle2 = SDL_DisplayFormatAlpha(needle2);
	compatibleCompassNeedle3 = SDL_DisplayFormatAlpha(needle2);
	SDL_SetColorKey(needle, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 255, 255, 255));
	SDL_SetColorKey(needle2, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 255, 255, 255));
	SDL_SetColorKey(needle3, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 255, 255, 255));
	
	//STRING REPRESENTATIONS OF THE ANGLES:
	std::string yaw = std::to_string(-angles[0]);
	std::string pitch = std::to_string(-angles[1]);
	std::string roll = std::to_string(-angles[2]);

	//STRING ANGLES TO BLIT LATER:
	angleYAW = TTF_RenderText_Blended(fontRPY, yaw.c_str(), text_color);
	anglePITCH = TTF_RenderText_Blended(fontRPY, pitch.c_str(), text_color);
	angleROLL = TTF_RenderText_Blended(fontRPY, roll.c_str(), text_color);
		
	//INITIAL SCREEN FLIPPING:
	SDL_FillRect(screen, NULL, 0x000000); // 0xFFFFFF = white in RGB, NULL = full window
	SDL_Flip(screen);
	
	//LOOP VARIABLES:
    	bool running = true;
	const int FPS = 40;	
	Uint32 start;
	
	//SUBSCRIBER CALLBACK:
	ros::Subscriber sub = n.subscribe("data", 1000, chatterCallback);
	
	//MAIN LOOP:
	while(running){
		
		start = SDL_GetTicks();
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
		    switch(event.type) {
			    case SDL_QUIT:
				    running = false;
                                    break;
		    }
		}
		//MOVEMENT DETECTION:
	  	ROS_INFO("YAW:   [%f] degrees.", -angles[0]);
	  	ROS_INFO("PITCH: [%f] degrees.", -angles[1]);
	  	ROS_INFO("ROLL:  [%f] degrees.", -angles[2]);
	
	    	//INITIAL DECLARATION FOR LOGIC AND RENDER ROTATION:
		SDL_Rect c2_loc; // 2nd outercompass location
		c2_loc.x = 316;
		c2_loc.y = 0;
		SDL_Rect c3_loc; // 3rd
		c3_loc.x = 632;
		c3_loc.y = 0;
		SDL_Rect location; // 1st needle initial location
		location.x = 139.5;
		location.y = 18;
		SDL_Rect location2; // 2nd needle
		location2.x = 455.5;
		location2.y = 18;
		SDL_Rect location3; // 3rd needle
		location3.x = 771.5;
		location3.y = 18;
		
		//TEXT LOCATIONS:
		SDL_Rect text_loc;
		text_loc.x = 147.5;
		text_loc.y = 320;
		SDL_Rect text_loc2;
		text_loc2.x = 463.5;
		text_loc2.y = 320;
		SDL_Rect text_loc3;
		text_loc3.x = 779.5;
		text_loc3.y = 320;
		
		//DETAILS LOCATIONs:
		SDL_Rect yaw_loc;
		yaw_loc.x = 3;
		yaw_loc.y = 355;
		SDL_Rect pitch_loc;
		pitch_loc.x = 3;
		pitch_loc.y = 370;
		SDL_Rect roll_loc;
		roll_loc.x = 3;
		roll_loc.y = 385;
		
		//ANGLES LOCATIONs:
		SDL_Rect ayaw_loc;
		ayaw_loc.x = 100;
		ayaw_loc.y = 355;
		SDL_Rect apitch_loc;
		apitch_loc.x = 100;
		apitch_loc.y = 370;
		SDL_Rect aroll_loc;
		aroll_loc.x = 100;
		aroll_loc.y = 385;
		
		//ROTATING NEEDLES:
		SDL_Surface* rotatedneedle;
		SDL_Surface* rotatedneedle2;
		SDL_Surface* rotatedneedle3;
		
		//LOGIC AND RENDER ROTATION:
		rotatedneedle = rotozoomSurface(needle, angles[0], 1.0, 0);
		rotatedneedle2 = rotozoomSurface(needle2, angles[1], 1.0, 0);
		rotatedneedle3 = rotozoomSurface(needle3, angles[2], 1.0, 0);

		//RECENTERING NEEDLE PIVOT:
	 	location.x -= rotatedneedle->w/2-compatibleCompassNeedle->w/2;
		location.y -= rotatedneedle->h/2-compatibleCompassNeedle->h/2;
		location2.x -= rotatedneedle2->w/2-compatibleCompassNeedle2->w/2;
		location2.y -= rotatedneedle2->h/2-compatibleCompassNeedle2->h/2;
		location3.x -= rotatedneedle3->w/2-compatibleCompassNeedle3->w/2;
		location3.y -= rotatedneedle3->h/2-compatibleCompassNeedle3->h/2;

		//BLITTING IMAGES TO SURFACE AFTER ADJUSTMENT:
		SDL_FillRect(screen, NULL, 0);
		SDL_BlitSurface(image, NULL, screen, NULL);
		SDL_BlitSurface(rotatedneedle, NULL, screen, &location);
		SDL_BlitSurface(image2, NULL, screen, &c2_loc);
		SDL_BlitSurface(image3, NULL, screen, &c3_loc);
		SDL_BlitSurface(rotatedneedle2, NULL, screen, &location2);
		SDL_BlitSurface(rotatedneedle3, NULL, screen, &location3);
		SDL_BlitSurface(text, NULL, screen, &text_loc);
		SDL_BlitSurface(text2, NULL, screen, &text_loc2);
		SDL_BlitSurface(text3, NULL, screen, &text_loc3);
		SDL_BlitSurface(detailsYAW, NULL, screen, &yaw_loc);
		SDL_BlitSurface(detailsPITCH, NULL, screen, &pitch_loc);
		SDL_BlitSurface(detailsROLL, NULL, screen, &roll_loc);
		SDL_BlitSurface(angleYAW, NULL, screen, &ayaw_loc);
		SDL_BlitSurface(anglePITCH, NULL, screen, &apitch_loc);
		SDL_BlitSurface(angleROLL, NULL, screen, &aroll_loc);

		//FREEING ROTATED NEEDLES TO AVOID MEMORY LEAK:
		SDL_FreeSurface(rotatedneedle);
		SDL_FreeSurface(rotatedneedle2);
		SDL_FreeSurface(rotatedneedle3);
	
		//FLIPPING SCREEN:
	   	SDL_Flip(screen);
		if(1000/FPS > SDL_GetTicks()-start)
		{
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));	
		}
		
		//SPIN THROUGH TOPIC ONCE IN EVERY LOOP:
		ros::spinOnce();
	}
	  
	//FREEING WHEN QUIT:
	SDL_FreeSurface(compatibleCompassNeedle);
	SDL_FreeSurface(compatibleCompassNeedle2);
	SDL_FreeSurface(compatibleCompassNeedle3);
	SDL_FreeSurface(image);
	SDL_FreeSurface(image2);
	SDL_FreeSurface(image3);
	SDL_FreeSurface(text);
	SDL_FreeSurface(text2);
	SDL_FreeSurface(text3);
	SDL_FreeSurface(detailsYAW);
	SDL_FreeSurface(detailsPITCH);
	SDL_FreeSurface(detailsROLL);
	SDL_FreeSurface(angleYAW);
	SDL_FreeSurface(anglePITCH);
	SDL_FreeSurface(angleROLL);
	TTF_CloseFont(font);
	TTF_CloseFont(fontRPY);
	TTF_Quit();
	SDL_FreeSurface(screen);
	SDL_FreeSurface(icon);
    	SDL_Quit;
    	
	//ROS TERMINATION:
	ros::shutdown();
    	return 0;
}
