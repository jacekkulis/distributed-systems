#include <Chat.h>
#include <GroupServerI.h>
#include <ChatException.cpp>

GroupServerI::GroupServerI(const string& name) : groupName(name)
{
}

string GroupServerI::Name(const Ice::Current&)
{ 
	return groupName;
}


void GroupServerI::Join(const UserPrx& userPrx, const Ice::Current& c)
{ 
	for (unsigned int i = 0; i < usersInGroup.size(); i++) {
		if (usersInGroup[i]->GetName() == userPrx->GetName()){
			cout << "User already registered" << endl;	
			throw Chat::UserAlreadyRegistered();
			return;	
		}
	}

	
	cout << "User " << userPrx->GetName() << " joined group: " << this->Name(c) << endl;
	usersInGroup.push_back(userPrx);
}

void GroupServerI::Leave(const UserPrx& userPrx, const Ice::Current& c)
{ 
	for (unsigned int i = 0; i < usersInGroup.size(); i++) {
		if (usersInGroup[i]->GetName() == userPrx->GetName()){	
			cout << "User " << userPrx->GetName() << " left group: " << this->Name(c) << endl;
			usersInGroup.erase(usersInGroup.begin()+i);
			return;
		}
	}

	throw Chat::UserDoesNotExist();
}

void GroupServerI::SendMessage(const string& msg, const UserPrx& userPrx, const Ice::Current& c)
{ 
	Ice::CommunicatorPtr ic = c.adapter->getCommunicator();
	string groupName = this->Name(c);
	GroupServerPrx serverGroupPrx = GroupServerPrx::checkedCast(ic->stringToProxy(groupName + ":tcp -p 10002"));

	for (unsigned int i = 0; i < usersInGroup.size(); i++) {
		usersInGroup[i]->ReceiveText(msg, userPrx, serverGroupPrx);
	}
}

Users GroupServerI::UserList(const Ice::Current& current)
{ 
	Users users;
	Ice::CommunicatorPtr ic = current.adapter->getCommunicator();

	for(unsigned int i = 0; i < usersInGroup.size(); i++){
		string userName = usersInGroup[i]->GetName();
		try{
			//UserPrx userPrx = UserPrx::checkedCast(ic->stringToProxy(userName+":tcp -p 10001"));
			users.push_back(usersInGroup[i]);		
		}catch(const Ice::Exception e){
			cerr << "Caught an exception: " << e.ice_name() << endl;
		}
	}

	return users;
}
