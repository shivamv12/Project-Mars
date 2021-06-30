#include          <dos.h>
#include         <math.h>
#include        <stdio.h>
#include        <conio.h>
#include       <stdlib.h>
#include     <iostream.h>
#include     <graphics.h>

#define cld cleardevice()

static double _projectionAngle = 0.0;
static const int _moonRadius = 20, _earthRadius = 40, _marsRadius = 25;

void _mars () {
    setfillstyle(9, BROWN);
    setcolor(BROWN);
    circle(getmaxx() - _marsRadius, 50, _marsRadius);
    floodfill(getmaxx() - 27, 52, BROWN);
}

void _moon () {
	setfillstyle(9, WHITE);
	setcolor(WHITE);
	circle(getmaxx()/2, getmaxy()/2, _moonRadius);
	floodfill(getmaxx()/2, getmaxy()/2, WHITE);

	//===== Moon's gravitational area
	setfillstyle(SOLID_FILL, DARKGRAY);
	setcolor(DARKGRAY);
	circle(getmaxx()/2, getmaxy()/2, _moonRadius * 5);
}

void _earth () {
	setfillstyle(9, GREEN);
	setcolor(GREEN);
	circle(40, getmaxy() - 100, _earthRadius);
	floodfill(42, getmaxy() - 102, GREEN);
}

void _countryFlag() {
	setcolor(GREEN);
	setfillstyle(1, GREEN);
	rectangle(getmaxx()/2 - 31, 200, getmaxx()/2 - 1, 240);
	floodfill(getmaxx()/2 - 29, 220, GREEN);
	setcolor(WHITE);
	setfillstyle(1, WHITE);
	rectangle(getmaxx()/2, 200, getmaxx()/2 + 30, 240);
	floodfill(getmaxx()/2 + 2, 201, WHITE);
	setcolor(GREEN);
	setfillstyle(1, GREEN);	
	rectangle(getmaxx()/2 + 31, 200, getmaxx()/2 + 61, 240);
	floodfill(getmaxx()/2 + 33, 201, GREEN);
}

void _loadingBar() {
	gotoxy(getmaxx()/2, getmaxy()/2);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t Mission Initiating...\n");
	setcolor(YELLOW);
	rectangle(0, 400, getmaxx(), 405);
	for(int i = 0; i <= getmaxx(); i++) {
		setcolor(RED);
		line(1, 401, i-1, 401);
		line(1, 402, i-1, 402);
		line(1, 403, i-1, 403);
		line(1, 404, i-1, 404);
		delay(10);
	}
}	

void _rocket (int x, int y) {
	// setcolor(WHITE);
    // rectangle(x, y, x + 10, y - 10);

	setcolor(YELLOW);
	arc(x, y, 30, 150, 25);
	arc(x, y - 25, 210, 330, 25);

	setcolor(CYAN);
	setfillstyle(1, CYAN);
	circle(x, y - 13, 6);
	floodfill(x + 2, y - 11, CYAN);
}

void _rocketClear (int x, int y) {
	// setcolor(BLACK);
	// rectangle(x, y, x + 10, y - 10);

	setcolor(BLACK);
	arc(x, y, 30, 150, 25);
	arc(x, y - 25, 210, 330, 25);
	
	setcolor(BLACK);
	setfillstyle(1, BLACK);
	circle(x, y - 13, 6);
	floodfill(x + 2, y - 11, BLACK);
}

void main () {
	clrscr();
	int angle, speed;

	gotoxy(150,100);
	printf("\n\n\t\t\tWelcome to NASRDA Space Mission\n");
	delay(1000);
	gotoxy(350,240);
	printf("\nWe are about to lauch our Mars mission.\n\tWe need to find out the exact projection speed and angle through this simulation to make our mission successful and cost effective.");
	delay(5000);

	printf("\n\nPlease provide parameters.\n\nEnter projection angle (range from 5 to 90)\n");
	scanf("%d", &angle);

	if(angle > 90 || angle < 5) {
		printf("\nInvalid projection angle! Program terminated.");
		getch();
		exit(0);
	}

	printf("\nProjection angle is %d deg", angle);
	delay(1000);
    _projectionAngle = (angle * 3.14) / 180.0;

	printf("\n\nEnter projection speed (range from 10 to 100)\n");
	scanf("%d", &speed);
	printf("\nProjection speed is %d", speed);
	delay(1000);

	if(speed > 100 || speed < 10) {
		printf("\nInvalid projection speed! Program terminated.");
		getch();
		exit(0);
	}

	int gd=DETECT, gm, i, j, k;
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

	_countryFlag();
	_loadingBar();

	cld;

	_mars();
	_moon();
	_earth();
	_rocket(100, getmaxy() - 100);
	// _ignition();

	//===== Some sound effect
	// for (int a = 0; a <= 3000; a = a + 20) {
	//	sound(a);
	//	delay(25);
	// }
	// nosound();

	//===== To store prev position
    int prev_i = 100, prev_j = getmaxy() - 100;

    //===== Increments will be constant for a given angle and speed
    const int x_inc = cos(_projectionAngle) * speed;
    const int y_inc = sin(_projectionAngle) * speed;

    //===== i and j will be updated with their respective increments
    for (i = 100, j = getmaxy() - 100; i < getmaxx() + 100 && j >= -10; i += x_inc, j -= y_inc) {
        //===== clear the previous position
        _rocketClear(prev_i, prev_j);

        //===== draw rocket at current position
        _rocket(i, j);

		sound(i);

        //===== make current position as previous position
        prev_i = i;
        prev_j = j;
        
		//===== Speed implementation
		delay(500 / speed);

		nosound();
    }

	getch();
}
