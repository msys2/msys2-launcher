MSYS2 launcher
==============

A helper for launching MSYS2 shells. Features blink-less launching and correct taskbar/start pinning.

Installation
------------

Just `make` and put the .exe and .ini files inside your MSYS2 root. Needs mintty v2.1.6 or newer.

Configuration
-------------

All three default launchers are the same (except for embedded icons and descriptions) and are configured by corresponding .ini files. The .ini file has to be in the same directory as the .exe file and have the same filename (except for the `.exe` -> `.ini` change).

By default, only `MSYSTEM` is set, but options for inheriting `PATH` and tweaking `MSYS` are prepared, as well as `CHERE_INVOKING` for the shell to stay in the current working directory (instead of changing to the home directory).

The .ini file contains environment variables, each on a separate line, in the usual `VAR=val` format. Lines starting with `#` are ignored. The values are expanded using the current environment (use Windows `%var%` syntax).
