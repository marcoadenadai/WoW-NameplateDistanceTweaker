# World of Warcraft v2.4.3 nameplateMaxDistance Tweaker Tool.

Created to change the distance of nameplates since in this client version it is not possible to do so natively (eg: ```/run SetCVar(“nameplateMaxDistance”, “60”)```). 
It works on all private servers that uses the original client, **check your server's usage rules before using this tool.**

This tool uses memory hacking techniques, changing the value of the game's memory address referring to the display distance of the nameplates. **Requires administrative permission.**

Note: The distance measurement unit used here is called yards, but the distance value is an approximation. I recommend trying different values until you find one that fits for you.

## Download
[Latest Releases](https://github.com/marcoadenadai/WoW-NameplateDistanceTweaker/releases)

## Prerequisites for development
- Windows OS (Tested on Windows 10)
- MinGW ([Get Started with C++ and Mingw in Visual Studio Code](https://code.visualstudio.com/docs/cpp/config-mingw))
- msys64, g++, make, windres
- Compile using: ```make```

## Demo
![GUI Tweaking Nameplate Max Distance Image using ElvUI](https://github.com/marcoadenadai/wow-tbc-243-tweaks/raw/main/demo.png)

