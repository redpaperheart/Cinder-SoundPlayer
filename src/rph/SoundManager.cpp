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
            mSounds[key] = SoundPlayer::create(cinder::app::loadAsset(path)); // use next line instead for resources
            // mSounds[key] = SoundPlayer::create(ci::app::loadResource(path));
            return mSounds[key];
        }
        catch(...) {
            cinder::app::console() << "SoundManager::loadSound FAILED: " << path << std::endl;
            return NULL;
        }
    }
}