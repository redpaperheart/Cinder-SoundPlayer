#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "cinder/params/Params.h"
#include "rph/SoundPlayer.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SoundPlayerBasicApp : public AppNative {
public:
    void setup();
    void draw();
    void keyDown( KeyEvent event );
    void updateVolume();
    void updatePan();
    
    params::InterfaceGlRef  mParams;
    rph::SoundPlayerRef     mSound;
    float                   mVolume;
    float                   mPan;
};

void SoundPlayerBasicApp::setup()
{
    setWindowSize(200, 200);
    
    // Load and setup sound players
    mSound = rph::SoundPlayer::create(loadAsset("8bit.mp3"));                  // loadResource works too
    mSound->setLoop(true);
    mVolume = 1.0;
    mPan = 0.0;
    
    // Create buttons for playback
    mParams = params::InterfaceGl::create("SoundPlayer", ivec2(160, 160));
    mParams->addButton("Play", std::bind(&rph::SoundPlayer::play, mSound));     // mSound.play()
    mParams->addButton("Pause", std::bind(&rph::SoundPlayer::pause, mSound));   // mSound.pause()
    mParams->addButton("Stop", std::bind(&rph::SoundPlayer::stop, mSound));     // mSound.stop()
    mParams->addParam("Volume", &mVolume).min(0.0f).max(5.0f).step(0.1f).updateFn([this] {
        mSound->setVolume(mVolume);
    });
    mParams->addParam("Pan", &mPan).min(-1.0f).max(1.0f).step(0.05f).updateFn([this] {
        mSound->setPan(mPan);
    });
}

void SoundPlayerBasicApp::keyDown( KeyEvent event )
{
    switch (event.getCode()) {
        case KeyEvent::KEY_SPACE:
            if (mSound->isPlaying()) mSound->pause();
            else                     mSound->play();
            break;
        case KeyEvent::KEY_UP:
            mVolume += 0.1; // we update this so it shows in params, but we dont need to
            mSound->setVolume(mVolume);
            break;
        case KeyEvent::KEY_DOWN:
            mVolume -= 0.1;
            mSound->setVolume(mVolume);
            break;
        case KeyEvent::KEY_RIGHT:
            mPan += 0.1;
            mSound->setPan(mPan);
            break;
        case KeyEvent::KEY_LEFT:
            mPan -= 0.1;
            mSound->setPan(mPan);
            break;
        default:
            break;
    }
}

void SoundPlayerBasicApp::draw()
{
    gl::clear( Color( 0, 0, 0 ) );
    mParams->draw();
}

CINDER_APP_NATIVE( SoundPlayerBasicApp, RendererGl )
