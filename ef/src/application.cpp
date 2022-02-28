#include "application.h"

#include <iostream>

#include <SDL.h>
#include "glad/glad.h"

namespace ef
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::run()
	{
        
		while (1)
		{

		}
	}
	void Application::print()
	{

        
	}

}

#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_eferus_ef_MainActivity_stringFromJNI2(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello 2 C++";
    return env->NewStringUTF(hello.c_str());