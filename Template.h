// Template.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Resource.h"

#include "..\Common\Ascii.h"
#include "..\Common\Common.h"

#include "..\Classes\MessageClass.h"
#include "..\Classes\WindowClassClass.h"

#define MAIN_WINDOW_CLASS_NAME													"Main Template Window Class"

#define MAIN_WINDOW_CLASS_STYLE													0
#define MAIN_WINDOW_CLASS_ICON_NAME												IDI_APPLICATION
#define MAIN_WINDOW_CLASS_ICON													LoadIcon( NULL, MAIN_WINDOW_CLASS_ICON_NAME )
#define MAIN_WINDOW_CLASS_CURSOR												LoadCursor( NULL, IDC_ARROW )
#define MAIN_WINDOW_CLASS_BACKGROUND											( HBRUSH )( COLOR_WINDOW + 1 )
#define MAIN_WINDOW_CLASS_MENU_NAME												MAKEINTRESOURCE( IDR_MAIN_MENU )

#define MAIN_WINDOW_EXTENDED_STYLE												( WS_EX_WINDOWEDGE | WS_EX_ACCEPTFILES )
#define MAIN_WINDOW_STYLE														WS_OVERLAPPEDWINDOW
#define MAIN_WINDOW_TEXT														"Template"

#define MAIN_WINDOW_MINIMUM_WIDTH												320
#define MAIN_WINDOW_MINIMUM_HEIGHT												200

#define LIST_BOX_WINDOW_EXTENDED_STYLE											0
#define LIST_BOX_WINDOW_STYLE													( WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY )
#define LIST_BOX_WINDOW_TEXT													NULL

#define STATUS_BAR_WINDOW_EXTENDED_STYLE										0
#define STATUS_BAR_WINDOW_STYLE													( WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP )
#define STATUS_BAR_WINDOW_TEXT													NULL

#define SYSTEM_MENU_SEPARATOR_ITEM_POSITION										5
#define SYSTEM_MENU_ABOUT_ITEM_POSITION											6
#define SYSTEM_MENU_ABOUT_ITEM_TEXT												"About"

#define ABOUT_MESSAGE_TEXT														"Template\r\n"						\
																				"\r\n"								\
																				"Written by Jim Smith\r\n"			\
																				"\r\n"								\
																				"December 2024"

#define UNABLE_TO_CREATE_MAIN_WINDOW_ERROR_MESSAGE								"Unable to Create Main Window"
