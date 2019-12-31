#pragma once
#include <windows.h>
#include <string>
#include <thread>
#include <libloaderapi.h>
#include <iostream>
#include <fstream>
#include <tlhelp32.h>
#include <stdio.h> 
class injector {
public:
	int grabproc();
	bool dllexists(std::string name);
	static DWORD GetTargetThreadIDFromProcName(const char* ProcName);
	void inject(const char* dll, DWORD proc_id, const char* path);
};