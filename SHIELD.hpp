void InitShields()
{
    shield[0] = SHIELD();
    shield[0].img[0] = load_image( "img/shieldIce.png" );
    shield[0].img[1] = load_image( "img/shieldIce.png" );
    shield[0].time = 4 * 0.12 * VEL_MODIFIER;
    shield[0].stun = true;
    
    shield[1] = SHIELD();
    shield[1].img[0] = load_image( "img/shield_new2_1.png" );
    shield[1].img[1] = load_image( "img/shield_new2_1.png" );
    shield[1].time = 10 * VEL_MODIFIER;
    shield[1].modifier = 0.5;
    
    shield[2] = SHIELD();
    shield[2].img[0] = load_image( "img/shield_new2_2.png" );
    shield[2].img[1] = load_image( "img/shield_new2_2.png" );
    shield[2].time = 5 / VEL_MODIFIER;
    shield[2].modifier = 0.5;
    shield[2].reflect = true;
    
    shield[3] = SHIELD();
    shield[3].img[0] = load_image( "img/shield_new2_3.png" );
    shield[3].img[1] = load_image( "img/shield_new2_3.png" );
    shield[3].time = 3.5 / VEL_MODIFIER;
    shield[3].modifier = 0;
    
    shield[3] = SHIELD();
    shield[3].img[0] = load_image( "img/shield_new2_4.png" );
    shield[3].img[1] = load_image( "img/shield_new2_4.png" );
    shield[3].time = 2.5 / VEL_MODIFIER;
    shield[3].modifier = -1;
}

SHIELD::SHIELD()
{
    x = -64;
    y = 0;
    width = 64;
    height = 64;
    modifier = 1;
    time = 0;
    stun = false;
    reflect = false;
}

void SHIELD::update(float X, float Y, Uint32 deltaTicks)
{
    x = X;
    y = Y;
    if(time > 0)
    {
        time -= deltaTicks / 1000.f;
        if(time <= 0)
        {
            time = 0;
            modifier = 1;
            stun = false;
            reflect = false;
        }
    }
}

void SHIELD::show(int pl)
{
    if(time > 0)
    {
        apply_surface( (int)x, (int)y, img[pl], screen );
    }
}
