#include "Resource.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>

Resource::Resource()
{
}

Resource::~Resource()
{
	delete buttonWindow, map, mapblur, chibi;
	delete bitmapstatus, bitmapbonds, bitmapinvent, bitmapskill;
	for (int i=0; i<=58;i++) delete huruf[i];
}


Resource * Resource::getInstance()
{
	if (!inst) {
		inst = new Resource();
	}
	return inst;
}


void Resource::LoadResourceBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	fileLocation = stdPaths.GetExecutablePath();

	wxString locmenu = wxFileName(fileLocation).GetPath() + wxT("\\MAP - FIX.png");
	wxImage image(locmenu, wxBITMAP_TYPE_PNG);
	map = new wxBitmap(image);
	wxString locationmap = wxFileName(fileLocation).GetPath() + wxT("\\MAP - blur.png");
	wxImage image0(locationmap, wxBITMAP_TYPE_PNG);
	mapblur = new wxBitmap(image0);
	wxString locwindow = wxFileName(fileLocation).GetPath() + wxT("\\button window.png");
	wxImage image1(locwindow, wxBITMAP_TYPE_PNG);
	buttonWindow = new wxBitmap(image1);
	wxString locationchibi = wxFileName(fileLocation).GetPath() + wxT("\\chibi sprites.png");
	wxImage image2(locationchibi, wxBITMAP_TYPE_PNG);
	chibi = new wxBitmap(image2);

}

void Resource::LoadMenuBitmap()
{
	wxString locstatus = wxFileName(fileLocation).GetPath() + wxT("\\button status.png");
	wxImage image1(locstatus, wxBITMAP_TYPE_PNG);
	bitmapstatus = new wxBitmap(image1);

	wxString locbond = wxFileName(fileLocation).GetPath() + wxT("\\button bonds.png");
	wxImage image2(locbond, wxBITMAP_TYPE_PNG);
	bitmapbonds = new wxBitmap(image2);

	wxString locinven = wxFileName(fileLocation).GetPath() + wxT("\\button inventory.png");
	wxImage image3(locinven, wxBITMAP_TYPE_PNG);
	bitmapinvent = new wxBitmap(image3);

	wxString locskill = wxFileName(fileLocation).GetPath() + wxT("\\button upgrade.png");
	wxImage image4(locskill, wxBITMAP_TYPE_PNG);
	bitmapskill = new wxBitmap(image4);

}


void Resource::LoadHurufbesarBitmap()
{
	wxString loca = wxFileName(fileLocation).GetPath() + wxT("\\a.png");
	wxImage image1(loca, wxBITMAP_TYPE_PNG);
	huruf[1] = new wxBitmap(image1);

	wxString locb = wxFileName(fileLocation).GetPath() + wxT("\\b.png");
	wxImage image2(locb, wxBITMAP_TYPE_PNG);
	huruf[2] = new wxBitmap(image2);

	wxString locc = wxFileName(fileLocation).GetPath() + wxT("\\c.png");
	wxImage image3(locc, wxBITMAP_TYPE_PNG);
	huruf[3] = new wxBitmap(image3);

	wxString locd = wxFileName(fileLocation).GetPath() + wxT("\\d.png");
	wxImage image4(locd, wxBITMAP_TYPE_PNG);
	huruf[4] = new wxBitmap(image4);

	wxString loce = wxFileName(fileLocation).GetPath() + wxT("\\e.png");
	wxImage image5(loce, wxBITMAP_TYPE_PNG);
	huruf[5] = new wxBitmap(image5);

	wxString locf = wxFileName(fileLocation).GetPath() + wxT("\\f.png");
	wxImage image6(locf, wxBITMAP_TYPE_PNG);
	huruf[6] = new wxBitmap(image6);

	wxString locg = wxFileName(fileLocation).GetPath() + wxT("\\g.png");
	wxImage image7(locg, wxBITMAP_TYPE_PNG);
	huruf[7] = new wxBitmap(image7);

	wxString loch = wxFileName(fileLocation).GetPath() + wxT("\\h.png");
	wxImage image8(loch, wxBITMAP_TYPE_PNG);
	huruf[8] = new wxBitmap(image8);

	wxString loci = wxFileName(fileLocation).GetPath() + wxT("\\i.png");
	wxImage image26(loci, wxBITMAP_TYPE_PNG);
	huruf[9] = new wxBitmap(image26);

	wxString locj = wxFileName(fileLocation).GetPath() + wxT("\\j.png");
	wxImage image9(locj, wxBITMAP_TYPE_PNG);
	huruf[10] = new wxBitmap(image9);

	wxString lock = wxFileName(fileLocation).GetPath() + wxT("\\k.png");
	wxImage image10(lock, wxBITMAP_TYPE_PNG);
	huruf[11] = new wxBitmap(image10);

	wxString locl = wxFileName(fileLocation).GetPath() + wxT("\\l.png");
	wxImage image11(locl, wxBITMAP_TYPE_PNG);
	huruf[12] = new wxBitmap(image11);

	wxString locm = wxFileName(fileLocation).GetPath() + wxT("\\m.png");
	wxImage image12(locm, wxBITMAP_TYPE_PNG);
	huruf[13] = new wxBitmap(image12);

	wxString locn = wxFileName(fileLocation).GetPath() + wxT("\\n.png");
	wxImage image13(locn, wxBITMAP_TYPE_PNG);
	huruf[14] = new wxBitmap(image13);

	wxString loco = wxFileName(fileLocation).GetPath() + wxT("\\o.png");
	wxImage image14(loco, wxBITMAP_TYPE_PNG);
	huruf[15] = new wxBitmap(image14);

	wxString locp = wxFileName(fileLocation).GetPath() + wxT("\\p.png");
	wxImage image15(locp, wxBITMAP_TYPE_PNG);
	huruf[16] = new wxBitmap(image15);

	wxString locq = wxFileName(fileLocation).GetPath() + wxT("\\q.png");
	wxImage image16(locq, wxBITMAP_TYPE_PNG);
	huruf[17] = new wxBitmap(image16);

	wxString locr = wxFileName(fileLocation).GetPath() + wxT("\\r.png");
	wxImage image17(locr, wxBITMAP_TYPE_PNG);
	huruf[18] = new wxBitmap(image17);

	wxString locs = wxFileName(fileLocation).GetPath() + wxT("\\s.png");
	wxImage image18(locs, wxBITMAP_TYPE_PNG);
	huruf[19] = new wxBitmap(image18);

	wxString loct = wxFileName(fileLocation).GetPath() + wxT("\\t.png");
	wxImage image19(loct, wxBITMAP_TYPE_PNG);
	huruf[20] = new wxBitmap(image19);

	wxString locu = wxFileName(fileLocation).GetPath() + wxT("\\u.png");
	wxImage image20(locu, wxBITMAP_TYPE_PNG);
	huruf[21] = new wxBitmap(image20);

	wxString locv = wxFileName(fileLocation).GetPath() + wxT("\\v.png");
	wxImage image21(locv, wxBITMAP_TYPE_PNG);
	huruf[22] = new wxBitmap(image21);

	wxString locw = wxFileName(fileLocation).GetPath() + wxT("\\w.png");
	wxImage image22(locw, wxBITMAP_TYPE_PNG);
	huruf[23] = new wxBitmap(image22);

	wxString locx = wxFileName(fileLocation).GetPath() + wxT("\\x.png");
	wxImage image23(locx, wxBITMAP_TYPE_PNG);
	huruf[24] = new wxBitmap(image23);

	wxString locy = wxFileName(fileLocation).GetPath() + wxT("\\y.png");
	wxImage image24(locy, wxBITMAP_TYPE_PNG);
	huruf[25] = new wxBitmap(image24);

	wxString locz = wxFileName(fileLocation).GetPath() + wxT("\\z.png");
	wxImage image25(locz, wxBITMAP_TYPE_PNG);
	huruf[26] = new wxBitmap(image25);
}

void Resource::LoadHurufkecilBitmap()
{
	wxString loca = wxFileName(fileLocation).GetPath() + wxT("\\akecil.png");
	wxImage image1(loca, wxBITMAP_TYPE_PNG);
	huruf[33] = new wxBitmap(image1);

	wxString locb = wxFileName(fileLocation).GetPath() + wxT("\\bkecil.png");
	wxImage image2(locb, wxBITMAP_TYPE_PNG);
	huruf[34] = new wxBitmap(image2);

	wxString locc = wxFileName(fileLocation).GetPath() + wxT("\\ckecil.png");
	wxImage image3(locc, wxBITMAP_TYPE_PNG);
	huruf[35] = new wxBitmap(image3);

	wxString locd = wxFileName(fileLocation).GetPath() + wxT("\\dkecil.png");
	wxImage image4(locd, wxBITMAP_TYPE_PNG);
	huruf[36] = new wxBitmap(image4);

	wxString loce = wxFileName(fileLocation).GetPath() + wxT("\\ekecil.png");
	wxImage image5(loce, wxBITMAP_TYPE_PNG);
	huruf[37] = new wxBitmap(image5);

	wxString locf = wxFileName(fileLocation).GetPath() + wxT("\\fkecil.png");
	wxImage image6(locf, wxBITMAP_TYPE_PNG);
	huruf[38] = new wxBitmap(image6);

	wxString locg = wxFileName(fileLocation).GetPath() + wxT("\\gkecil.png");
	wxImage image7(locg, wxBITMAP_TYPE_PNG);
	huruf[39] = new wxBitmap(image7);

	wxString loch = wxFileName(fileLocation).GetPath() + wxT("\\hkecil.png");
	wxImage image8(loch, wxBITMAP_TYPE_PNG);
	huruf[40] = new wxBitmap(image8);

	wxString loci = wxFileName(fileLocation).GetPath() + wxT("\\ikecil.png");
	wxImage image26(loci, wxBITMAP_TYPE_PNG);
	huruf[41] = new wxBitmap(image26);

	wxString locj = wxFileName(fileLocation).GetPath() + wxT("\\jkecil.png");
	wxImage image9(locj, wxBITMAP_TYPE_PNG);
	huruf[42] = new wxBitmap(image9);

	wxString lock = wxFileName(fileLocation).GetPath() + wxT("\\kkecil.png");
	wxImage image10(lock, wxBITMAP_TYPE_PNG);
	huruf[43] = new wxBitmap(image10);

	wxString locl = wxFileName(fileLocation).GetPath() + wxT("\\lkecil.png");
	wxImage image11(locl, wxBITMAP_TYPE_PNG);
	huruf[44] = new wxBitmap(image11);

	wxString locm = wxFileName(fileLocation).GetPath() + wxT("\\mkecil.png");
	wxImage image12(locm, wxBITMAP_TYPE_PNG);
	huruf[45] = new wxBitmap(image12);

	wxString locn = wxFileName(fileLocation).GetPath() + wxT("\\nkecil.png");
	wxImage image13(locn, wxBITMAP_TYPE_PNG);
	huruf[46] = new wxBitmap(image13);

	wxString loco = wxFileName(fileLocation).GetPath() + wxT("\\okecil.png");
	wxImage image14(loco, wxBITMAP_TYPE_PNG);
	huruf[47] = new wxBitmap(image14);

	wxString locp = wxFileName(fileLocation).GetPath() + wxT("\\pkecil.png");
	wxImage image15(locp, wxBITMAP_TYPE_PNG);
	huruf[48] = new wxBitmap(image15);

	wxString locq = wxFileName(fileLocation).GetPath() + wxT("\\qkecil.png");
	wxImage image16(locq, wxBITMAP_TYPE_PNG);
	huruf[49] = new wxBitmap(image16);

	wxString locr = wxFileName(fileLocation).GetPath() + wxT("\\rkecil.png");
	wxImage image17(locr, wxBITMAP_TYPE_PNG);
	huruf[50] = new wxBitmap(image17);

	wxString locs = wxFileName(fileLocation).GetPath() + wxT("\\skecil.png");
	wxImage image18(locs, wxBITMAP_TYPE_PNG);
	huruf[51] = new wxBitmap(image18);

	wxString loct = wxFileName(fileLocation).GetPath() + wxT("\\tkecil.png");
	wxImage image19(loct, wxBITMAP_TYPE_PNG);
	huruf[52] = new wxBitmap(image19);

	wxString locu = wxFileName(fileLocation).GetPath() + wxT("\\ukecil.png");
	wxImage image20(locu, wxBITMAP_TYPE_PNG);
	huruf[53] = new wxBitmap(image20);

	wxString locv = wxFileName(fileLocation).GetPath() + wxT("\\vkecil.png");
	wxImage image21(locv, wxBITMAP_TYPE_PNG);
	huruf[54] = new wxBitmap(image21);

	wxString locw = wxFileName(fileLocation).GetPath() + wxT("\\wkecil.png");
	wxImage image22(locw, wxBITMAP_TYPE_PNG);
	huruf[55] = new wxBitmap(image22);

	wxString locx = wxFileName(fileLocation).GetPath() + wxT("\\xkecil.png");
	wxImage image23(locx, wxBITMAP_TYPE_PNG);
	huruf[56] = new wxBitmap(image23);

	wxString locy = wxFileName(fileLocation).GetPath() + wxT("\\ykecil.png");
	wxImage image24(locy, wxBITMAP_TYPE_PNG);
	huruf[57] = new wxBitmap(image24);

	wxString locz = wxFileName(fileLocation).GetPath() + wxT("\\zkecil.png");
	wxImage image25(locz, wxBITMAP_TYPE_PNG);
	huruf[58] = new wxBitmap(image25);
}
