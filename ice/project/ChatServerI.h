#ifndef CHAT_SERVER_I_H
#define CHAT_SERVER_I_H

#include <Ice/Ice.h>
#include <Chat.h>
#include <GroupServerI.h>

using namespace Chat;
using namespace std;

class ChatServerI : public ChatServer {
	public:
		ChatServerI();
		virtual void LogIn(const UserPrx&, const Ice::Current&);
		virtual UserPrx GetUserByName(const string&, const Ice::Current&);
		virtual Groups GroupList(const Ice::Current&);
		virtual GroupServerPrx GetGroupServerByName(const string&, const Ice::Current&);
		virtual void CreateGroup(const string&, const Ice::Current&);
		virtual void DeleteGroup(const string&, const Ice::Current&);
		virtual void RegisterServer(const GroupServerManagerPrx&, const Ice::Current&);
		virtual void UnregisterServer(const GroupServerManagerPrx&, const Ice::Current&);

	private:
		//vector<GroupServerPrx> serverGroups;
		vector<UserPrx> userListOnServer;
		GroupServerManagerPrx groupServerManager;
};

#endif
