#include "RegularWindow.h"
#include <Application.h>
#include <Window.h>
#include <MenuBar.h>

const char* kSender = "sender";

RegularWindow::RegularWindow(BRect frame, const char* title,
							 window_type type, uint32 flags, uint32 quitMsg)
	: BWindow(frame, title, type, flags, B_CURRENT_WORKSPACE),
	  fQuitMsg(quitMsg)
{
}


void
RegularWindow::InitContent(BView* content)
{
	BRect bounds(Frame());
	content->ResizeTo(bounds.Width(), bounds.Height());
	AddChild(content);
}


void
RegularWindow::InitContent(BMenuBar* menuBar, BView* content)
{
	AddChild(menuBar);
	BRect menuBarBounds(menuBar->Frame());
	BRect bounds(Frame());
	content->ResizeTo(bounds.Width(),
					  bounds.Height() - menuBarBounds.Height() - 1);
	content->MoveBy(0, menuBarBounds.Height() + 1);
	AddChild(content);
}


void
RegularWindow::Quit()
{
	BMessage quitMessage(fQuitMsg);

	quitMessage.AddPointer(kSender, this);
	be_app->PostMessage(&quitMessage);
	BWindow::Quit();
}
