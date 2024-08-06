enum EPlayerStatsExt : EPlayerStats_current
{
	FROSTRESIST = 850000,
};

modded class PlayerStatsPCO_current
{
	override void Init()
	{
		super.Init();
		RegisterStat(EPlayerStatsExt.FROSTRESIST, new PlayerStat<float>(0, 1, 0, "FrostResistance", EPSstatsFlags.EMPTY));
	}
};