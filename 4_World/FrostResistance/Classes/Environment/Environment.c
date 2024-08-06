modded class Environment
{
	protected float m_FrostResistance;
	
	override void Init(PlayerBase pPlayer)
	{
		super.Init(pPlayer);
		
		m_FrostResistance = 0;
	}
	
	override protected void CollectAndSetPlayerData()
	{
		super.CollectAndSetPlayerData();
		
		m_FrostResistance = m_Player.GetStatFrostResistance().Get();
		
		if (m_HeatComfort < PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_WARNING && m_Player.GetStatFrostResistance().Get() < 1.0)
		{
			float amount = Math.AbsFloat(m_HeatComfort) * 0.01 + m_FrostResistance;
			m_Player.GetStatFrostResistance().Set(amount);
		}
	}
	
	override void ProcessItemsHeat()
	{
		float hcHead, hcBody, hcFeet; //! Heat Comfort
		float hHead, hBody, hFeet; //! Heat from items
		
		float heatComfortAvg;
		float heatAvg;
		
		BodyPartHeatProperties(m_HeadParts, GameConstants.ENVIRO_HEATCOMFORT_HEADPARTS_WEIGHT, hcHead, hHead);
		BodyPartHeatProperties(m_BodyParts, GameConstants.ENVIRO_HEATCOMFORT_BODYPARTS_WEIGHT, hcBody, hBody);
		BodyPartHeatProperties(m_FeetParts, GameConstants.ENVIRO_HEATCOMFORT_FEETPARTS_WEIGHT, hcFeet, hFeet);

		heatComfortAvg = (hcHead + hcBody + hcFeet) / 3;
		heatAvg = (hHead + hBody + hFeet) / 3;
		heatAvg = heatAvg * GameConstants.ENVIRO_ITEM_HEAT_TRANSFER_COEF;
		
		// heat buffer
		float applicableHB = 0.0;
		if (m_UTSAverageTemperature < 0.001)
		{
			applicableHB = m_Player.GetStatHeatBuffer().Get() / 30.0;
			if (applicableHB > 0.0)
			{
				if (m_HeatBufferTimer > 1.0)
				{
					m_Player.GetStatHeatBuffer().Add(Math.Min(EnvTempToCoef(m_EnvironmentTemperature), -0.1) * GameConstants.ENVIRO_PLAYER_HEATBUFFER_DECREASE);
				}
				else
				{
					m_HeatBufferTimer += GameConstants.ENVIRO_PLAYER_HEATBUFFER_TICK;
				}
			}
			else
			{
				m_HeatBufferTimer = 0.0;
			}			
		}
		else
		{
			applicableHB = m_Player.GetStatHeatBuffer().Get() / 30.0;
			if (m_HeatComfort > PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_WARNING)
			{
				m_Player.GetStatHeatBuffer().Add(GameConstants.ENVIRO_PLAYER_HEATBUFFER_INCREASE);
				m_HeatBufferTimer = 0.0;
			}
			else
			{
				m_HeatBufferTimer = 0.0;
			}
		}
		
		m_HeatComfort = (heatComfortAvg + heatAvg + (GetPlayerHeat() / 100)) + EnvTempToCoef(m_EnvironmentTemperature);
		
		if ((m_HeatComfort + applicableHB) < (PlayerConstants.THRESHOLD_HEAT_COMFORT_PLUS_WARNING - 0.01))
		{
			m_HeatComfort += applicableHB;
		}
		else
		{
			if (m_HeatComfort <= (PlayerConstants.THRESHOLD_HEAT_COMFORT_PLUS_WARNING - 0.01))
			{
				m_HeatComfort = PlayerConstants.THRESHOLD_HEAT_COMFORT_PLUS_WARNING - 0.01;
			}
		}
		
		// Frost resistance
		Print("fr: " + m_FrostResistance + ", hc: " + m_HeatComfort);
		m_HeatComfort += m_FrostResistance * 0.2;
		
		if (m_HeatComfort >= PlayerConstants.THRESHOLD_HEAT_COMFORT_PLUS_WARNING)
		{
			m_HeatComfort = PlayerConstants.THRESHOLD_HEAT_COMFORT_PLUS_WARNING - 0.01;
		}
		//
		
		m_HeatComfort = Math.Clamp(m_HeatComfort, m_Player.GetStatHeatComfort().GetMin(), m_Player.GetStatHeatComfort().GetMax());
		
		m_Player.GetStatHeatComfort().Set(m_HeatComfort);
	}
};