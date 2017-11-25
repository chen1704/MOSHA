#include "ImageFrame.h"
#include "MOSHA.h"

ImageFrame::ImageFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title)
{
	this->mosha = new MOSHA(this);
	this->SetInitialSize(wxSize(500, 800));
}
