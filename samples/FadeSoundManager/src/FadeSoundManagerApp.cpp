#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/params/Params.h"

#include "rph/SoundPlayer.h"
#include "rph/SoundManager.h"

#define SOUND_SYNTH "synth.mp3"
#define SOUND_JAZZ  "jazz.mp3"
#define SOUND_8BIT  "8bit.mp3"

using namespace ci;
using namespace ci::app;
using namespace std;

class FadeSoundManagerApp : public AppNative {
  public:
	void setup();
	void draw();
    void playNextSong(string key);
    
    params::InterfaceGlRef  mParams;
    rph::SoundManager*      mSoundManager;
    std::string             mCurrentSongName;
    float                   mFadeTime;
};

void FadeSoundManagerApp::setup()
{
    setWindowSize(240, 200);

    // Load sounds
    mSoundManager = rph::SoundManager::getInstance();
    mSoundManager->loadSound(SOUND_SYNTH)->setLoop(true);
    mSoundManager->loadSound(SOUND_JAZZ)->setLoop(true);
    mSoundManager->loadSound(SOUND_8BIT)->setLoop(true);
    mCurrentSongName = "";
    mFadeTime = 4.0;
    
    // Create buttons for playback
    mParams = params::InterfaceGl::create("Loops", vec2(200, 160));
    mParams->addButton("Play Ethereal", std::bind(&FadeSoundManagerApp::playNextSong, this, SOUND_SYNTH));
    mParams->addButton("Play Jazz", std::bind(&FadeSoundManagerApp::playNextSong, this, SOUND_JAZZ));
    mParams->addButton("Play 8Bit", std::bind(&FadeSoundManagerApp::playNextSong, this, SOUND_8BIT));
    mParams->addParam("Fade Time", &mFadeTime).min(0.1).max(10.0).step(0.1);
}

void FadeSoundManagerApp::playNextSong(string key)
{
    // Fade out current song
    if (mCurrentSongName != "") {
        mSoundManager->getSound(mCurrentSongName)->fadeOutAndPause(mFadeTime);
    }
    
    // Fade in next song
    mSoundManager->getSound(key)->fadeInAndPlay(mFadeTime);

    // Save current song
    mCurrentSongName = key;
}

void FadeSoundManagerApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    mParams->draw();
}

CINDER_APP_NATIVE( FadeSoundManagerApp, RendererGl )
