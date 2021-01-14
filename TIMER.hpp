


TIMER::TIMER()
{
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void TIMER::start()
{
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
}

void TIMER::stop()
{
    started = false;
    paused = false;
}

void TIMER::pause()
{
    if( ( started == true ) && ( paused == false ) )
    {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void TIMER::unpause()
{
    if( paused == true )
    {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

int TIMER::get_ticks()
{
    if( started == true )
    {
        if( paused == true )
        {
            return pausedTicks;
        }
        else
        {
            return SDL_GetTicks() - startTicks;
        }
    }
    return 0;
}

bool TIMER::is_started()
{
    return started;
}

bool TIMER::is_paused()
{
    return paused;
}
