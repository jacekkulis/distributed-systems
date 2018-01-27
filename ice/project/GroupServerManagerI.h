#ifndef GROUP_SERVER_MANAGER_I_H
#define GROUP_SERVER_MANAGER_I_H

#include <Ice/Ice.h>
#include <Chat.h>
#include <GroupServerI.h>

using namespace Chat;
using namespace std;

class GroupServerManagerI: public GroupServerManager {
	public:
		GroupServerManagerI();
		virtual GroupServerPrx CreateGroup(const string&, const Ice::Current&);
		virtual void DeleteGroup(const string&, const Ice::Current&);
		virtual Groups ListGroups(const Ice::Current&);
		virtual GroupServerPrx GetGroupServerByName(const string&, const Ice::Current&);
	private:
		string name;
		vector<GroupServerPrx> serverGroups;
};
#endif
