#include <Ice/Ice.h>
#include <Chat.h>

using namespace Chat;
using namespace std;

class NameDoesNotExist : public Ice::UserException {
	public:
		NameDoesNotExist();
		virtual std::string ice_name() const = 0;
};

class NameAlreadyExists : public Ice::UserException {
	public:
		NameAlreadyExists();
		virtual std::string ice_name() const = 0;
};

class ServerAlreadyRegistered : public Ice::UserException {
	public:
		ServerAlreadyRegistered();
		virtual std::string ice_name() const = 0;
};

class ServerDoesNotExist : public Ice::UserException {
	public:
		ServerDoesNotExist();
		virtual std::string ice_name() const = 0;
};

class UserAlreadyRegistered : public Ice::UserException {
	public:
		UserAlreadyRegistered();
		virtual std::string ice_name() const = 0;
};

class UserDoesNotExist : public Ice::UserException {
	public:
		UserDoesNotExist();
		virtual std::string ice_name() const = 0;
};
