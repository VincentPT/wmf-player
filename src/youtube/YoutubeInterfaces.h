#pragma once

#ifdef _WIN32
#define TEMPLATE_EXTERN
#ifdef EXPORT_YOUTUBE_INTERFACES
#define YOUTUBE_INTERFACE __declspec(dllexport)
#define COMMON_API_EXPORT
#else
#define YOUTUBE_INTERFACE __declspec(dllimport)
#endif // EXPORT_YOUTUBE_INTERFACES
#else
#define TEMPLATE_EXTERN extern
#define YOUTUBE_INTERFACE
#endif // _WIN32