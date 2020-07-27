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
key: gh0001
---
Here, we'll explain what game hacking is.

## What is Game Hacking?
Game Hacking is finding "Game Logic" flaws (A recent Age of Empires 2 : Definitive Edition patch had a bug that increases ingame resources on spending them xD) or finding other ways to change the behaviour of the game. Although, nobody should cheat while playing games online (could get yourself banned and it also disrupts the community) it can be fun and can teach you many things related to processes, data structures, memory and also game developement. "Game Logic" flaws are exploited by speedrunners whose goals are to complete the game as fast as possible (like completing NFS:MW in 3 hours 41 minutes). Also, many professional hackers have said that they started getting into their profession through hacking games. So, how do we get started in game hacking?

## Getting Started
There are various tools available online for game hacking. You can find books, video tutorials (Guided Hacking, ZeroMemory, LiveOverflow on YouTube), tools and much more on the internet. One of the most used tools is Cheat-Engine (Cheat-Engine is a free software. But be careful while installing it. During installation it will also prompt you to install adware which messes up your browser and is also not easy to remove :( But we can refuse to install the adware and now we are good to go :) ). Cheat-Engine allows us to modify a game's (or any other process's) memory while it is running. Why is modifying memory important? Every ingame property like our player's HP (hit-points), ammo, armour or even the victory condition is stored in the memory. Now if we can modify these properties while the game is running we can do anything. Doing this manually every time can be boring and just useless really :P but we can write scripts to automate this.
![Cheat Engine](https://github.com/CSEA-IITB/IITBreachers-wiki/blob/master/assets/images/gamehacking/cheatengine.png?raw=true)

## Online Games
The above techniques do not work on most online games. This is because the main "Game Logic" runs on a server and modifying these variables locally will not do anything as these are maintained and updated by the server (It may still work if the server updates these variables from the client or the game is peer-to-peer). But this doesn't stop us (again, do not try this in online competitive games. It may ruin another player's experience. This is just for learning and having fun). We can still modify how the game interacts with the client i.e. we can write scripts to do what a normal human player cannot. We can create aim-assists, wall-hacks, movement hacks (We will write some of these in our later posts) for FPS (first person shooter) games and map-reveal and other hacks on RTS (Real Time Strategy) games. This is because all of this data is already present on the client or is dependant on client-interaction.

## Other Techniques
Game Hacking can be as simple as changing memory using Cheat-Engine (or any other tool) to using advanced process injection techniques like DLL injection (Injecting our own dll into the the game's process), DLL hijacking (Load our dll into the game's process instead of the intented one), using Code Caves (Use unused bytes in the game's process' memory to inject our code) or any other technique (Read Game Hacking by Nick Cano for more). We can also patch our game binary to included our hacks.

## Mitigation
To stop these cheats, games and online clients (Steam, Riot, Game-Ranger, Voobly, etc) use Anti-Cheat softwares. These softwares, like Valve Anti-Cheat (VAC), PunkBuster, Vangaurd and others, detect (or atleast try to detect) external programs interfering with the game. Developing these Anti-Cheat softwares is quite challenging as cheaters always find new ways to bypass these softwares and increase their stealth. So the fight between cheaters and anti-cheat developers is always progressing. Game clients and organizations encourage the community (i.e. us) to report cheaters and keep the online gaming environment clean and healthy.<br>

![VAC](https://github.com/CSEA-IITB/IITBreachers-wiki/blob/master/assets/images/gamehacking/vac.png?raw=true)

For more materials on Game Hacking: <br>
[ZeroMemory YouTube Channel](https://www.youtube.com/user/HackVise) <br>
[LiveOverflow Game Hacking Playlist](https://www.youtube.com/playlist?list=PLhixgUqwRTjzzBeFSHXrw9DnQtssdAwgG) <br>
[Guided Hacking YouTube Channel](https://www.youtube.com/user/L4DL4D2EUROPE)
{:.info}