#include "injector.h"

using namespace std;

int injector::grabproc() {
	DWORD pid;
	HWND hwnd = FindWindowA(0, "Team Fortress 2");
	GetWindowThreadProcessId(hwnd, &pid);
	return pid;
}
bool injector::dllexists(std::string name) {
	std::ifstream exists(name);
	return (bool)exists;
}
void injector::inject(const char* dll, DWORD proc_id,const char* path) {
	HANDLE proc_handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, proc_id);
	if (!proc_handle) {
		cout << "[+] Failed to open handle to process" << endl;
		std::this_thread::sleep_for(5000ms);
		exit(EXIT_FAILURE);
	}
	void* alloc = VirtualAllocEx(proc_handle, NULL, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (!alloc) {
		cout << "[+] Failed to allocate memory" << endl;
		std::this_thread::sleep_for(5000ms);
		exit(EXIT_FAILURE);
	}
	if (!WriteProcessMemory(proc_handle, alloc, (void*)path, strlen(path) + 1, NULL))
	{
		cout << "[+] Failed to write memory to process" << endl;
		std::this_thread::sleep_for(5000ms);
		exit(EXIT_FAILURE);
	}

	HANDLE thread = CreateRemoteThread(proc_handle, 0, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"), "LoadLibraryA"), alloc, 0, 0);

	if (!thread) {
		cout << "[+] Failed to create remote tread" << endl;
		std::this_thread::sleep_for(5000ms);
		exit(EXIT_FAILURE);
	}

	WaitForSingleObject(thread, INFINITE);

	std::this_thread::sleep_for(10000ms);

	CloseHandle(proc_handle);
	VirtualFreeEx(proc_handle, alloc, NULL, MEM_RELEASE);
	cout << "[+] Sucessfully injected.";
	std::this_thread::sleep_for(5000ms);
}