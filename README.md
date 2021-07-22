# audacious-plugin-rpc
A Discord Rich Presence plugin for the Audacious music player!

# Usage
1. Download the current release from the [releases page](https://github.com/darktohka/audacious-plugin-rpc/releases).
2. Extract `libaudacious-plugin-rpc.so` into the folder `/usr/lib/audacious/General/`.
3. Open Audacious, go to Settings > Plugins and enable the `Discord RPC` plugin.

# Screenshots
![Screenshot 1](https://i.imgur.com/fmSBkpt.png)
![Screenshot 2](https://i.imgur.com/INHK64d.png)

# Compilation
1. Clone the repository.
2. If encountering compiling issues pass `cmake .. -DCMAKE_INSTALL_PREFIX=<installation path> -DCMAKE_POSITION_INDEPENDENT_CODE=ON` then proceed to next steps.
3. Clone Discord's [discord-rpc](https://github.com/discordapp/discord-rpc) repository.
4. Compile the discord-rpc library using the CMake steps found in the discord-rpc README.
5. Copy `libdiscord-rpc.a` into the `audacious-plugin-rpc` folder.
6. Compile and install the plugin:
```
mkdir build
cd build
cmake ..
make install
```
