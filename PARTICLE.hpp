PARTICLE::PARTICLE(SDL_Surface *IMG, float X, float Y, float DIRECTION, float VEL, float LIVETIME, float TURBCHANCE, float TURBSTRENGTH, Uint32 COLOR[2], float FADEOUT)
{
    img = IMG;
    x = X;
    y = Y;
    dir = DIRECTION;
    vel = VEL * VEL_MODIFIER;
    width = img->w;
    height = img->h;
    maxLivetime = LIVETIME;
    livetime = LIVETIME;
    TurbulenceChance = TURBCHANCE;
    TurbulenceStrength = TURBSTRENGTH;
    color[0] = COLOR[0];
    color[1] = COLOR[1];
    FadeOutStartPerc = FADEOUT;
}

void PARTICLE::update(Uint32 deltaTicks)
{
    if(livetime > 0)
    {
        if((rand() % 100) < TurbulenceChance)
        {
            dir += (-TurbulenceStrength + (rand() % (int)(1 + 2 * TurbulenceStrength)));
        }
        x += (vel * cos(dir * (3.141 / 180))) * ( deltaTicks / 1000.f );
        y += (vel * sin(dir * (3.141 / 180))) * ( deltaTicks / 1000.f );
        livetime -= deltaTicks;
    }
}

void PARTICLE::show()
{
	if(x < 1024 && x > 0 && y < 768 && y > 0)
	{
    if(livetime > 0)
    {
        Uint32 tempPx[width][height];
        Uint32 tempPx2;
        Uint32 tempPx3 = BlendPixels(	color[1],
                        				color[0],
                        				1,
										1 - (livetime / maxLivetime));
		//(color[0] * (maxLivetime / (maxLivetime - livetime))) + (color[1] * (1 - (maxLivetime / (maxLivetime - livetime))));
        
        for(int i = 0; i < width; i++)
        {
            for(int j = 0; j < height; j++)
            {
                tempPx[i][j] = get_pixel32(img, (int)i, (int)j);
                tempPx2 =   BlendPixels(get_pixel32(screen, ((int)x - width/2)+i, (int)y+j),
                                		get_pixel32(img, (int)i, (int)j),
                                		3);
                tempPx2 =   BlendPixels(tempPx2,
                                		tempPx3,
                                		4
										);
										
				tempPx2 = FadePixel(tempPx2, livetime, maxLivetime, FadeOutStartPerc);
                //tempPx2);
                put_pixel32(img,
                            (int)i,
                            (int)j,
                            tempPx2
                            );
            }
        }
        
        //printf("%X\n", FadePixel(0xffffffff, 1, 100, 0.5));

        apply_surface( (int)x - width/2, (int)y, img, screen );
        
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
    }
	}
}
