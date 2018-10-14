#include "YoutubeInterface.h"

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace web::http;
using namespace web::http::client;
using namespace std;

class CppRestSDKAsynTask : public AsyncTask {
protected:
	Concurrency::task<void> _task;
public:
	CppRestSDKAsynTask(Concurrency::task<void> nativeTask) : _task(nativeTask) {}
	~CppRestSDKAsynTask() {
		wait();
	}
	void wait() {
		_task.wait();
	}
};

AsyncTask* getDirectLink(const wchar_t* url, void* userData, void(*processDirectLinkCallback)(void* userData, bool error, const wchar_t* directLink)) {
	http_client client(U("https://you-link.herokuapp.com/?url=") + utility::conversions::to_string_t(url));

	// Make the request and asynchronously process the response. 
	auto task = client.request(methods::GET).then([userData, processDirectLinkCallback](http_response response)
	{
		bool error = true;
		if (response.status_code() == 200) {
			//auto ress = response.extract_utf8string().get();
			auto jsResponse = response.extract_json().get();
			auto& arr = jsResponse.as_array();
			if (arr.size()) {
				// get first video
				auto& videoObject = arr[0].as_object();
				auto it = videoObject.find(U("url"));
				if (it != videoObject.end()) {
					auto videoURL = it->second.as_string();
					error = false;
					processDirectLinkCallback(userData, error, utility::conversions::to_utf16string(videoURL).c_str());
				}
			}
		}
		if (error) {
			processDirectLinkCallback(userData, error, L"");
		}
	});

	return new CppRestSDKAsynTask(task);
}