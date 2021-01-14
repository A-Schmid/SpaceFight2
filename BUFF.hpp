void InitBuffs()
{
    for(int i = 0; i < 17; i++)
    {
        buff_allowed[i] = true;
    }
    
    img_buff[0] = load_image( "img/buff_wpn1.png" );
    img_buff[1] = load_image( "img/buff_wpn2.png" );
    img_buff[2] = load_image( "img/buff_wpn3.png" );
    img_buff[3] = load_image( "img/buff_wpn4.png" );
    img_buff[4] = load_image( "img/buff_wpn5.png" );
    img_buff[5] = load_image( "img/buff_wpn6.png" );
    img_buff[12] = load_image( "img/buff_shield1.png" );
    img_buff[7] = load_image( "img/buff_shield2.png" );
    img_buff[8] = load_image( "img/buff_heal1.png" );
    img_buff[9] = load_image( "img/buff_heal2.png" );
    img_buff[10] = load_image( "img/buff_speed.png" );
    img_buff[11] = load_image( "img/buff_dmg.png" );
    
    
    img_buff[6] = load_image( "img/buff_wpn7.png" );
    
    img_buff[13] = load_image( "img/buff_shield3.png" );
    
    img_buff[14] = load_image( "img/buff_ammo.png" );
    img_buff[15] = load_image( "img/buff_triple.png" );
    img_buff[16] = load_image( "img/buff_shield4.png" );
}


BUFF::BUFF()
{
    
    type = 0;
    type = rand() % 17;
    while(buff_allowed[type] == false)
    {
        type = rand() % 17;
    }
    x = 64 + rand() % (1024 - 128);
    y = 64 + rand() % (768 - 128);
    alive = true;
    width = 16;
    height = 16;
    img = img_buff[type];
}

BUFF::BUFF(int X, int Y, int TYPE)
{
    type = TYPE;
    x = X;
    y = Y;
    alive = true;
    width = 16;
    height = 16;
    img = img_buff[type];
}

void BUFF::update()
{
    for(int i = 0; i < 2; i++)
    {
        if(GetCollision(x, y, width, height, (int)player[i].x, (int)player[i].y, player[i].width, player[i].height) && alive)
        {
            use(player[i]);
        }
    }
}

void BUFF::show()
{
    if(alive)
    {
        apply_surface( x, y, img, screen );
    }
}

void BUFF::use(PLAYER pl)
{
    alive = false;
    switch(type)
    {
        case 0: player[pl.id].setWeapon(0); break;
        case 1: player[pl.id].setWeapon(1); break;
        case 2: player[pl.id].setWeapon(2); break;
        case 3: player[pl.id].setWeapon(3); break;
        case 4: player[pl.id].setWeapon(4); break;
        case 5: player[pl.id].setWeapon(5); break;
        case 12: player[pl.id].shield = shield[1]; break;
        case 7: player[pl.id].shield = shield[2]; break;
        case 8:
            if(player[pl.id].lives < (maxLives - 30))
            {
                player[pl.id].lives += 30;
            }
            else
            {
                player[pl.id].lives = maxLives;
            }
            break;
        case 9: 
            if(player[pl.id].lives < (maxLives - 80))
            {
                player[pl.id].lives += 80;
            }
            else
            {
                player[pl.id].lives = maxLives;
            }
            break;
        case 10:
            player[pl.id].vel_mod = 300;
            player[pl.id].vel_mod_time = 5.0;
            break;
        case 11:
            player[pl.id].dmg_mod = 1.5;
            player[pl.id].dmg_mod_time = 2.5;
            break;
        case 6: player[pl.id].setWeapon(6); break;
        case 13: player[pl.id].shield = shield[3]; break;
        case 14: player[pl.id].shots += 10; break;
        case 15:
			player[pl.id].numshot = 3;
            player[pl.id].numshot_time = 5;
            break;
        case 16: player[pl.id].shield = shield[4]; break;
    }
}
