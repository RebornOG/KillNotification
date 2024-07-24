modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();
        KillNotification.GetInstance();
    }

    override void OnEntityKilled(EntityAI victim, EntityAI killer, EntityAI tool)
    {
        super.OnEntityKilled(victim, killer, tool);

        if (killer && killer.IsInherited(PlayerBase) && victim && victim.IsInherited(PlayerBase))
        {
            PlayerBase playerKiller = PlayerBase.Cast(killer);
            PlayerBase playerVictim = PlayerBase.Cast(victim);

            int damageType = playerVictim.GetHealth("head", "") <= 0 ? DT_HEADSHOT : DT_DEFAULT;

            KillNotification.GetInstance().OnPlayerKilled(playerKiller, playerVictim, damageType, playerVictim.GetHealth("", ""));
        }
    }
}
