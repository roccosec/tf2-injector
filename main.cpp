#include "injector.h"
#include <iostream>
#include <string>

using namespace std;
injector inj;
const char* const compiled = __DATE__ " @ " __TIME__;

string RandomString(int len)
{
	srand(time(0));
	string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	string newstr;
	int pos;
	while (newstr.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr;
}
 
int main() {
	char path[MAX_PATH];
	DWORD proc_id = NULL;
	char* dll = new char[64];
	SetWindowTextA(GetConsoleWindow(), RandomString(32).c_str());

	cout << "[+] Injector built at: " << compiled << endl;
	cout << "[+] Please input the dll name." << endl;
	cin >> dll;
		if (!inj.dllexists(dll)) {
			cout << "[+] dll " << dll << " does not exist" << endl;
			std::this_thread::sleep_for(5000ms);
			exit(EXIT_FAILURE);
		}
		if (!GetFullPathNameA(dll, MAX_PATH, path, NULL)) {
			cout << "[+] Failed to get full path." << endl;
			std::this_thread::sleep_for(5000ms);
			exit(EXIT_FAILURE);
		}
		proc_id = inj.grabproc();
		if (proc_id == NULL) {
			cout << "[+] Error getting process id" << endl;
			std::this_thread::sleep_for(5000ms);
			exit(EXIT_FAILURE);
		}

		inj.inject(dll, proc_id, path);
		return 0;
	}