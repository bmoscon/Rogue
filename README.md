# Rogue

A rogue clone, written in C, using NCurses

Because I have had difficulty getting codepage 437 to display in the default
Ubuntu terminal, this uses unicode characters. I've tested it in the Ubuntu 
terminal, and rxvt-unicode. Other terminals may or may not work.

Note: unicode support requires NCursesw!

Linux and OSX are supported, provided the correct libraries are installed. 
On OSX, the macports ncurses library incldues both ncurses and ncursesw, 
so please use that. (On Ubuntu package name is libncursesw5-dev)


This is a work in progress! Is not fully playable!
