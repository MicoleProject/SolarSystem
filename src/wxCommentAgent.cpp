/*
 * This file is part of Space Application made in MICOLE project.
 *
 * Copyright (C) 2007 Micole partners
 *
 * Space Application is free software: you can redistribute it 
 * and/or modify it under the terms of the GNU Lesser General 
 * Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or (at your option) any 
 * later version.
 *
 * Space Application is distributed in the hope that it will be 
 * useful, * but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
 * PURPOSE.  See the GNU Lesser General Public License for more 
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Space Application.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "wxCommentAgent.h"
#include <MicoleStringStream.h>
#include <wx/thread.h>

/*
BEGIN_EVENT_TABLE(wxCommentAgent, wxApp)
EVT_KEY_DOWN(wxCommentAgent::OnKeyD)
END_EVENT_TABLE()
*/

DECLARE_EVENT_TYPE(wxEVT_MY_EVENT, -1)
DEFINE_EVENT_TYPE(wxEVT_MY_EVENT)

BEGIN_EVENT_TABLE(wxCommentAgent::MainFrame, wxFrame)
	//EVT_MENU(ID_Quit, wxCommentAgent::MainFrame::onQuit)
	//EVT_MENU(ID_About, wxCommentAgent::MainFrame::onAbout)
	//EVT_BUTTON(1003,wxCommentAgent::MainFrame::onSendCommand)
	//EVT_BUTTON(1004,wxCommentAgent::MainFrame::onCancelCommand)
	//EVT_GRID_CELL_LEFT_DCLICK(wxCommentAgent::MainFrame::onGridDClick)
	//EVT_GRID_SELECT_CELL(wxCommentAgent::MainFrame::OnGridDClick)
	//EVT_KEY_DOWN(wxCommentAgent::MainFrame::OnKeyD)
	EVT_COMMAND(1010,wxEVT_MY_EVENT, wxCommentAgent::MainFrame::OnMyEvent)
END_EVENT_TABLE()

wxCommentAgent::MainFrame::MainFrame(wxCommentAgent *master,const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame((wxFrame *)NULL, 1010, title, pos, size, wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLIP_CHILDREN), master_(master)
	{
		focused=0;
		this->SetExtraStyle(wxWS_EX_PROCESS_UI_UPDATES | wxWS_EX_PROCESS_IDLE);
		context_conv["EARTH"]="Maa";
		context_conv["MARS"]="Mars";
		context_conv["JUPITER"]="Jupiter";
		context_conv["SATURN"]="Saturnus";
		context_conv["MERCURY"]="Merkurius";
		context_conv["SUN"]="Aurinko";
		context_conv["PLUTO"]="Pluto";
		context_conv["VENUS"]="Venus";
		context_conv["URANUS"]="Uranus";
		context_conv["NEPTUNE"]="Neptunus";

		this->SetMinSize(size);
		/*
		wxMenu *menuFile = new wxMenu;
		
		menuFile->Append( ID_About, _T("&About...") );
		menuFile->AppendSeparator();
		menuFile->Append( ID_Quit, _T("E&xit") );
		
		wxMenuBar *menuBar = new wxMenuBar;
		menuBar->Append( menuFile, _T("&File") );
		
		SetMenuBar( menuBar );
		
		CreateStatusBar();
		SetStatusText( _T("Welcome to wxWidgets!") );
		*/
		wba = new wxPanel(this);
		wxBoxSizer *vb1 = new wxBoxSizer(wxVERTICAL);
		
		wxBoxSizer *titlebox = new wxBoxSizer(wxHORIZONTAL);
		titlebox->AddStretchSpacer(1);
		topiclabel = new wxStaticText(wba, -1, _T(""));
		wxFont lfont(GetFont());
		lfont.SetPointSize(24);
		topiclabel->SetFont(lfont);
		titlebox->Add(topiclabel,1);
		titlebox->AddStretchSpacer(1);
		
		vb1->Add(titlebox);
		lfont.SetPointSize(14);

		commentlog = new wxGrid(wba, ID_Grid);
		//commentlog->Connect(wxID_ANY,wxEVT_KEY_DOWN,wxKeyEventHandler(wxCommentAgent::MainFrame::onKeyD),NULL,this);
		commentlog->SetEditable(false);
		commentlog->CreateGrid(0,1);
		commentlog->SetRowLabelSize(0);
		commentlog->SetColLabelSize(0);
		//commentlog->SetCellValue( 0, 0, _T("wxGrid is goodaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\nkekkonen kakkonen\nkomonen") );
		commentlog->SetDefaultCellFont(lfont);
		commentlog->AutoSize();
		vb1->Add(commentlog,wxSizerFlags(1).Expand());
		vb1->AddSpacer(10);
		wxFlexGridSizer *hb2 = new wxFlexGridSizer(2,4,5,5);
		hb2->AddGrowableCol(2,1);
		hb2->AddGrowableRow(1,1);

		//wxBoxSizer *hb1 = new wxBoxSizer(wxHORIZONTAL);
		wxStaticText *l1 = new wxStaticText(wba,1002,_T("Aihe"));
		subject = new wxTextCtrl(wba,1002);
		hb2->AddSpacer(5);
		hb2->Add(l1);
		hb2->Add(subject,wxSizerFlags(1).Expand().Border(wxALL, 1));
		hb2->AddSpacer(5);
		
		//wxBoxSizer *hb2 = new wxBoxSizer(wxHORIZONTAL);
		wxStaticText *l2 = new wxStaticText(wba,1001,_T("Viesti"));
		message= new wxTextCtrl(wba,1003,_T(""),wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE);
		hb2->AddSpacer(5);
		hb2->Add(l2);
		hb2->Add(message,wxSizerFlags(1).Expand().Border(wxALL, 1));//1,wxEXPAND); //,1);
		hb2->AddSpacer(5);
		//hb2->SetSizeHints( this);
		vb1->Add(hb2,wxSizerFlags(1).Expand());

		message->SetFont(lfont);
		subject->SetFont(lfont);
		l2->SetFont(lfont);
		l1->SetFont(lfont);
		//wxBoxSizer *hb3 = new wxBoxSizer(wxHORIZONTAL);
		//wxButton *b1 = new wxButton(wba,1003,_T("Ok"));
		//wxButton *b2 = new wxButton(wba,1004,_T("Peruuta"));
		//hb3->AddStretchSpacer(1);
		//hb3->Add(b2);
		//hb3->Add(b1);
		//vb1->Add(hb3,wxSizerFlags(0).Expand());
		wba->SetSizer(vb1);
		vb1->Fit(wba);
		vb1->SetSizeHints( this );
		message->SetFocus();
		comment_end = false;
}

void wxCommentAgent::MainFrame::resizeFrame()
{
	commentlog->AutoSize();
	//frame->Layout();
	wba->Fit();
	this->Layout(); //SetClientSize(wba->GetSize());
	this->SendSizeEvent();
}

void wxCommentAgent::MainFrame::OnMyEvent( wxCommandEvent &event )
{
    // do something
	if(focused==0)
	{
		message->SetFocus();
	}
	else
	{
		subject->SetFocus();
	}
	focused++;
	if(focused>1) focused=0;
}

void wxCommentAgent::MainFrame::setTopic(string topic)
{
	string tpic="";
	map<string, string>::iterator i= context_conv.find(topic);
	if(i!=context_conv.end())
		tpic=(*i).second;
	topiclabel->SetLabel(wxString(tpic.c_str(),wxConvISO8859_1));
}

void wxCommentAgent::MainFrame::clearAll()
{
	comments.clear();
	if(commentlog->GetNumberRows()>0)
		commentlog->DeleteRows(0,commentlog->GetNumberRows());
}

void wxCommentAgent::MainFrame::ClearComment()
{
	subject->Clear();
	message->Clear();
}

void wxCommentAgent::MainFrame::focusSubject()
{
	this->Raise();
    wxCommandEvent event( wxEVT_MY_EVENT, GetId() );
    event.SetEventObject( this);
	GetEventHandler()->AddPendingEvent(event);
    //GetEventHandler()->ProcessEvent( event );
	//focused++;

}

void wxCommentAgent::MainFrame::enableComment(bool enable)
{
	subject->Enable(enable);
	message->Enable(enable);
}


void wxCommentAgent::MainFrame::addComment(Comment c)
{
	commentlog->AppendRows();
	int row= commentlog->GetRows()-1;
	wxString foo(c.toString().c_str(),wxConvISO8859_1);
	commentlog->SetCellValue( row, 0, foo);
	comments.push_back(c);
}

void wxCommentAgent::MainFrame::currentComment()
{
	if(commentlog->GetNumberRows()<=0)
		return;
	int sidx = commentlog->GetGridCursorRow();
	string msg=comments[sidx].subject + " " + comments[sidx].message;
	string txt="OUT SPCH : str=" + msg + ";priority=true;";
	master_->sendMessage(txt.c_str());
}

void wxCommentAgent::MainFrame::nextComment()
{
	if(commentlog->GetNumberRows()==0) return;
	int sidx = commentlog->GetGridCursorRow()+1;
	if(sidx>commentlog->GetNumberRows()-1 || sidx>=comments.size())
	{
		if(comment_end)
		{
			sidx=0;
			comment_end=false;
		}
		else
		{
			comment_end=true;
			master_->sendMessage("OUT SND : name=kiling.wav;type=1;vol=100;spk=FRONT;pan=0;");
			return;
		}
	}
	commentlog->SetGridCursor(sidx,0);
	commentlog->MakeCellVisible(sidx,0);
	string msg=comments[sidx].subject;
	string txt="OUT SPCH : str=" + msg + ";priority=true;";
	master_->sendMessage(txt.c_str());
}

void wxCommentAgent::MainFrame::previousComment()
{
	int sidx = commentlog->GetGridCursorRow()-1;
	if(sidx<0 || sidx>=comments.size())
		return;
	commentlog->SetGridCursor(sidx,0);
	commentlog->MakeCellVisible(sidx,0);
	string msg=comments[sidx].subject;
	string txt="OUT SPCH : str=" + msg + ";";
	master_->sendMessage(txt.c_str());
}


void wxCommentAgent::MainFrame::onKeyD(wxKeyEvent &ev)
{
	int kcode=ev.GetKeyCode();

	if(kcode==WXK_RIGHT || kcode==WXK_LEFT)
		currentComment();
	else if(kcode == WXK_DOWN )
		nextComment();
	else if(kcode == WXK_UP )
		previousComment();
	ev.Skip(true); 	
}

void wxCommentAgent::MainFrame::onGridDClick(wxGridEvent& ev)
{
	string txt;
	int sidx = commentlog->GetGridCursorRow();

	string msg=comments[sidx].subject + "" + comments[sidx].message;
	txt="OUT SPCH : str=" + msg + ";priority=true;";
	master_->sendMessage(txt.c_str());
	ev.Skip(true);
}

void wxCommentAgent::MainFrame::onQuit(wxCommandEvent& event)
{
	Close(TRUE);
}

void wxCommentAgent::MainFrame::onAbout(wxCommandEvent& event)
{
	wxMessageBox(_T("This is a wxWidgets Hello world sample"),
		_T("About Hello World"), wxOK | wxICON_INFORMATION, this);
}

void wxCommentAgent::MainFrame::onSendCommand(/*wxCommandEvent& ev*/)
{
	if(!message->IsEmpty())
	{
		if(subject->IsEmpty())
			subject->SetValue(_T("Ei otsikkoa"));
		master_->writeLog(subject->GetValue(),message->GetValue());
	}
	
	//string txt = "IN COMMENT : user="+ master_->getUser() +"; topic=" + master_->getTopic() + "; subject="+ subj +"; comment=" + msg +";"; 
	//master_->sendMessage(txt.c_str());
	
	message->Clear();
	subject->Clear();
	
	string txt = "OUT COMMENT : display="+master_->getTopic()+";";
	master_->sendMessage(txt.c_str());
};

void wxCommentAgent::MainFrame::onCancelCommand(/*wxCommandEvent& ev*/){
	static int counter=1;
	message->Clear();
	subject->Clear();
};


wxCommentAgent::wxCommentAgent() : wxApp(), MicoleAgentThread("CommentAgent", "Agent to record user entries.")
{
	logfiles["SUN"]="-sun.txt";
	logfiles["MERCURY"]="-mercury.txt";
	logfiles["VENUS"]="-venus.txt";
	logfiles["EARTH"]="-earth.txt";
	logfiles["MARS"]="-mars.txt";
	logfiles["JUPITER"]="-jupiter.txt";
	logfiles["SATURN"]="-saturn.txt";
	logfiles["URANUS"]="-uranus.txt";
	logfiles["NEPTUNE"]="-neptune.txt";
	logfiles["PLUTO"]="-pluto.txt";

	//m_mutex = new wxMutex();
	// request to write a new comment
	bindMessage( "^OUT COMMENT : pos=(.*);$", BUS_CALLBACK_OF(wxCommentAgent, handleCommentWriteRequest));
	// save comment from some other source
	bindMessage("^IN COMMENT : user=(.*); topic=(.*); subject=(.*); comment=(.*);$", BUS_CALLBACK_OF(wxCommentAgent, handleCommentMessage));
	// show comments
	//bindMessage( "^OUT COMMENT : display=(.*);$", BUS_CALLBACK_OF(wxCommentAgent, handleCommentViewRequest));

	// solarsystem: planet touched
	bindMessage( "^OUT COMMENT : active=(.*);$", BUS_CALLBACK_OF(wxCommentAgent, handleCommentViewRequest));

	// user handling
	bindMessage( "^OUT COMMENT : user=(.*);$", BUS_CALLBACK_OF(wxCommentAgent, handleNewUser));

	// comment handling
	bindMessage( "^OUT COMMENT : command=(.*);$", BUS_CALLBACK_OF(wxCommentAgent, handleCommentCommand));

	// scene switching
	bindMessage( "^OUT SSWA : scene=(.*);$", BUS_CALLBACK_OF(wxCommentAgent, handleUserNavigation));

}

void wxCommentAgent::setParams(HINSTANCE hInstance) 
{
	hinst_=hInstance;
}

void wxCommentAgent::run() 
{
	sendMessage("CommentAgent STARTING.");
	wxEntry(hinst_);
	sendMessage("CommentAgent quitting.");
}

bool wxCommentAgent::OnInit()
{
	frame = new MainFrame(this, _T("Kommentti"), wxPoint(1280,0), wxSize(1280,990) );
	frame->Show(TRUE);
	SetTopWindow(frame);
	//displayLog("EARTH");
	frame->enableComment(false);
	return TRUE;
} 

void wxCommentAgent::displayLog(string cntxt)
{
	wxMutexLocker log_lock(m_mutex);
	map<string,string>::iterator i=logfiles.find(cntxt);
	if(i!=logfiles.end())
	{
		frame->clearAll();
		topic = cntxt;
		ifstream log;
		string logfile=".\\"+getUser()+(*i).second;
		log.open(logfile.c_str(),ios_base::in);
		if(log.fail()){
			// create the file
			ofstream os;
			os.open(logfile.c_str(),ios_base::out);
			os.close();
			// try again;
			log.open(logfile.c_str(),ios_base::in);
			if(log.fail())
				return;
		}

		int count=0;
		string buf;
		getline(log,buf,'¤');
		while(!log.eof())
		{
			Comment comment(buf);
			frame->addComment(comment);
			getline(log,buf,'¤');
		}
		log.close();
		frame->resizeFrame();
		frame->setTopic(topic);
	}
}

void wxCommentAgent::handleCommentWriteRequest(MicoleBus *app, int argc, const char **argv)
{
	if(argc<1) return;
	topic = argv[0];
}

void wxCommentAgent::handleCommentViewRequest(MicoleBus *app, int argc, const char **argv)
{
	if (argc > 0)
	{
		displayLog(argv[0]);
	}
}

void wxCommentAgent::handleNewUser(MicoleBus *app, int argc, const char **argv)
{
	if (argc > 0)
	{
		user=argv[0];
		displayLog(topic);
	}
}

void wxCommentAgent::handleCommentMessage( MicoleBus *app, int argc, const char **argv )
{
	MicoleStringStream ss;
	if (argc > 3)
	{
		logMessage(argv[0],argv[1], argv[2],argv[3]);
	}
}


void wxCommentAgent::handleUserNavigation( MicoleBus *app, int argc, const char **argv )
{
	if(argc<1) return;
	string scene=argv[0];
	if(scene.compare("SOLARSYSTEM")==0)
	{
		// moved back to ss
		frame->onSendCommand();
		frame->ClearComment();
		frame->enableComment(false);
	}
	else
	{
		frame->enableComment(true);
		displayLog(scene);
	}

}


void wxCommentAgent::handleCommentCommand( MicoleBus *app, int argc, const char **argv )
{
	if(argc<1)
		return;
	
	string command=argv[0];
	if(command.compare("NEXT")==0)
	{
		frame->nextComment();
	}
	else if(command.compare("PREVIOUS")==0)
	{
		frame->previousComment();
	}
	else if(command.compare("CURRENT")==0)
	{
		frame->currentComment();
	}
	else if(command.compare("EDIT")==0)
	{
		frame->focusSubject();
	}
	else if(command.compare("OK")==0)
	{
		frame->onSendCommand();
		displayLog(getTopic());
	}
	else  if(command.compare("CANCEL")==0)
	{
		frame->onCancelCommand();
	}
}


void wxCommentAgent::writeLog(wxString subj, wxString msg)
{
	char tsubj[1024];
	char tmsg[2048];
	wxCSConv converter(_T("ISO8859-1"));
	converter.WC2MB(tsubj,subj,subj.Length());
	converter.WC2MB(tmsg,msg,msg.Length());
	logMessage(getUser(), getTopic(), tsubj, tmsg);
}

void wxCommentAgent::logMessage(string user, string topic, string subject, string message)
{
	wxMutexLocker log_lock(m_mutex);
	time_t tim = time (NULL);
	struct tm t;	
	localtime_s(&t, &tim);
	
	map<string,string>::iterator i=logfiles.find(topic);
	if(i!=logfiles.end())
	{
		ofstream log;
		string logfile=".\\"+getUser()+(*i).second;
		log.open(logfile.c_str(),ios_base::app|ios_base::out);
		log << t.tm_mday << "." << t.tm_mon+1 << "." << 1900+t.tm_year << "\t" << t.tm_hour << ":" << (t.tm_min>9?"":"0") << t.tm_min << "\t" << user << " \t" << subject << "\t" << message << '¤' << endl;
		log.close();
	}
}
