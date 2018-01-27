#ifndef USER_I_H
#define USER_I_H

#include <Ice/Ice.h>
#include <Chat.h>

using namespace std;
using namespace Chat;

class UserI: public User {
	public:	
		UserI(string name);

		virtual string GetName(const Ice::Current&);
		virtual void ReceiveText(const string&, const UserPrx&, const GroupServerPrx&, const Ice::Current&);
		virtual void ReceivePrivateText(const string&, const UserPrx&, const Ice::Current&);
	private:
		string Name;
};

#endif
