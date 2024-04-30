#pragma once

#ifdef DYNAMICLIB_EXPORTS
#define MY_DLL extern "C" __declspec(dllexport)
#else
#define MY_DLL extern "C" __declspec(dllimport)
#endif

MY_DLL float floor(float _f);