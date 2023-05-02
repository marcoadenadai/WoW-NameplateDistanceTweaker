# WoW - World of Warcraft 2.4.3 TBC - Tweaks Tool

Tool to change Nameplate display distance for WoW client version 2.4.3 (The Burning Crusader). It works on all private servers that use the original client, check your server's usage rules before using this tool - in some cases it may result in banning.

This tool uses memory hacking techniques, changing the value of the game's memory address referring to the display distance of the nameplates and therefore requires administrative permission. Part of this code is for generating a manifest to ensure that the compiled output will run with administrator privileges.

Note: The distance measurement unit used here is called yards, but it is important to mention that it is an approximation assuming that the default distance of nampletes is equal to 20 yards in game.

## Prerequisites for development
- Windows OS (Tested on Windows 10)
- MinGW ([Get Started with C++ and Mingw in Visual Studio Code](https://code.visualstudio.com/docs/cpp/config-mingw))

## Demo

![GUI Tweaking Nameplate Max Distance Image using ElvUI](https://github.com/marcoadenadai/wow-tbc-243-tweaks/raw/main/demo.png)