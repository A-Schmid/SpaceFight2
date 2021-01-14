SDL_Surface *load_image( std::string filename )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        SDL_FreeSurface( loadedImage );
    }
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    if(once)
    {
        SDL_Init( SDL_INIT_EVERYTHING );
        TTF_Init();
        SDLNet_Init();
        
        icon = load_image( "img/ICON.ico" );
        SDL_WM_SetIcon( icon, 0 );
        
        screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF );
        SDL_WM_SetCaption( "SpaceFight 2", NULL );
        
        srand( SDL_GetTicks() );
        
        wpnShots[0] = 15;
        wpnShots[1] = 25;
        wpnShots[2] = 10;
        wpnShots[3] = 20;
		wpnShots[4] = 15;
        wpnShots[5] = 15;
        wpnShots[6] = 10;
        once = false;
    }
    nextBuffTime = 1000;
    
    font = TTF_OpenFont( "aliee13.ttf", 48 );
    fontWin = TTF_OpenFont( "aliee13.ttf", 96 );
    fontTest = TTF_OpenFont( "aliee13.ttf", 16 );
    fontMenu = TTF_OpenFont( "aliee13.ttf", 32 );
    
    background = load_image( "img/BG.png" );
    logo = load_image( "img/logo.png" );
    
    p1_healthbar_full = load_image( "img/healthbar_full.png" );
    p1_healthbar_empty = load_image( "img/healthbar_empty.png" );
    p2_healthbar_full = load_image( "img/healthbar_full.png" );
    p2_healthbar_empty = load_image( "img/healthbar_empty.png" );
    
    p1_lives_bg = load_image( "img/hud2_1.png" );
    p2_lives_bg = load_image( "img/hud2_2.png" );

    InitEmitters();
    InitBuffs();
    InitShields();
    InitPlayers();  
    InitProjectiles();
    InitMenuItems();
    
    
    
    //SDLNet_ResolveHost(&ip, NULL, 2000);
    //sd = SDLNet_TCP_Open(&ip);
    
    return true;
}

bool load_files()
{
    return true;
}

void clean_up(bool quit)
{
    SDL_FreeSurface( background );
    SDL_FreeSurface( p1_lives_bg );
    SDL_FreeSurface( p2_lives_bg );
    SDL_FreeSurface( p1_healthbar_full );
    SDL_FreeSurface( p1_healthbar_empty );
    SDL_FreeSurface( player[0].img );
    SDL_FreeSurface( player[1].img );
    SDL_FreeSurface( shield[0].img[0] );
    SDL_FreeSurface( shield[0].img[1] );
    SDL_FreeSurface( shield[1].img[0] );
    SDL_FreeSurface( shield[1].img[1] );
    SDL_FreeSurface( shield[2].img[0] );
    SDL_FreeSurface( shield[2].img[1] );
    SDL_FreeSurface( shield[3].img[0] );
    SDL_FreeSurface( shield[3].img[1] );
    SDL_FreeSurface( emitter[0].img );
    SDL_FreeSurface( emitter[1].img );
    SDL_FreeSurface( emitter[2].img );
    SDL_FreeSurface( emitter[3].img );
    SDL_FreeSurface( emitter[4].img );
    SDL_FreeSurface( emitter[5].img );
    SDL_FreeSurface( emitter[6].img );
    SDL_FreeSurface( emitter[7].img );
    SDL_FreeSurface( emitter[8].img );
    SDL_FreeSurface( emitter[11].img );
    SDL_FreeSurface( img_buff[0] );
    SDL_FreeSurface( img_buff[1] );
    SDL_FreeSurface( img_buff[2] );
    SDL_FreeSurface( img_buff[3] );
    SDL_FreeSurface( img_buff[4] );
    SDL_FreeSurface( img_buff[5] );
    SDL_FreeSurface( img_buff[6] );
    SDL_FreeSurface( img_buff[7] );
    SDL_FreeSurface( img_buff[8] );
    SDL_FreeSurface( img_buff[9] );
    SDL_FreeSurface( img_buff[10] );
    SDL_FreeSurface( img_buff[11] );
    SDL_FreeSurface( img_buff[12] );
    SDL_FreeSurface( img_buff[13] );
    SDL_FreeSurface( img_buff[14] );
    SDL_FreeSurface( projectile[0][0].img );
    SDL_FreeSurface( projectile[0][1].img );
    SDL_FreeSurface( projectile[1][0].img );
    SDL_FreeSurface( projectile[1][1].img );
    SDL_FreeSurface( projectile[2][0].img );
    SDL_FreeSurface( projectile[2][1].img );
    SDL_FreeSurface( projectile[3][0].img );
    SDL_FreeSurface( projectile[3][1].img );
    SDL_FreeSurface( projectile[4][0].img );
    SDL_FreeSurface( projectile[4][1].img );
    SDL_FreeSurface( projectile[5][0].img );
    SDL_FreeSurface( projectile[5][1].img );
    SDL_FreeSurface( p1_lives_text );
    SDL_FreeSurface( p2_lives_text );
    SDL_FreeSurface( menuitem[0].img );
    SDL_FreeSurface( menuitem[0].img_hover );
    SDL_FreeSurface( menuitem[0].text );
    SDL_FreeSurface( menuitem[0].text_hover );
    SDL_FreeSurface( menuitem[1].img );
    SDL_FreeSurface( menuitem[1].img_hover );
    SDL_FreeSurface( menuitem[1].text );
    SDL_FreeSurface( menuitem[1].text_hover );
    SDL_FreeSurface( menuitem[2].img );
    SDL_FreeSurface( menuitem[2].img_hover );
    SDL_FreeSurface( menuitem[2].text );
    SDL_FreeSurface( menuitem[2].text_hover );
    SDL_FreeSurface( menuitem[3].img );
    SDL_FreeSurface( menuitem[3].img_hover );
    SDL_FreeSurface( menuitem[3].text );
    SDL_FreeSurface( menuitem[3].text_hover );
    SDL_FreeSurface( logo );
    SDL_FreeSurface( text_win );
    if(gamemode == 1)
    {
        SDLNet_TCP_Close( server.sd );
        SDLNet_TCP_Close( server.csd );
    }
    if(gamemode == 2)
    {
        SDLNet_TCP_Close( client.sd );
        SDLNet_TCP_Close( client.csd );
    }
        
    list<PROJECTILE>::iterator it = list_projectile.begin();
    while(it != list_projectile.end())
    {
        if(it->alive)
        {
            it->alive = false;
        }
        ++it;
    }   

    if(quit)
    {
        SDL_FreeSurface( icon );
        SDL_Quit();
    }    
}

void handle_input()
{
    Uint8 *keystate = SDL_GetKeyState(NULL);
    
    //-------
    if(keystate[SDLK_ESCAPE])
    {
        newGame();
        gamemode = -1;
    }

    if(keystate[SDLK_SPACE] || keystate[SDLK_b])
    {
        if(player[0].shootDown == false)
        {
            player[0].shoot();
        }
    }
    else
    {
        player[0].shootDown = false;
    }
    
    if(keystate[SDLK_w])
    {
        player[0].yVel = -1;
    }
    else
    {
        if(player[0].yVel < 0)
        {
            player[0].yVel = 0;
        }
    }
    
    if(keystate[SDLK_s])
    {
        player[0].yVel = 1;
    }
    else
    {
        if(player[0].yVel > 0)
        {
            player[0].yVel = 0;
        }
    }
    
    if(keystate[SDLK_a])
    {
        player[0].xVel = -1;
    }
    else
    {
        if(player[0].xVel < 0)
        {
            player[0].xVel = 0;
        }
    }
    
    if(keystate[SDLK_d])
    {
        player[0].xVel = 1;
    }
    else
    {
        if(player[0].xVel > 0)
        {
            player[0].xVel = 0;
        }
    }
    
    
    
    //----
    
    if(keystate[SDLK_KP0] || keystate[SDLK_RCTRL])
    {
        if(player[1].shootDown == false)
        {
            player[1].shoot();
        }
    }
    else
    {
        player[1].shootDown = false;
    }
    
    
    if(keystate[SDLK_UP])
    {
        player[1].yVel = -1;
    }
    else
    {
        if(player[1].yVel < 0)
        {
            player[1].yVel = 0;
        }
    }
    
    if(keystate[SDLK_DOWN])
    {
        player[1].yVel = 1;
    }
    else
    {
        if(player[1].yVel > 0)
        {
            player[1].yVel = 0;
        }
    }
    
    if(keystate[SDLK_LEFT])
    {
        player[1].xVel = -1;
    }
    else
    {
        if(player[1].xVel < 0)
        {
            player[1].xVel = 0;
        }
    }
    
    if(keystate[SDLK_RIGHT])
    {
        player[1].xVel = 1;
    }
    else
    {
        if(player[1].xVel > 0)
        {
            player[1].xVel = 0;
        }
    }
    
    
    
    
    
    /*if( event.type == SDL_KEYDOWN )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_w: player[0].yVel -= player[0].vel; break;
            case SDLK_s: player[0].yVel += player[0].vel; break;
            case SDLK_a: player[0].xVel -= player[0].vel; break;
            case SDLK_d: player[0].xVel += player[0].vel; break;
            case SDLK_SPACE: player[0].shoot(); break;
            
            case SDLK_o:
                if(gamemode == 0)
                {
                    gamemode = 1;
                    server = SERVER();
                    server.init();
                }
                break;
            case SDLK_p:
                if(gamemode == 0)
                {
                    gamemode = 2;
                    client = CLIENT();
                }
                break;
            
            case SDLK_UP: player[1].yVel -= player[1].vel; break;
            case SDLK_DOWN: player[1].yVel += player[1].vel; break;
            case SDLK_LEFT: player[1].xVel -= player[1].vel; break;
            case SDLK_RIGHT: player[1].xVel += player[1].vel; break;
            case SDLK_KP0: player[1].shoot(); break;
        }
    }
    else if( event.type == SDL_KEYUP )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_w: player[0].yVel += player[0].vel; break;
            case SDLK_s: player[0].yVel -= player[0].vel; break;
            case SDLK_a: player[0].xVel += player[0].vel; break;
            case SDLK_d: player[0].xVel -= player[0].vel; break;
            
            case SDLK_UP: player[1].yVel += player[1].vel; break;
            case SDLK_DOWN: player[1].yVel -= player[1].vel; break;
            case SDLK_LEFT: player[1].xVel += player[1].vel; break;
            case SDLK_RIGHT: player[1].xVel -= player[1].vel; break;
        }
    }*/
}

void handle_input_server()
{
    Uint8 *keystate = SDL_GetKeyState(NULL);

    if(keystate[SDLK_ESCAPE])
    {
        newGame();
        gamemode = -1;
    }

    if(keystate[SDLK_SPACE] || keystate[SDLK_b])
    {
        if(player[0].shootDown == false)
        {
            player[0].shoot();
            server.send("2");
        }
    }
    else
    {
        player[0].shootDown = false;
    }
    
    if(keystate[SDLK_w])
    {
        player[0].yVel = -1;
    }
    else
    {
        if(player[0].yVel < 0)
        {
            player[0].yVel = 0;
        }
    }
    
    if(keystate[SDLK_s])
    {
        player[0].yVel = 1;
    }
    else
    {
        if(player[0].yVel > 0)
        {
            player[0].yVel = 0;
        }
    }
    
    if(keystate[SDLK_a])
    {
        player[0].xVel = -1;
    }
    else
    {
        if(player[0].xVel < 0)
        {
            player[0].xVel = 0;
        }
    }
    
    if(keystate[SDLK_d])
    {
        player[0].xVel = 1;
    }
    else
    {
        if(player[0].xVel > 0)
        {
            player[0].xVel = 0;
        }
    }
    
    sprintf(buffer, "1~%f~%f~%f~%f~%i~%i~", player[0].xVel,
                                            player[0].yVel,
                                            player[0].x,
                                            player[0].y,
                                            player[0].lives,
                                            player[0].weapon);
    //SDL_WM_SetCaption("blub", NULL);
    //SDL_Delay(1000);
    //printf("S: %i\n", strlen(buffer));
    server.send(buffer);
}

float getBufferData()
{
    char *tempstr = new char[strlen(server.buffer)];
    float tempfloat = 0;
    bool quit = false;
    int i = 0;
    int j = 0;
    
    while(server.buffer[j] == '0')
    {
        j++;
    }
    server.buffer[j] = '0';
    j++;
    while(quit == false)
    {
        tempstr[i] = server.buffer[j];
        server.buffer[j] = '0';
        i++;
        j++;
        if(server.buffer[j] == '~')
        {
            quit = true;
        }
    }
    tempfloat = atoi(tempstr);
    return tempfloat;
}

float getBufferData2()
{
    //printf("f1: %s\n", client.buffer);
    char *tempstr = new char[strlen(client.buffer)];
    float tempfloat = 0;
    bool quit = false;
    int i = 0;
    int j = 0;
    
    while(client.buffer[j] == '0')
    {
        j++;
    }
    //printf("f2: %i\n", j);
    client.buffer[j] = '0';
    j++;
    while(quit == false)
    {
        tempstr[i] = client.buffer[j];
        //printf("f3: %s\n", tempstr);
        client.buffer[j] = '0';
        i++;
        j++;
        if(client.buffer[j] == '~')
        {
            quit = true;
        }
    }
    //printf("f4: %s\n", tempstr);
    tempfloat = atoi(tempstr);
    //printf("f5: %f\n", tempfloat);
    return tempfloat;
}

void handle_input_server_2()
{
    //printf("1\n");
    
    /*
    float tempfloat = 0;
    int i;
    char *tempstr;
    bool quit = false;
    */
    
    //printf("2 - %s\n", server.buffer);
    
    server.listen(100);
    
    //printf("3 - %s\n", server.buffer);
    //strcpy(server.buffer, "00");
    //while(server.listen(3))
    //{
    //SDL_WM_SetCaption(server.buffer, NULL);
    switch(server.buffer[0])
    {
        case '1':
            server.buffer[0] = '0';
            player[1].xVel      = getBufferData();
            player[1].yVel      = getBufferData();
            player[1].x         = getBufferData();
            player[1].y         = getBufferData();
            player[1].lives     = (int)getBufferData();
            player[1].weapon    = (int)getBufferData();
            //printf("s8 - %f\n", player[1].x);
            break;
        case '2':
            player[1].shoot();
            break;
        default:
            break;
    }
    //}
    //SDL_WM_SetCaption(server.buffer, NULL);
    //delete tempstr;
}

void handle_input_client_2()
{
    BUFF tempBuff;
    float tempfloat1;
    float tempfloat2;
    float tempfloat3;
    //printf("1\n");
    
    /*float tempfloat = 0;
    int i;
    char *tempstr;
    bool quit = false;*/
    
    //printf("2 - %s\n", server.buffer);
    client.listen(100);
    //strcpy(client.buffer, "1~1~1~100~200~200~3~");
    
    //printf("3 - %s\n", server.buffer);
    //strcpy(server.buffer, "00");
    //while(server.listen(3))
    //{
    //SDL_WM_SetCaption(client.buffer, NULL);
    switch(client.buffer[0])
    {
        case '1':
            client.buffer[0] = '0';
            player[0].xVel      = getBufferData2();
            player[0].yVel      = getBufferData2();
            player[0].x         = getBufferData2();
            player[0].y         = getBufferData2();
            player[0].lives     = (int)getBufferData2();
            player[0].weapon    = (int)getBufferData2();
            //printf("c8 - %f\n", player[0].x);
            break;
        case '2':
            player[0].shoot();
            break;
        case '3':
            //SDL_WM_SetCaption(client.buffer, NULL);
            client.buffer[0] = '0';
            //printf("s2: %s\n", client.buffer);
            getBufferData2();
            tempfloat1    = getBufferData2();
            tempfloat2    = getBufferData2();
            tempfloat3    = getBufferData2();
            //printf("x2: %f\n", tempfloat1);
            //printf("y2: %f\n", tempfloat2);
            //printf("t2: %f\n\n", tempfloat3);
            tempBuff = BUFF((int)tempfloat1, (int)tempfloat2, (int)tempfloat3);
            list_buff.push_back(tempBuff);
            break;
        default:
            break;
    }
    //}
    
    //delete tempstr;
}

void handle_input_client()
{
    Uint8 *keystate = SDL_GetKeyState(NULL);
    
    if(keystate[SDLK_ESCAPE])
    {
        newGame();
        gamemode = -1;
    }
    
    if(keystate[SDLK_KP0] || keystate[SDLK_RCTRL])
    {
        if(player[1].shootDown == false)
        {
            player[1].shoot();
            client.send("2");
        }
    }
    else
    {
        player[1].shootDown = false;
    }
        
    
    if(keystate[SDLK_UP])
    {
        player[1].yVel = -1;
        //client.send("11");
    }
    else
    {
        if(player[1].yVel < 0)
        {
            player[1].yVel = 0;
        }
    }
    
    if(keystate[SDLK_DOWN])
    {
        player[1].yVel = 1;
        //client.send("12");
    }
    else
    {
        if(player[1].yVel > 0)
        {
            player[1].yVel = 0;
        }
    }
    
    if(keystate[SDLK_LEFT])
    {
        player[1].xVel = -1;
        //client.send("13");
    }
    else
    {
        if(player[1].xVel < 0)
        {
            player[1].xVel = 0;
        }
    }
    
    if(keystate[SDLK_RIGHT])
    {
        player[1].xVel = 1;
        //client.send("14");
    }
    else
    {
        if(player[1].xVel > 0)
        {
            player[1].xVel = 0;
        }
    }
    
    sprintf(buffer, "1~%f~%f~%f~%f~%i~%i~", player[1].xVel,
                                            player[1].yVel,
                                            player[1].x,
                                            player[1].y,
                                            player[1].lives,
                                            player[1].weapon);
    client.send(buffer);
    //SDL_Delay(1000);
}

void CreateBuff()
{
    BUFF tempBuff = BUFF();
    if(gamemode == 1)
    {
        //printf("x1: %i\n", tempBuff.x);
        //printf("y1: %i\n", tempBuff.y);
        //printf("t1: %i\n\n", tempBuff.type);
        sprintf(buffer, "3~0~%i~%i~%i~~",   tempBuff.x,
                                            tempBuff.y,
                                            tempBuff.type);
        //SDL_WM_SetCaption(buffer, NULL);
        server.send(buffer);
    }
    list_buff.push_back(tempBuff);
}

bool GetCollision(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2)
{
    int left1 = x1;
    int right1 = x1 + width1;
    int top1 = y1;
    int bottom1 = y1 + height1;
    
    int left2 = x2;
    int right2 = x2 + width2;
    int top2 = y2;
    int bottom2 = y2 + height2;
    
    if(right1 < left2)
    {
        return false;
    }
    if(right2 < left1)
    {
        return false;
    }
    if(bottom1 < top2)
    {
        return false;
    }
    if(bottom2 < top1)
    {
        return false;
    }    
    
    return true;
}

void newGame()
{
    player[0].x = 200;
    player[0].y = SCREEN_HEIGHT / 2 - player[0].height / 2;
    player[0].weapon = 0;
    player[0].lives = maxLives;
    player[0].shots = wpnShots[player[0].weapon];
    player[0].dmg_over_time_time = 0;
    
    player[1].x = SCREEN_WIDTH - 200 - player[1].width;
    player[1].y = SCREEN_HEIGHT / 2 - player[1].height / 2;
    player[1].weapon = 0;
    player[1].lives = maxLives;
    player[1].shots = wpnShots[player[1].weapon];
    player[1].dmg_over_time_time = 0;
    
    SP_score = 0;
    
    list<PROJECTILE>::iterator it = list_projectile.begin();
    while(it != list_projectile.end())
    {
        if(it->alive)
        {
            it->alive = false;
        }
        ++it;
    }
    
    list<BUFF>::iterator it2 = list_buff.begin();
    while(it2 != list_buff.end())
    {
        if(it2->alive)
        {
            it2->alive = false;
        }
        ++it2;
    }
}

SERVER::SERVER()
{
    SDLNet_ResolveHost(&ip, NULL, 2000);
    sd = SDLNet_TCP_Open(&ip);    
}

void SERVER::init()
{
    buffer = new char[0];
    int quit = 0;
    while (!quit)
	{
		if (csd = SDLNet_TCP_Accept(sd))
		{
            remoteIP = SDLNet_TCP_GetPeerAddress(csd);
            quit = 1;
		}
	}
}

/*void CLIENT::init()
{
    buffer = new char[0];
    int quit = 0;
    while (!quit)
	{
		if (csd = SDLNet_TCP_Accept(sd))
		{
            remoteIP = SDLNet_TCP_GetPeerAddress(csd);
            quit = 1;
		}
	}
}*/

bool SERVER::listen(int len)
{
    //SDL_WM_SetCaption("0", NULL);
    int quit = 0;
    int tempint;
    delete buffer;
    buffer = new char[len];
    for(int i = 0; i < len; i++)
    {
        buffer[i] = '0';
    }
    //SDL_WM_SetCaption("A", NULL);
	if (SDLNet_TCP_Recv(csd, buffer, len) > 0)
	{
        //printf("SERVER: %s\n", buffer);
        //SDL_WM_SetCaption("B", NULL);
        return true;
    }
    //strcpy(buffer, "1~1~1~100~200~200~3~");
    //SDL_WM_SetCaption("BLAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB", NULL);
    return false;
}

bool CLIENT::listen(int len)
{
    //SDL_WM_SetCaption("0", NULL);
    int quit = 0;
    int tempint;
    delete buffer;
    buffer = new char[len];
    for(int i = 0; i < len; i++)
    {
        buffer[i] = '0';
    }
    //SDL_WM_SetCaption("A", NULL);
	if (SDLNet_TCP_Recv(sd, buffer, len) > 0)
	{
        //printf("CLIENT: %s\n", buffer);
        //SDL_WM_SetCaption("B", NULL);
        return true;
    }
    //strcpy(buffer, "1~1~1~100~200~200~3~");
    //SDL_WM_SetCaption("BLAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB", NULL);
    return false;
}


CLIENT::CLIENT(char* getIp)
{
    SDLNet_ResolveHost(&ip, getIp, 2000);
    sd = SDLNet_TCP_Open(&ip);
}

void CLIENT::send(char* data)
{
    //SDL_Quit();
    //SDL_WM_SetCaption("C", NULL);
    int len = strlen(data) + 1;
    //printf("C: send1\n");
    SDLNet_TCP_Send(sd, data, len);
    //printf("C: send2\n");
    //SDL_WM_SetCaption("D", NULL);
}

void SERVER::send(char* data)
{
    //SDL_Quit();
    //SDL_WM_SetCaption("C", NULL);
    int len = strlen(data) + 1;
    //printf("S: send1\n");
    SDLNet_TCP_Send(csd, data, len);
    //printf("S: send2\n");
    //SDL_WM_SetCaption("D", NULL);
}

string read_file(int line, char* filepath)
{
    FILE *file;
    char file_c;
    std::string tempstr = "";
    int i = 0;
    
    file = fopen(filepath, "r+");
    file_c = fgetc(file);
    
    while(i < line)
    {
        while(file_c != '\n')
        {
            file_c = fgetc(file);
        }
        i++;
        file_c = fgetc(file);
    }
    
    i = 0;
    
    while(file_c != EOF && file_c != '\n')
    {
        tempstr += file_c;
        i++;
        file_c = fgetc(file);
    }
    
    /*if(line == 5)
	{
		while(file_c != EOF)
    	{
			file_c = fgetc(file);
		}
		fgetc(file);
		fputs("\n0.5", file);
	}*/
    fclose(file);
    //SDL_WM_SetCaption(tempstr, NULL);
    //printf("%s\n", tempstr);
    return tempstr;
}

void showHealthBars(bool show1, bool show2)
{
    SDL_Rect clip;
    if(show1)
    {
        clip.x = 0;
        clip.y = 0;
        clip.w = (int)((256.f/200.f) * player[0].lives);
        clip.h = 16;

        apply_surface( 32, SCREEN_HEIGHT - 20, p1_healthbar_empty, screen );    
        apply_surface( 32, SCREEN_HEIGHT - 20, p1_healthbar_full, screen, &clip );
    }
    
    if(show2)
    {
        clip.x = (int)(((256.f/200.f) * player[1].lives) - 256);
        clip.y = 0;
        clip.w = 256;
        clip.h = 16;
    
        apply_surface( SCREEN_WIDTH - 256 - 32, SCREEN_HEIGHT - 20, p2_healthbar_empty, screen );    
        apply_surface( SCREEN_WIDTH - 256 - 32, SCREEN_HEIGHT - 20, p2_healthbar_full, screen, &clip );
    }
}

Uint32 stringToHex(char* str)
{
	//printf("+%s\n", str);
	Uint32 ret;
	unsigned int hex[8];
	char hexChars[]= "0123456789ABCDEF";
	unsigned int hexNums[]= {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF};
	for(int i = 0; i < 8; i++)
	{
		//printf(" %i\n", i);
		for(int j = 0; j < 16; j++)
		{
			//printf("  %i\n", j);
			//printf("   %c\n", hexChars[j]);
			//printf("   %X\n", hexNums[j]);
			if(str[i] == hexChars[j])
			{
				hex[i] = hexNums[j];
				//printf("    %X\n", hex[i]);
			}
		}
	}
    ret =   (hex[7]	<<  0)	|
            (hex[6]	<<  4)	|
            (hex[5]	<<  8)	|
            (hex[4]	<<  12) |
			(hex[3]	<<  16)	|
            (hex[2]	<<  20)	|
            (hex[1]	<<  24)	|
            (hex[0]	<<  28);
    //printf("-%X\n", ret);
    return ret;
}

EMITTER readEmitterFromFile(char* filepath)
{
    EMITTER tempEmit                    = EMITTER();
    tempEmit.img                        = load_image(      (char*) read_file(0, filepath).c_str()  );
    tempEmit.x                          = atoi(            (char*) read_file(1, filepath).c_str()  );
    tempEmit.y                          = atoi(            (char*) read_file(2, filepath).c_str()  );
    tempEmit.width                      = atoi(            (char*) read_file(3, filepath).c_str()  );
    tempEmit.height                     = atoi(            (char*) read_file(4, filepath).c_str()  );
    tempEmit.addY                       = atoi(            (char*) read_file(5, filepath).c_str()  );
    tempEmit.delay                      = atoi(            (char*) read_file(6, filepath).c_str()  );
    tempEmit.nextSpawn                  = atoi(            (char*) read_file(7, filepath).c_str()  );
    tempEmit.livetime                   = atoi(            (char*) read_file(8, filepath).c_str()  );
    tempEmit.permanent                  = strcmp("false",  (char*) read_file(9, filepath).c_str()  );
    tempEmit.spawnAtOnce                = atoi(            (char*) read_file(10, filepath).c_str() );
    tempEmit.particleCount              = atoi(            (char*) read_file(11, filepath).c_str() );
    tempEmit.maxParticleCount           = atoi(            (char*) read_file(12, filepath).c_str() );
    tempEmit.ParticleMinVel             = atoi(            (char*) read_file(13, filepath).c_str() );
    tempEmit.ParticleMaxVel             = atoi(            (char*) read_file(14, filepath).c_str() );
    tempEmit.ParticleMinDir             = atoi(            (char*) read_file(15, filepath).c_str() );
    tempEmit.ParticleMaxDir             = atoi(            (char*) read_file(16, filepath).c_str() );
    tempEmit.ParticleMinLivetime        = atoi(            (char*) read_file(17, filepath).c_str() );
    tempEmit.ParticleMaxLivetime        = atoi(            (char*) read_file(18, filepath).c_str() );
    tempEmit.ParticleTurbulenceChance   = atoi(            (char*) read_file(19, filepath).c_str() );
    tempEmit.ParticleTurbulenceStrength = atoi(            (char*) read_file(20, filepath).c_str() );
    tempEmit.color[0]					= stringToHex(	   (char*) read_file(21, filepath).c_str() );
    tempEmit.color[1]					= stringToHex(	   (char*) read_file(22, filepath).c_str() );
    tempEmit.ParticleFadeOutStartPerc	= atoi(            (char*) read_file(23, filepath).c_str() );
    return tempEmit;
}


Uint32 get_pixel32( SDL_Surface *surface, int x, int y ) 
{
    Uint32 *pixels = (Uint32 *)surface->pixels; 
    return pixels[ ( y * surface->w ) + x ]; 
}

void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel ) 
{
    Uint32 *pixels = (Uint32 *)surface->pixels; 
    pixels[ ( y * surface->w ) + x ] = pixel; 
}

Uint32 BlendPixels(Uint32 src, Uint32 trg, int mode, float srcRatio)
{
    /*unsigned int srcBlue   = (src >>  0)   & 0xff;
    unsigned int srcRed     = (src >>  8)   & 0xff;
    unsigned int srcGreen   = (src >>  16)  & 0xff;
    unsigned int srcAlpha    = (src >>  24)  & 0xff;
    unsigned int trgBlue   = (src >>  0)   & 0x00;
    unsigned int trgRed     = (trg >>  8)   & 0x00;
    unsigned int trgGreen   = (trg >>  16)  & 0x00;
    unsigned int trgAlpha    = (trg >>  24)  & 0x00;*/
    Uint8 *srcColors = (Uint8*)&src;
    Uint8 *trgColors = (Uint8*)&trg;    
    
    unsigned int srcBlue  = srcColors[0];
    unsigned int srcRed    = srcColors[1];
    unsigned int srcGreen  = srcColors[2];
    unsigned int srcAlpha   = srcColors[3];
    unsigned int trgBlue  = trgColors[0];
    unsigned int trgRed    = trgColors[1];
    unsigned int trgGreen  = trgColors[2];
    unsigned int trgAlpha   = trgColors[3];
    
    unsigned int finBlue;
    
    float trgRatio = (1 - srcRatio);
    /*printf("s0: %u\n", srcBlue);
    printf("s1: %u\n", srcRed);
    printf("s2: %u\n", srcGreen);
    printf("s3: %u\n", srcAlpha);
    printf("t0: %u\n", trgBlue);
    printf("t1: %u\n", trgRed);
    printf("t2: %u\n", trgGreen);
    printf("t3: %u\n", trgAlpha);*/
    
    switch(mode)
    {
        case -1:
            return  (srcBlue   <<  0)  |
                    (srcRed     <<  8)  |
                    (srcGreen   <<  16) |
                    (srcAlpha    <<  24);
            break;
        case 0:
            /*finBlue    = srcBlue + trgBlue - srcBlue * trgBlue;
            if(finBlue == 0)
            {
                srcBlue = 0;
            }
            else
            {
                srcBlue /= finBlue;
            }
            trgBlue    = 0xFF - srcBlue;
            trgRed      = (srcRed   * srcBlue) + (trgRed   * trgBlue);
            trgGreen    = (srcGreen * srcBlue) + (trgGreen * trgBlue);
            trgAlpha     = (srcAlpha  * srcBlue) + (trgAlpha  * trgBlue);
            trgBlue    = finBlue;*/
            break;
        case 1: //avg
        	/*printf("1: %X\n", srcRed);
        	printf("2: %f\n", srcRatio);
        	printf("3: %x\n", srcRatio * srcRed);
        	printf("4: %x\n", (Uint8)srcRatio * srcRed);
        	printf("5: %x\n", (Uint8)(srcRatio * (float)srcRed));*/
        	//trgAlpha = 0.5;
        	//srcRatio *= (float)trgAlpha;
        	//trgRatio *= (float)trgAlpha;
            trgRed      = (srcRatio * srcRed   + trgRatio * trgRed);
            trgGreen    = (srcRatio * srcGreen + trgRatio * trgGreen);
            //trgAlpha     = (srcRatio * srcAlpha  + trgRatio * trgAlpha);
            trgAlpha = srcAlpha;
            trgBlue    = (srcRatio * srcBlue + trgRatio * trgBlue);
            break;
        case 2: //mul
            trgRed      = (srcRed   * trgRed)   >> 8;
            trgGreen    = (srcGreen * trgGreen) >> 8;
            trgBlue     = (srcBlue  * trgBlue)  >> 8;
            break;
        case 3: //add
        	//srcBlue = 0x00;
            trgRed      += srcRed;
            trgGreen    += srcGreen;
            trgBlue    += srcBlue;
            trgAlpha     += srcAlpha;
            if(trgRed   > 0xff) trgRed      = 0xff;
            if(trgGreen > 0xff) trgGreen    = 0xff;
            if(trgAlpha  > 0xff) trgAlpha     = 0xff;
            if(trgBlue > 0xff) trgBlue    = 0xff;
            //trgBlue = 0xff;
            break;
        case 4: //avg2
        	/*printf("1: %X\n", trgAlpha);
        	printf("2: %f\n", (float)trgAlpha);
        	printf("3: %X\n", trgRatio * trgAlpha);
        	printf("4: %X\n", trgAlpha / 0xff);
        	printf("5: %X\n", trgRatio * (trgAlpha / 0xff));*/
        	
        	/*printf("1a: %X\n", srcRed);
        	printf("1b: %X\n", srcGreen);
        	printf("1c: %X\n", srcAlpha);
        	printf("1d: %X\n", srcBlue);
			printf("2a: %X\n", trgRed);
        	printf("2b: %X\n", trgGreen);
        	printf("2c: %X\n", trgAlpha);
        	printf("2d: %X\n", trgBlue);*/
        	
        	trgRatio = (float)trgAlpha / 255;
        	//trgRatio = 0;
        	srcRatio = 1 - trgRatio;
            if(srcRed 	> 0x00) trgRed		= (srcRatio * srcRed   + trgRatio * trgRed)		; else trgRed	= 0x00;
            if(srcGreen > 0x00) trgGreen	= (srcRatio * srcGreen + trgRatio * trgGreen)	; else trgGreen	= 0x00;
            //if(srcAlpha 	> 0x00) trgAlpha		= (srcRatio * srcAlpha  + trgRatio * trgAlpha)	; else trgAlpha	= 0x00;
            trgAlpha = srcAlpha;
            if(srcBlue > 0x00) trgBlue	= (srcRatio * srcBlue + trgRatio * trgBlue)	; else trgBlue	= 0x00;
            break;
        default:
            return 0;
    }
    
    return  (trgBlue   <<  0)  |
            (trgRed     <<  8)  |
            (trgGreen   <<  16) |
            (trgAlpha    <<  24);
}

Uint32 FadePixel(Uint32 px, float LiveTime, float maxLiveTime, float FadePerc)
{
	Uint8 *colors = (Uint8*)&px;  
    
    unsigned int Alpha  = colors[3];
    unsigned int Red    = colors[1];
    unsigned int Green  = colors[2];
    unsigned int Blue   = colors[0];
    
    if(maxLiveTime - LiveTime >= maxLiveTime * FadePerc)
    {
		Alpha *= ((0.1 / (1 - FadePerc)) * (LiveTime / (0.1 * maxLiveTime)));
	}
    
    return  (Blue    <<  0)  |
        	(Red     <<  8)  |
        	(Green   <<  16) |
        	(Alpha   <<  24);
}
