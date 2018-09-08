#include <iostream>
#include <string.h>

#include <libaudcore/drct.h>
#include <libaudcore/i18n.h>
#include <libaudcore/plugin.h>
#include <libaudcore/hook.h>
#include <libaudcore/audstrings.h>
#include <libaudcore/tuple.h>

#include "discord_rpc.h"

#define EXPORT __attribute__((visibility("default")))
#define APPLICATION_ID "fill_this"

class RPCPlugin : public GeneralPlugin {

public:
    static constexpr PluginInfo info = {
        N_("Discord RPC"),
        "audacious-plugin-rpc",
        nullptr,
    };

    constexpr RPCPlugin() : GeneralPlugin (info, false) {}

    bool init();
    void cleanup();
};

EXPORT RPCPlugin aud_plugin_instance;

DiscordEventHandlers handlers;
DiscordRichPresence presence;
std::string fullTitle;

void init_discord() {
    memset(&handlers, 0, sizeof(handlers));
    Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);
}

void update_presence() {
    Discord_UpdatePresence(&presence);
}

void init_presence() {
	memset(&presence, 0, sizeof(presence));
	presence.state = "Initialized";
	presence.details = "Waiting...";
	presence.largeImageKey = "logo";
    presence.smallImageKey = "stop";
    update_presence();
}

void cleanup_discord() {
	Discord_ClearPresence();
    Discord_Shutdown();
}

void update_title_presence(void*, void*) {
	if (!aud_drct_get_ready()) {
		return;
	}

	if (aud_drct_get_playing()) {
		bool paused = aud_drct_get_paused();
		Tuple tuple = aud_drct_get_tuple();
		std::string artist(tuple.get_str(Tuple::Artist));
		std::string title(tuple.get_str(Tuple::Title));
		fullTitle = (artist + " - " + title).substr(0, 127);

		presence.details = fullTitle.c_str();
		presence.state = paused ? "Paused" : "Listening";
		presence.smallImageKey = paused ? "pause" : "play";
	} else {
		presence.state = "Stopped";
		presence.smallImageKey = "stop";
	}

	update_presence();
}

bool RPCPlugin::init() {
    init_discord();
    init_presence();
    hook_associate("playback ready", update_title_presence, nullptr);
    hook_associate("playback end", update_title_presence, nullptr);
    hook_associate("playback stop", update_title_presence, nullptr);
    hook_associate("playback pause", update_title_presence, nullptr);
    hook_associate("playback unpause", update_title_presence, nullptr);
    hook_associate("title change", update_title_presence, nullptr);
    return true;
}

void RPCPlugin::cleanup() {
    hook_dissociate("playback ready", update_title_presence);
    hook_dissociate("playback end", update_title_presence);
    hook_dissociate("playback stop", update_title_presence);
    hook_dissociate("playback pause", update_title_presence);
    hook_dissociate("playback unpause", update_title_presence);
    hook_dissociate("title change", update_title_presence);
    cleanup_discord();
}