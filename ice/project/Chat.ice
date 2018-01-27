module Chat {
	interface GroupServer;
	interface GroupServerManager;
	interface User;

	exception NameDoesNotExist{};
	exception NameAlreadyExists{};
	exception ServerAlreadyRegistered{};
	exception ServerDoesNotExist{};
	exception UserAlreadyRegistered{};
	exception UserDoesNotExist{};

	sequence<GroupServer*> Groups;
	sequence<User*> Users; 

	interface ChatServer {
		void LogIn(User* callback) throws NameAlreadyExists;
		User* GetUserByName(string name);
		Groups GroupList();
		GroupServer* GetGroupServerByName(string name) throws NameDoesNotExist;
		void CreateGroup(string name) throws NameAlreadyExists;
		void DeleteGroup(string name) throws NameDoesNotExist;
		void RegisterServer(GroupServerManager* serverManager) throws ServerAlreadyRegistered;
		void UnregisterServer(GroupServerManager* serverManager) throws ServerDoesNotExist;
	};

	interface GroupServer {
		string Name();
		void Join(User* who)  throws UserAlreadyRegistered;
		void Leave(User* who) throws UserDoesNotExist;
		void SendMessage(string message, User* sender) throws UserDoesNotExist;
		Users UserList();
	};

	interface GroupServerManager {
		GroupServer* CreateGroup(string name) throws NameAlreadyExists;
		Groups ListGroups();
		void DeleteGroup(string name) throws NameDoesNotExist;
		GroupServer* GetGroupServerByName(string name);
	};

	interface User {
		string GetName();
		void ReceiveText(string msg, User* sender, GroupServer* gServer);
		void ReceivePrivateText(string msg, User* sender);
	};
};
