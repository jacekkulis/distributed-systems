#include <Ice/Ice.h>
#include <Chat.h>
#include <UserI.h>
#include <GroupServerI.h>
#include <GroupServerManagerI.h>

using namespace std;
using namespace Chat;

void printStartingInterface(){
	printf("Choose option (write number): \n");
	printf("1. Log in\n");
	printf("2. Exit\n");
}

void printUserInterface(){
	printf("\n0. Logout\n");
	printf("1. List groups\n");
	printf("2. Join group\n");
	printf("2. Leave group\n");
	printf("4. List users\n");
	printf("5. Send private message\n");
	printf("6. Send message to group\n");
}

int main(int argc, char* argv[])
{
	int status = 0;
	Ice::CommunicatorPtr ic;

	try {
		ic = Ice::initialize(argc, argv);
		Ice::ObjectPrx base = ic->stringToProxy("ChatServer:default -p 10001");

		ChatServerPrx chatServer = ChatServerPrx::checkedCast(base->ice_twoway()->ice_timeout(-1)->ice_secure(false));

		if (!chatServer)
			throw "Invalid proxy to chatserver";
		
		Ice::ObjectAdapterPtr adapter = ic->createObjectAdapterWithEndpoints("ChatClient", "default");
		adapter->activate();

		Ice::ObjectPrx gsmBase = ic->stringToProxy("GroupServerManager:default -p 10002");
		GroupServerManagerPrx groupServerManager = GroupServerManagerPrx::checkedCast(gsmBase->ice_twoway()->ice_timeout(-1)->ice_secure(false));

		if (!groupServerManager)
			throw "Invalid proxy to gsm";


		chatServer->RegisterServer(groupServerManager);
		
		try{
			chatServer->CreateGroup("Group1");
			chatServer->CreateGroup("Group2");
			chatServer->CreateGroup("Group3");
			chatServer->CreateGroup("Group4");
		}
		catch (const NameAlreadyExists& e) {
			//nothing
		}

		printStartingInterface();
		int choice = 0;
		scanf("%d", &choice);
		
		string username;
		UserPrx userPrx;

		if(choice == 1){
			printf("Write your name:\n");
			cin >> username;
			try{
				UserPtr userPtr = new UserI(username);
				adapter->add(userPtr, ic->stringToIdentity(userPtr->GetName()));
		
				userPrx = UserPrx::checkedCast(adapter->createProxy(ic->stringToIdentity(userPtr->GetName())));
				
				chatServer->LogIn(userPrx);	
			}
			catch (const NameAlreadyExists& e) {
				cerr << "Caught an exception: " << e.ice_name() << endl;
				return EXIT_FAILURE;
			}


			GroupServerPrx groupServerPrx;
			Groups groups;
			Users users;		

			while(1){	
				printUserInterface();
				scanf("%d", &choice);

				if (choice == 0){
					break;
				}

				if (choice == 1){
					groups = chatServer->GroupList();

					cout << "Available rooms:" << endl;
					for (unsigned int i = 0; i < groups.size(); i++) {
						cout << groups[i]->Name() << endl;
					}

				}
				
				if (choice == 2){
					try{
						string groupName;
						printf("Write group name:\n");	
						cin >> groupName;
						groupServerPrx = groupServerManager->GetGroupServerByName(groupName);
						groupServerPrx->Join(userPrx);
					}
					catch (const NameDoesNotExist& e) {
						cerr << "Caught an exception: " << e.ice_name() << endl;
					}
					
				}
				
				if (choice == 3){
					if (!groupServerPrx){
						cout << "You are not in any group" << endl;
					}				
					else 
						groupServerPrx->Leave(userPrx);
				}
				
				if (choice == 4){
					if (!groupServerPrx){
						cout << "You are not in any group" << endl;
					}	
					else{
						users = groupServerPrx->UserList();

						cout << "Users in group " + groupServerPrx->Name() + ":" << endl;
						for (unsigned int i = 0; i < users.size(); i++) {
							cout << users[i]->GetName() << endl;
						}
					}
				}

				if (choice == 5){
					string nameToSendMessage;
					printf("Write user name to send pm:\n");	
					cin >> nameToSendMessage;
					UserPrx userToSendMsg = chatServer->GetUserByName(nameToSendMessage);
					string writeMessage;
					printf("Write message:\n");	
					cin >> writeMessage;
					userToSendMsg->ReceivePrivateText(writeMessage, userPrx);
				}

				if (choice == 6){
					if (!groupServerPrx){
						cout << "You are not in any group" << endl;
					}
					else {
						string writeMessage;
						printf("Write message:\n");	
						cin >> writeMessage;
						groupServerPrx->SendMessage(writeMessage, userPrx);
					}
				}

			}	
		}

		if(choice == 2){
			//exit
		}
	}
 	catch(const Ice::UserException& e){
		cerr << e << endl;		
	}
	catch (const Ice::Exception& ex) {
		cerr << ex << endl;
		status = 1;
	} 
	catch (const char* msg) {
		cerr << msg << endl;
		status = 1;
	}

	if (ic)
		ic->destroy();

	return status;
}
