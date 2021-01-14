void InitPlayers()
{
    player[0] = PLAYER();
    player[0].img = load_image( "img/raumschiff_new_combo_sprite.png" );
    player[0].x = 200;
    player[0].y = SCREEN_HEIGHT / 2 - player[0].height / 2;
    player[0].weapon = 0;
    player[0].id = 0;
    player[0].flyEmitter = emitter[6];
    player[0].color = 0;

    player[1] = PLAYER();
    player[1].img = load_image( "img/raumschiff_new_combo_sprite.png" );
    player[1].x = SCREEN_WIDTH - 200 - player[1].width;
    player[1].y = SCREEN_HEIGHT / 2 - player[1].height / 2;
    player[1].weapon = 0;
    player[1].id = 1;
    player[1].flyEmitter = emitter[6];
    player[1].color = 1;
}


PLAYER::PLAYER()
{
    x = 0;
    y = 0;
    imgframe = 4;
    imgframetime = 0;
    xVel = 0;
    yVel = 0;
    vel = (int)(500 * VEL_MODIFIER);
    vel_mod = 0;
    vel_mod_time = 0;  
    dmg_mod = 1;
    dmg_mod_time = 0;
    dmg_over_time = 0;
    dmg_over_time_time = 0;
    dmg_over_time_freq = 0;
    dmg_over_time_counter = 0;
    width = 64;
    height = 64;
    lives = maxLives;
    delay = 0;
    shootDown = false;
    color = 0;
    shots = 0;
    numshot = 1;
    numshot_time = 0;
}

void PLAYER::update( Uint32 deltaTicks )
{    
    delay -= 0.25 * (deltaTicks / 1000.f);
    
    if(numshot_time > 0)
    {
        numshot_time -= deltaTicks / 1000.f;
        if(numshot_time <= 0)
        {
            numshot_time = 0;
            numshot = 1;
        }
    }
    
    if(vel_mod_time > 0)
    {
        vel_mod_time -= deltaTicks / 1000.f;
        if(vel_mod_time <= 0)
        {
            vel_mod_time = 0;
            vel_mod = 0;
        }
    }
    
    if(dmg_mod_time > 0)
    {
        dmg_mod_time -= deltaTicks / 1000.f;
        if(dmg_mod_time <= 0)
        {
            dmg_mod_time = 0;
            dmg_mod = 1;
        }
    }
    
    if(dmg_over_time_time > 0)
    {
        dmg_over_time_time -= deltaTicks / 1000.f;
        dmg_over_time_counter -= deltaTicks / dmg_over_time_freq;
        if(dmg_over_time_counter < 0)
        {
            lives -= dmg_over_time;
            dmg_over_time_counter = dmg_over_time_freq;
        }
    }
    if(dmg_over_time_time <= 0)
    {
        dmg_over_time_time = 0;
        dmg_over_time_counter = 0;
        dmg_over_time_freq = 0;
        dmg_over_time = 0;
    }
    
    if(shield.stun == false)
    {
        if(xVel < 0)
        {
            x -= (vel + vel_mod) * ( deltaTicks / 1000.f );
        }
        else if(xVel > 0)
        {
            x += (vel + vel_mod) * ( deltaTicks / 1000.f );
        }
        
        if(yVel < 0)
        {
            y -= (vel + vel_mod) * ( deltaTicks / 1000.f );
            if(imgframe < 8)
            {
                imgframetime += deltaTicks;
                if(imgframetime > 4 / VEL_MODIFIER)
                {
                    imgframe++;
                    imgframetime = 0;
                }
            }
        }
        else if(yVel > 0)
        {
            y += (vel + vel_mod) * ( deltaTicks / 1000.f );
            if(imgframe > 0)
            {
                imgframetime -= deltaTicks;
                if(imgframetime < 4 / VEL_MODIFIER)
                {
                    imgframe--;
                    imgframetime = 16;
                }
            }
        }
        else
        {
            if(imgframe < 4)
            {
                imgframetime += deltaTicks;
                if(imgframetime > 4 / VEL_MODIFIER)
                {
                    imgframe++;
                    imgframetime = 0;
                }
            }
            if(imgframe > 4)
            {
                imgframetime -= deltaTicks;
                if(imgframetime < 4 / VEL_MODIFIER)
                {
                    imgframe--;
                    imgframetime = 16;
                }
            }
        }
    }
    
    if( x < 0 )
    {
        x = 0;
    }
    else if( x + width > SCREEN_WIDTH )
    {
        x = SCREEN_WIDTH - width;
    }   
    if( y < 0 )
    {
        y = 0;
    }
    else if( y + height > SCREEN_HEIGHT )
    {
        y = SCREEN_HEIGHT - height;
    }
    /*if(x < 256 || x + width > SCREEN_WIDTH - 256)
    {
        if(y > SCREEN_HEIGHT - 60 - height)
        {
            y = SCREEN_HEIGHT - 60 - height;
        }
    }*/
    
    flyEmitter.update(x + (id * width), y + 24, deltaTicks);
    
    shield.update( x, y, deltaTicks );
}

void PLAYER::show()
{
    SDL_Rect clip;
    clip.x = 0 + imgframe * 64 + (id * 576);
    clip.y = color * 64;
    clip.w = 64;
    clip.h = 64;
    
    flyEmitter.show();    
    apply_surface( (int)x, (int)y, img, screen, &clip );
    shield.show(id);
}

void PLAYER::shoot(int wpn, bool instant)
{
    if(instant == true)
    {
        PROJECTILE p;
        if(wpn == -1)
        {
            p = projectile[weapon][id];
        }
        else
        {
            p = projectile[wpn][id];
        }
        p.x = x + width - id * (width + p.width);
        p.y = y + 0.5 * height - 0.5 * p.height;
        p.damage = (int)(p.damage * dmg_mod);
        p.alive = true;
        list_projectile.push_back(p);
    }
    else
    {
        if(delay <= 0 && shield.stun == false)
        {
			if(shots > 0)
			{
			for(int i = numshot - 1; i >= 0; i--)
			{
            PROJECTILE p;
            if(wpn == -1)
            {
                p = projectile[weapon][id];
            }
            else
            {
                p = projectile[wpn][id];
            }
            p.x = x + width - id * (width + p.width);
            p.y = y + 0.5 * height - 0.5 * p.height;
            p.damage = (int)(p.damage * dmg_mod);
            p.alive = true;
            p.y_add = 50 * (((numshot - 1) / 2) - i);
            delay = p.delay;
            shootDown = true;
            list_projectile.push_back(p);
			}
            if(!no_ammo)
			{
				shots--;
			}
			}
        }
    }
}

void PLAYER::setWeapon(int num)
{
	if(num == weapon)
	{
		shots += wpnShots[num];
	}
	else
	{
		weapon = num;
		shots = wpnShots[num];
	}
}
