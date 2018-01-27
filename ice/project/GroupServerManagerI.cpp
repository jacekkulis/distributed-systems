#include <Ice/Ice.h>
#include <Chat.h>
#include <GroupServerManagerI.h>
#include <GroupServerI.h>
#include <ChatException.cpp>

GroupServerManagerI::GroupServerManagerI(){
}

GroupServerPrx GroupServerManagerI::CreateGroup(const string& groupName, const Ice::Current& current)
{ 
	for (unsigned int i = 0; i < serverGroups.size(); i++) {
		if (serverGroups[i]->Name() == groupName){
			throw Chat::NameAlreadyExists();
			return NULL;
		}
	}

	GroupServerPtr serverGroup = new GroupServerI(groupName);	

	Ice::CommunicatorPtr ic = current.adapter->getCommunicator();
	current.adapter->add(serverGroup, ic->stringToIdentity(groupName));	
	GroupServerPrx serverGroupPrx = GroupServerPrx::checkedCast(current.adapter->createProxy(ic->stringToIdentity(groupName)));
	serverGroups.push_back(serverGroupPrx);

	cout << "Room " << serverGroup->Name() << " was created." << endl;
	return serverGroupPrx;
}

void GroupServerManagerI::DeleteGroup(const string& groupName, const Ice::Current& current)
{ 
	cout << "ChatServerI: DeleteGroup" << endl;
	for (unsigned int i = 0; i < serverGroups.size(); i++) {
		if (serverGroups[i]->Name() == groupName){
			serverGroups.erase(serverGroups.begin()+i);
			return;
		}
	}
	
	throw Chat::NameDoesNotExist();
}

Groups GroupServerManagerI::ListGroups(const Ice::Current& current)
{ 
	Groups groups;
	Ice::CommunicatorPtr ic = current.adapter->getCommunicator();

	for(unsigned int i = 0; i < serverGroups.size(); i++){
		string groupName = serverGroups[i]->Name();
		GroupServerPrx serverGroupPrx = GroupServerPrx::checkedCast(ic->stringToProxy(groupName+ ":tcp -p 10002"));
		groups.push_back(serverGroupPrx);
	}

	return groups;
}

GroupServerPrx GroupServerManagerI::GetGroupServerByName(const string& groupName, const Ice::Current& current)
{ 
	for (unsigned int i = 0; i < serverGroups.size(); i++) {
		if (serverGroups[i]->Name() == groupName){
			cout << "Found group with name: " + groupName << endl;
			return serverGroups[i];	
		}
	}	
		
	throw Chat::NameDoesNotExist();
	return NULL;
}
