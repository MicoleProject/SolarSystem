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

#ifndef COMMENTAGENT_H
#define COMMENTAGENT_H
/**
 * A GUI agent that takes users notes and sends it to other agents.
 **/

#include <iostream>
#include <fstream>

#include <wx/wx.h>
#include <wx/grid.h>
//#include <wx/stream.h>
//#include <wx/wfstream.h>
//#include <wx/txtstrm.h>
#include <wx/strconv.h>

#include <MicoleAgentThread.h>
#include "micolelib.h"

using namespace std;

enum
{
	ID_Quit = 1,
	ID_About,
	ID_Grid
};

class Comment
{
public:
	Comment(string comment)
	{
		int pos=0;
		int count=0;
		bool done=false;
		string subst;
		while(!done)
		{
			int tmppos=comment.find('\t',pos);
			if(tmppos==string::npos)
			{
				if(pos==0)
				{
					done=true;
					continue;
				}
				else
				{
					done=true;
					subst=comment.substr(pos);
				}
			}
			else
			{
				subst=comment.substr(pos,tmppos-pos);
			}
			pos=tmppos+1;
			cout << subst.c_str() << endl;
			if(count==0)
				date=subst;
			else if(count==1)
				time=subst;
			else if(count==2)
				user=subst;
			else if(count==3)
				subject=subst;
			else if(count==4)
				message=subst;
			count++;
		}
	}

	string toString()
	{
		string msg = splitMessage();
		return date+"    "+time+"    "+user+"    "+subject+"\n"+msg+"\n";
	}

	string splitMessage()
	{
		string retval="";
		int location=0;
		const int limit = 45;
		int pos=0;
		while(1) //pos!=string::npos)
		{
				int tmppos = message.find(' ',pos);
				string subs = message.substr(pos,tmppos-pos);
				if(location + subs.length() > limit && location>0)
				{
					retval+="\n";
					location=0;
				}
				else
				{
					retval += " ";
				}
				location += subs.length();
				retval += subs;
				if(tmppos==string::npos)
					break;
				pos=tmppos+1;
		}
		return retval;
	}

	string user;
	string subject;
	string message;
	string date;
	string time;
};


class wxCommentAgent: public wxApp, public MicoleAgentThread
{
public:
	class MainFrame: public wxFrame
	{
	public:
		MainFrame(wxCommentAgent *master, const wxString& title, const wxPoint& pos, const wxSize& size);

		void OnMyEvent( wxCommandEvent &event );

		void setTopic(string);
		void clearAll();
		void addComment(Comment c);
		void resizeFrame();
		void enableComment(bool enable);
		void ClearComment();
		void focusSubject();

		void currentComment();
		void nextComment();
		void previousComment();

		//void setContext(string context);

		void onGridDClick(wxGridEvent& ev);
		void onQuit(wxCommandEvent& event);
		void onAbout(wxCommandEvent& event);
		void onKeyD(wxKeyEvent& ev);

		void onSendCommand(/*wxCommandEvent&*/);
		void onCancelCommand(/*wxCommandEvent&*/);

		DECLARE_EVENT_TABLE()
	private:
		bool comment_end;
		wxCommentAgent *master_;
		wxGrid *commentlog;
		wxTextCtrl *subject;
		wxTextCtrl *message;
		wxStaticText *topiclabel;
		wxPanel *wba;
		vector<Comment> comments;
		int focused;
		map<string, string> context_conv;
	};
	wxCommentAgent();
	~wxCommentAgent() {};
	void setParams(HINSTANCE);
	virtual void run();

	virtual bool OnInit();
	
	void displayLog(string topic);

	void handleCommentWriteRequest(MicoleBus *app, int argc, const char **argv);
	void handleCommentViewRequest(MicoleBus *app, int argc, const char **argv);
	void handleCommentMessage( MicoleBus *app, int argc, const char **argv );

	void handleUserNavigation( MicoleBus *app, int argc, const char **argv );
	void handleCommentCommand( MicoleBus *app, int argc, const char **argv );
	void handleNewUser( MicoleBus *app, int argc, const char **argv );

	void logMessage(string user, string topic , string subject, string message);
	void writeLog(wxString subject, wxString message);

	string getTopic() { return topic; }
	string getUser() { return user;}
	//DECLARE_EVENT_TABLE()
private:
	string user;
	HINSTANCE hinst_;
	map<string,string> logfiles;
	MainFrame *frame;
	string topic;
	wxMutex m_mutex;
};

#endif

