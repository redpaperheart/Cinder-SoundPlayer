#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Json.h"
#include "cinder/Rand.h"

#include "rph/SoundPlayer.h"
#include "rph/SoundManager.h"

#include "Cell.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class AudioMatrixApp : public App {
  public:
	void setup() override;
    void draw() override;
    void resize() override;
    void mouseMove( MouseEvent event ) override;
    void mouseDown( MouseEvent event ) override;
    void mouseDrag( MouseEvent event) override;
    void keyDown( KeyEvent event) override;
    
    void loadSounds();
    void nextStep();
    void checkCell(ivec2 pos, bool toggle);
    
    int mRows = 4;
    int mCols = 6;
    int curColumn = -1;
    float mCellPadding = 10;
    float mGridMargin = 20;
    float mCellSize;
    
    Rectf mGridRect;
    CueRef mCue;
    
    Cell* mCurCell;
    Cell mGrid[6][4];
    std::map < int, std::vector<rph::SoundPlayerRef>> mSounds;
    
};

void AudioMatrixApp::setup()
{
    Rand::randomize();
    gl::enableVerticalSync(false);
    
    loadSounds();
    
    // initialize cells and enable some randomnly
    for (int x = 0; x < mCols; x++) {
        for (int y = 0; y < mRows; y++) {
            mGrid[x][y].setup(x, y);
            
            if (randFloat() < 0.15)
                mGrid[x][y].enable(true);
        }
    }
    
    // setup sequencer loop
    mCue = timeline().add( bind(&AudioMatrixApp::nextStep, this), timeline().getCurrentTime() );
    mCue->setDuration( 0.5 );
    mCue->setAutoRemove( false );
    mCue->setLoop();
}

void AudioMatrixApp::loadSounds()
{
    JsonTree jsonFile = JsonTree( loadAsset( "audioMatrix.json" ));
    
    for (JsonTree row : jsonFile["audio"].getChildren()) {
        int index = row["index"].getValue<int>();
        
        for (JsonTree file : row["files"].getChildren()) {
            std::string fileName = file["filename"].getValue<std::string>();
            float volume = file["volume"].getValue<float>();
            
            rph::SoundPlayerRef soundPlayer = rph::SoundPlayer::create(loadAsset(fileName));
            soundPlayer->setVolume(volume);
            mSounds[index].push_back(soundPlayer);
        }
    }
}

void AudioMatrixApp::nextStep()
{
    curColumn = (curColumn +1) % mCols;
    
    for (int x = 0; x < mCols; x++) {
        for (int y = 0 ; y < mRows; y++) {
            
            if (x == curColumn) {
                mGrid[x][y].setPlayhead(true);
                
                if (mGrid[x][y].isEnabled()) {
                    mSounds[y][x]->start();
                }
            }
            else{
                mGrid[x][y].setPlayhead(false);
            }
        }
    }
}

void AudioMatrixApp::draw()
{
	gl::clear(Color(1,1,1));
    
    for (int x = 0; x < mCols; x++) {
        for (int y = 0 ; y < mRows; y++) {
            mGrid[x][y].draw(mCellSize, mCellPadding, mGridRect.getUpperLeft());
        }
    }
}

void AudioMatrixApp::resize()
{
    Rectf minRect = Rectf(0, 0, mCols, mRows);
    mGridRect = minRect.getCenteredFit(Rectf(getWindowBounds()).inflated(ivec2(-mGridMargin)), true);
    mCellSize = mGridRect.getWidth() / mCols;
    mCellPadding = mCellSize * 0.1;
}

void AudioMatrixApp::mouseMove( MouseEvent event )
{
    checkCell(event.getPos(), false);
}

void AudioMatrixApp::mouseDown( MouseEvent event )
{
    if (mCurCell) mCurCell->toggle();
}

void AudioMatrixApp::mouseDrag( MouseEvent event )
{
    checkCell(event.getPos(), true);
}

void AudioMatrixApp::checkCell(ivec2 pos, bool toggle)
{
    if (mGridRect.contains(pos)) {
        
        // doesn't account for padding
        int x = lmap(pos.x, (int)mGridRect.getX1(), (int)mGridRect.getX2(), 0, mCols);
        int y = lmap(pos.y, (int)mGridRect.getY1(), (int)mGridRect.getY2(), 0, mRows);
        Cell* cell = &mGrid[x][y];
        
        if (mCurCell != cell) {
            if (mCurCell) mCurCell->setSelected(false);
            mCurCell = cell;
            mCurCell->setSelected(true);
            if (toggle) mCurCell->toggle();
        }
    }
    else if (mCurCell) {
        mCurCell->setSelected(false);
        mCurCell = nullptr;
    }
}

void AudioMatrixApp::keyDown( KeyEvent event )
{
    switch (event.getCode()) {
        case KeyEvent::KEY_RIGHT:
            mCue->setDuration(mCue->getDuration() + 0.05f);
            break;
        case KeyEvent::KEY_LEFT:
            mCue->setDuration(std::max(mCue->getDuration() - 0.05f, 0.05f));
            break;
        default:
            break;
    }
}

CINDER_APP( AudioMatrixApp, RendererGl(), [&]( App::Settings *settings ) {
    settings->setWindowSize( 640, 440 );
    settings->disableFrameRate();
})
