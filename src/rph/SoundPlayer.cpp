/*
 * SoundPlayer.cpp
 *
 * Created by Adria Navarro on 9/8/14.
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

#include "SoundPlayer.h"
#include "cinder/audio/Context.h"
#include "cinder/audio/Source.h"

namespace rph {
    
    SoundPlayerRef SoundPlayer::create(const DataSourceRef &source, size_t maxFramesForBufferPlayback)
    {
        SoundPlayerRef ref(new SoundPlayer(source, maxFramesForBufferPlayback));
        return ref;
    }

    SoundPlayer::SoundPlayer(const DataSourceRef &source, size_t maxFramesForBufferPlayback)
    {
        SourceFileRef sourceFile = audio::load(source);
        Context *ctx = Context::master();
        
        // Load source file in memory or stream from file depending on its size
        if (sourceFile->getNumFrames() <= maxFramesForBufferPlayback) {
            mPlayer = ctx->makeNode(new BufferPlayerNode(sourceFile->loadBuffer()));
        }
        else {
            mPlayer = ctx->makeNode(new FilePlayerNode(sourceFile));
        }
        
        // Create gain and other nodes
        mGain = ctx->makeNode(new GainNode());
        mPan  = ctx->makeNode(new Pan2dNode());
        
        // Connect them to master and default speakers
        mPlayer >> mGain >> mPan >> ctx->getOutput();
        
        // Start context
        ctx->enable();
    }
    
    void SoundPlayer::fadeInAndPlay(float seconds, float volume)
    {
        fade(0.0f, volume, seconds);
        mStopTimer.stop();
        play();
    }
    
    void SoundPlayer::fadeInAndStart(float seconds, float volume)
    {
        fade(0.0f, volume, seconds);
        mStopTimer.stop();
        start();
    }

    void SoundPlayer::fadeOutAndStop(float seconds)
    {
        fadeTo(0.0f, seconds);
        
        // There's no thread safe callbacks from audio ramps yet, so we just hack it with timeline
        mStopTimer.stop();
        cinder::app::timeline().apply(&mStopTimer, 0.0f, seconds).finishFn(boost::bind(&SoundPlayer::stop, this));
    }
    
    void SoundPlayer::fadeOutAndPause(float seconds)
    {
        fadeTo(0.0f, seconds);
        
        // There's no thread safe callbacks from audio ramps yet, so we just hack it with timeline
        mStopTimer.stop();
        cinder::app::timeline().apply(&mStopTimer, 0.0f, seconds).finishFn(boost::bind(&SoundPlayer::pause, this));
    }
    
    void SoundPlayer::fade(float from, float to, float seconds, float delay)
    {
        mGain->getParam()->applyRamp(from, to, seconds, Param::Options().delay(delay));
    }
    
    void SoundPlayer::pan(float from, float to, float seconds)
    {
        // no getParam in Pan node?
        // mPan->getParam()->applyRamp(from, pos, seconds);
    }
}