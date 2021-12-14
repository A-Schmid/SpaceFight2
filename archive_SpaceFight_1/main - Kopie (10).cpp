#include <windows.h>
#include "main.h"
#include "math.h"
#include <list>
#include <time.h>
#include <stdlib.h> 
#include <stdio.h>
//#include <afxwin.h>

using namespace std;
/*  Declare Windows procedure  */

static HINSTANCE g_hInst = NULL;
/*  Make the class name into a global variable  */
char szClassName[ ] = "WindowsApp";
const UINT idTimer1 = 1;
UINT nTimerDelay = 0;

HBITMAP bg, guiBG;
HBITMAP livePic[10];
int first;
int i;
int eclapsed;
int lives100;
int lives10;
int lives1;
int tempint;
int maxlive = 200;
int msgbox1;
//long sek;
//time(&sek);
//srand((unsigned)sek);
//srand((unsigned)time(NULL));

/*class DROP
{
public:
	RECT rct;
    HBITMAP hbm;
    HBITMAP mask;
    BITMAP bmp;
    int X;
    int Y;
	int alive;
	int height;
	int width;
	int anim;
	int animtemp;
	HBITMAP frame[20];
	HBITMAP fmask[20];
	int framedelay;
	int framedelaytemp;
	void update();
};*/

class SHIELD
{
public:
	RECT rct;
	HBITMAP hbm;
	HBITMAP mask;
	BITMAP bmp;
	//int X;
    //int Y;
	float modifier;
	int on;
	int time;
	int reflect;
	void update()
	{
		if(time == 1)
		{
			//X = 2000;
			//Y = 2000;
			time = 0;
			on = 0;
			modifier = 1;
			reflect = 0;
		}
		else if(time > 1)
		{
			time--;
			on = 1;
		}
	}
};

class projectile
{    
	public:
	HDC hdc;
	RECT rct;
    HBITMAP hbm;
    HBITMAP mask;
    BITMAP bmp;
    int X;
    int Y;
    int A;
    int delta;
    int dmg;
    int owner;
	int alive;
	int height;
	int width;
	int follow;
	int type;
	int slow;
	int slowTime;
	SHIELD addShield;
	int anim;
	int animtemp;
	HBITMAP frame[20];
	int framedelay;
	int framedelaytemp;
	/*DROP drop[50];
	int dropnum;
	int dropdelay;
	int dropdelaytemp;*/
	void update();
};


class player
{
public:
	RECT rct;
	HBITMAP hbm;
	HBITMAP liveBmp[3];
	HBITMAP mask;
	BITMAP bmp;
	int X;
    int Y;
    int lives;
    int A;
    int skill;
    int wpn;
    int delta;
    int pid;
	int down;
	int speedbuffremove;
	int slowhealremove;
	float slowheal;
	int delay;
	float dmgModifier;
	int dmgModRemove;
	SHIELD shield;
};

class buff
{
public:
	int type;
/*	1 = heal
	2 = speed
	3 = shield
	4 = Standartwaffe
	5 = MG-Laser
	6 = Homing Missiles
	7 = Reflektor
	8 = Schock 
	9 = Eis */
	RECT rct;
	HBITMAP hbm;
	HBITMAP mask;
	BITMAP bmp;
	HDC hdc;
	int X;
    int Y;
	int alive;
	void create(HDC gethdc)
	{
		srand( (unsigned)time( NULL ) );
		type = rand()%18;
		//type = 7;
		type++;
		hdc = gethdc;
		X = rand()%900;
		X += 50;
		Y = rand()%650;
		Y += 20;
		mask = LoadBitmap(g_hInst, "BUFFMASK");
		switch(type)
		{
		case 1:
			hbm = LoadBitmap(g_hInst, "HEALBUFF1");
			break;
		case 2:
			hbm = LoadBitmap(g_hInst, "SPEEDBUFF1");
			break;
		case 3:
			hbm = LoadBitmap(g_hInst, "SHIELDBUFF1");
			break;
		case 4:
			hbm = LoadBitmap(g_hInst, "WPNROCKET1");
			break;
		case 5:
			hbm = LoadBitmap(g_hInst, "WPNMG1");
			break;
		case 6:
			hbm = LoadBitmap(g_hInst, "WPNROCKET2");
			break;
		case 7:
			hbm = LoadBitmap(g_hInst, "SHIELDBUFF2");
			break;
		case 8:
			hbm = LoadBitmap(g_hInst, "WPNSHOCK1");
			break;
		case 9:
			hbm = LoadBitmap(g_hInst, "WPNICE1");
			break;
		case 10:
			hbm = LoadBitmap(g_hInst, "WPNPSY1");
			break;
		case 11:
			hbm = LoadBitmap(g_hInst, "HEALBUFF3");
			break;
		case 12:
			hbm = LoadBitmap(g_hInst, "HEALBUFF4");
			break;
		case 13:
			hbm = LoadBitmap(g_hInst, "TRAP1");
			break;
		case 14:
			hbm = LoadBitmap(g_hInst, "TRAP1");
			break;
		case 15:
			hbm = LoadBitmap(g_hInst, "TRAP1");
			break;
		case 16:
			hbm = LoadBitmap(g_hInst, "TRAP1");
			break;
		case 17:
			hbm = LoadBitmap(g_hInst, "TRAP1");
			break;
		case 18:
			hbm = LoadBitmap(g_hInst, "DMGBUFF1");
			break;
		}
		alive = 1;
	}

	void update();

	void use(int Player);
};

player P1;
player P2;
SHIELD S1;
SHIELD S2;
projectile *proj = NULL;
list<projectile> listProj;
list<buff> listBuff;
int numProj;
int ereasevar;
int placebuffvar = 200;


/*HBITMAP GetRotatedBitmapNT( HBITMAP hBitmap, float deg, COLORREF clrBack, HDC hdc)
{
	// Create a memory DC compatible with the display
	
	HDC sourceDC, destDC;
	sourceDC = CreateCompatibleDC( hdc );
	destDC = CreateCompatibleDC( hdc );

	// Get logical coordinates
	BITMAP bm;
	::GetObject( hBitmap, sizeof( bm ), &bm );

    float radians = ((deg * 2 * 3.141) / 360);
	float cosine = (float)cos(radians);
	float sine = (float)sin(radians);

	// Compute dimensions of the resulting bitmap
	// First get the coordinates of the 3 corners other than origin
	int x1 = (int)(bm.bmHeight * sine);
	int y1 = (int)(bm.bmHeight * cosine);
	int x2 = (int)(bm.bmWidth * cosine + bm.bmHeight * sine);
	int y2 = (int)(bm.bmHeight * cosine - bm.bmWidth * sine);
	int x3 = (int)(bm.bmWidth * cosine);
	int y3 = (int)(-bm.bmWidth * sine);

	int minx = min(0,min(x1, min(x2,x3)));
	int miny = min(0,min(y1, min(y2,y3)));
	int maxx = max(0,max(x1, max(x2,x3)));
	int maxy = max(0,max(y1, max(y2,y3)));

	int w = maxx - minx;
	int h = maxy - miny;

	// Create a bitmap to hold the result
	HBITMAP hbmResult = ::CreateCompatibleBitmap(CClientDC(NULL), w, h);

	HBITMAP hbmOldSource = (HBITMAP)::SelectObject( sourceDC.m_hDC, hBitmap );
	HBITMAP hbmOldDest = (HBITMAP)::SelectObject( destDC.m_hDC, hbmResult );

	// Draw the background color before we change mapping mode
	HBRUSH hbrBack = CreateSolidBrush( clrBack );
	HBRUSH hbrOld = (HBRUSH)::SelectObject( destDC.m_hDC, hbrBack );
	destDC.PatBlt( 0, 0, w, h, PATCOPY );
	::DeleteObject( ::SelectObject( destDC.m_hDC, hbrOld ) );

	// We will use world transform to rotate the bitmap
	SetGraphicsMode(destDC.m_hDC, GM_ADVANCED);
	XFORM xform;
	xform.eM11 = cosine;
	xform.eM12 = -sine;
	xform.eM21 = sine;
	xform.eM22 = cosine;
	xform.eDx = (float)-minx;
	xform.eDy = (float)-miny;

	SetWorldTransform( destDC.m_hDC, &xform );

	// Now do the actual rotating - a pixel at a time
	destDC.BitBlt(0,0,bm.bmWidth, bm.bmHeight, &sourceDC, 0, 0, SRCCOPY );

	// Restore DCs
	::SelectObject( sourceDC.m_hDC, hbmOldSource );
	::SelectObject( destDC.m_hDC, hbmOldDest );

	return hbmResult;
}*/

void newgame()
{
	     bg          = LoadBitmap(g_hInst, "BACKGROUND");
         guiBG          = LoadBitmap(g_hInst, "GUIBG");

		livePic[0] = LoadBitmap(g_hInst, "NR0");
		livePic[1] = LoadBitmap(g_hInst, "NR1");
		livePic[2] = LoadBitmap(g_hInst, "NR2");
		livePic[3] = LoadBitmap(g_hInst, "NR3");
		livePic[4] = LoadBitmap(g_hInst, "NR4");
		livePic[5] = LoadBitmap(g_hInst, "NR5");
		livePic[6] = LoadBitmap(g_hInst, "NR6");
		livePic[7] = LoadBitmap(g_hInst, "NR7");
		livePic[8] = LoadBitmap(g_hInst, "NR8");
		livePic[9] = LoadBitmap(g_hInst, "NR9");

		if(!P1.hbm){P1.hbm      = LoadBitmap(g_hInst, "RAUMSCHIFF1");}
         P1.mask     = LoadBitmap(g_hInst, "RAUMSCHIFF1MASK");
         P1.X        = 200;
         P1.Y        = 380;
         P1.lives    = maxlive;
         P1.A        = 0;
         P1.skill    = 0;
         P1.wpn      = 1;
         P1.delta    = 4;
         P1.pid      = 1;
		 P1.down	 = 0;
		 P1.shield	 = S1;
		 P1.delay	 = 10;
		 P1.slowhealremove = 0;
		 P1.slowheal = 0;
		 P1.dmgModifier = 1;
		 P1.dmgModRemove = 0;

         P1.shield.hbm      = LoadBitmap(g_hInst, "SHIELD1");
         P1.shield.mask     = LoadBitmap(g_hInst, "SHIELD1MASK");
		 P1.shield.modifier = 1;
		 P1.shield.on		= 0;
		 P1.shield.reflect	= 0;


         if(!P2.hbm){P2.hbm      = LoadBitmap(g_hInst, "RAUMSCHIFF2BLUE");}
         P2.mask     = LoadBitmap(g_hInst, "RAUMSCHIFF2MASK");
         P2.X        = 800;
         P2.Y        = 380;
         P2.lives    = maxlive;
         P2.A        = 135;
         P2.skill    = 0;
         P2.wpn      = 1;
         P2.delta    = 4;
         P2.pid      = 2;
		 P2.down	 = 0;
		 P2.shield	 = S2;
		 P2.delay	 = 10;
		 P2.slowhealremove = 0;
		 P2.slowheal = 0;
		 P2.dmgModifier = 1;
		 P2.dmgModRemove = 0;

		 P2.shield.hbm      = LoadBitmap(g_hInst, "SHIELD2");
         P2.shield.mask     = LoadBitmap(g_hInst, "SHIELD2MASK");
		 P2.shield.modifier = 1;
		 P2.shield.on		= 0;
		 P2.shield.reflect	= 0;


		 list<buff>::iterator p2 = listBuff.begin();
		while(p2 != listBuff.end())
		{
			p2->X = -50;
			p2->update();
			++p2;
		}
}

player i2p(int i)
{
	if(i == 1)
	{
		return P1;
	}
	else if(i == 2)
	{
		return P2;
	}
}

void shoot(int X, int Y, int A, int owner, int wpn, HDC hdc)
{
     projectile tempProj;
     tempProj.X				= X;
     tempProj.Y				= Y - 16;
     tempProj.A				= A;
     tempProj.owner			= owner;
	 tempProj.follow		= 0;
	 tempProj.type			= wpn;
	 tempProj.slow			= 0;
	 tempProj.slowTime		= 0;
	 tempProj.anim			= 0;
	 tempProj.framedelay	= 0;
	 tempProj.framedelaytemp= 0;
	 tempProj.animtemp		= 0;
	 /*tempProj.dropdelay		= 0;
	 tempProj.dropdelaytemp	= 0;
	 tempProj.dropnum		= 0;*/
     switch(wpn)
     {
                case 1:
                     tempProj.dmg       = 10;
                     tempProj.delta     = 8;
					 tempProj.height	= 32;
					 tempProj.width		= 32;
					 if(owner == 1)
					 {
						 tempProj.hbm       = LoadBitmap(g_hInst, "SHOT1");
						 tempProj.mask      = LoadBitmap(g_hInst, "SHOT1MASK");
					 }
					 else if(owner == 2)
					 {
						 tempProj.hbm       = LoadBitmap(g_hInst, "SHOT1_2");
						 tempProj.mask      = LoadBitmap(g_hInst, "SHOT1_2MASK");
					 }
                     break;
				case 2:
					 tempProj.dmg       = 5;
                     tempProj.delta     = 10;
					 tempProj.height	= 16;
					 tempProj.width		= 16;
					 tempProj.hbm       = LoadBitmap(g_hInst, "SHOT2");
					 tempProj.mask      = LoadBitmap(g_hInst, "SHOT2MASK");
					 break;
				case 3:
					 tempProj.dmg       = 15;
                     tempProj.delta     = 6;
					 tempProj.height	= 32;
					 tempProj.width		= 32;
					 tempProj.follow	= 1;
					 if(owner == 1)
					 {
						tempProj.hbm       = LoadBitmap(g_hInst, "SHOT3");
						tempProj.mask      = LoadBitmap(g_hInst, "SHOT3MASK");
					 }
					 else if(owner == 2)
					 {
						tempProj.hbm       = LoadBitmap(g_hInst, "SHOT3_2");
						tempProj.mask      = LoadBitmap(g_hInst, "SHOT3_2MASK");
					 }
					 break;
				case 4:
					 tempProj.dmg       = 5;
                     tempProj.delta     = 5;
					 tempProj.height	= 32;
					 tempProj.width		= 32;
					 tempProj.follow	= 0;
					 tempProj.slow		= 2;
					 tempProj.slowTime  = 200;
					 if(owner == 1)
					 {
						tempProj.hbm       = LoadBitmap(g_hInst, "SHOT4");
						tempProj.mask      = LoadBitmap(g_hInst, "SHOT4MASK");
					 }
					 else if(owner == 2)
					 {
						tempProj.hbm       = LoadBitmap(g_hInst, "SHOT4_2");
						tempProj.mask      = LoadBitmap(g_hInst, "SHOT4_2MASK");
					 }
					 break;
				case 5:
					 tempProj.dmg       = 8;
                     tempProj.delta     = 8;
					 tempProj.height	= 32;
					 tempProj.width		= 32;
					 tempProj.follow	= 0;
					 tempProj.slow		= 4;
					 tempProj.slowTime  = 50;
					 if(owner == 1)
					 {
						tempProj.hbm       = LoadBitmap(g_hInst, "SHOT5");
						tempProj.mask      = LoadBitmap(g_hInst, "SHOT5MASK");
					 }
					 else if(owner == 2)
					 {
						tempProj.hbm       = LoadBitmap(g_hInst, "SHOT5_2");
						tempProj.mask      = LoadBitmap(g_hInst, "SHOT5_2MASK");
					 }
					 tempProj.addShield.hbm	= LoadBitmap(g_hInst, "SHIELDICE");
					 tempProj.addShield.mask = LoadBitmap(g_hInst, "SHIELDICEMASK");
					 tempProj.addShield.modifier = 0.5;
					 tempProj.addShield.on = 1;
					 tempProj.addShield.time = 20;
					 tempProj.addShield.reflect = 0;
					 break;
				case 6:
					 tempProj.dmg       = 14;
                     tempProj.delta     = 6;
					 tempProj.height	= 32;
					 tempProj.width		= 32;
					 tempProj.follow	= 0;
					 tempProj.hbm		= LoadBitmap(g_hInst, "SHOT6F1");
					 tempProj.mask      = LoadBitmap(g_hInst, "SHOT6MASK");
					 tempProj.anim			= 5;
					 tempProj.framedelay	= 8;
					 tempProj.framedelaytemp= 1;
					 tempProj.animtemp		= 5;
					 tempProj.frame[1]		= LoadBitmap(g_hInst, "SHOT6F1");
					 tempProj.frame[2]		= LoadBitmap(g_hInst, "SHOT6F2");
					 tempProj.frame[3]		= LoadBitmap(g_hInst, "SHOT6F3");
					 tempProj.frame[4]		= LoadBitmap(g_hInst, "SHOT6F4");
					 tempProj.frame[5]		= LoadBitmap(g_hInst, "SHOT6F5");
					 /*tempProj.dropdelay		= 15;
					 tempProj.dropdelaytemp	= 1;
					 tempProj.dropnum		= 1;*/
					 break;
				default:
					 tempProj.dmg       = 10;
                     tempProj.delta     = 8;
					 tempProj.height	= 32;
					 tempProj.width		= 32;
					 if(owner == 1)
					 {
						 tempProj.hbm       = LoadBitmap(g_hInst, "SHOT1");
						 tempProj.mask      = LoadBitmap(g_hInst, "SHOT1MASK");
					 }
					 else if(owner == 2)
					 {
						 tempProj.hbm       = LoadBitmap(g_hInst, "SHOT1_2");
						 tempProj.mask      = LoadBitmap(g_hInst, "SHOT1_2MASK");
					 }
                     break;
     }
	if(owner == 1)
	{
		tempProj.dmg = tempProj.dmg * P1.dmgModifier;
	}
	else if(owner == 2)
	{
		tempProj.dmg = tempProj.dmg * P2.dmgModifier;
	}
	 tempProj.alive = 1;
	 tempProj.hdc = hdc;
	 tempProj.update();
	 listProj.push_back(tempProj);
     //return tempProj;
}
 
void buff::update()
	{
		if(alive == 1)
		{
			rct.left = X;
			rct.top = Y;
			rct.right = X + 16;
			rct.bottom = Y + 16;
			FillRect(hdc, &rct, (HBRUSH)(COLOR_BTNFACE-5));

			if( X > P1.X &&
				X < P1.X + 64 &&
				Y > P1.Y &&
				Y < P1.Y + 64)
			{
				use(1);
			}
		
			if( X - 16 > P2.X - 64 &&
				X - 16 < P2.X &&
				Y > P2.Y &&
				Y < P2.Y + 64)
			{
				use(2);
			}

			HDC hdcMemory;
			hdcMemory = CreateCompatibleDC(hdc);

			SelectObject(hdcMemory, mask);
			BitBlt(hdc, X, Y, 16, 16, hdcMemory, 0, 0, SRCAND);
			SelectObject(hdcMemory, hbm);
			BitBlt(hdc, X, Y, 16, 16, hdcMemory, 0, 0, SRCPAINT);

			DeleteDC(hdcMemory);

			

			if(X < -30 || X > 1100 || Y < -30 || Y > 800)
			{
				alive = 0;
			}
		}
	}


void buff::use(int Player)
	{
		X = -50;
		if(Player == 1)
		{
			switch(type)
			{
			case 1:
				if(P1.lives <= maxlive - 50)
				{
					P1.lives += 50;
				}
				else
				{
					P1.lives = maxlive;
				}
				break;
			case 2:
				if(P1.speedbuffremove == 0)
				{
					P1.delta += 3;
				}
				P1.speedbuffremove += 600;
				break;
			case 3:
				P1.shield.hbm = LoadBitmap(g_hInst, "SHIELD1");
				P1.shield.mask = LoadBitmap(g_hInst, "SHIELD1MASK");
				P1.shield.modifier = 0.5;
				P1.shield.reflect = 0;
				P1.shield.time += 400;
				break;
			case 4:
				P1.wpn = 1;
				P1.delay = 10;
				break;
			case 5:
				P1.wpn = 2;
				P1.delay = 1;
				break;
			case 6:
				P1.wpn = 3;
				P1.delay = 40;
				break;
			case 7:
				P1.shield.hbm = LoadBitmap(g_hInst, "SHIELD3");
				P1.shield.mask = LoadBitmap(g_hInst, "SHIELD1MASK");
				P1.shield.modifier = 0.8;
				P1.shield.reflect = 1;
				P1.shield.time += 200;
				break;
			case 8:
				P1.wpn = 4;
				P1.delay = 8;
				break;
			case 9:
				P1.wpn = 5;
				P1.delay = 12;
				break;
			case 10:
				P1.wpn = 6;
				P1.delay = 18;
				break;
			case 11:
				P1.lives = maxlive;
				break;
			case 12:
				P1.slowheal = 1;
				P1.slowhealremove += 100;
				break;
			case 13:
				P1.delta = 0;
				P1.speedbuffremove = 200;
				break;
			case 14:
				P1.lives -= 30;
				break;
			case 15:
				P1.shield.hbm = NULL;
				P1.shield.mask = NULL;
				P1.shield.modifier = 2;
				P1.shield.reflect = 0;
				P1.shield.time += 400;
				break;
			case 16:
				P1.delta = -4;
				P1.speedbuffremove = 600;
				break;
			case 17:
				P1.dmgModifier = .5;
				P1.dmgModRemove = 300;
				break;
			case 18:
				P1.dmgModifier = 2;
				P1.dmgModRemove = 200;
				break;
			}
		}
		else if(Player == 2)
		{
			switch(type)
			{
			case 1:
				if(P2.lives <= maxlive - 50)
				{
					P2.lives += 50;
				}
				else
				{
					P2.lives = maxlive;
				}
				break;
			case 2:
				if(P2.speedbuffremove == 0)
				{
					P2.delta += 3;
				}
				P1.speedbuffremove += 600;
				break;
			case 3:
				P2.shield.hbm = LoadBitmap(g_hInst, "SHIELD2");
				P2.shield.mask = LoadBitmap(g_hInst, "SHIELD2MASK");
				P2.shield.modifier = 0.5;
				P2.shield.reflect = 0;
				P2.shield.time += 400;
				break;
			case 4:
				P2.wpn = 1;
				P2.delay = 10;
				break;
			case 5:
				P2.wpn = 2;
				P2.delay = 1;
				break;
			case 6:
				P2.wpn = 3;
				P2.delay = 40;
				break;
			case 7:
				P2.shield.hbm = LoadBitmap(g_hInst, "SHIELD4");
				P2.shield.mask = LoadBitmap(g_hInst, "SHIELD2MASK");
				P2.shield.modifier = 0.8;
				P2.shield.reflect = 1;
				P2.shield.time += 200;
				break;
			case 8:
				P2.wpn = 4;
				P2.delay = 8;
				break;
			case 9:
				P2.wpn = 5;
				P2.delay = 12;
				break;
			case 10:
				P2.wpn = 6;
				P2.delay = 18;
				break;
			case 11:
				P2.lives = maxlive;
				break;
			case 12:
				P2.slowheal = 1;
				P2.slowhealremove += 100;
				break;
			case 13:
				P2.delta = 0;
				P2.speedbuffremove = 200;
				break;
			case 14:
				P2.lives -= 30;
				break;
			case 15:
				P2.shield.hbm = NULL;
				P2.shield.mask = NULL;
				P2.shield.modifier = 2;
				P2.shield.reflect = 0;
				P2.shield.time += 400;
				break;
			case 16:
				P2.delta = -4;
				P2.speedbuffremove = 600;
				break;
			case 17:
				P2.dmgModifier = .5;
				P2.dmgModRemove = 300;
				break;
			case 18:
				P2.dmgModifier = 2;
				P2.dmgModRemove = 200;
				break;
			}
		}
	}


void projectile::update()
{
	if(alive == 1)
	{
			rct.left = X;
			rct.top = Y;
			rct.right = X + width;
			rct.bottom = Y + height;
			FillRect(hdc, &rct, (HBRUSH)(COLOR_BTNFACE-5));

			Y += (sin(A) * delta);
			X += (cos(A) * delta);

			if(owner == 1)
			{
				if(P2.Y + 16 < Y)
				{
					Y -= follow;
				}
				else if(P2.Y + 16 > Y)
				{
					Y += follow;
				}
			}
			else if(owner == 2)
			{
				if(P1.Y + 8 < Y)
				{
					Y -= follow;
				}
				else if(P1.Y + 8 > Y)
				{
					Y += follow;
				}
			}

			if( X > P1.X &&
				X < P1.X + 64 &&
				Y > P1.Y &&
				Y < P1.Y + 64 &&
				owner == 2)
			{
				P1.lives -= dmg * P1.shield.modifier;
				if(P1.shield.reflect == 1)
				{
					shoot(P1.X + 30, P1.Y + 32, P1.A, 1, type, hdc);
				}
				if(P1.speedbuffremove == 0 && slow != 0)
				{
					P1.delta -= slow;
					P1.speedbuffremove += slowTime;
				}
				if(addShield.on == 1)
				{
					P1.shield = addShield;
				}
				X = -50;
			}
		
			if( X - width > P2.X - 64&&
				X - width < P2.X &&
				Y > P2.Y &&
				Y < P2.Y + 64&&
				owner == 1)
			{
				P2.lives -= dmg * P2.shield.modifier;
				if(P2.shield.reflect == 1)
				{
					shoot(P2.X + 30, P2.Y + 32, P2.A, 2, type, hdc);
				}
				if(P2.speedbuffremove == 0 && slow != 0)
				{
					P2.delta -= slow;
					P2.speedbuffremove += slowTime;
				}
				if(addShield.on == 1)
				{
					P2.shield = addShield;
				}
				X = -50;
			}

			if(anim > 0)
			{
				if(framedelaytemp >= framedelay)
				{
					hbm = frame[animtemp];
					if(animtemp >= anim)
					{
						animtemp = 0;
					}
					animtemp++;
					framedelaytemp = 0;
				}
				framedelaytemp++;
			}

			/*if(dropnum > 0)
			{
				if(dropdelaytemp >= dropdelay)
				{
					drop[dropnum].hbm = drop[dropnum].frame[drop.animtemp];
					drop[dropnum].alive = 1;
					drop[dropnum].anim = 4;
					drop[dropnum].animtemp = 0;
					drop[dropnum].
					animtemp++;
					framedelaytemp = 0;
				}
				framedelaytemp++;
			}*/

			HDC hdcMemory;
			hdcMemory = CreateCompatibleDC(hdc);

			SelectObject(hdcMemory, mask);
			BitBlt(hdc, X, Y, width, height, hdcMemory, 0, 0, SRCAND);
			SelectObject(hdcMemory, hbm);
			BitBlt(hdc, X, Y, width, height, hdcMemory, 0, 0, SRCPAINT);

			DeleteDC(hdcMemory);

			

			if(X < -30 || X > 1100 || Y < -30 || Y > 800)
			{
				alive = 0;
			}
	}
}

void CreateBuff(HDC hdc)
{
	buff tempbuff;
	tempbuff.create(hdc);
	tempbuff.update();
	listBuff.push_back(tempbuff);
	//MessageBox ( NULL, "test", "test", MB_OK);
	srand( (unsigned)time( NULL ) );
	placebuffvar = rand()%200 + 200;
}

void Erase(HDC hdc) 
{
    if(ereasevar == 100)
	{
	RECT rct;
	rct.left = 0;
	rct.top = 0,
	rct.right = 1024;
	rct.bottom = 700;
	FillRect(hdc, &rct, (HBRUSH)(COLOR_BTNFACE-5));
	ereasevar = 0;
	}
	ereasevar++;
	
	P1.rct.left = P1.X;
    P1.rct.top = P1.Y;
    P1.rct.right = P1.X + P1.bmp.bmWidth;
    P1.rct.bottom = P1.Y + P1.bmp.bmHeight;
    FillRect(hdc, &P1.rct, (HBRUSH)(COLOR_BTNFACE-5));
     
    P2.rct.left = P2.X;
    P2.rct.top = P2.Y;
    P2.rct.right = P2.X + P2.bmp.bmWidth;
    P2.rct.bottom = P2.Y + P2.bmp.bmHeight;
    FillRect(hdc, &P2.rct, (HBRUSH)(COLOR_BTNFACE-5));
     
	list<projectile>::iterator p = listProj.begin();
	while(p != listProj.end())
	{
		p->update();
		++p;
	}

	list<buff>::iterator p2 = listBuff.begin();
	while(p2 != listBuff.end())
	{
		p2->update();
		++p2;
	}

     /*for(i = 0; i < numProj;)
     {
           i++;
           (proj+i)->rct.left = (proj+i)->X;
           (proj+i)->rct.top = (proj+i)->Y;
           (proj+i)->rct.right = (proj+i)->X + 32;
           (proj+i)->rct.bottom = (proj+i)->Y + 32;
           FillRect(hdc, &(proj+i)->rct, (HBRUSH)(COLOR_BTNFACE-5));
     }*/

	/*HDC hdcMemory;
     hdcMemory = CreateCompatibleDC(hdc);
     
     SelectObject(hdcMemory, bg);
     BitBlt(hdc, 0, 0, 1024, 700, hdcMemory, 0, 0, SRCPAINT);

	 DeleteDC(hdcMemory);*/
}

void Draw(HDC hdc) 
{
     HDC hdcMemory;
     hdcMemory = CreateCompatibleDC(hdc);
     
     

	 SelectObject(hdcMemory, P1.mask);
     BitBlt(hdc, P1.X, P1.Y, P1.bmp.bmWidth, P1.bmp.bmHeight, hdcMemory, 0, 0, SRCAND);

     SelectObject(hdcMemory, P1.hbm);
     BitBlt(hdc, P1.X, P1.Y, P1.bmp.bmWidth, P1.bmp.bmHeight, hdcMemory, 0, 0, SRCINVERT);
	
	 if(P1.shield.on == 1)
	 {
		SelectObject(hdcMemory, P1.shield.mask);
		BitBlt(hdc, P1.X, P1.Y, P1.bmp.bmWidth, P1.bmp.bmHeight, hdcMemory, 0, 0, SRCAND);

		SelectObject(hdcMemory, P1.shield.hbm);
		BitBlt(hdc, P1.X, P1.Y, P1.bmp.bmWidth, P1.bmp.bmHeight, hdcMemory, 0, 0, SRCPAINT);
	 }
   
     //-----------------------------------------------------
   
	 

     SelectObject(hdcMemory, P2.mask);
     BitBlt(hdc, P2.X, P2.Y, P2.bmp.bmWidth, P2.bmp.bmHeight, hdcMemory, 0, 0, SRCAND);

     SelectObject(hdcMemory, P2.hbm);
     BitBlt(hdc, P2.X, P2.Y, P2.bmp.bmWidth, P2.bmp.bmHeight, hdcMemory, 0, 0, SRCPAINT);

	 if(P2.shield.on == 1)
	 {
		SelectObject(hdcMemory, P2.shield.mask);
		BitBlt(hdc, P2.X, P2.Y, P2.bmp.bmWidth, P2.bmp.bmHeight, hdcMemory, 0, 0, SRCAND);

		SelectObject(hdcMemory, P2.shield.hbm);
		BitBlt(hdc, P2.X, P2.Y, P2.bmp.bmWidth, P2.bmp.bmHeight, hdcMemory, 0, 0, SRCPAINT);
	 }
     //-----------------------------------------------------

     /*for(i = 0; i < numProj;)
     {
           i++;
           SelectObject(hdcMemory, (proj+i)->mask);
           BitBlt(hdc, (proj+i)->X, (proj+i)->Y, (proj+i)->bmp.bmWidth, (proj+i)->bmp.bmHeight, hdcMemory, 0, 0, SRCAND);

           SelectObject(hdcMemory, (proj+i)->hbm);
           BitBlt(hdc, (proj+i)->X, (proj+i)->Y, (proj+i)->bmp.bmWidth, (proj+i)->bmp.bmHeight, hdcMemory, 0, 0, SRCPAINT);
     }*/
     
     //-----------------------------------------------------
     
     SelectObject(hdcMemory, bg);
     BitBlt(hdc, 0, 0, 1024, 700, hdcMemory, 0, 0, SRCPAINT);

     SelectObject(hdcMemory, guiBG);
     BitBlt(hdc, 0, 700, 1024, 32, hdcMemory, 0, 0, SRCCOPY);


	tempint = P1.lives;
	lives100 = 0;
	lives10	 = 0;
	lives1   = 0;
	while(tempint >= 100)
	{
		lives100++;
		tempint -= 100;
	}
	while(tempint >= 10)
	{
		lives10++;
		tempint -= 10;
	}
	while(tempint >= 1)
	{
		lives1++;
		tempint--;
	}
	P1.liveBmp[0] = livePic[lives100];
	P1.liveBmp[1] = livePic[lives10];
	P1.liveBmp[2] = livePic[lives1];
	
	SelectObject(hdcMemory, P1.liveBmp[0]);
    BitBlt(hdc, 50, 700, 26, 26, hdcMemory, 0, 0, SRCCOPY);
	SelectObject(hdcMemory, P1.liveBmp[1]);
    BitBlt(hdc, 76, 700, 26, 26, hdcMemory, 0, 0, SRCCOPY);
	SelectObject(hdcMemory, P1.liveBmp[2]);
    BitBlt(hdc, 102, 700, 26, 26, hdcMemory, 0, 0, SRCCOPY);

	tempint = P2.lives;
	lives100 = 0;
	lives10	 = 0;
	lives1   = 0;
	while(tempint >= 100)
	{
		lives100++;
		tempint -= 100;
	}
	while(tempint >= 10)
	{
		lives10++;
		tempint -= 10;
	}
	while(tempint >= 1)
	{
		lives1++;
		tempint--;
	}
	P2.liveBmp[0] = livePic[lives100];
	P2.liveBmp[1] = livePic[lives10];
	P2.liveBmp[2] = livePic[lives1];
	
	SelectObject(hdcMemory, P2.liveBmp[0]);
    BitBlt(hdc, 800, 700, 26, 26, hdcMemory, 0, 0, SRCCOPY);
	SelectObject(hdcMemory, P2.liveBmp[1]);
    BitBlt(hdc, 826, 700, 26, 26, hdcMemory, 0, 0, SRCCOPY);
	SelectObject(hdcMemory, P2.liveBmp[2]);
    BitBlt(hdc, 852, 700, 26, 26, hdcMemory, 0, 0, SRCCOPY);

	tempint = 0;

     DeleteDC(hdcMemory);
}

void Update(HWND hwnd, HDC hdc)
{
     if(GetAsyncKeyState(0x53) && P1.Y + P1.bmp.bmHeight < 700 && P1.Y + P1.bmp.bmHeight > -10)
     {
                               P1.Y += P1.delta;
     }
     if(GetAsyncKeyState(0x57) && P1.Y + P1.bmp.bmHeight < 710 && P1.Y + P1.bmp.bmHeight > 0)
     {
                               P1.Y -= P1.delta;
     }
     if(GetAsyncKeyState(0x44) && P1.X + P1.bmp.bmWidth > -10 && P1.X + P1.bmp.bmWidth < 1000)
     {
                               P1.X += P1.delta;
     }
     if(GetAsyncKeyState(0x41) && P1.X + P1.bmp.bmWidth > 0 && P1.X + P1.bmp.bmWidth < 1010)
     {
                               P1.X -= P1.delta;
     }
     
     //------------------------------------------------
     
     if(GetAsyncKeyState(VK_DOWN) && P2.Y + P2.bmp.bmHeight > -10 && P2.Y + P2.bmp.bmHeight < 700)
     {
                               P2.Y += P2.delta;
     }
     if(GetAsyncKeyState(VK_UP) && P2.Y + P2.bmp.bmHeight > 0 && P2.Y + P2.bmp.bmHeight < 710)
     {
                               P2.Y -= P2.delta;
     }
     if(GetAsyncKeyState(VK_RIGHT) && P2.X + P1.bmp.bmWidth > -10 && P2.X + P2.bmp.bmWidth < 1000)
     {
                               P2.X += P2.delta;
     }
     if(GetAsyncKeyState(VK_LEFT) && P2.X + P1.bmp.bmWidth > 0 && P2.X + P2.bmp.bmWidth < 1010)
     {
                               P2.X -= P2.delta;
     }
     


     /*if(GetAsyncKeyState(0x53) && P1.Y + P1.bmp.bmHeight < 768)
     {
                               P1.Y -= (sin(P1.A) * P1.delta);
                               P1.X -= (cos(P1.A) * P1.delta);
     }
     if(GetAsyncKeyState(0x57) && P1.Y > 0)
     {
                               P1.Y += (sin(P1.A) * P1.delta);
                               P1.X += (cos(P1.A) * P1.delta);
     }
     if(GetAsyncKeyState(0x44) && P1.X + P1.bmp.bmWidth < 1024)
     {
                               P1.A++;
     }
     if(GetAsyncKeyState(0x41) && P1.X > 0)
     {
                               P1.A--;
     }
     
     //------------------------------------------------
     
     if(GetAsyncKeyState(VK_DOWN) && P2.Y + P2.bmp.bmHeight < 768)
     {
                               P2.Y -= (sin(P2.A) * P2.delta);
                               P2.X -= (cos(P2.A) * P2.delta);
     }
     if(GetAsyncKeyState(VK_UP) && P2.Y > 0)
     {
                               P2.Y += (sin(P2.A) * P2.delta);
                               P2.X += (cos(P2.A) * P2.delta);
     }
     if(GetAsyncKeyState(VK_RIGHT) && P2.X + P2.bmp.bmWidth < 1024)
     {
                               P2.A++;
     }
     if(GetAsyncKeyState(VK_LEFT) && P2.X > 0)
     {
                               P2.A--;
     }*/
     
     
     if(GetAsyncKeyState(VK_SPACE) && P1.down == 0 && P1.delta > 0)
     {
           numProj++;
		   shoot(P1.X + 30, P1.Y + 32, P1.A, 1, P1.wpn, hdc);
           if(GetAsyncKeyState(VK_SPACE))
		   {
			   P1.down = P1.delay;
		   }
     }
	 if(!GetAsyncKeyState(VK_SPACE) && P1.down > 0)
	 {
		 P1.down--;
	 }
     
     
     if((GetAsyncKeyState(VK_NUMPAD0) || GetAsyncKeyState(VK_END)) && P2.down == 0 && P2.delta > 0)
     {
           numProj++;
		   shoot(P2.X - 30, P2.Y + 32, P2.A, 2, P2.wpn, hdc);
		   if(GetAsyncKeyState(VK_NUMPAD0) || GetAsyncKeyState(VK_END))
		   {
			   P2.down = P2.delay;
		   }
     }
	 if(!GetAsyncKeyState(VK_NUMPAD0) && !GetAsyncKeyState(VK_END) && P2.down > 0)
	 {
		 P2.down--;
	 }
     
     
     /*for(i = 1; i < numProj;)
     {
           i++;
           (proj+i)->Y += (sin((proj+i)->A) * (proj+i)->delta);
           (proj+i)->X += (cos((proj+i)->A) * (proj+i)->delta);
     }*/
	
	if(P1.lives <= 0)
	{
		P1.lives = 1000;
		msgbox1 = MessageBox ( hwnd, "Spieler 2 hat gewonnen!\nNeustart?", "Space Fight", MB_YESNO);
		switch(msgbox1)
		{
		case IDYES:
			newgame();
			break;
		case IDNO:
			DestroyWindow(hwnd);
			break;
		}
	}

	if(P2.lives <= 0)
	{
		P2.lives = 1000;
		msgbox1 = MessageBox ( hwnd, "Spieler 1 hat gewonnen!\nNeustart?", "Space Fight", MB_YESNO);
		switch(msgbox1)
		{
		case IDYES:
			newgame();
			break;
		case IDNO:
			DestroyWindow(hwnd);
			break;
		}
	}


	if(P1.speedbuffremove == 1)
	{
		P1.delta = 4;
		P1.speedbuffremove = 0;
	}
	else if(P1.speedbuffremove > 1)
	{
		P1.speedbuffremove--;
	}

	if(P2.speedbuffremove == 1)
	{
		P2.delta = 4;
		P2.speedbuffremove = 0;
	}
	else if(P2.speedbuffremove > 1)
	{
		P2.speedbuffremove--;
	}

	
	if(P1.slowhealremove == 1)
	{
		P1.slowheal = 0;
		P1.slowhealremove = 0;
	}
	else if(P1.slowhealremove > 1)
	{
		if(P1.lives < maxlive)
		{
			P1.lives += P1.slowheal;
		}
		else
		{
			P1.lives = maxlive;
		}
		P1.slowhealremove--;
	}

	if(P2.slowhealremove == 1)
	{
		P2.slowheal = 0;
		P2.slowhealremove = 0;
	}
	else if(P2.slowhealremove > 1)
	{
		if(P2.lives < maxlive)
		{
			P2.lives += P2.slowheal;
		}
		else
		{
			P2.lives = maxlive;
		}
		P2.slowhealremove--;
	}

	if(P1.dmgModRemove == 1)
	{
		P1.dmgModifier = 1;
		P1.dmgModRemove = 0;
	}
	else if(P1.dmgModRemove > 1)
	{
		P1.dmgModRemove--;
	}

	if(P2.dmgModRemove == 1)
	{
		P2.dmgModifier = 1;
		P2.dmgModRemove = 0;
	}
	else if(P2.dmgModRemove > 1)
	{
		P2.dmgModRemove--;
	}


	if(placebuffvar <= 1)
	{
		CreateBuff(hdc);
	}
	else if(placebuffvar > 1)
	{
		placebuffvar--;
	}

	
	while(P1.Y >= 700)
	{
		P1.Y--;
	}
	while(P1.Y <= 0)
	{
		P1.Y++;
	}
	while(P1.X >= 1000)
	{
		P1.X--;
	}
	while(P1.X <= 0)
	{
		P1.X++;
	}
	while(P2.Y >= 700)
	{
		P2.Y--;
	}
	while(P2.Y <= 0)
	{
		P2.Y++;
	}
	while(P2.X >= 1000)
	{
		P2.X--;
	}
	while(P2.X <= 0)
	{
		P2.X++;
	}


	P1.shield.update();
	P2.shield.update();
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
   HDC hdcWindow;
   hdcWindow = GetDC(hwnd);
   switch(Message)
   {
      case WM_CREATE:
		newgame();



         GetObject(P1.hbm, sizeof(P1.bmp), &P1.bmp);
         GetObject(P2.hbm, sizeof(P2.bmp), &P2.bmp);
         SetTimer(hwnd, idTimer1, nTimerDelay, NULL);

      break; 
	  case WM_COMMAND:
		    switch( wParam )
           {
             case IDM_NEWGAME:
				ereasevar = 100;
				Erase(hdcWindow);
				newgame();
				return 0;
             case IDM_FILEEXIT:
				 DestroyWindow(hwnd);
                return 0;
			case IDM_P1GREY:
				P1.hbm      = LoadBitmap(g_hInst, "RAUMSCHIFF1");
				return 0;
			case IDM_P1BLUE:
				P1.hbm      = LoadBitmap(g_hInst, "RAUMSCHIFF1BLUE");
				return 0;
			case IDM_P1PINK:
				P1.hbm      = LoadBitmap(g_hInst, "RAUMSCHIFF1PINK");
				return 0;
			case IDM_P1GREEN:
				P1.hbm      = LoadBitmap(g_hInst, "RAUMSCHIFF1GREEN");
				return 0;
			case IDM_P1VIOLET:
				P1.hbm      = LoadBitmap(g_hInst, "RAUMSCHIFF1VIOLET");
				return 0;
			case IDM_P1RED:
				P1.hbm      = LoadBitmap(g_hInst, "RAUMSCHIFF1RED");
				return 0;
			case IDM_P1CYAN:
				P1.hbm      = LoadBitmap(g_hInst, "RAUMSCHIFF1CYAN");
				return 0;
			case IDM_P1YELLOW:
				P1.hbm      = LoadBitmap(g_hInst, "RAUMSCHIFF1YELLOW");
				return 0;


			case IDM_P2GREY:
				P2.hbm      = LoadBitmap(g_hInst, "RAUMSCHIFF2");
				return 0;
			case IDM_P2BLUE:
				P2.hbm      = LoadBitmap(g_hInst, "RAUMSCHIFF2BLUE");
				return 0;
			case IDM_P2PINK:
				P2.hbm      = LoadBitmap(g_hInst, "RAUMSCHIFF2PINK");
				return 0;
			case IDM_P2GREEN:
				P2.hbm      = LoadBitmap(g_hInst, "RAUMSCHIFF2GREEN");
				return 0;
			case IDM_P2VIOLET:
				P2.hbm      = LoadBitmap(g_hInst, "RAUMSCHIFF2VIOLET");
				return 0;
			case IDM_P2RED:
				P2.hbm      = LoadBitmap(g_hInst, "RAUMSCHIFF2RED");
				return 0;
			case IDM_P2CYAN:
				P2.hbm      = LoadBitmap(g_hInst, "RAUMSCHIFF2CYAN");
				return 0;
			case IDM_P2YELLOW:
				P2.hbm      = LoadBitmap(g_hInst, "RAUMSCHIFF2YELLOW");
				return 0;

			case IDM_LIVES_1:
				maxlive = 1;
				return 0;
			case IDM_LIVES_100:
				maxlive = 100;
				return 0;
			case IDM_LIVES_200:
				maxlive = 200;
				return 0;
			case IDM_LIVES_300:
				maxlive = 300;
				return 0;
			case IDM_LIVES_400:
				maxlive = 400;
				return 0;
			case IDM_LIVES_500:
				maxlive = 500;
				return 0;
			case IDM_LIVES_600:
				maxlive = 600;
				return 0;
			case IDM_LIVES_700:
				maxlive = 700;
				return 0;
			case IDM_LIVES_800:
				maxlive = 800;
				return 0;
			case IDM_LIVES_900:
				maxlive = 900;
				return 0;
			case IDM_LIVES_999:
				maxlive = 999;
				return 0;
           }
			break;
      case WM_TIMER:
            Erase(hdcWindow);
            Update(hwnd, hdcWindow);
            Draw(hdcWindow);

			eclapsed = 1;
            ReleaseDC(hwnd, hdcWindow);
      break;
      case WM_PAINT:
            PAINTSTRUCT ps;
            hdcWindow = BeginPaint(hwnd, &ps);

            Draw(hdcWindow);           
            EndPaint(hwnd, &ps);
      break;
      case WM_CLOSE:
         DestroyWindow(hwnd);
      break;
      case WM_DESTROY:
         KillTimer(hwnd, idTimer1);
         
         DeleteObject(P1.hbm);
         DeleteObject(P1.mask);
         DeleteObject(P2.hbm);
         DeleteObject(P2.mask);
         
         delete[] proj;
         
         PostQuitMessage(0);
      break;
      default:
         return DefWindowProc(hwnd, Message, wParam, lParam);
   }
   return 0;
}



int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    HWND hwnd;               /* This is the handle for our window */
    HMENU menu;
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    g_hInst = hThisInstance;

    /* The Window structure */
    wincl.hInstance         = g_hInst;
    wincl.lpszClassName     = szClassName;
    wincl.lpfnWndProc       = WndProc;      /* This function is called by windows */
    wincl.style             = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize            = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon             = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm           = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor           = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName      = NULL;                 /* No menu */
    wincl.cbClsExtra        = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra        = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground     = (HBRUSH)(COLOR_BTNFACE-5);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Space Fight",       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           1024,                 /* The programs width */
           788,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           g_hInst,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    menu = LoadMenu(g_hInst, MAKEINTRESOURCE(ID_MENU));
    SetMenu(hwnd, menu);
    /* Make the window visible on the screen */
    ShowWindow (hwnd, nFunsterStil);
    UpdateWindow(hwnd);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_COMMAND:
//--------------------------
           break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
	return 0;
}