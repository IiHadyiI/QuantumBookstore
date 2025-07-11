#include <iostream>
#include <vector>
#include "User.h"
#include "Admin.h"
class OnlineReaderSystem {
private:
	Inventory inventory;
	UsersManager users_manager;
	SessionManager sessoinManager;

	void LoadDatabase() {
		users_manager.LoadDatabase();
		inventory.LoadDatabase();
	}

public:
	OnlineReaderSystem() :
			inventory(Inventory()), users_manager(UsersManager()),sessoinManager(SessionManager()) {
	}

	~OnlineReaderSystem() {
		cout << "Destuctor: OnlineReaderSystem\n";
	}

	void Run() {	// only public one
		LoadDatabase();

		while (true) {
			users_manager.AccessSystem();	// login/signup

			// Let's make for every user, its own viewer class: Remember: Single responsibility principle
			if (users_manager.GetCurrentUser()->is_library_admin()) {
				Admin view(inventory,users_manager);
				view.admin_menu();
			} else {
				UserView view(users_manager,inventory,sessoinManager);
				view.Display();
			}
		}
	}
};
int main(){
	OnlineReaderSystem sys=OnlineReaderSystem();
	sys.Run();
}	