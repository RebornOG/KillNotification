class KillNotificationUI
{
    protected TextWidget m_NotificationWidget;
    protected float m_NotificationDuration = 5.0;
    protected float m_TimeElapsed = 0;

    void KillNotificationUI()
    {
        m_NotificationWidget = TextWidget.Cast(GetGame().GetWorkspace().CreateWidgets("YourModPath/layouts/KillNotification.layout"));
        m_NotificationWidget.Show(false);
    }

    void ShowNotification(string message)
    {
        m_NotificationWidget.SetText(message);
        m_NotificationWidget.Show(true);
        m_TimeElapsed = 0;
    }

    void Update(float deltaTime)
    {
        if (m_NotificationWidget.IsVisible())
        {
            m_TimeElapsed += deltaTime;
            if (m_TimeElapsed >= m_NotificationDuration)
            {
                m_NotificationWidget.Show(false);
            }
        }
    }
}

modded class MissionGameplay
{
    protected ref KillNotificationUI m_KillNotificationUI;

    void MissionGameplay()
    {
        m_KillNotificationUI = new KillNotificationUI();
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        if (m_KillNotificationUI)
        {
            m_KillNotificationUI.Update(timeslice);
        }
    }

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, target, rpc_type, ctx);

        if (rpc_type == ERPCs.RPC_USER_ACTION_MESSAGE)
        {
            Param1<string> param;
            if (ctx.Read(param))
            {
                m_KillNotificationUI.ShowNotification(param.param1);
            }
        }
    }
}
