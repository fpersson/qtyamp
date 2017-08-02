# qtyamp

## Status
[![Build Status](https://travis-ci.org/fpersson/qtyamp.svg?branch=master)](https://travis-ci.org/fpersson/qtyamp)

## About.

qtyamp is a mp3 player based qt5 (it's not "cute young tramp" as some people might belive).

It's a simple and primitive mp3 without any fancy functions, but it use a tcpsocket as remotecontrol
and a udp socket to broadcast info about current track to your network. For simplicity use telnet to 
control qtyamp or write your own remotecontrol.

## Usage

telnet 127.0.0.1 1234

Trying 127.0.0.1...

Connected to 127.0.0.1.

Escape character is '^]'.

Welcome to my musicplayer!

Valid commads are start|stop|shuffle|next|prev|gettrack|continue

Enter command:

## Configure
You can find settings.ini in ~/.qtyamp, all settings are not implemented yet
```
[Network]
tcp_port=1234
udp_broadcast=true

[Playlist]
playlist=/path/to/playlist
shuffle=true
volume=75
```

## How to build

**Requirement**

QT 5.5 or later.

**Build:**
* mkdir ./build
* cd build
* cmake .. or cmake ../ -DCMAKE_PREFIX_PATH=/path_to/Qt/5.7/gcc_64/
* cd ..
* make -C build/
