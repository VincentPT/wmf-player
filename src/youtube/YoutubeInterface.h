#pragma once
#include "YoutubeInterfaces.h"
#include "AsyncTask.h"

YOUTUBE_INTERFACE AsyncTask* getDirectLink(const wchar_t* url, void* userData, void (*ProcessDirectLinkCallback)(void* userData, bool error, const wchar_t* directLink));