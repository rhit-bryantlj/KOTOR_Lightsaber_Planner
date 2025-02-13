# KOTOR Lightsaber Planner (Command Line)
## Current Build V1.3
### See Devlog for past builds / future development plans

## Description
This is a Lightsaber Planning Console App for BioWare's 2003 Star Wars Knights of the Old Republic. The intention of this app is to create a base to use Qt and create a GUI version once this is a fully fledged working version. If you prefer some fine text in your console, feel free to stick with this.


## To Run
1. Download the code using preferred method (zip, ssh, etc)
2. unzip folder (if downloaded as zip)
3. CD to the top level directory using linux env/c++ build env
4. make all
5. ./main.exe

## Devlog
#### V1.0 Released
#### V1.1 Released
- Updated with option to show equipped crystal locations
- Integrated crystal stats into Lightsaber output
- Added basic Max and Min value checking for Attributes
- Show the Bonus from strength or dex for which stat is higher
- Updated some output to console
- Fixed some typos in Crystals.json
#### V1.2 Released
- Added in Save, Load, and Delete functionality
- Fixed bug causing infinite loop on string/character input
#### V1.3 Released
- Added the ability to equip a second lightsaber
- When second Lightsaber equipped, update options require choice between saber 1 and 2

follow Development at https://www.youtube.com/@logeeman8

### Future Development
- Complete fix to prevent user from going out of bounds on attributes by implementing the 30 point +4 calculation.
- Add in the option to output the current saved build to an excel sheet (ask for input from users)

### Future of this Project
- Create the app in a GUI to be more user friendly
- Use Qt or other framework for C++
- Upload the App to Github for users to download
- Upload to Itch.io, Android, Apple (potentially, theres a fee lmao)

## Future Project
Integrate this into a full character creator with everything that the Lightsaber Builder offers
- saving character builds
- switching armor, weapons, shields, etc
- give a guide on where people can get these items