/*
 * SoundManager.cpp
 *
 * Created by Daniel Scheibel, Charlie Whitney, Adrià Navarro on 12/13/11.
 *
 * Copyright (c) 2014, Red Paper Heart, All rights reserved.
 * This code is intended for use with the Cinder C++ library: http://libcinder.org
 *
 * To contact Red Paper Heart, email hello@redpaperheart.com or tweet @redpaperhearts
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in
 * the documentation and/or other materials provided with the
 * distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "cinder/Rand.h"
#include "cinder/Log.h"
#include "rph/SoundManager.h"

namespace rph {
    
    // Global static pointer used to ensure a single instance of the class.
    SoundManager* SoundManager::mInstance = NULL;

    SoundManager* SoundManager::getInstance()
    {
        if (!mInstance) // Only allow one instance of class to be generated.
            mInstance = new SoundManager();
        return mInstance;
    }

    SoundPlayerRef SoundManager::loadSound( std::string path )
    {
        return loadSound( path, path );
    }
        
    SoundPlayerRef SoundManager::loadSound( std::string key, std::string path )
    {
        try {
            SoundPlayerRef sound = SoundPlayer::create(ci::app::loadAsset(path)); // use next line instead for resources
            //SoundPlayerRef sound = SoundPlayer::create(ci::app::loadResource(path));
            
            if (getNumSounds(key) == 0) mSounds[key] = { sound };
            else                        mSounds[key].push_back(sound);

            return sound;
        }
        catch( std::exception &exc ) {
            CI_LOG_EXCEPTION( "Failed to load sound with key: " << key << ", path: " << path, exc );
            return NULL;
        }
    }
    
    SoundPlayerRef SoundManager::getSound( std::string key )
    {
        int numSounds = getNumSounds(key);

        if (numSounds == 0) {
            return nullptr;
        }
        else if (numSounds == 1) {
            return mSounds.at(key).back();
        }
        else {
            return mSounds.at(key).at(randInt(numSounds));
        }
    }
    
    int SoundManager::getNumSounds(std::string key)
    {
        if (mSounds.count(key) == 0) return 0;
        else return mSounds.at(key).size();
    }

}