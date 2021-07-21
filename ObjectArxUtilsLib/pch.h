// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。
#pragma once

#ifndef PCH_H
#define PCH_H


#define OBJECTARX_UTILS
// 添加要在此处预编译的标头
#include "framework.h"

#ifndef _ALLOW_RTCc_IN_STL
#define _ALLOW_RTCc_IN_STL
#endif

#pragma pack(push, 8)
#pragma warning(disable : 4786 4996 4099)
#pragma warning(disable: 4098)


#ifndef PI
#define PI 3.1415926535897932384626
#endif // !PI

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN //- Exclude rarely-used stuff from Windows headers
#endif

#ifndef WINVER //- Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0601 //- Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif

	//- ObjectARX and OMF headers needs this
#include <map>

#include <afxwin.h> //- MFC core and standard components
#include <afxext.h> //- MFC extensions
#include <afxcmn.h> //- MFC support for Windows Common Controls


#include <arxHeaders.h>

#endif //PCH_H
