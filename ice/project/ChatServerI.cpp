#include <Chat.h>
#include <ChatServerI.h>
#include <ChatException.cpp>

ChatServerI::ChatServerI(){
}

void ChatServerI::LogIn(const UserPrx& userPrx, const Ice::Current& c)
{ 
	for (unsigned int i = 0; i < userListOnServer.size(); i++) {
		if (userListOnServer[i]->GetName() == userPrx->GetName()){
			cout << "User already logged in" << endl;	
			throw Chat::NameAlreadyExists();
			return;	
		}
	}

	cout << "Server: User " << userPrx->GetName() << " has logged in."<< endl;
	userListOnServer.push_back(userPrx);
}

UserPrx ChatServerI::GetUserByName(const string& username, const Ice::Current&)
{ 
	for (unsigned int i = 0; i < userListOnServer.size(); i++) {
		if (userListOnServer[i]->GetName() == username){
			cout << "Found user with name: " + username << endl;
			return userListOnServer[i];	
		}
	}	

	return NULL;
}

Groups ChatServerI::GroupList(const Ice::Current& current)
{ 
	return this->groupServerManager->ListGroups();
}


GroupServerPrx ChatServerI::GetGroupServerByName(const string& groupName, const Ice::Current&)
{ 
	return this->groupServerManager->GetGroupServerByName(groupName);
}

void ChatServerI::CreateGroup(const string& groupName, const Ice::Current& current)
{ 
	this->groupServerManager->CreateGroup(groupName);
}

void ChatServerI::DeleteGroup(const string& groupName, const Ice::Current&)
{ 
	this->groupServerManager->DeleteGroup(groupName);
}

void ChatServerI::RegisterServer(const GroupServerManagerPrx& groupServerManager, const Ice::Current& current)
{ 
	cout << "ChatServerI: RegisterServer" << endl;
	this->groupServerManager = groupServerManager;
	
}

void ChatServerI::UnregisterServer(const GroupServerManagerPrx&, const Ice::Current& current)
{ 
	cout << "ChatServerI: UnregisterServer" << endl;
	this->groupServerManager = NULL;
}
