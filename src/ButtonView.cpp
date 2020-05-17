#include "ButtonView.h"
#include <Button.h>
#include <StringView.h>

ButtonView::ButtonView(BRect frame, const char* name,
					   uint32 resizeMask, uint32 flags)
	: BView(frame, name, resizeMask, flags)
{
	BButton*  button;
	BMessage* message;

	button = new BButton(BRect(20, 30, 70, 60), "hide button", "Hide",
						 nullptr);
	message = new BMessage(B_MINIMIZE);
	message->AddBool("minimize", true);
	button->SetMessage(message);
	AddChild(button);

	button = new BButton(BRect(90, 30, 140, 60), "close button", "Close",
						 nullptr);
	message = new BMessage(B_QUIT_REQUESTED);
	button->SetMessage(message);
	AddChild(button);

	AddChild(new BStringView(BRect(10, 10, 200, 25),
							 "caption", "This is my 4th app."));

	SetViewColor(0xDD, 0xDD, 0xDD);
}


