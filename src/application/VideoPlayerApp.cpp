#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "../src/AntTweakBar/AntTweakBar.h"

#include "ciWMFVideoPlayer.h"
#include "string_util.hpp"
#include "YoutubeInterface.h"
#include "UIThreadRunner.h"
#include "CinderImGui.h"
#include "ui/ImWidget.h"

using namespace std;

class AddressBar : public ImWidget {
	std::function<void()> _updateContentCallback;
public:
	AddressBar()
	{
		_window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
	}
	void setCallback(const std::function<void()>& updateContentCallback) {
		_updateContentCallback = updateContentCallback;
	}

	void draw() {
		ui::SetNextWindowSize(_window_size, ImGuiCond_FirstUseEver);
		ui::SetNextWindowPos(_window_pos, ImGuiCond_FirstUseEver);
		ui::SetNextWindowBgAlpha(0.1f);

		ui::ScopedWindow window("##addressbar", _window_flags);

		if (_updateContentCallback) {
			_updateContentCallback();
		}
	}
};

class VideoPlayerApp : public ci::app::App
{
public:
	VideoPlayerApp();
	~VideoPlayerApp();

	void draw();
	void mouseDown( ci::app::MouseEvent event ) override;
	void mouseDrag( ci::app::MouseEvent event ) override;
	void setup();
	void update();
	void loadVideo(const wstring& videoURL);

protected:
	static void loadVideoInternal(VideoPlayerApp* app, bool error, const wchar_t* videoURL) {
		wstring url = videoURL;
		if (error) {
			app->_loadStatus = "error code 2";
		}
		else {
			app->_uiThreadRunner.postTask(std::bind(&VideoPlayerApp::loadVideo, app, url));
		}
	}

private:
	bool						mVideoSetup;
	ciWMFVideoPlayer			mVideo1;

	float						mFps;
	//std::string					mVideoURL = "https://www.youtube.com/watch?v=5U3jf8BRdE4";
	//std::string					mVideoURL = "https://www.youtube.com/watch?v=Bntj6OCe2_g";
	std::string					mVideoURL = "https://www.youtube.com/watch?v=M_XwzBMTJaM";
	std::shared_ptr< AsyncTask > _asynTask;
	UIThreadRunner _uiThreadRunner;
	AddressBar _addressbar;
	std::string _loadStatus;
};

class DummyInterfaceGL : public ci::params::InterfaceGl {
public:
	static int getBarOffset() {
		return offsetof(DummyInterfaceGL, mBar);
	}
};

#include "cinder/app/RendererGl.h"
#include "cinder/Log.h"

using namespace ci;
using namespace ci::app;
using namespace std;

VideoPlayerApp::VideoPlayerApp() :
	mFps( 0.0f )
{
}

VideoPlayerApp::~VideoPlayerApp()
{
}

void VideoPlayerApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
	mVideo1.draw( 0, 0 );

	_addressbar.draw();
}

void VideoPlayerApp::loadVideo(const wstring& videoURL) {
	std::pair<std::wstring, std::wstring> deviceItem;
	mVideo1.mPlayer->getDefaultAudioDevice(deviceItem);

	if (mVideo1.loadMovie(videoURL, deviceItem.second.c_str())) {
		mVideo1.play();
		_loadStatus = "";
	}
	else {
		_loadStatus = "error code 1";
	}
}

void VideoPlayerApp::setup()
{
	ImGui::initialize();

	mVideo1.getPresentationEndedSignal().connect( []() {
		ci::app::console() << "Video finished playing!" << std::endl;
	} );

	//auto mBarOffset = DummyInterfaceGL::getBarOffset();
	//TwBar* pBar = ((std::shared_ptr<TwBar>*)((char*)mParams.get() + mBarOffset))->get();
	//int width = 400;
	//TwSetParam(pBar, NULL, "valueswidth", TW_PARAM_INT32, 1, &width);

	_addressbar.setPos(10, 10);
	_addressbar.setSize(800, 35);
	_addressbar.setCallback([this]() {
		ui::InputText("", &mVideoURL); ui::SameLine();
	
		if (ui::Button("load video")) {
			trim(mVideoURL);
			wstring videoURL(mVideoURL.begin(), mVideoURL.end());
			typedef void(*Handler)(void*, bool, const wchar_t*);
			_loadStatus = "Loading...";
			char youtubePrefix[] = "https://www.youtube.com";
			if (strncmp(mVideoURL.c_str(), youtubePrefix, sizeof(youtubePrefix) - 1) == 0) {
				_asynTask.reset(getDirectLink(videoURL.c_str(), this, (Handler)&VideoPlayerApp::loadVideoInternal));
			}
			else {
				loadVideo(videoURL);
			}
		}
		ui::SameLine();
		ui::Text("%.1f", mFps);
		ui::SameLine();
		ui::TextColored(ImVec4(1, 0, 0, 1), _loadStatus.c_str());
	});
}

void VideoPlayerApp::mouseDown( MouseEvent event )
{
	CI_LOG_I( "Video position: " << mVideo1.getPosition() );
}

void VideoPlayerApp::mouseDrag( MouseEvent event )
{
}

void VideoPlayerApp::update()
{
	_uiThreadRunner.executeTasks(0);

	mFps = getAverageFps();
	mVideo1.update();
}

CINDER_APP( VideoPlayerApp, RendererGl, []( App::Settings * settings )
{
	settings->setFrameRate( 60.0f );
	settings->prepareWindow( Window::Format().size( 1280, 720 ).title( "Simple Playback" ) );
} )
