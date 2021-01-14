void InitMenuItems()
{
    menuitem[0]             = MENU_ITEM();
    menuitem[0].x           = (SCREEN_WIDTH / 2) - (menuitem[0].width / 2);
    menuitem[0].y           = 250 + 80 * 0;
    menuitem[0].label       = "Neues Spiel";
    menuitem[0].img         = load_image("img/menuitem1.png");
    menuitem[0].img_hover   = load_image("img/menuitem1_hover.png");
    menuitem[0].has_hover   = true;
    menuitem[0].has_click   = true;
    menuitem[0].has_text    = true;
    menuitem[0].init();
    
    menuitem[1]             = MENU_ITEM();
    menuitem[1].x           = (SCREEN_WIDTH / 2) - (menuitem[1].width / 2);
    menuitem[1].y           = 250 + 80 * 1;
    menuitem[1].label       = "Server Hosten";
    menuitem[1].img         = load_image("img/menuitem1.png");
    menuitem[1].img_hover   = load_image("img/menuitem1_hover.png");
    menuitem[1].has_hover   = true;
    menuitem[1].has_click   = true;
    menuitem[1].has_text    = true;
    menuitem[1].init();
    
    menuitem[2]             = MENU_ITEM();
    menuitem[2].x           = (SCREEN_WIDTH / 2) - (menuitem[2].width / 2);
    menuitem[2].y           = 250 + 80 * 2;
    menuitem[2].label       = "Server Suchen";
    menuitem[2].img         = load_image("img/menuitem1.png");
    menuitem[2].img_hover   = load_image("img/menuitem1_hover.png");
    menuitem[2].has_hover   = true;
    menuitem[2].has_click   = true;
    menuitem[2].has_text    = true;
    menuitem[2].init();
    
    menuitem[3]             = MENU_ITEM();
    menuitem[3].x           = (SCREEN_WIDTH / 2) - (menuitem[3].width / 2);
    menuitem[3].y           = 250 + 80 * 3;
    menuitem[3].label       = "Einzelspieler";
    menuitem[3].img         = load_image("img/menuitem1.png");
    menuitem[3].img_hover   = load_image("img/menuitem1_hover.png");
    menuitem[3].has_hover   = true;
    menuitem[3].has_click   = true;
    menuitem[3].has_text    = true;
    menuitem[3].init();
    
    menuitem[4]             = MENU_ITEM();
    menuitem[4].x           = (SCREEN_WIDTH / 2) - (menuitem[4].width / 2);
    menuitem[4].y           = 250 + 80 * 4;
    menuitem[4].label       = "Fullscreen";
    menuitem[4].img         = load_image("img/menuitem1.png");
    menuitem[4].img_hover   = load_image("img/menuitem1_hover.png");
    menuitem[4].has_hover   = true;
    menuitem[4].has_click   = true;
    menuitem[4].has_text    = true;
    menuitem[4].init();
    
    menuitem[5]             = MENU_ITEM();
    menuitem[5].x           = (SCREEN_WIDTH / 2) - (menuitem[5].width / 2);
    menuitem[5].y           = 250 + 80 * 5;
    menuitem[5].label       = "Verlassen";
    menuitem[5].img         = load_image("img/menuitem1.png");
    menuitem[5].img_hover   = load_image("img/menuitem1_hover.png");
    menuitem[5].has_hover   = true;
    menuitem[5].has_click   = true;
    menuitem[5].has_text    = true;
    menuitem[5].init();
    
    toggle_ammo             = MENU_ITEM();
    toggle_ammo.x           = (SCREEN_WIDTH / 2) - (menuitem[5].width / 2) + 300;
    toggle_ammo.y           = 250 + 80 * 5;
    toggle_ammo.img_add_x	= 250;
    toggle_ammo.img_add_y	= 14;
    toggle_ammo.label       = "Munition";
    toggle_ammo.img         = load_image("img/menuitem4.png");
    toggle_ammo.img_hover   = load_image("img/menuitem4_checked.png");
    toggle_ammo.img_checked = load_image("img/menuitem5.png");
    toggle_ammo.has_hover   = false;
    toggle_ammo.has_click   = true;
    toggle_ammo.has_text    = true;
    toggle_ammo.has_check   = true;
    toggle_ammo.checked	    = true;
    toggle_ammo.init();
    
    
    change_color[0][0] = MENU_ITEM();
    change_color[0][0].x = player[0].x + 64 + 16;
    change_color[0][0].y = (SCREEN_HEIGHT / 2) - 16;
    change_color[0][0].width = 32;
    change_color[0][0].height = 32;
    change_color[0][0].img = load_image("img/menuitem2.png");
    change_color[0][0].img_hover = load_image("img/menuitem2_hover.png");
    change_color[0][0].has_hover = true;
    change_color[0][0].has_click = true;
    change_color[0][0].init();
    
    change_color[0][1] = MENU_ITEM();
    change_color[0][1].x = player[0].x - 32 - 16;
    change_color[0][1].y = (SCREEN_HEIGHT / 2) - 16;
    change_color[0][1].width = 32;
    change_color[0][1].height = 32;
    change_color[0][1].img = load_image("img/menuitem3.png");
    change_color[0][1].img_hover = load_image("img/menuitem3_hover.png");
    change_color[0][1].has_hover = true;
    change_color[0][1].has_click = true;
    change_color[0][1].init();
    
    change_color[1][0] = MENU_ITEM();
    change_color[1][0].x = player[1].x + 64 + 16;
    change_color[1][0].y = (SCREEN_HEIGHT / 2) - 16;
    change_color[1][0].width = 32;
    change_color[1][0].height = 32;
    change_color[1][0].img = load_image("img/menuitem2.png");
    change_color[1][0].img_hover = load_image("img/menuitem2_hover.png");
    change_color[1][0].has_hover = true;
    change_color[1][0].has_click = true;
    change_color[1][0].init();
    
    change_color[1][1] = MENU_ITEM();
    change_color[1][1].x = player[1].x - 32 - 16;
    change_color[1][1].y = (SCREEN_HEIGHT / 2) - 16;
    change_color[1][1].width = 32;
    change_color[1][1].height = 32;
    change_color[1][1].img = load_image("img/menuitem3.png");
    change_color[1][1].img_hover = load_image("img/menuitem3_hover.png");
    change_color[1][1].has_hover = true;
    change_color[1][1].has_click = true;
    change_color[1][1].init();
    
    for(int i = 0; i < 17; i++)
    {
        switch_buff[i]              = MENU_ITEM();
        switch_buff[i].x            = (SCREEN_WIDTH / 2) - ((16 * 40) / 2) + i * 40;
        switch_buff[i].y            = 720;
        switch_buff[i].width        = 32;
        switch_buff[i].height       = 32;
        switch_buff[i].img          = load_image("img/menuitem4.png");
        switch_buff[i].img_checked  = load_image("img/menuitem4_checked.png");
        switch_buff[i].img_2        = img_buff[i];
        switch_buff[i].has_click    = true;
        switch_buff[i].has_check    = true;
        switch_buff[i].has_img_2    = true;
        switch_buff[i].checked      = true;
        switch_buff[i].init();
    }
}

MENU_ITEM::MENU_ITEM()
{
    x           = 0;
    y           = 0;
    img_add_x	= 0;
    img_add_y	= 0;
    width       = 320;
    height      = 64;
    label       = " ";
    has_img_2   = false;
    has_text    = false;
    has_hover   = false;
    hovered     = false;
    has_check   = false;
    checked     = false;
    has_click   = false;
    clicked     = false;
    clickDelay  = false;
}

void MENU_ITEM::init()
{
    text = TTF_RenderText_Solid( fontMenu, label.c_str(), textColor );
    text_hover = TTF_RenderText_Solid( fontMenu, label.c_str(), textColor );
}

void MENU_ITEM::update()
{
    int mouse_state;
    int mouse_x;
    int mouse_y;
    Uint8 MouseState = SDL_GetMouseState(&mouse_x, &mouse_y);
    
    if((mouse_x > x && mouse_x < x + width) && (mouse_y > y && mouse_y < y + height))
    {
        hovered = true;
        if(MouseState & SDL_BUTTON_LMASK)
        {
            if(clickDelay == false)
            {
                clicked = true;
                if(checked == false)
                {
                    checked = true;
                }
                else
                {
                    checked = false;
                }
                clickDelay = true;
            }
            else
            {
                clicked = false;
            }
        }
        else
        {
            clickDelay = false;
            clicked = false;
        }
    }
    else
    {
        hovered = false;
        clicked = false;
    }
}

void MENU_ITEM::show()
{
    if(hovered && has_hover)
    {
        if(checked && has_check)
        {
            apply_surface( (int)(x + img_add_x), (int)(y + img_add_y), img_checked_hover, screen, NULL );
        }
        else
        {
            apply_surface( (int)(x + img_add_x), (int)(y + img_add_y), img_hover, screen, NULL );
        }
    }
    else
    {
        if(checked && has_check)
        {
            apply_surface( (int)(x + img_add_x), (int)(y + img_add_y), img_checked, screen, NULL );
        }
        else
        {
            apply_surface( (int)(x + img_add_x), (int)(y + img_add_y), img, screen, NULL );
        }
    }
    if(has_img_2)
    {
        apply_surface( (int)((x + (width / 2) - (img_2->w / 2)) + img_add_x), (int)((y + (height / 2) - (img_2->h / 2)) + img_add_y), img_2, screen, NULL );
    }
    if(has_text)
    {
        apply_surface( (int)(x + (width / 2) - (text->w / 2)), (int)(y + (height / 2) - (text->h / 2)), text, screen, NULL );
    }
}
