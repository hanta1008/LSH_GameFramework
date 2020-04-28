#pragma once

#include "../Resource.h"
#include "iWindow.h"

#ifdef _DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif

bool loadApp();
void resizeWindow(float width, float height);
void monitorSettings();

// ------------------
// Window Kill
// ------------------
extern bool runWnd;
void exitProgram();


////////////////////////////////////////////////////////////////////////////
// Settings
////////////////////////////////////////////////////////////////////////////
#if 0

옵션 C / C++ / 미리컴파일된 헤더 / 사용안함

0. 인코딩
솔루션 폴더 / .editorconfig 파일복사
C / C++ / 명령줄 / 추가옵션 : / utf - 8 입력

1. 폴더 복사
프로젝트명.cpp / h 삭제
프로젝트경로 / windows
프로젝트경로 / lib

2. 디렉토리 추가
C / C++ / 추가디렉토리
$(ProjectDir)\windows
$(ProjectDir)\lib
C : \workspace\openalSdk\include

	링커 / 추가 라이브러리 디렉토리
	Win32 = > C:\workspace\openalSdk\libs\Win32
	x64 = > C:\workspace\openalSdk\libs\Win64

	3. 매크로
	C / C++ / 전처리기 / 전처리기 정의

	윈도우 프로그래밍
	컨트롤러 사용시 - (어플리케이션)WIN32_LEAN_AND_MEAN 주석처리
	컨트롤러 사용X - (게임개발)WIN32_LEAN_AND_MEAN 선언

	// strcpy, sprintf
	_CRT_SECURE_NO_WARNINGS

	// glew
	GLEW_STATIC

	// lib
	_OS_ = 2

	// math M_PI
	_USE_MATH_DEFINES

	// GdiPlus 1.1 이상 지원
	GDIPVER = 0x0110

	// opengl version(0: v1.x, 1: v3.2)
	SUPPORT_OPENGL_3 = 1

	// 0:게임용(AppForGame.cpp), 1:앱용(AppForCtrl.cpp)
	USE_SYSTEM_MENU = 1

	// ====================================
	// 헤더파일 정리해야 할것들
	// ====================================
	iWindow.h / iGraphics.h / iPlatform.h

	// ====================================
	// GLEW 설정
	// ====================================
	다운로드 http ://glew.sourceforge.net/ 
glew.h & wglew.h 복사 C : \Program Files(x86)\Windows Kits\10\Include\10.0.17763.0\um\gl
glew.c 복사 $(ProjectDir)\windows
GLEW_STATIC 매크로선언

// ====================================
// OPENAL 설정
// ====================================
다운로드 https ://www.openal.org/
2. 디렉토리 추가 참조

#endif