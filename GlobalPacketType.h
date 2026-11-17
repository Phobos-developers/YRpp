#pragma once

#include <GeneralStructures.h>
#include <cstddef>

enum class NetCommandType : int
{
	NET_QUERY_GAME,      // Hey, what games are out there?
	NET_ANSWER_GAME,     // Yo, Here's my game's name!
	NET_QUERY_PLAYER,    // Hey, what players are in this game?
	NET_ANSWER_PLAYER,   // Yo, I'm in that game!
	NET_CHAT_ANNOUNCE,   // I'm at the chat screen
	NET_CHAT_REQUEST,    // Respond with a CHAT_ANNOUNCE, please.
	NET_QUERY_JOIN,      // Hey guys, can I play too?
	NET_CONFIRM_JOIN,    // Well, OK, if you really want to.
	NET_REJECT_JOIN,     // No, you can't join; sorry, dude.
	NET_GAME_OPTIONS,    // Hey, dudes, here's some new game options
	NET_SIGN_OFF,        // Bogus, dudes, my boss is coming; I'm outta here!
	NET_GO,              // OK, jump into the game loop!
	NET_MESSAGE,         // Here's a message
	NET_PING,            // I'm pinging you to take a time measurement
	NET_LOADGAME,        // start a game by loading a saved game
	NET_PROGRESS_REPORT, // Report the player's loading progress as a percentage.
	NET_REQ_SCENARIO,    // Reqest that host sends the scenario file to the other players.
	NET_FILE_INFO,       // Info about the file that is going to be transferred
	NET_FILE_CHUNK,      // A chunk of scenario
	NET_READY_TO_GO,     // Sent in response to a 'GO' command
	NET_NO_SCENARIO,     // Scenario isn't available on remote machine so we cant play
	NET_FILE_INFO_ACK,   // Acknowledge file information before receiving the file chunks.
	NET_PLAYER_SLOTS,    // Update the lobby slots, including open, closed and AI slots.
	NET_PUB_GAMEOPT,     // Send the host's shared game options to lobby players.
	NET_PRIV_GAMEOPT,    // Send a player's requested country and color to the host.
	NET_PREVIEW_MODE,    // Ask clients to prepare for a random-map preview transfer.
	NET_PREVIEW_ACK,     // Confirm readiness to receive the random-map preview.
	NET_REQ_PREVIEW,     // Request a random-map preview from the host.
	NET_PROPOSE_KICK,    // Vote to disconnect a player on the reconnect screen.
	NET_TAUNT,           // Play a predefined taunt for the selected recipients.
	NET_UNKNOWN_30,      // No native sender or handler identified.
	NET_UNKNOWN_31,      // No native sender or handler identified.
	NET_PLACE_BEACON,    // Place a player's beacon at the supplied coordinates.
	NET_DELETE_BEACON,   // Remove the specified player beacon.
	NET_EDIT_BEACON,     // Update the text of the specified player beacon.
	NET_COOP_START_ACK,  // Acknowledge preparation for the next cooperative mission.
	NET_COOP_LEAVE,      // Leave the cooperative campaign from the results screen.
	NET_COOP_NOT_READY,  // Clear readiness on the cooperative results screen.
	NET_COOP_READY,      // Set readiness on the cooperative results screen.
	NET_IM_STILL_HERE,   // Keep the connection alive while waiting for other players.
	NET_REQUEST_READY,   // The host asks lobby players to accept so the game can start.
	NET_PORT_PROBE,      // Probe UDP connectivity and discover the peer's translated port.
	NET_DONT_GO,         // Cancel game startup during scenario transfer negotiation.
	NET_MANGLER_REQUEST, // Ask the NAT server how it sees the sender's UDP port.
	NET_MANGLER_RESPONSE,// Return the observed and original UDP ports.
	NET_UNKNOWN_45,      // No native sender or handler identified.
	NET_UNKNOWN_46,      // No native sender or handler identified.
	NET_PORT_UNREACHABLE // Report an unreachable UDP peer.
};

#pragma pack(push, 1)
struct GlobalPacketType
{
	static constexpr unsigned short ProductID = 0xAA04;

	NetCommandType Command;
	char Name[43]; // Player or game name.

	union
	{
		unsigned char DataBuffer[408];

		struct GAME_INFO
		{
			unsigned int IsOpen : 1;
			unsigned int Reserved : 31;
		} GameInfo;

		struct PLAYER_INFO
		{
			int House;
			int Color;
			unsigned int NameCRC;
			unsigned int MinVersion;
			unsigned int MaxVersion;
			int CheatCheck;
			int AICheatCheck;
			int ArtCheatCheck;
			unsigned int BuildNumber;
			int Unknown24;
			int IsSpectator;
		} PlayerInfo;

		struct SCENARIO_INFO
		{
			unsigned char Unknown00[128];
			unsigned int FileLength;
			char ShortFileName[13];
		} ScenarioInfo;

		struct MESSAGE
		{
			unsigned char RecipientMask;
			wchar_t Buf[112];
			int Color;
			unsigned int NameCRC;
		} Message;

		struct RESPONSE_TIME
		{
			int OneWay;
		} ResponseTime;

		struct REJECT
		{
			int Why;
		} Reject;

		struct CHAT
		{
			unsigned int ID;
			int Color;
		} Chat;

		struct OPTIONS
		{
			char Buf[400];
			int Color;
			unsigned int NameCRC;
		} Options;

		struct PROGRESS
		{
			int Percent;
		} Progress;

		struct KICK
		{
			unsigned int KickeeID;
			unsigned int KickerID;
		} Kick;

		struct PLAYER_SLOTS
		{
			wchar_t Buf[204]; // Comma-separated lobby slots, including special slot entries.
		} PlayerSlots;

		struct MANGLER_REQUEST
		{
			unsigned char Unknown00[6];
			unsigned short OriginalPort;
			unsigned char Unknown08; // Boolean request option; purpose not yet identified.
		} ManglerRequest;

		struct MANGLER_RESPONSE
		{
			unsigned short ObservedPort;
			unsigned char Unknown02[4];
			unsigned short OriginalPort;
		} ManglerResponse;

		struct TAUNT
		{
			unsigned char RecipientMask;
			unsigned char Index;
			unsigned char Unknown02[3];
			unsigned int NameCRC;
		} Taunt;

		struct BEACON
		{
			CoordStruct Position;
			signed char BeaconIndex;
			signed char HouseIndex;
		} Beacon;

		struct BEACON_DELETE
		{
			unsigned char Unknown00[12];
			signed char BeaconIndex;
			signed char HouseIndex;
		} BeaconDelete;

		struct BEACON_TEXT
		{
			signed char BeaconIndex;
			signed char HouseIndex;
			wchar_t Message[128];
		} BeaconText;
	};
};
#pragma pack(pop)

static_assert(sizeof(GlobalPacketType) == 455);
static_assert(sizeof(GlobalPacketType::GameInfo) == 4);
