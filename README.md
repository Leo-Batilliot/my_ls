# my_ls  
## Goal of the project  
Recode the ls command including flags [-lrRadt]  
## Flags  
All of the flags have a unique usage and can be combined together :  
- l : prints additional informations about each file (rights, owner, modification time, name, etc...) 
- r : prints the result in reversed order
- R : recursively goes through each sub directory
- a : shows hidden files
- d : only shows the directory's infos
- t : sort by modification time
## Usage
./my_ls (+any flags or files in any order)  
exemples :  
- ./my_ls  
    will print your current directory
- ./my_ls -Rl lib  
    will print detailed informations about every file inside lib and its subdirectory
