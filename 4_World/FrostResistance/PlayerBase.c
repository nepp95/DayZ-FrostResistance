modded class PlayerBase
{
	protected float m_FrostResistance = 0;
	
	override void OnJumpStart()
	{
		Print("Still printing ts");
	}
	
	override void Init()
	{
		Print("FrostResistance is now active!");
		
		super.Init();
	}
	
    override void OnTick()
    {
		m_FrostResistance += 0.001;
        Print(m_FrostResistance);
		
        super.OnTick();
    }
}