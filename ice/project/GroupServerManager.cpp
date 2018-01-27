#include <Ice/Ice.h>
#include <Chat.h>
#include <GroupServerManagerI.h>

using namespace std;
using namespace Chat;

int main(int argc, char* argv[]) 
{
	int status = 0;
	Ice::CommunicatorPtr ic;

	try {
		ic = Ice::initialize(argc, argv);
		Ice::ObjectAdapterPtr adapter = ic->createObjectAdapterWithEndpoints("GroupServerManagerAdapter", "default -p 10002");

		Ice::ObjectPtr object = new GroupServerManagerI();
		adapter->add(object, ic->stringToIdentity("GroupServerManager"));
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
