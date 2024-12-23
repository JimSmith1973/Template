// Template.cpp

#include "Template.h"

// Global variables
HWND g_hWndListBox;
HWND g_hWndStatusBar;

void OpenFileFunction( LPCTSTR lpszFilePath )
{
	// Add file to list box window
	SendMessage( g_hWndListBox, LB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )lpszFilePath );

} // End of function OpenFileFunction

int ShowAboutMessage( HWND hWndParent )
{
	int nResult = 0;

	MSGBOXPARAMS mbp;

	// Clear message box parameter structure
	ZeroMemory( &mbp, sizeof( mbp ) );

	// Initialise message box parameter structure
	mbp.cbSize		= sizeof( MSGBOXPARAMS );
	mbp.hwndOwner	= hWndParent;
	mbp.hInstance	= NULL;
	mbp.lpszText	= ABOUT_MESSAGE_TEXT;
	mbp.lpszCaption	= ABOUT_MESSAGE_CAPTION;
	mbp.dwStyle		= ( MB_OK | MB_USERICON );
	mbp.lpszIcon	= WINDOW_CLASS_CLASS_DEFAULT_ICON_NAME;

	// Show message box
	nResult = MessageBoxIndirect( &mbp );

	return nResult;

} // End of function ShowAboutMessage

LRESULT CALLBACK MainWindowProcedure( HWND hWndMain, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	LRESULT lr = 0;

	// Select message
	switch( uMessage )
	{
		case WM_CREATE:
		{
			// A create message
			HINSTANCE hInstance;

			// Get instance
			hInstance = ( ( LPCREATESTRUCT )lParam )->hInstance;

			// Create list box window
			g_hWndListBox = CreateWindowEx( LIST_BOX_WINDOW_EXTENDED_STYLE, WC_LISTBOX, LIST_BOX_WINDOW_TEXT, LIST_BOX_WINDOW_STYLE, 0, 0, 0, 0, hWndMain, ( HMENU )NULL, hInstance, NULL );

			// Ensure that list box window was created
			if( g_hWndListBox )
			{
				// Successfully created list box window
				Font font;

				// Get font
				font = DEFAULT_GUI_FONT;

				// Set list box window font
				SendMessage( g_hWndListBox, WM_SETFONT, ( WPARAM )font, ( LPARAM )TRUE );

				// Create status bar window
				g_hWndStatusBar = CreateWindowEx( STATUS_BAR_WINDOW_EXTENDED_STYLE, STATUSCLASSNAME, STATUS_BAR_WINDOW_TEXT, STATUS_BAR_WINDOW_STYLE, 0, 0, 0, 0, hWndMain, ( HMENU )NULL, hInstance, NULL );

				// Ensure that status bar window was created
				if( g_hWndStatusBar )
				{
					// Successfully created status bar window

					// Set status bar window font
					SendMessage( g_hWndStatusBar, WM_SETFONT, ( WPARAM )font, ( LPARAM )TRUE );

				} // End of successfully created status bar window

			} // End of successfully created list box window

			// Break out of switch
			break;

		} // End of a create message
		case WM_SIZE:
		{
			// A size message
			int nClientWidth;
			int nClientHeight;
			RECT rcStatus;
			int nStatusWindowHeight;
			int nListBoxWindowHeight;

			// Store client width and height
			nClientWidth	= ( int )LOWORD( lParam );
			nClientHeight	= ( int )HIWORD( lParam );

			// Size status bar window
			SendMessage( g_hWndStatusBar, WM_SIZE, ( WPARAM )NULL, ( LPARAM )NULL );

			// Get status window size
			GetWindowRect( g_hWndStatusBar, &rcStatus );

			// Calculate window sizes
			nStatusWindowHeight		= ( rcStatus.bottom - rcStatus.top );
			nListBoxWindowHeight	= ( nClientHeight - nStatusWindowHeight );

			// Move list box window
			MoveWindow( g_hWndListBox, 0, 0, nClientWidth, nListBoxWindowHeight, TRUE );

			// Break out of switch
			break;

		} // End of a size message
		case WM_ACTIVATE:
		{
			// An activate message

			// Focus on list box window
			SetFocus( g_hWndListBox );

			// Break out of switch
			break;

		} // End of an activate message
		case WM_GETMINMAXINFO:
		{
			// A get min max info message
			MINMAXINFO FAR *lpMinMaxInfo;

			// Get min max info structure
			lpMinMaxInfo = ( MINMAXINFO FAR * )lParam;

			// Update min max info structure
			lpMinMaxInfo->ptMinTrackSize.x = MAIN_WINDOW_MINIMUM_WIDTH;
			lpMinMaxInfo->ptMinTrackSize.y = MAIN_WINDOW_MINIMUM_HEIGHT;

			// Break out of switch
			break;

		} // End of a get min max info message
		case WM_DROPFILES:
		{
			// A drop files message
			DroppedFiles droppedFiles;

			// Get dropped files
			if( droppedFiles.Get( wParam ) )
			{
				// Successfully got dropped files

				// Process dropped files
				droppedFiles.Process( &OpenFileFunction );

			} // End of successfully got dropped files

			// Break out of switch
			break;

		} // End of a drop files message
		case WM_COMMAND:
		{
			// A command message

			// Select command
			switch( LOWORD( wParam ) )
			{
				case IDM_FILE_EXIT:
				{
					// A file exit command

					// Destroy window
					DestroyWindow( hWndMain );

					// Break out of switch
					break;

				} // End of a file exit command
				case IDM_HELP_ABOUT:
				{
					// A help about command

					// Show about message
					ShowAboutMessage( hWndMain );

					// Break out of switch
					break;

				} // End of a help about command
				default:
				{
					// Default command

					// See if command message is from list box window
					if( ( HWND )lParam == g_hWndListBox )
					{
						// Command message is from list box window

						// Select list box window notification code
						switch( HIWORD( wParam ) )
						{
							case LBN_DBLCLK:
							{
								// A list box window double click notification code
								int nSelectedItem;

								// Allocate string memory
								LPTSTR lpszSelected = new char[ STRING_LENGTH ];

								// Get selected item
								nSelectedItem = SendMessage( g_hWndListBox, LB_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

								// Get selected item text
								if( SendMessage( g_hWndListBox, LB_GETTEXT, ( WPARAM )nSelectedItem, ( LPARAM )lpszSelected ) )
								{
									// Successfully got selected item text

									// Display selected item text
									MessageBox( hWndMain, lpszSelected, INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

								} // End of successfully got selected item text

								// Free string memory
								delete [] lpszSelected;

								// Break out of switch
								break;

							} // End of a list box window double click notification code
							case LBN_SELCHANGE:
							{
								// A list box window selection change notification code
								int nSelectedItem;

								// Allocate string memory
								LPTSTR lpszSelected = new char[ STRING_LENGTH ];

								// Get selected item
								nSelectedItem = SendMessage( g_hWndListBox, LB_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

								// Get selected item text
								if( SendMessage( g_hWndListBox, LB_GETTEXT, ( WPARAM )nSelectedItem, ( LPARAM )lpszSelected ) )
								{
									// Successfully got selected item text

									// Show selected item text on status bar window
									SendMessage( g_hWndStatusBar, SB_SETTEXT, ( WPARAM )NULL, ( LPARAM )lpszSelected );

								} // End of successfully got selected item text

								// Free string memory
								delete [] lpszSelected;

								// Break out of switch
								break;

							} // End of a list box window selection change notification code
							default:
							{
								// Default list box window notification code

								// Call default procedure
								lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

								// Break out of switch
								break;

							} // End of default list box window notification code

						}; // End of selection for list box window notification code

					} // End of command message is from list box window
					else
					{
						// Command message is not from list box window

						// Call default procedure
						lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

					} // End of command message is not from list box window

					// Break out of switch
					break;

				} // End of default command

			}; // End of selection for command

			// Break out of switch
			break;

		} // End of a command message
		case WM_SYSCOMMAND:
		{
			// A system command message

			// Select system command
			switch( LOWORD( wParam ) )
			{
				case IDM_HELP_ABOUT:
				{
					// A help about system command

					// Show about message
					ShowAboutMessage( hWndMain );

					// Break out of switch
					break;

				} // End of a help about system command
				default:
				{
					// Default system command

					// Call default procedure
					lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

					// Break out of switch
					break;

				} // End of default system command

			}; // End of selection for system command

			// Break out of switch
			break;

		} // End of a system command message
		case WM_NOTIFY:
		{
			// A notify message

			// Call default handler
			lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

			// Break out of switch
			break;

		} // End of a notify message
		case WM_CONTEXTMENU:
		{
			// A context menu message
			Menu popupMenu;

			// Load popup menu
			popupMenu.Load( MAKEINTRESOURCE( IDR_CONTEXT_MENU ) );

			// Show popup menu
			popupMenu.TrackPopupMenu( 0, lParam, hWndMain );

			// Break out of switch
			break;

		} // End of a context menu message
		case WM_CLOSE:
		{
			// A close message

			// Destroy main window
			DestroyWindow( hWndMain );

			// Break out of switch
			break;

		} // End of a close message
		case WM_DESTROY:
		{
			// A destroy message

			// Terminate thread
			PostQuitMessage( 0 );

			// Break out of switch
			break;

		} // End of a destroy message
		default:
		{
			// Default message

			// Call default window procedure
			lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

			// Break out of switch
			break;

		} // End of default message

	}; // End of selection for message

	return lr;

} // End of function MainWindowProcedure

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow )
{
	Message message;

	WindowClass mainWindowClass;

	// Initialise main window class
	mainWindowClass.Initialise( MAIN_WINDOW_CLASS_NAME, hInstance, MainWindowProcedure, MAIN_WINDOW_CLASS_MENU_NAME );

	// Register main window class
	if( mainWindowClass.Register() )
	{
		// Successfully registered main window class
		Window mainWindow;

		// Create main window
		if( mainWindow.Create( MAIN_WINDOW_CLASS_NAME, NULL, hInstance, MAIN_WINDOW_TEXT ) )
		{
			// Successfully created main window
			Menu systemMenu;
			ArgumentList argumentList;

			// Get system menu
			systemMenu.GetSystem( mainWindow );

			// Add separator item to system menu
			systemMenu.InsertSeparator( SYSTEM_MENU_SEPARATOR_ITEM_POSITION );

			// Add about item to system menu
			systemMenu.InsertItem( SYSTEM_MENU_ABOUT_ITEM_POSITION, IDM_HELP_ABOUT, SYSTEM_MENU_ABOUT_ITEM_TEXT );

			// Get argument list
			if( argumentList.Get() )
			{
				// Successfully got argument list

				// Process arguments
				argumentList.ProcessArguments( &OpenFileFunction );

			} // End of successfully got argument list

			// Show main window
			mainWindow.Show( nCmdShow );

			// Update main window
			mainWindow.Update();

			// Message loop
			while( message.Get() > 0 )
			{
				// Translate message
				message.Translate();

				// Dispatch message
				message.Dispatch();

			}; // End of message loop

		} // End of successfully created main window
		else
		{
			// Unable to create main window

			// Display error message
			MessageBox( NULL, WINDOW_CLASS_UNABLE_TO_CREATE_WINDOW_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

		} // End of unable to create main window

	} // End of successfully registered main window class
	else
	{
		// Unable to register main window class

		// Display error message
		MessageBox( NULL, WINDOW_CLASS_CLASS_UNABLE_TO_REGISTER_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

	} // End of unable to register main window class

	return message;

} // End of function WinMain