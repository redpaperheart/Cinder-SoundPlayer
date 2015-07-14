#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "rph/SoundPlayer.h"
#include "rph/SoundManager.h"
#include "cinder/audio/Context.h"
#include "cinder/Json.h"
#include "cinder/Timer.h"
#include "Cell.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class AudioMatrixApp : public App {
  public:
    AudioMatrixApp(){};
    
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void mouseDrag( MouseEvent event) override;
	void update() override;
	void draw() override;
    
    void nextStep();
    
    void loadSounds();
    void audioOn(int y, int x);
    void audioOff(int x, int y);
    float getColWidth();
    float getRowHeight();
    float mFrameSpeed = 3.0f;
    float mFramUpdateTime = 1.0f/mFrameSpeed;
    
    std::map < int, std::vector<rph::SoundPlayerRef>> mSounds;
    int mRow = 4;
    int mColumn = 6;
    int mGridTop = 20;
    int mGridLeft = 20;
    int mGridWidth = getWindowWidth()-(mGridLeft*2);
    int mGridHeight = getWindowHeight()-(mGridTop*2);
    int curColumn = -1;
    
    float mColWidth = mGridWidth/mColumn;
    float mRowHeight = mGridHeight/mRow;
    
    bool setState = false;
    
    CueRef mCue;
    
    Cell mGrid[6][4];

};

void AudioMatrixApp::setup()
{
    loadSounds();
    mCue = timeline().add( bind(&AudioMatrixApp::nextStep, this), timeline().getCurrentTime() + 1 );
    mCue->setDuration( 0.7 );
    mCue->setAutoRemove( false );
    mCue->setLoop();
    
    for (int x = 0; x<mColumn; x++) {
        for (int y = 0 ; y< mRow; y++) {
            mGrid[x][y] = *new Cell(x,y);
        }
    }
}

void AudioMatrixApp::loadSounds(){
    mSounds.clear();
    JsonTree jsonFile = JsonTree( loadAsset( "audioMatrix.json" ));
    for(int i = 0; i < jsonFile["audio"].getNumChildren(); i++){
        int index = jsonFile["audio"][i]["index"].getValue<int>();
        
        for(int j = 0; j < jsonFile["audio"][ci::toString(i)]["files"].getNumChildren(); j++){
            std::string fileName = jsonFile["audio"][i]["files"][j]["filename"].getValue<std::string>();
            rph::SoundPlayerRef soundPlayer = rph::SoundPlayer::create( loadAsset(fileName));
            mSounds[ index ].push_back(soundPlayer);
           
        }
    }
    
}

void AudioMatrixApp::audioOn(int y, int x){
    mSounds[y][x]->start();
}

void AudioMatrixApp::audioOff(int x, int y){
    mSounds[x][y]->stop();
}



void AudioMatrixApp::mouseDown( MouseEvent event )
{

    vec2 mCurrentPos = event.getPos();
    int mX = lmap(int(mCurrentPos.x - mGridLeft), 0, mGridWidth, 0, mColumn);
    int mY = lmap(int(mCurrentPos.y - mGridTop),0, mGridHeight, 0, mRow);
    if(mX >= 0 && mX < mColumn && mY >= 0 && mY < mRow){
        setState = ! mGrid[mX][mY].mState;
        mGrid[mX][mY].mState = setState;
        mGrid[mX][mY].mSelected = setState;

    }
    
}


void AudioMatrixApp::mouseDrag( MouseEvent event ){
    vec2 mCurrentPos = event.getPos();
    int mX = lmap(int(mCurrentPos.x ), 0, mGridWidth-15, 0, mColumn);
    int mY = lmap(int(mCurrentPos.y ), 0, mGridHeight-15, 0, mRow);
    if(mX >= 0 && mX < mColumn && mY >= 0 && mY < mRow){

        mGrid[mX][mY].mState = setState;
        mGrid[mX][mY].mSelected = setState;

    }
    
    
}

void AudioMatrixApp::nextStep(){
    curColumn = (curColumn +1) % mColumn;
//    int lastColumn = (curColumn + mColumn-1) % mColumn;
    
    for (int x = 0; x<mColumn;x++) {
        for (int y = 0 ; y< mRow;y++) {
            
            if (mGrid[x][y].mX == curColumn) {
                mGrid[x][y].sliderOn();
                if (mGrid[x][y].mState) {
                    mGrid[x][y].cellOn();
                    audioOn(y, x);
                }
            }
            else{
                mGrid[x][y].sliderOff();
                mGrid[x][y].cellOff();
            
            }
        }
    }
}

void AudioMatrixApp::update()
{
}



void AudioMatrixApp::draw()
{
    
	gl::clear( Color(1,1,1));
    
    for (int x = 0; x<mColumn;x++) {
        for (int y = 0 ; y< mRow;y++) {
            Cell cell = mGrid[x][y];
            cell.draw(mColWidth, mRowHeight, mGridTop, mGridLeft);
        }
    }
}



CINDER_APP( AudioMatrixApp, RendererGl(), [&]( App::Settings *settings ) {
    settings->setWindowSize( 640, 440 );
    settings->setFrameRate(60);

})
