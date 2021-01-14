void InitProjectiles()
{
    projectile[0][0] = PROJECTILE();
    projectile[0][0].img = load_image( "img/shot1_1.png" );
    projectile[0][0].type = 0;
    projectile[0][0].minDmg = 8;
    projectile[0][0].maxDmg = 11;
    projectile[0][0].owner = &player[0];
    projectile[0][0].enemy = &player[1];
    projectile[0][0].flyEmitter = emitter[0];
    projectile[0][0].hasFlyEmitter = true;
    projectile[0][0].hitEmitter = emitter[7];
    projectile[0][0].hasHitEmitter = true;
    projectile[0][0].hasImg = false;
    projectile[0][0].init();
    
    projectile[0][1] = PROJECTILE();
    projectile[0][1].img = load_image( "img/shot1_2.png" );
    projectile[0][1].vel = -650;
    projectile[0][1].type = 0;
    projectile[0][1].minDmg = 8;
    projectile[0][1].maxDmg = 11;
    projectile[0][1].owner = &player[1];
    projectile[0][1].enemy = &player[0];
    projectile[0][1].flyEmitter = emitter[0];
    projectile[0][1].hasFlyEmitter = true;
    projectile[0][1].hitEmitter = emitter[7];
    projectile[0][1].hasHitEmitter = true;
    projectile[0][1].hasImg = false;
    projectile[0][1].init();

    projectile[1][0] = PROJECTILE();
    projectile[1][0].img = load_image( "img/shot2_1.png" );
    projectile[1][0].width = 16;
    projectile[1][0].height = 16;
    projectile[1][0].vel = 700;
    projectile[1][0].type = 1;
    projectile[1][0].minDmg = 4;
    projectile[1][0].maxDmg = 6;
    projectile[1][0].damage = 5;
    projectile[1][0].delay = 0.01;
    projectile[1][0].owner = &player[0];
    projectile[1][0].enemy = &player[1];
    projectile[1][0].flyEmitter = emitter[1];
    projectile[1][0].hasFlyEmitter = true;
    projectile[1][0].hasImg = false;
    projectile[1][0].init();
    
    projectile[1][1] = PROJECTILE();
    projectile[1][1].img = load_image( "img/shot2_2.png" );
    projectile[1][1].width = 16;
    projectile[1][1].height = 16;
    projectile[1][1].vel = -700;
    projectile[1][1].type = 1;
    projectile[1][1].minDmg = 4;
    projectile[1][1].maxDmg = 6;
    projectile[1][1].damage = 5;
    projectile[1][1].delay = 0.01;
    projectile[1][1].owner = &player[1];
    projectile[1][1].enemy = &player[0];
    projectile[1][1].flyEmitter = emitter[1];
    projectile[1][1].hasFlyEmitter = true;
    projectile[1][1].hasImg = false;
    projectile[1][1].init();
    
    projectile[2][0] = PROJECTILE();
    projectile[2][0].img = load_image( "img/shot3_1.png" );
    projectile[2][0].vel = 600;
    projectile[2][0].follow = 100;
    projectile[2][0].type = 2;
    projectile[2][0].minDmg = 12;
    projectile[2][0].maxDmg = 18;
    projectile[2][0].damage = 15;
    projectile[2][0].delay = 0.15;
    projectile[2][0].owner = &player[0];
    projectile[2][0].enemy = &player[1];
    projectile[2][0].flyEmitter = emitter[2];
    projectile[2][0].hasFlyEmitter = true;
    projectile[2][0].hitEmitter = emitter[8];
    projectile[2][0].hasHitEmitter = true;
    projectile[2][0].init();
    
    projectile[2][1] = PROJECTILE();
    projectile[2][1].img = load_image( "img/shot3_2.png" );
    projectile[2][1].vel = -600;
    projectile[2][1].follow = 100;
    projectile[2][1].type = 2;
    projectile[2][1].minDmg = 12;
    projectile[2][1].maxDmg = 18;
    projectile[2][1].damage = 15;
    projectile[2][1].delay = 0.15;
    projectile[2][1].owner = &player[1];
    projectile[2][1].enemy = &player[0];
    projectile[2][1].flyEmitter = emitter[2];
    projectile[2][1].hasFlyEmitter = true;
    projectile[2][1].hitEmitter = emitter[8];
    projectile[2][1].hasHitEmitter = true;
    projectile[2][1].init();
    
    projectile[3][0] = PROJECTILE();
    projectile[3][0].img = load_image( "img/shot4_1.png" );
    projectile[3][0].vel = 600;
    projectile[3][0].type = 3;
    projectile[3][0].minDmg = 2;
    projectile[3][0].maxDmg = 10;
    projectile[3][0].damage = 8;
    projectile[3][0].slow = (int)(-250 * VEL_MODIFIER);
    projectile[3][0].slow_time = 2.5 * VEL_MODIFIER;
    projectile[3][0].delay = 0.03;
    projectile[3][0].owner = &player[0];
    projectile[3][0].enemy = &player[1];
    projectile[3][0].flyEmitter = emitter[3];
    projectile[3][0].hasFlyEmitter = true;
    projectile[3][0].init();
    
    projectile[3][1] = PROJECTILE();
    projectile[3][1].img = load_image( "img/shot4_2.png" );
    projectile[3][1].vel = -600;
    projectile[3][1].type = 3;
    projectile[3][1].minDmg = 2;
    projectile[3][1].maxDmg = 10;
    projectile[3][1].damage = 8;
    projectile[3][1].slow = (int)(-250 * VEL_MODIFIER);
    projectile[3][1].slow_time = 2.5 * VEL_MODIFIER;
    projectile[3][1].delay = 0.03;
    projectile[3][1].owner = &player[1];
    projectile[3][1].enemy = &player[0];
    projectile[3][1].flyEmitter = emitter[3];
    projectile[3][1].hasFlyEmitter = true;
    projectile[3][1].init();
    
    projectile[4][0] = PROJECTILE();
    projectile[4][0].img = load_image( "img/shot5_1.png" );
    projectile[4][0].vel = 700;
    projectile[4][0].type = 4;
    projectile[4][0].minDmg = 5;
    projectile[4][0].maxDmg = 7;
    projectile[4][0].damage = 7;
    projectile[4][0].slow = (int)(-500 * VEL_MODIFIER);
    projectile[4][0].slow_time = 4 * 0.12 * VEL_MODIFIER;
    projectile[4][0].delay = 0.08;
    projectile[4][0].owner = &player[0];
    projectile[4][0].enemy = &player[1];
    projectile[4][0].shield = shield[0];
    projectile[4][0].addShield = true;
    projectile[4][0].flyEmitter = emitter[4];
    projectile[4][0].hasFlyEmitter = true;
    projectile[4][0].hitEmitter = emitter[9];
    projectile[4][0].hasHitEmitter = true;
    projectile[4][0].init();
    
    projectile[4][1] = PROJECTILE();
    projectile[4][1].img = load_image( "img/shot5_2.png" );
    projectile[4][1].vel = -700;
    projectile[4][1].type = 4;
    projectile[4][1].minDmg = 5;
    projectile[4][1].maxDmg = 7;
    projectile[4][1].damage = 7;
    projectile[4][1].slow = (int)(-500 * VEL_MODIFIER);
    projectile[4][1].slow_time = 4 * 0.08 * VEL_MODIFIER;
    projectile[4][1].delay = 0.08;
    projectile[4][1].owner = &player[1];
    projectile[4][1].enemy = &player[0];
    projectile[4][1].shield = shield[0];
    projectile[4][1].addShield = true;
    projectile[4][1].flyEmitter = emitter[4];
    projectile[4][1].hasFlyEmitter = true;
    projectile[4][1].hitEmitter = emitter[9];
    projectile[4][1].hasHitEmitter = true;
    projectile[4][1].init();
    
    projectile[5][0] = PROJECTILE();
    projectile[5][0].img = load_image( "img/shot6_1.png" );
    projectile[5][0].type = 5;
    projectile[5][0].minDmg = 14;
    projectile[5][0].maxDmg = 16;
    projectile[5][0].damage = 15;
    projectile[5][0].owner = &player[0];
    projectile[5][0].enemy = &player[1];
    projectile[5][0].flyEmitter = emitter[5];
    projectile[5][0].hasFlyEmitter = true;
    projectile[5][0].hitEmitter = emitter[10];
    projectile[5][0].hasHitEmitter = true;
    projectile[5][0].init();
        
    projectile[5][1] = PROJECTILE();
    projectile[5][1].img = load_image( "img/shot6_2.png" );
    projectile[5][1].type = 5;
    projectile[5][1].minDmg = 14;
    projectile[5][1].maxDmg = 16;
    projectile[5][1].damage = 15;
    projectile[5][1].vel = -650;
    projectile[5][1].owner = &player[1];
    projectile[5][1].enemy = &player[0];
    projectile[5][1].flyEmitter = emitter[5];
    projectile[5][1].hasFlyEmitter = true;
    projectile[5][1].hitEmitter = emitter[10];
    projectile[5][1].hasHitEmitter = true;
    projectile[5][1].init();
    
    projectile[6][0] = PROJECTILE();
    projectile[6][0].img = load_image( "img/particle9.png" );
    projectile[6][0].type = 6;
    projectile[6][0].minDmg = 5;
    projectile[6][0].maxDmg = 6;
    projectile[6][0].owner = &player[0];
    projectile[6][0].enemy = &player[1];
    projectile[6][0].flyEmitter = emitter[11];
    projectile[6][0].hasFlyEmitter = true;
    projectile[6][0].hitEmitter = emitter[12];
    projectile[6][0].hasHitEmitter = true;
    projectile[6][0].delay = 0.2;
    projectile[6][0].dmg_over_time = 1;
    projectile[6][0].dmg_over_time_time = 2 * VEL_MODIFIER;
    projectile[6][0].dmg_over_time_freq = 10;
    projectile[6][0].hasImg = false;
    projectile[6][0].init();
    
    projectile[6][1] = PROJECTILE();
    projectile[6][1].img = load_image( "img/particle9.png" );
    projectile[6][1].vel = -650;
    projectile[6][1].type = 6;
    projectile[6][1].minDmg = 5;
    projectile[6][1].maxDmg = 6;
    projectile[6][1].owner = &player[1];
    projectile[6][1].enemy = &player[0];
    projectile[6][1].flyEmitter = emitter[11];
    projectile[6][1].hasFlyEmitter = true;
    projectile[6][1].hitEmitter = emitter[12];
    projectile[6][1].hasHitEmitter = true;
    projectile[6][1].delay = 0.2;
    projectile[6][1].dmg_over_time = 1;
    projectile[6][1].dmg_over_time_time = 2 * VEL_MODIFIER;
    projectile[6][1].dmg_over_time_freq = 10;
    projectile[6][1].hasImg = false;
    projectile[6][1].init();
}


PROJECTILE::PROJECTILE()
{
    x = 0;
    y = 0;
    y_add = 0;
    width = 32;
    height = 32;
    follow = 0;
    vel = 650;
    minDmg = 10;
    maxDmg = 10;
    damage = 10;
    slow = 0;
    slow_time = 0;
    dmg_over_time = 0;
    dmg_over_time_time = 0;
    dmg_over_time_freq = 0;
    delay = 0.05;
    alive = false;
    addShield = false;
    hasFlyEmitter = false;
    hasHitEmitter = false;
    hasImg = true;
}

void PROJECTILE::init()
{
    vel *= VEL_MODIFIER;
    if(vel > 0)
    {
        vel += 150;
    }
    else
    {
        vel -= 150;
    }
}

void PROJECTILE::move( Uint32 deltaTicks )
{
    if(alive && true)
    {
        x += vel * ( deltaTicks / 1000.f );
        
        y += y_add * ( deltaTicks / 1000.f );
        
        if(follow > 0)
        {
            if(y > enemy->y + enemy->height / 2 - height / 2)
            {
                y -= follow * ( deltaTicks / 1000.f );
            }
            else if(y < enemy->y + enemy->height / 2 - height / 2)
            {
                y += follow * ( deltaTicks / 1000.f );
            }
        }
        
        if(hasFlyEmitter)
        {
            flyEmitter.update(x + width/2, y, deltaTicks);
        }

        if( x < 0 - width - SCREEN_WIDTH || x > SCREEN_WIDTH * 2 || y <= 0)
        {
            die();
        }
            else if(GetCollision((int)x, (int)y, width, height, (int)enemy->x, (int)enemy->y, enemy->width, enemy->height))		    
        {
            hit();
        }
    }
}

void PROJECTILE::show()
{
    //SDL_Surface tempSurface = *img;
    //SDL_FreeSurface(tempSurface);
    Uint32 tempPx[width][height];
    if(hasFlyEmitter)
    {
        flyEmitter.show();
    }

	if(hasImg)
	{
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            //printf("s: %8x\n", get_pixel32(screen, (int)x+i, (int)y+j));
            //printf("i: %8x\n\n", get_pixel32(img, (int)i, (int)j));
            /*printf("%8x\n", BlendPixels(
                            get_pixel32(screen, (int)x+i, (int)y+j),
                            get_pixel32(img, (int)i, (int)j),
                            -1));*/
            tempPx[i][j] = get_pixel32(img, (int)i, (int)j);
            put_pixel32(img,
                        (int)i,
                        (int)j,
                        BlendPixels(
                            get_pixel32(screen, (int)x+i, (int)y+j),
                            get_pixel32(img, (int)i, (int)j),
                            3)
                        );
            
        }
    }
    
    
    /*Uint32 blendPx = BlendPixels(
                        0x00112233,
                        0xAABBCCDD,
                        1);
    Uint8 *colors = (Uint8*)&blendPx;
                        
    Uint8 alpha = colors[0];
    Uint8 red = colors[1];
    Uint8 green = colors[2];
    Uint8 blue = colors[3];
    printf("r0: %u\n", alpha);
    printf("r1: %u\n", red);
    printf("r2: %u\n", green);
    printf("r3: %u\n", blue);*/
        
    apply_surface( (int)x, (int)y, img, screen );
    
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            put_pixel32(img,
                        (int)i,
                        (int)j,
                        tempPx[i][j]
                        );            
        }
    }
    //*img = tempSurface;
    //SDL_FreeSurface(img);
    //img = tempSurface;
    //img = &tempSurface;
	}
}

void PROJECTILE::die()
{
    alive = false;
}

void PROJECTILE::hit()
{
    if(gamemode != 3)
    {
    if(hasHitEmitter)
    {
        hitEmitter.x = enemy->x + enemy->width / 2;
        hitEmitter.y = enemy->y + enemy->height / 2;
        list_hit_emitter.push_back(hitEmitter);
    }
    enemy->lives -= (int)((minDmg + rand() % (maxDmg - minDmg)) * enemy->shield.modifier);
    if(enemy->shield.reflect)
    {
        enemy->shoot(type, true);
    }
    if(slow != 0)
    {
        enemy->vel_mod = slow;
        enemy->vel_mod_time = slow_time;
    }
    if(dmg_over_time != 0)
    {
        enemy->dmg_over_time = dmg_over_time;
        enemy->dmg_over_time_time = dmg_over_time_time;
        enemy->dmg_over_time_freq = dmg_over_time_freq;
    }
    if(addShield)
    {
        if(enemy->shield.modifier == 1)
        {
            enemy->shield = shield;
        }
    }
    die();
    }
}

void PROJECTILE::hit(SP_ENEMY *enemy2)
{
    if(hasHitEmitter)
    {
        hitEmitter.x = enemy2->x + enemy2->width / 2;
        hitEmitter.y = enemy2->y + enemy2->height / 2;
        list_hit_emitter.push_back(hitEmitter);
    }
    enemy2->lives -= (int)(minDmg + rand() % (maxDmg - minDmg));
    die();
}
