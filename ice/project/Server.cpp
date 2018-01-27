#include <Ice/Ice.h>
#include <Chat.h>
#include <ChatServerI.h>
#include <GroupServerI.h>

using namespace std;
using namespace Chat;

int main(int argc, char* argv[]) 
{
	int status = 0;
	Ice::CommunicatorPtr ic;

	try {
		ic = Ice::initialize(argc, argv);
		Ice::ObjectAdapterPtr adapter = ic->createObjectAdapterWithEndpoints("ChatServerAdapter", "default -p 10001");

		Ice::ObjectPtr object = new ChatServerI();
		adapter->add(object, ic->stringToIdentity("ChatServer"));
		adapter->activate();
		ic->waitForShutdown();
	} catch (const Ice::Exception& e) {
		cerr << e << endl;
		status = 1;
	} catch (const char* msg) {
		cerr << msg << endl;
		status = 1;
	}

	if (ic) {
		try {
			ic->destroy();
		} 
		catch (const Ice::Exception& e) {
			cerr << e << endl;
			status = 1;
		}
	}

	return status;
}
