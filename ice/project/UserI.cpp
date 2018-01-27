#include <Chat.h>
#include <UserI.h>


UserI::UserI(string name) : Name(name){
}

string UserI::GetName(const Ice::Current&)
{ 
	return this->Name;
}

void UserI::ReceiveText(const string& msg, const UserPrx& userPrx, const GroupServerPrx& groupServerPrx, const Ice::Current& c)
{ 
	cout << userPrx->GetName() << ": " << msg << endl;
}

void UserI::ReceivePrivateText(const string& msg, const UserPrx& userPrx, const Ice::Current&)
{ 
	cout << userPrx->GetName() << ": " << msg << endl;
}
