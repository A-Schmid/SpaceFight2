SP_ENEMY::SP_ENEMY(int type)
{
    switch(type)
    {
        case 1:
            img = load_image("img/shot1_2.png");
            lives = 1;
            vel = 300;
            dmg = 10;
            score = 10;
            break;
        case 2:
            img = load_image("img/shot2_1.png");
            lives = 1;
            vel = 350;
            dmg = 5;
            score = 15;
            break;
        case 3:
            img = load_image("img/shot3_2.png");
            lives = 15;
            vel = 250;
            dmg = 15;
            score = 20;
            break;
        case 4:
            img = load_image("img/shot4_2.png");
            lives = 20;
            vel = 280;
            dmg = 12;
            score = 25;
            break;
        case 5:
            img = load_image("img/shot5_2.png");
            lives = 20;
            vel = 320;
            dmg = 18;
            score = 30;
            break;
        case 6:
            img = load_image("img/shot6_2.png");
            lives = 25;
            vel = 300;
            dmg = 25;
            score = 35;
            break;
    }
    
    width = img->w;
    height = img->h;
    x = SCREEN_WIDTH + 100;
    y = rand() % (SCREEN_HEIGHT - height);
}

void SP_ENEMY::update( Uint32 deltaTicks )
{
    if(lives >= -100)
    {
        x -= vel * (deltaTicks / 1000.f);
    }
    if(x < -100)
    {
        lives = 0;
        SP_score -= score;
    }
    list<PROJECTILE>::iterator it;
    it = list_projectile.begin();
    while(it != list_projectile.end())
    {
        if(GetCollision((int)x, (int)y, width, height, (int)it->x, (int)it->y, it->width, it->height))
        {
            it->hit(this);
            SP_score += score;
        }
        ++it;
    }
    if(GetCollision((int)x, (int)y, width, height, (int)player[0].x, (int)player[0].y, player[0].width, player[0].height))
    {
        hit();
    }
}

void SP_ENEMY::show()
{
    apply_surface((int)x, (int)y, img, screen);
}

void SP_ENEMY::hit()
{
    player[0].lives -= dmg;
    lives = 0;
}
