/*
Made by: Erictemponi
*/

#include "ScriptMgr.h"
#include "Config.h"
#include "Guild.h"
#include "GuildMgr.h"

class StartingGuildScript : public PlayerScript
{
    public:
        StartingGuildScript() : PlayerScript("StartingGuildScript") { }

        // called when some player is created
        void OnCreate(Player* pPlayer)
        {
            if (sConfigMgr->GetBoolDefault("StartingGuild.Enable", false))
            {
                uint32 guildID = sConfigMgr->GetIntDefault("StartingGuild.GuildID", 1);
                Guild* targetGuild = sGuildMgr->GetGuildById(guildID);
                if (targetGuild)
                {
                    ObjectGuid playerGuid = pPlayer->GetGUID();
                    // player's guild membership checked in AddMember before add
                    CharacterDatabaseTransaction trans(nullptr);
                    targetGuild->AddMember(trans, playerGuid);
                }
            }
        }
};

void AddSC_starting_guild()
{
    new StartingGuildScript();
}