void InitEmitters()
{
    emitter[0]  = readEmitterFromFile("emitters/shot1.emi");        // shot 1 fly emitter
    emitter[1]  = readEmitterFromFile("emitters/shot2.emi");        // shot 2 fly emitter
    emitter[2]  = readEmitterFromFile("emitters/shot3.emi");        // shot 3 fly emitter
    emitter[3]  = readEmitterFromFile("emitters/shot4.emi");        // shot 4 fly emitter
    emitter[4]  = readEmitterFromFile("emitters/shot5.emi");        // shot 5 fly emitter
    emitter[5]  = readEmitterFromFile("emitters/shot6.emi");        // shot 6 fly emitter
    emitter[6]  = readEmitterFromFile("emitters/playerEmitter.emi");// player fly emitter
    emitter[7]  = readEmitterFromFile("emitters/hit1.emi");         // shot 1 hit emitter
    emitter[8]  = readEmitterFromFile("emitters/hit3.emi");         // shot 3 hit emitter
    emitter[9]  = readEmitterFromFile("emitters/hit5.emi");         // shot 5 hit emitter
    emitter[10] = readEmitterFromFile("emitters/hit6.emi");         // shot 6 hit emitter
    emitter[11] = readEmitterFromFile("emitters/shot7.emi");        // shot 7 fly emitter
    emitter[12] = readEmitterFromFile("emitters/hit7.emi");         // shot 7 hit emitter
    

    /*emitter[7].livetime = 20000;
    emitter[7].spawnAtOnce = 1000;
    emitter[7].particleCount = -1;
    emitter[7].maxParticleCount = 10000;
    emitter[7].ParticleMinVel = 0;
    emitter[7].ParticleMaxVel = 301;
    emitter[7].ParticleMinDir = 0;
    emitter[7].ParticleMaxDir = 360;
    emitter[7].ParticleMinLivetime = 100;
    emitter[7].ParticleMaxLivetime = 401;
    emitter[7].ParticleTurbulenceChance = 100;
    emitter[7].ParticleTurbulenceStrength = 10;
    emitter[7].delay = 100000;*/
    /*emitter[6].ParticleMinLivetime = 300;
    emitter[6].ParticleMaxLivetime = 301;
    emitter[6].delay = 1000;
    emitter[6].spawnAtOnce = 5;*/
    //emitter[2].spawnAtOnce = 3;
    //emitter[2].color[0] = 0x00ffff88;
    //emitter[2].color[1] = 0x00ff5500;
    //emitter[2].ParticleMinDir = -25;
    //emitter[2].ParticleMaxDir = 25;
}

EMITTER::EMITTER()
{
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    addY = 0;
    livetime = 0;
    permanent = false;
    spawnAtOnce = 1;
    particleCount = -1;
    maxParticleCount = 0;
    ParticleMinVel = 0;
    ParticleMaxVel = 0;
    ParticleMinDir = 0;
    ParticleMaxDir = 0;
    ParticleMinLivetime = 1000;
    ParticleMaxLivetime = 1001;
    ParticleTurbulenceChance = 0;
    ParticleTurbulenceStrength = 0;
    delay = 0;
    nextSpawn = delay;
    color[0] = 0x00ffffff;
    color[1] = 0x00ffffff;
    ParticleFadeOutStartPerc = 1.0;
}

void EMITTER::update(float X, float Y, Uint32 deltaTicks, bool move)
{
    if(livetime > 0)
    {
        if(move)
        {
            x = X;
            y = Y + addY;
        }
    
        nextSpawn -= deltaTicks;
        if(nextSpawn <= 0 && particleCount < maxParticleCount)
        {
            for(int i = 0; i < spawnAtOnce; i++)
            {
                particleCount++;
                particle.push_back(PARTICLE(img,
                                            x + (-width + rand() % (int)(1 + 2 * width)),
                                            y + (-height + rand() % (int)(1 + 2 * height)),
                                            ParticleMinDir + rand() % (int)(ParticleMaxDir - ParticleMinDir),
                                            ParticleMinVel + rand() % (int)(ParticleMaxVel - ParticleMinVel),
                                            ParticleMinLivetime + rand() % (int)(ParticleMaxLivetime - ParticleMinLivetime),
                                            ParticleTurbulenceChance,
                                            ParticleTurbulenceStrength,
                                            color,
                                            ParticleFadeOutStartPerc
                                            ));
            }
            nextSpawn = delay;
        }
        it = particle.begin();
        while(it != particle.end())
        {
            if(it->livetime > 0)
            {
                it->update(deltaTicks);
                ++it;
            }
            else
            {
                it = particle.erase(it);
            }
        }
        if(permanent == false)
        {
            livetime -= deltaTicks;
        }
    }
}

void EMITTER::show()
{
    if(livetime > 0)
    {
        it = particle.begin();
        while(it != particle.end())
        {
            if(it->livetime > 0)
            {
                it->show();
                ++it;
            }
            else
            {
                particleCount--;
                it = particle.erase(it);
            }
        }
    }
    else
    {
        it = particle.begin();
        while(it != particle.end())
        {
            it = particle.erase(it);
        }
    }
}
