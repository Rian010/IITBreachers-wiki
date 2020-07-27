---
title: Game Hacking
author: Rahul
tags: binary exploitation
aside:
  toc: true
sidebar:
  nav: layouts
mathjax: false
mathjax_autoNumber: false
mermaid: false
chart: false
excerpt_separator: <!--more-->
key: gh0002
---
Here, we'll explain what game hacking is and create a simple script.

## What is Game Hacking?
If you have ever played multi-player games online you may have encountered them. These people will shoot you in the head even before you can see them or be completely invincible (Do not try this, you can get banned :P and it is not good for the community). They use bugs in game logic or write scripts to change game memory however they want. Anyways, game hacking can be a lot of fun and teach you more about process memory and data structures in general.

## How does Game Hacking work?
Let's start with an example. Counter-Strike:Global Offensive is a first person shooter (FPS) game. This game is a 5v5 where one of the goal is to eliminate the enemy team. Being multi-player and the way it is designed, the main "game logic" runs on a central server so we cannot modify game properties as those are maintained by the server. But what we can change is how the client i.e. ourselves interact with the game. We can write aim-assist scripts that automatically place our crosshair on our enemy or movement scripts like bunny-hopping (bunny-hopping or bhopping is a technique to move faster ingame. Bhopping uses continuous jumps while strafing to increase player velocity). Let's write a script for bhopping :)

![CS:GO](https://github.com/CSEA-IITB/IITBreachers-wiki/blob/master/assets/images/gamehacking/csgologo.png?raw=true)

## Analyzing Memory
First we need to find certain data-structures in our game's memory. We can assume that our game has a structure for our current player (say Player1). We need to locate the starting address of Player1 in the process's memory. We can inspect memory using Cheat-Engine and other tools but for now we will find these online (many repositories on github maintain global game offsets). As the game is updated regularly these offsets change but they are constant within an update or patch. Next we find whether our player is on the ground or in the air (OnGround variable inside the Player1 structure). This can be found online aswell. At the time of writing this post it is at `0x100` after the start of our Player1 structure. Player1 is at an offset of `0x00A77D2C` from the start of client.dll which contains the client code of the game.  


## Writing Code
Now we begin to actually writing our script. First we create a class to contain the variables and methods that we need.

```C++

class Game
{
public:
	DWORD ModuleBase;
	HWND window;
	DWORD player;
	DWORD pid;
	HANDLE handle;

	Game(const char* window_title);				//Constructor
	~Game();						//Destructor
	template <typename T> T* Read(DWORD addr);		//ReadProcessMemory template wrapper
	bool OnGroundCheck();					//Check if player is on the ground
	DWORD GetModuleBase(const char* module_name);		//Get base of loaded module (client.dll)

};

````

Next, we need a handle to our game (A handle is an object that we can use to access our game inside our script) and find our module i.e "client.dll" inside its memory. To do that we use the standard Windows API.

```C++

	while (this->window == NULL) 		//Loop till find Game (Game Process may not have started)
	{
		this->window = FindWindow(NULL, window_title);
		if(this->window == NULL)
		{
			cout<<"Error finding window"<<endl;
		}
	}

	//Get PID
	GetWindowThreadProcessId(window, &this->pid);

	//Open process
	this->handle = OpenProcess(PROCESS_VM_READ, 0, (DWORD)this->pid);
	if(this->handle == NULL)
	{
		cout<<"Error opening process"<<endl;
	}

	this->ModuleBase = this->GetModuleBase("client.dll");

DWORD Game::GetModuleBase(const char* module_name)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->pid);
	if(snapshot == INVALID_HANDLE_VALUE)
	{
		cout<<"Error creating snapshot"<<endl;
	}

	MODULEENTRY32 module_entry;
	module_entry.dwSize = sizeof(MODULEENTRY32);
	BYTE* module_base = 0;

	if (snapshot && Module32First(snapshot, &module_entry))
	{
		while (Module32Next(snapshot, &module_entry))
		{
			if (lstrcmpi(module_entry.szModule, (LPCSTR)module_name) == 0)
			{
				module_base = module_entry.modBaseAddr;
				break;
			}
		}
	}

	CloseHandle(snapshot);
	return (DWORD)module_base;
}

```

Thirdly, we write a function to check if our player is on the ground or in the air.

```C++

//Check if player is on ground
bool Game::OnGroundCheck()
{
	UINT16 flag = (UINT16)this->Read<UINT16>(this->player + 0x100);		//OnGround flag at 0x100 from player
	if(flag == 256)
	{
		return FALSE;
	}

	return TRUE;

}

```

Then we keep spamming our jump key to constantly keep jumping. We do this using SendMessage function in the Windows API.

```C++

	while (1)
	{
		CSGO.player = (DWORD)CSGO.Read<DWORD>(CSGO.ModuleBase + 0x00A77D2C);	//Player-Base offset in client.dll
		
		if (GetAsyncKeyState(VK_SPACE) && CSGO.OnGroundCheck())
		{
			SendMessage(CSGO.window, WM_KEYDOWN, VK_SPACE, 0x390000);
			SendMessage(CSGO.window, WM_KEYUP, VK_SPACE, 0x390000);
		}
	}

```

### Putting it all together
Now all that is left, is to combine everything and add few stdout lines for convenience. Our final code looks like this...

```C++

//CSGO bhop script (KEEP SPACE PRESSED) (Compile with -fpermissive to neglect typecasting precision loss)
//Just for fun :P

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

using namespace std;

class Game
{
public:
	DWORD ModuleBase;
	HWND window;
	DWORD player;
	DWORD pid;
	HANDLE handle;

	Game(const char* window_title);						//Constructor
	~Game();										//Destructor
	template <typename T> T* Read(DWORD addr);		//ReadProcessMemory template wrapper
	bool OnGroundCheck();							//Check if player is on the ground
	DWORD GetModuleBase(const char* module_name);	//Get base of loaded module (client.dll)

};

//Constructor
Game::Game(const char* window_title)
{
	while (this->window == NULL) 		//Loop till find Game (Game Process may not have started)
	{
		this->window = FindWindow(NULL, window_title);
		if(this->window == NULL)
		{
			cout<<"Error finding window"<<endl;
		}
	}

	//Get PID
	GetWindowThreadProcessId(window, &this->pid);

	//Open process
	this->handle = OpenProcess(PROCESS_VM_READ, 0, (DWORD)this->pid);
	if(this->handle == NULL)
	{
		cout<<"Error opening process"<<endl;
	}

	this->ModuleBase = this->GetModuleBase("client.dll");

}

//Check if player is on ground
bool Game::OnGroundCheck()
{
	UINT16 flag = (UINT16)this->Read<UINT16>(this->player + 0x100);		//OnGround flag at 0x100 from player
	if(flag == 256)
	{
		return FALSE;
	}

	return TRUE;
}

//ReadProcMem template wrapper
template <typename T>
T* Game::Read(DWORD addr)
{
	T* value;
	ReadProcessMemory(this->handle, (LPVOID)addr, &value, sizeof(T), NULL);
	return value;
}

//Get base of client.dll
DWORD Game::GetModuleBase(const char* module_name)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->pid);
	if(snapshot == INVALID_HANDLE_VALUE)
	{
		cout<<"Error creating snapshot"<<endl;
	}

	MODULEENTRY32 module_entry;
	module_entry.dwSize = sizeof(MODULEENTRY32);
	BYTE* module_base = 0;

	if (snapshot && Module32First(snapshot, &module_entry))
	{
		while (Module32Next(snapshot, &module_entry))
		{
			if (lstrcmpi(module_entry.szModule, (LPCSTR)module_name) == 0)
			{
				module_base = module_entry.modBaseAddr;
				break;
			}
		}
	}

	CloseHandle(snapshot);
	return (DWORD)module_base;
}

//Destructor (Close handle to process)
Game::~Game()
{
	CloseHandle(this->handle);
}

Game CSGO = Game("Counter-Strike: Global Offensive");

int main(void)
{
	cout<< "PID: " <<CSGO.pid<<endl;
	while (1)
	{
		CSGO.player = (DWORD)CSGO.Read<DWORD>(CSGO.ModuleBase + 0x00A77D2C);	//Player-Base offset in client.dll
		
		if (GetAsyncKeyState(VK_SPACE) && CSGO.OnGroundCheck())
		{
			SendMessage(CSGO.window, WM_KEYDOWN, VK_SPACE, 0x390000);
			SendMessage(CSGO.window, WM_KEYUP, VK_SPACE, 0x390000);
		}
	}

	return 0;
}

```

Now we can compile and and run our program along side CS:GO.
Keep the Space (Jump) key pressed to enable our script.

For more materials on Game Hacking: <br>
[ZeroMemory YouTube Channel](https://www.youtube.com/user/HackVise) <br>
[LiveOverflow Game Hacking Playlist](https://www.youtube.com/playlist?list=PLhixgUqwRTjzzBeFSHXrw9DnQtssdAwgG) <br>
[Guided Hacking YouTube Channel](https://www.youtube.com/user/L4DL4D2EUROPE)
{:.info}
