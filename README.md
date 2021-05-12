# lemin_viz

careful, has loud music

TLDR:
build it by make, then do one of the following:
./vizuals -h
./vizuals "lem-in output file"
./vizuals -g "lem-in output file"

The file it wants is the whole thing your lem-in produces. Including map printing. Just do something like ./lem-in ... whatever your args are ... > "yes_its_a_map.file", that would be the correct file for visualizer.

 updts: 

- found a random bus error, seems to happen at first launch, will fix some time later, for now just launch it again if it happens.

- fixed invalid resource paths that used to be configured 4 debug mode, now it works properly instead of producing resource-loading error


A playable visualizer for 21/42 lem-in project. It draws a map, recieved as argument and show "ants" movement (hit space for that, if i remember correctly, lol). -g flag will launch it in game mode. Runs on macos, uses SDL2 4 that. U could quite easily make it run on Win/Linux, u'd need appropriate versions of SDL2/SDL2 image to it tho.

Licence is of course WTFPL.

