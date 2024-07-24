class KillNotification
{
    static ref KillNotification instance;
    ref map<string, int> playerKills;

    void KillNotification()
    {
        playerKills = new map<string, int>();
        instance = this;
    }

    static KillNotification GetInstance()
    {
        if (!instance)
        {
            instance = new KillNotification();
        }
        return instance;
    }

    void OnPlayerKilled(PlayerBase killer, PlayerBase victim, int damageType, float damage)
    {
        if (!killer || !victim) return;

        string killerName = killer.GetIdentity().GetName();
        if (!playerKills.Contains(killerName))
        {
            playerKills.Set(killerName, 0);
        }

        int kills = playerKills.Get(killerName) + 1;
        playerKills.Set(killerName, kills);

        float distance = vector.Distance(killer.GetPosition(), victim.GetPosition());
        string message;

        if (damageType == DT_HEADSHOT)
        {
            message = "Headshot!";
            if (distance > 100)
            {
                message += string.Format(" (%1 m)", Math.Floor(distance));
            }
        }
        else
        {
            if (distance > 100)
            {
                message = string.Format("%1x Kill (%2 m)", kills, Math.Floor(distance));
            }
            else
            {
                message = string.Format("%1x Kill", kills);
            }
        }

        SendNotification(killer, message);
    }

    void SendNotification(PlayerBase player, string message)
    {
        if (player && player.GetIdentity())
        {
            GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, new Param1<string>(message), true, player.GetIdentity());
        }
    }
}
