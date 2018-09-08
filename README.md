# audacious-plugin-rpc
A Discord Rich Presence plugin for the Audacious music player!

# Usage
1. Download the current release from the [releases page](https://github.com/darktohka/audacious-plugin-rpc/releases).
2. Extract `libaudacious-plugin-rpc.so` into the folder `/usr/lib/x86_64-linux-gnu/audacious/General`.
3. Open Audacious, go to Settings > Plugins and enable the `Discord RPC` plugin.

# Screenshots
![Screenshot 1](https://i.imgur.com/Epokoo1.png)
![Screenshot 2](https://i.imgur.com/agfdo0Z.png)

# Compilation
1. Clone the repository.
2. Clone Discord's [discord-rpc](https://github.com/discordapp/discord-rpc) repository.
3. Compile the discord-rpc library using the CMake steps found in the discord-rpc README.
4. Copy `libdiscord-rpc.a` into the `audacious-plugin-rpc` folder.
5. Compile and install the plugin:
```mkdir build
cd build
cmake ..
make install
```
