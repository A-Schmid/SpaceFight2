#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_net.h"
//#include "SDL.h"
//#include "SDL_image.h"
//#include "SDL_ttf.h"
//#include "SDL_net.h"
#include <string>
#include <list>
#include "math.h"
#include <iostream>
#include <fstream>

using namespace std;

//The screen sttributes
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int SCREEN_BPP = 32;
const float VEL_MODIFIER = 0.5;

//The surfaces
SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;
SDL_Surface *logo = NULL;
SDL_Surface *icon = NULL;

SDL_Surface *testSurface;

SDL_Surface *p1_healthbar_full = NULL;
SDL_Surface *p1_healthbar_empty = NULL;

SDL_Surface *p2_healthbar_full = NULL;
SDL_Surface *p2_healthbar_empty = NULL;

SDL_Surface *p1_lives_text = NULL;
SDL_Surface *p2_lives_text = NULL;

SDL_Surface *p1_lives_bg = NULL;
SDL_Surface *p2_lives_bg = NULL;

SDL_Surface *p1_wpn_icon = NULL;
SDL_Surface *p2_wpn_icon = NULL;

SDL_Surface *p1_ammo_text = NULL;
SDL_Surface *p2_ammo_text = NULL;

SDL_Surface *text_win = NULL;
TTF_Font *font = NULL;
TTF_Font *fontWin = NULL;
TTF_Font *fontTest = NULL;
TTF_Font *fontMenu = NULL;
SDL_Color textColor = { 255, 255, 255 };
char buffer[500];

bool once = true;



//The event structure
SDL_Event event;

int nextBuffTime;
int nextEnemyTime;
int maxLives = 200;
float dmgDelay = 1000;
int SP_score = 0;

bool skip = false;

int gamemode = -1; // -1 = menu, 0 = normal, 1 = server, 2 = client, 3 = sp
int menumode = 0;

int wpnShots[7];

SDL_Surface *load_image( std::string filename );
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
bool init();
bool load_files();
void clean_up(bool quit = true);
void handle_input();
void handle_input_server();
void handle_input_server_2();
void handle_input_client();
void CreateBuff();
bool GetCollision(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2);
void InitBuffs();
void InitShields();
void InitPlayers();
void InitProjectiles();
void InitEmitters();
void InitMenuItems();
void showHealthBars(bool show1 = true, bool show2 = true);
void newGame();
Uint32 stringToHex(char* str);
Uint32 FadePixel(Uint32 px, float LiveTime, float maxLiveTime, float FadePerc);
string read_file(int line, char* filepath = "config.ini");
Uint32 get_pixel32( SDL_Surface *surface, int x, int y );
void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel );
Uint32 BlendPixels(Uint32 src, Uint32 trg, int mode, float srcRatio = 0.5);
int main( int argc, char* args[] );


class MENU_ITEM
{
   public:
        SDL_Surface *img;
        SDL_Surface *img_hover;
        SDL_Surface *img_checked;
        SDL_Surface *img_checked_hover;
        SDL_Surface *img_2;
        SDL_Surface *text;
        SDL_Surface *text_hover;
        float x, y;
        float img_add_x, img_add_y;
        int width, height;
        std::string label;
        bool has_hover;
        bool hovered;
        bool has_check;
        bool checked;
        bool has_click;
        bool clicked;
        bool clickDelay;
        bool has_img_2;
        bool has_text;
        MENU_ITEM();
        void update();
        void init();
        void show();
};

class SERVER
{
    public:
        TCPsocket sd, csd;
        IPaddress ip, *remoteIP;
        char* buffer;
        SERVER();
        void init();
        //void init(int blub);
        bool listen(int len);
        void send(char* data);
        
};

class CLIENT
{
    public:
        IPaddress ip, *remoteIP;
        TCPsocket sd, csd;
        char* buffer;
        CLIENT(char* getIp);
        void init();
        void send(char* data);
        bool listen(int len);
};

class TIMER
{
    private:
        int startTicks;
        int pausedTicks;
        bool paused;
        bool started;
    public:
        TIMER();
        void start();
        void stop();
        void pause();
        void unpause();
        int get_ticks();
        bool is_started();
        bool is_paused();
};

class PARTICLE
{
    public:
        SDL_Surface *img;
        float x, y;
        float dir;
        float vel;
        int width;
        int height;
        float maxLivetime;
        float livetime;
        float TurbulenceChance;
        float TurbulenceStrength;
        float FadeOutStartPerc;
        Uint32 color[2];
        PARTICLE(SDL_Surface *IMG, float X, float Y, float DIR, float VEL, float LIVETIME, float TURBCHANCE, float TURBSTRENGTH, Uint32 COLOR[2], float FADEOUT);
        void update(Uint32 deltaTicks);
        void show();
};

class EMITTER
{
    public:
        SDL_Surface *img;
        float x, y;
        float width;
        float height;
        float addY;
        float delay;
        float nextSpawn;
        float livetime;
        bool permanent;
        int spawnAtOnce;
        int particleCount;
        int maxParticleCount;
        float ParticleMinVel;
        float ParticleMaxVel;
        float ParticleMinDir;
        float ParticleMaxDir;
        float ParticleMinLivetime;
        float ParticleMaxLivetime;
        float ParticleTurbulenceChance;
        float ParticleTurbulenceStrength;
        float ParticleFadeOutStartPerc;
        Uint32 color[2];
        list<PARTICLE> particle;
        list<PARTICLE>::iterator it;
        EMITTER();
        void update(float X, float Y, Uint32 deltaTicks, bool move = true);
        void show();
};

class SHIELD
{
    public:
        SDL_Surface *img[2];
        float x, y;
        int width;
        int height;
        float modifier;
        float time;
        bool stun;
        bool reflect;
        SHIELD();
        void update( float X, float Y, Uint32 deltaTicks );
        void show(int pl);
};

class PLAYER
{
    public:
        SDL_Surface *img;
        int imgframe;
        float imgframetime;
        float x, y;
        float xVel, yVel;
        int width;
        int height;
        int vel;
        int vel_mod;
        float vel_mod_time;
        float dmg_mod;
        float dmg_mod_time;
        int dmg_over_time;
        float dmg_over_time_time;
        float dmg_over_time_freq;
        float dmg_over_time_counter;
        int weapon;
        int id;
        int lives;
        float delay;
        bool shootDown;
        int color;
        int shots;
        int numshot;
        float numshot_time;
        SHIELD shield;
        EMITTER flyEmitter;
        PLAYER();
        void update( Uint32 deltaTicks );
        void show();
        void shoot(int wpn = -1, bool instant = false);
        void setWeapon(int num);
};

class SP_ENEMY
{
    public:
        SDL_Surface *img;
        float x, y;
        int width, height;
        int lives;
        float vel;
        int dmg;
        int score;
        SP_ENEMY(int type);
        void update( Uint32 deltaTicks );
        void show();
        void hit();
};

class PROJECTILE
{
    public:
        SDL_Surface *img;
        float x, y;
        float y_add;
        float vel;
        float follow;
        int width, height;
        int type;
        int minDmg;
        int maxDmg;
        int damage;
        int slow;
        float slow_time;
        int dmg_over_time;
        float dmg_over_time_time;
        float dmg_over_time_freq;
        float delay;
        bool alive;
        bool addShield;
        PLAYER *owner;
        PLAYER *enemy;
        SHIELD shield;
        EMITTER flyEmitter;
        bool hasFlyEmitter;
        EMITTER hitEmitter;
        bool hasHitEmitter;
        bool hasImg;
        PROJECTILE();
        void move( Uint32 deltaTicks );
        void show();
        void hit();
        void hit(SP_ENEMY *enemy2);
        void die();
        void init();
};

class BUFF
{
    public:
        SDL_Surface *img;
        int x, y;
        int width, height;
        int type;
        bool alive;
        BUFF();
        BUFF(int X, int Y, int TYPE);
        void update();
        void show();
        void use(PLAYER pl);
};



SDL_Surface *img_buff[17];
bool buff_allowed[17];
bool no_buffs = false;
bool no_ammo = false;
SHIELD shield[5];
PLAYER player[2];
PROJECTILE projectile[7][2];
EMITTER emitter[13];
SERVER server;
CLIENT client("0.0.0.0");
MENU_ITEM menuitem[6];
MENU_ITEM change_color[2][2];
MENU_ITEM switch_buff[17];
MENU_ITEM toggle_ammo;
list<EMITTER> list_hit_emitter;
list<PROJECTILE> list_projectile;
list<BUFF> list_buff;
list<SP_ENEMY> list_enemy;

EMITTER readEmitterFromFile(char* filepath);

#include "MENU_ITEM.hpp"
#include "TIMER.hpp"
#include "SHIELD.hpp"
#include "PLAYER.hpp"
#include "PROJECTILE.hpp"
#include "BUFF.hpp"
#include "PARTICLE.hpp"
#include "EMITTER.hpp"
#include "SP_ENEMY.hpp"
#include "functions.hpp"

int main( int argc, char* args[] )
{
    int blubtest = 0;
    bool quit = false;
    
    list<PROJECTILE>::iterator it;
    list<BUFF>::iterator it2;
    list<EMITTER>::iterator it3;
    list<SP_ENEMY>::iterator it4;
    
    TIMER delta;

    init();
    load_files();
    delta.start();

    
    while( quit == false )
    {
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }
        }
        if(gamemode == -1)
        {
            apply_surface( 0, 0, background, screen );
            apply_surface( 0, 0, logo, screen );
            
            change_color[0][0].update();
            change_color[0][1].update();
            change_color[1][0].update();
            change_color[1][1].update();            
            
            menuitem[0].update();
            menuitem[1].update();
            menuitem[2].update();
            menuitem[3].update();
            menuitem[4].update();
            menuitem[5].update();
            
            toggle_ammo.update();
            
            for(int i = 0; i < 16; i++)
            {
                switch_buff[i].update();
                buff_allowed[i] = switch_buff[i].checked;
            }
            
            if(menuitem[0].clicked)
            {
                gamemode = 0;
                newGame();
            }
            if(menuitem[1].clicked)
            {
                gamemode = 1;
                SDL_WM_SetCaption("server", NULL);
                newGame();
                server = SERVER();
                server.init();      
                skip = true;
            }
            if(menuitem[2].clicked)
            {
                gamemode = 2;
                SDL_WM_SetCaption("client", NULL);
                newGame();
                client = CLIENT((char*)read_file(0).c_str());
                skip = true;
            }
            if(menuitem[3].clicked)
            {
                gamemode = 3;
                newGame();
            }
            if(menuitem[4].clicked)
            {
                if(!(screen->flags & SDL_FULLSCREEN))
                {
                    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF | SDL_FULLSCREEN );
                }
                else
                {
                    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF );
                }
            }
            if(menuitem[5].clicked)
            {
                quit = true;
            }
            
            no_ammo = !toggle_ammo.checked;
            
            if(change_color[0][0].clicked)
            {
                player[0].color++;
                if(player[0].color >= 10)
                {
                    player[0].color = 0;
                }
            }
            if(change_color[0][1].clicked)
            {
                player[0].color--;
                if(player[0].color < 0)
                {
                    player[0].color = 9;
                }
            }
            if(change_color[1][0].clicked)
            {
                player[1].color++;
                if(player[1].color >= 10)
                {
                    player[1].color = 0;
                }
            }
            if(change_color[1][1].clicked)
            {
                player[1].color--;
                if(player[1].color < 0)
                {
                    player[1].color = 9;
                }
            }
            
            change_color[0][0].show();
            change_color[0][1].show();
            change_color[1][0].show();
            change_color[1][1].show();
            menuitem[0].show();
            menuitem[1].show();
            menuitem[2].show();
            menuitem[3].show();
            menuitem[4].show();
            menuitem[5].show();
            toggle_ammo.show();
            
            for(int i = 0; i < 16; i++)
            {
                switch_buff[i].show();
            }
            
            player[0].show();
            player[1].show();
        }
        else if(gamemode == 3)
        {
            handle_input();
            player[0].update( delta.get_ticks() );
            p1_wpn_icon = img_buff[player[0].weapon];
            
            it = list_projectile.begin();
            while(it != list_projectile.end())
            {
                if(it->alive)
                {
                    it->move( delta.get_ticks() );
                    ++it;
                }
                else
                {
                    it = list_projectile.erase(it);
                }
            }
            
            it2 = list_buff.begin();
            while(it2 != list_buff.end())
            {
                if(it2->alive)
                {
                    it2->update();
                    ++it2;
                }
                else
                {
                    it2 = list_buff.erase(it2);
                }
            }
            
            it3 = list_hit_emitter.begin();
            while(it3 != list_hit_emitter.end())
            {
                if(it3->livetime > 0)
                {
                    it3->update(0, 0 , delta.get_ticks(), false);
                    ++it3;
                }
                else
                {
                    it3 = list_hit_emitter.erase(it3);
                }
            }
            
            it4 = list_enemy.begin();
            while(it4 != list_enemy.end())
            {
                if(it4->lives > 0)
                {
                    it4->update(delta.get_ticks());
                    ++it4;
                }
                else
                {
                    it4 = list_enemy.erase(it4);
                }
            }
            
            if(gamemode != 2)
            {
                if( buff_allowed[0] || 
                    buff_allowed[1] || 
                    buff_allowed[2] || 
                    buff_allowed[3] || 
                    buff_allowed[4] || 
                    buff_allowed[5] || 
                    buff_allowed[6] || 
                    buff_allowed[7] || 
                    buff_allowed[8] || 
                    buff_allowed[9] || 
                    buff_allowed[10] || 
                    buff_allowed[11] || 
                    buff_allowed[12] || 
                    buff_allowed[13] ||
					buff_allowed[14] || 
                    buff_allowed[15] )
                {
                    nextBuffTime -= delta.get_ticks();
                    if(nextBuffTime <= 0)
                    {
                        nextBuffTime = 1000 + rand() % 10000;
                        CreateBuff();
                    }
                }
            }
            
            nextEnemyTime -= delta.get_ticks();
            if(nextEnemyTime <= 0)
            {
                nextEnemyTime = 10 + rand() % 1000;
                list_enemy.push_back(SP_ENEMY(1+rand()%6));
            }
                    
            delta.start();

            
            apply_surface( 0, 0, background, screen );
            player[0].show();
            
            it = list_projectile.begin();
            while(it != list_projectile.end())
            {
                if(it->alive)
                {
                    it->show();
                    ++it;
                }
                else
                {
                    it = list_projectile.erase(it);
                }
            }
            
            it2 = list_buff.begin();
            while(it2 != list_buff.end())
            {
                if(it2->alive)
                {
                    it2->show();
                    ++it2;
                }
                else
                {
                    it2 = list_buff.erase(it2);
                }
            }
            
            it3 = list_hit_emitter.begin();
            while(it3 != list_hit_emitter.end())
            {
                if(it3->livetime > 0)
                {
                    it3->show();
                    ++it3;
                }
                else
                {
                    it3 = list_hit_emitter.erase(it3);
                }
            }
            
            it4 = list_enemy.begin();
            while(it4 != list_enemy.end())
            {
                if(it4->lives > 0)
                {
                    it4->show();
                    ++it4;
                }
                else
                {
                    it4 = list_enemy.erase(it4);
                }
            }
            
            sprintf(buffer, "%d", player[0].lives);
            //itoa(player[0].lives, buffer, 10);
            
            //sprintf(buffer, "%f", (float)delta.get_ticks());
            p1_lives_text = TTF_RenderText_Solid( font, buffer, textColor );
            //itoa(player[1].lives, buffer, 10);            
            //p2_lives_text = TTF_RenderText_Solid( font, buffer, textColor );
            
            apply_surface( 0 - 64, 768 - 80, p1_lives_bg, screen, NULL );
            //apply_surface( 1024 - 256 + 64, 768 - 80, p2_lives_bg, screen, NULL );
            
            apply_surface( 0 + 8, 768 - 16 - 8, p1_wpn_icon, screen, NULL );
            //apply_surface( 1024 - 16 - 8, 768 - 16 - 8, p2_wpn_icon, screen, NULL );
            
            apply_surface( 32, 768 - 64, p1_lives_text, screen, NULL );
            
            sprintf(buffer, "%12i", SP_score);
            p2_lives_text = TTF_RenderText_Solid( font, buffer, textColor );
            apply_surface( 32, 8, p2_lives_text, screen, NULL );
            
            showHealthBars(true, false);
            
            
            
            if(player[0].lives <= 0)
            {
                text_win = TTF_RenderText_Solid( fontWin, "Verloren!", textColor );
                apply_surface( SCREEN_WIDTH / 2 - text_win->w / 2, 768 / 2, text_win, screen, NULL );
                SDL_Flip( screen );
                SDL_Delay(2000);
                newGame();
            }
        }
        else
        {
            //SDL_WM_SetCaption("F", NULL);
            switch(gamemode)
            {
                case 0:
                    handle_input();
                    break;
                case 1:
                    handle_input_server();
                    //printf("s1\n");
                    break;
                case 2:
                    handle_input_client();
                    //printf("c1\n");
                    break;
            }
            //SDL_WM_SetCaption("G", NULL);
            
            if(gamemode == 2 && !skip)
            {
                //SDL_Delay(1000);
                handle_input_client_2();
                //SDL_WM_SetCaption("H", NULL);
                //printf("c2\n");
            }
            
            if(gamemode == 1 && !skip)
            {
                //SDL_WM_SetCaption("E", NULL);
                handle_input_server_2();
                //printf("s2\n");
            }
            skip = false;
            
            dmgDelay -= delta.get_ticks();
            if(dmgDelay <= 0)
            {
                if(player[0].x + player[0].width > SCREEN_WIDTH / 2 + 100)
                {
                    player[0].lives -= 1;
                }
                if(player[1].x < SCREEN_WIDTH / 2 - 100)
                {
                    player[1].lives -= 1;
                }
                dmgDelay = 100;
            }
    
            //player[0].shoot();
            player[0].update( delta.get_ticks() );
            player[1].update( delta.get_ticks() );
            
            p1_wpn_icon = img_buff[player[0].weapon];
            p2_wpn_icon = img_buff[player[1].weapon];
            
            it = list_projectile.begin();
            while(it != list_projectile.end())
            {
                if(it->alive)
                {
                    it->move( delta.get_ticks() );
                    ++it;
                }
                else
                {
                    it = list_projectile.erase(it);
                }
            }
            
            it2 = list_buff.begin();
            while(it2 != list_buff.end())
            {
                if(it2->alive)
                {
                    it2->update();
                    ++it2;
                }
                else
                {
                    it2 = list_buff.erase(it2);
                }
            }
            
            it3 = list_hit_emitter.begin();
            while(it3 != list_hit_emitter.end())
            {
                if(it3->livetime > 0)
                {
                    it3->update(0, 0 , delta.get_ticks(), false);
                    ++it3;
                }
                else
                {
                    it3 = list_hit_emitter.erase(it3);
                }
            }
            
            if(gamemode != 2)
            {
                if( buff_allowed[0] || 
                    buff_allowed[1] || 
                    buff_allowed[2] || 
                    buff_allowed[3] || 
                    buff_allowed[4] || 
                    buff_allowed[5] || 
                    buff_allowed[6] || 
                    buff_allowed[7] || 
                    buff_allowed[8] || 
                    buff_allowed[9] || 
                    buff_allowed[10] || 
                    buff_allowed[11] || 
                    buff_allowed[12] || 
                    buff_allowed[13] || 
                    buff_allowed[14] || 
                    buff_allowed[15] )
                {
                    nextBuffTime -= delta.get_ticks();
                    if(nextBuffTime <= 0)
                    {
                        nextBuffTime = 1000 + rand() % 10000;
                        CreateBuff();
                    }
                }
            }
            delta.start();
            
            apply_surface( 0, 0, background, screen );
            
            player[0].show();
            player[1].show();
            
            it = list_projectile.begin();
            while(it != list_projectile.end())
            {
                if(it->alive)
                {
                    it->show();
                    ++it;
                }
                else
                {
                    it = list_projectile.erase(it);
                }
            }
            
            it2 = list_buff.begin();
            while(it2 != list_buff.end())
            {
                if(it2->alive)
                {
                    it2->show();
                    ++it2;
                }
                else
                {
                    it2 = list_buff.erase(it2);
                }
            }
            
            it3 = list_hit_emitter.begin();
            while(it3 != list_hit_emitter.end())
            {
                if(it3->livetime > 0)
                {
                    it3->show();
                    ++it3;
                }
                else
                {
                    it3 = list_hit_emitter.erase(it3);
                }
            }
            
            if(player[0].lives < 0)
            {
				player[0].lives = 0;
			}
			if(player[1].lives < 0)
            {
				player[1].lives = 0;
			}
            
            //itoa(player[0].lives, buffer, 10);
            sprintf(buffer, "%d", player[0].lives);
            //sprintf(buffer, "%f", (float)delta.get_ticks());
            p1_lives_text = TTF_RenderText_Solid( font, buffer, textColor );
            //itoa(player[1].lives, buffer, 10);            
            sprintf(buffer, "%d", player[1].lives);
            p2_lives_text = TTF_RenderText_Solid( font, buffer, textColor );
            //itoa(player[0].shots, buffer, 10);
            sprintf(buffer, "%d", player[0].shots);
            p1_ammo_text = TTF_RenderText_Solid( fontTest, buffer, textColor );
            //itoa(player[1].shots, buffer, 10);
            sprintf(buffer, "%d", player[1].shots);
            p2_ammo_text = TTF_RenderText_Solid( fontTest, buffer, textColor );
            
            apply_surface( 0 - 64, 768 - 80, p1_lives_bg, screen, NULL );
            apply_surface( 1024 - 256 + 64, 768 - 80, p2_lives_bg, screen, NULL );
            
            apply_surface( 0 + 8, 768 - 16 - 8, p1_wpn_icon, screen, NULL );
            apply_surface( 1024 - 16 - 8, 768 - 16 - 8, p2_wpn_icon, screen, NULL );
            
            apply_surface( 32, 768 - 64, p1_lives_text, screen, NULL );
            apply_surface( 1024 - 128, 768 - 64, p2_lives_text, screen, NULL );
            
            if(!no_ammo)
            {
            	apply_surface( 4, 768 - 44, p1_ammo_text, screen, NULL );
            	apply_surface( 1024 - 32, 768 - 44, p2_ammo_text, screen, NULL );
			}
            
            showHealthBars();
            
            /*
            sprintf(buffer, "x: %f", player[0].x);
            apply_surface( 0 + 8, 0 + 8, TTF_RenderText_Solid( fontTest, buffer, textColor ), screen, NULL );
            sprintf(buffer, "y: %f", player[0].y);
            apply_surface( 0 + 8, 0 + 8 + 16, TTF_RenderText_Solid( fontTest, buffer, textColor ), screen, NULL );
            sprintf(buffer, "x: %f", player[1].x);
            apply_surface( 0 + 8 + 800, 0 + 8, TTF_RenderText_Solid( fontTest, buffer, textColor ), screen, NULL );
            sprintf(buffer, "y: %f", player[1].y);
            apply_surface( 0 + 8 + 800, 0 + 8 + 16, TTF_RenderText_Solid( fontTest, buffer, textColor ), screen, NULL );
            */
            
            
            if(player[0].lives <= 0)
            {
                if(player[1].lives >= maxLives)
                {
                    text_win = TTF_RenderText_Solid( fontWin, "234-763-595", textColor );
                }
                else
                {
                    text_win = TTF_RenderText_Solid( fontWin, "Spieler 2 gewinnt!", textColor );
                }
                apply_surface( SCREEN_WIDTH / 2 - text_win->w / 2, 768 / 2, text_win, screen, NULL );
                SDL_Flip( screen );
                SDL_Delay(2000);
                newGame();
            }
            else if(player[1].lives <= 0)
            {
                if(player[0].lives >= maxLives)
                {
                    text_win = TTF_RenderText_Solid( fontWin, "234-763-595", textColor );
                }
                else
                {
                    text_win = TTF_RenderText_Solid( fontWin, "Spieler 1 gewinnt!", textColor );
                }
                apply_surface( SCREEN_WIDTH / 2 - text_win->w / 2, 768 / 2, text_win, screen, NULL );
                SDL_Flip( screen );
                SDL_Delay(2000);
                newGame();
            }
        }
        SDL_Flip( screen );
    }

    clean_up();
    return 0;
}
