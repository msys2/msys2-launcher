MSYS2 launcher
==============

A helper for launching MSYS2 shells.  Features blink-less launching and correct taskbar/start pinning.

Installation
------------

Just `make` and put the .exe and .ini files inside your MSYS2 root.  Needs mintty v2.1.6 or newer.

Configuration
-------------

All three default launchers are the same (except for embedded icons and descriptions) and are configured by corresponding .ini files.  The .ini file has to be in the same directory as the .exe file and have the same filename (except for the `.exe` -> `.ini` change).

The .ini file contains environment variables, each on a separate line, in the usual `VAR=val` format.  Lines starting with `#` are ignored.  The values are expanded using the current environment (use Windows `%var%` syntax), evaluated from top to bottom.  By default, only `MSYSTEM` is set and the rest is inherited from the outside environment, but some common options are prepared and commented out in the files:

- `MSYS=...`: configures runtime behavior
- `CHERE_INVOKING=1`: prevent the login scripts from changing the working directory to the user's home directory
- `MSYS2_PATH_TYPE=strict|minimal|inherit`: configures how the login scripts set up `PATH`

Pinning
-------

As with many other applications, the correct way to pin a shortcut to the taskbar is by right-clicking the button of a running MSYS2 shell (started by this launcher) on the taskbar and choosing "Pin this program to taskbar".  Pinning the `.exe` file itself won't create the shortcut correctly.  There are tools to diagnose and fix such a situation (7+ Taskbar Tweaker and Win7AppId) in case re-pinning is not preferred.
