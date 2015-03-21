/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  circle Plugin
 * Author:   Omer Cakir
 *
 ***************************************************************************
 *   Copyright (C) 2012 by Brazil BrokeTail                                *
 *   $EMAIL$                                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 */

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include "circle_pi.h"

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return new circle_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}

//---------------------------------------------------------------------------------------------------------
//
//    Calculator PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

#include "icons.h"

//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

circle_pi::circle_pi(void *ppimgr)
      :opencpn_plugin_18(ppimgr)
{
      // Create the PlugIn icons
      initialize_images();
}

int circle_pi::Init(void)
{
      AddLocaleCatalog( _T("opencpn-circle_pi") );

      // Set some default private member parameters
      m_route_dialog_x = 0;
      m_route_dialog_y = 0;
      ::wxDisplaySize(&m_display_width, &m_display_height);

      //    Get a pointer to the opencpn display canvas, to use as a parent for the POI Manager dialog
      m_parent_window = GetOCPNCanvasWindow();

      //    Get a pointer to the opencpn configuration object
      m_pconfig = GetOCPNConfigObject();

      //    And load the configuration items
      LoadConfig();

      //    This PlugIn needs a toolbar icon, so request its insertion
      m_leftclick_tool_id  = InsertPlugInTool(_T(""), _img_circle, _img_circle, wxITEM_NORMAL,
            _("circle"), _T(""), NULL,
             CALCULATOR_TOOL_POSITION, 0, this);

      m_pDialog = NULL;

      return (WANTS_CURSOR_LATLON      |
              WANTS_TOOLBAR_CALLBACK    |
              INSTALLS_TOOLBAR_TOOL     |
              WANTS_NMEA_EVENTS         |
              WANTS_PREFERENCES         |
              WANTS_CONFIG

           );
}

bool circle_pi::DeInit(void)
{
      //    Record the dialog position
      if (NULL != m_pDialog)
      {
            //Capture dialog position
            wxPoint p = m_pDialog->GetPosition();
            SetCalculatorDialogX(p.x);
            SetCalculatorDialogY(p.y);
            m_pDialog->Close();
            delete m_pDialog;
            m_pDialog = NULL;
      }
      SaveConfig();
      return true;
}

int circle_pi::GetAPIVersionMajor()
{
      return MY_API_VERSION_MAJOR;
}

int circle_pi::GetAPIVersionMinor()
{
      return MY_API_VERSION_MINOR;
}

int circle_pi::GetPlugInVersionMajor()
{
      return PLUGIN_VERSION_MAJOR;
}

int circle_pi::GetPlugInVersionMinor()
{
      return PLUGIN_VERSION_MINOR;
}

wxBitmap *circle_pi::GetPlugInBitmap()
{
      return _img_circle;
}

wxString circle_pi::GetCommonName()
{
      return _("circle");
}


wxString circle_pi::GetShortDescription()
{
      return _("Drawing circle");
}

wxString circle_pi::GetLongDescription()
{
      return _("Creates a circle GPX files with\n\
desired radius.");
}

int circle_pi::GetToolbarToolCount(void)
{
      return 1;
}

void circle_pi::SetColorScheme(PI_ColorScheme cs)
{
      if (NULL == m_pDialog)
            return;

      DimeWindow(m_pDialog);
}

void circle_pi::OnToolbarToolCallback(int id)
{
      if(NULL == m_pDialog)
      {
            m_pDialog = new Dlg(m_parent_window);
            m_pDialog->plugin = this;
            m_pDialog->Move(wxPoint(m_route_dialog_x, m_route_dialog_y));
      }
 m_pDialog->Fit();
      m_pDialog->Show(!m_pDialog->IsShown());
}

bool circle_pi::LoadConfig(void)
{
      wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

      if(pConf)
      {
            pConf->SetPath ( _T( "/Settings/circle_pi" ) );
            pConf->Read ( _T ( "Opacity" ),  &m_iOpacity, 255 );
           // pConf->Read       dialog->m_cpConnectorColor->SetColour(m_sConnectorColor);
            m_route_dialog_x =  pConf->Read ( _T ( "DialogPosX" ), 20L );
            m_route_dialog_y =  pConf->Read ( _T ( "DialogPosY" ), 20L );
            m_bCaptureCursor =  pConf->Read ( _T ( "CaptureCursor" ), true );
            m_bCaptureShip =  pConf->Read ( _T ( "CaptureShip" ), true );

            if((m_route_dialog_x < 0) || (m_route_dialog_x > m_display_width))
                  m_route_dialog_x = 5;
            if((m_route_dialog_y < 0) || (m_route_dialog_y > m_display_height))
                  m_route_dialog_y = 5;
            return true;
      }
      else
            return false;
}

bool circle_pi::SaveConfig(void)
{
      wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

      if(pConf)
      {
            pConf->SetPath ( _T ( "/Settings/circle_pi" ) );
            pConf->Write ( _T ( "Opacity" ), m_iOpacity );
            pConf->Write ( _T ( "DialogPosX" ),   m_route_dialog_x );
            pConf->Write ( _T ( "DialogPosY" ),   m_route_dialog_y );
            pConf->Write ( _T ( "CaptureCursor" ), m_bCaptureCursor );
            pConf->Write ( _T ( "CaptureShip" ),  m_bCaptureShip );
            return true;
      }
      else
            return false;
}

void circle_pi::ShowPreferencesDialog( wxWindow* parent )
{
      CfgDlg *dialog = new CfgDlg( parent, wxID_ANY, _("Circle Preferences"), wxPoint( m_route_dialog_x, m_route_dialog_y), wxDefaultSize, wxDEFAULT_DIALOG_STYLE );
      dialog->Fit();
      wxColour cl;
      DimeWindow(dialog);
      dialog->m_sOpacity->SetValue(m_iOpacity);
      dialog->m_CaptureCursor->SetValue(m_bCaptureCursor);
      dialog->m_CaptureShip->SetValue(m_bCaptureShip);

      if(dialog->ShowModal() == wxID_OK)
      {
            m_iOpacity = dialog->m_sOpacity->GetValue();
            m_bCaptureCursor = dialog->m_CaptureCursor->GetValue();
            m_bCaptureShip = dialog->m_CaptureCursor->GetValue();
            SaveConfig();
      }
      delete dialog;
}

void circle_pi::SetCursorLatLon(double lat, double lon)
{
    if (m_bCaptureShip){ //Option to save CPU
        m_cursor_lat=lat;
        m_cursor_lon=lon;
    }
    //std::cout<<"Cursor--> Lat: "<<m_cursor_lat<<" Lon: "<<m_cursor_lon<<std::endl;
}

void circle_pi::SetPositionFix(PlugIn_Position_Fix &pfix)
{
    if (m_bCaptureCursor){ //Option to save CPU
        m_ship_lon = pfix.Lon;
        m_ship_lat = pfix.Lat;
        //std::cout<<"Ship--> Lat: "<<m_ship_lat<<" Lon: "<<m_ship_lon<<std::endl;
    }
}
