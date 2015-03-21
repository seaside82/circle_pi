///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 20 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __CIRCLEGUI_H__
#define __CIRCLEGUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/notebook.h>
#include <wx/statbox.h>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/slider.h>
#include <wx/checkbox.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class DlgDef
///////////////////////////////////////////////////////////////////////////////
class DlgDef : public wxDialog 
{
	private:
	
	protected:
		wxNotebook* m_notebook1;
		wxPanel* m_panel3;
		wxPanel* m_panel8;
		wxStaticText* m_staticText32;
		wxTextCtrl* m_Approach_SS;
		wxStaticText* m_staticText33;
		wxStaticText* m_staticText321;
		wxTextCtrl* m_dx_SS;
		wxStaticText* m_staticText331;
		wxButton* m_button31121;
		wxNotebook* m_wxNotebook234;
		wxPanel* m_panel11;
		wxStaticText* m_staticText3231;
		wxTextCtrl* m_Lat1;
		wxStaticText* m_staticText3331;
		wxStaticText* m_staticText32311;
		wxTextCtrl* m_Lon1;
		wxStaticText* m_staticText33311;
		wxPanel* m_panel14;
		wxButton* m_button11;
		wxButton* m_Cursor;
		wxButton* m_button311111;
		wxStaticText* m_staticText323122;
		wxTextCtrl* m_Route;
		wxPanel* m_panel15;
		wxStaticText* m_staticText32313;
		wxTextCtrl* m_Lat1_d;
		wxStaticText* m_staticText33313;
		wxTextCtrl* m_Lat1_m;
		wxStaticText* m_staticText1143;
		wxTextCtrl* m_Lat1_s;
		wxStaticText* m_staticText1153;
		wxChoice* m_Lat1_NS;
		wxStaticText* m_staticText323112;
		wxTextCtrl* m_Lon1_d;
		wxStaticText* m_staticText333112;
		wxTextCtrl* m_Lon1_m;
		wxStaticText* m_staticText11412;
		wxTextCtrl* m_Lon1_s;
		wxStaticText* m_staticText11512;
		wxChoice* m_Lon1_EW;
		wxButton* m_button81;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnSSCalc( wxCommandEvent& event ) { event.Skip(); }
		virtual void key_shortcut( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnNoteBookFit( wxNotebookEvent& event ) { event.Skip(); }
		virtual void OnShip( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCursorSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSSGPX( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnConverttoDegree( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxBoxSizer* bSframe;
		
		DlgDef( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("circle_pi"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 321,580 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~DlgDef();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class CfgDlgDef
///////////////////////////////////////////////////////////////////////////////
class CfgDlgDef : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText17;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
	
	public:
		wxSlider* m_sOpacity;
		wxCheckBox* m_CaptureShip;
		wxCheckBox* m_CaptureCursor;
		
		CfgDlgDef( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("circle preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~CfgDlgDef();
	
};

#endif //__CIRCLEGUI_H__
