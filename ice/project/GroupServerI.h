#ifndef GROUP_SERVER_I_H
#define GROUP_SERVER_I_H

#include <Ice/Ice.h>
#include <Chat.h>

using namespace Chat;
using namespace std;

class GroupServerI: public GroupServer {
	public:
		GroupServerI(const string&);
		virtual string Name(const Ice::Current&);
		virtual void Join(const UserPrx&, const Ice::Current&);
		virtual void Leave(const UserPrx&, const Ice::Current&);
		virtual void SendMessage(const string&, const UserPrx&, const Ice::Current&);
		virtual Users UserList(const Ice::Current&);
	
	private:
		string groupName;
		vector<UserPrx> usersInGroup;
};


#endif
