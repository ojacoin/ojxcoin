Debian
======

This directory contains files used to package ojxd/ojx-qt
for Debian-based Linux systems. If you compile ojxd/ojx-qt yourself, there are some useful files here.

## ojx: URI support ##

ojx-qt.desktop (Gnome / Open Desktop)

To install:

	sudo desktop-file-install ojx-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your ojx-qt binary to `/usr/bin`
and the `../../share/pixmaps/ojx128.png` to `/usr/share/pixmaps`

ojx-qt.protocol (KDE)