modded class PlayerBase extends ManBase
{
	protected PlayerStat<float> m_FrostResistance;
	
	PlayerStat<float> GetStatFrostResistance()
	{
		if (!m_FrostResistance && GetPlayerStats())
		{
			for (int i = 0; i < 2147483646; i++)
			{
				m_FrostResistance = PlayerStat<float>.Cast(GetPlayerStats().GetStatObject(i));
				if (m_FrostResistance && m_FrostResistance.GetLabel())
				{
					if (m_FrostResistance.GetLabel() == "FrostResistance")
						break;
				}
				m_FrostResistance = null;
			}
		}
		
		return m_FrostResistance;
	}
};