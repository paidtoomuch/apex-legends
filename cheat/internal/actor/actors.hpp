#pragma once
#include <cheat/game/sdk.hpp>
#include <chrono>
#include <thread>
#include <iostream>

using namespace SDK;

/* Declare Player structures */
c_localplayer LocalPlayer;
c_entity Player;

/* Declare SDK classes */
CPlayer		*cPlayer;
CObjects	*cObjects;
CWorld		*cWorld;
CItems		*cItem;

UserCmd *cmdinput;

uintptr_t TargettedPlayer = 0;

inline const int toRead = 15000;
inline float lastvis_aim[toRead];

std::vector<uintptr_t> AimbotTargets;

int index = 0;

c_entity AimbotTarget;

class CAimbot
{
public:
	static uint64_t Target( c_entity Player );
	//static uint64_t FindPlayer();
};

auto cObjectLoop() -> bool
{
	if ( !objectCfg::objects_esp )
		return false;

	for ( int i = 0; i < ENTITY_MAX_COUNT; i++ )
	{
		Object.m_object = cObjects->m_GetObjectList( i );

		if ( !Object.m_object )
			continue;
		//if ( !LocalPlayer.m_entity )
		//	continue;
		Object.m_position = cPlayer->m_iGetPlayerOrigin( Object.m_object );

		float distance = ( int ) ( dist( LocalPlayer.m_position, Object.m_position ) / 39.62 );

		
		if ( distance < objectCfg::renderDistance )
		{
			std::string Classes;
			cPlayer->getClassNameX( Object.m_object, Classes );

			if ( Classes == ( "CZipline" ) )
			{
				if ( objectCfg::ziplines )
				{
					D3DXVECTOR2 ScreenPosition;
					if ( cWorld->WorldToScreen( Object.m_position, &ScreenPosition ) )
					{
						OutlinedText( m_pFont, x( "Zipline" ), ImVec2( ScreenPosition.x, ScreenPosition.y + 5 ), 10, { 255,255,255 , 255 }, true );
					}

				}
			}

			if ( Classes == ( "CDeathBoxProp" ) )
			{
				if ( objectCfg::deathbox )
				{
					*( int * ) ( Object.m_object + 0x3c8 ) = 1;
					*( int * ) ( Object.m_object + 0x3d0 ) = 2;
					*( GlowMode * ) ( Object.m_object + 0x2c4 ) = { 101,101,46,110 };
					*( float * ) ( Object.m_object + 0x1D0 ) = 0.f; // r
					*( float * ) ( Object.m_object + 0x1D4 ) = 15.f; // g
					*( float * ) ( Object.m_object + 0x1D8 ) = 15.f; // b

					D3DXVECTOR2 ScreenPosition;
					if ( cWorld->WorldToScreen( Object.m_position, &ScreenPosition ) )
					{
						OutlinedText( m_pFont, x( "Deathbox" ), ImVec2( ScreenPosition.x, ScreenPosition.y + 5 ), 10, { 255,223,0 , 255 }, true );
					}

				}
			}

			if ( Classes == ( "CBaseGrenade" ) )
			{
				if ( objectCfg::throwables )
				{
					D3DXVECTOR2 ScreenPosition;
					cWorld->WorldToScreen( Object.m_position, &ScreenPosition );

					if ( distance < objectCfg::renderDistance )
					{
						OutlinedText( m_pFont, x( "Explosive" ), ImVec2( ScreenPosition.x, ScreenPosition.y + 5 ), 10, { 255,223,0 , 255 }, true );

						if ( distance < 25 )
						{
							Line( Width - ( Width / 2 ), Height - Height + 540, ScreenPosition.x, ScreenPosition.y + 7, { 255, 223, 0, 255 }, 1 );
							OutlinedText( m_pFont, x( "* WARNING *" ), ImVec2( Width / 2, 250 ), 20, { 255, 0, 0, 255 }, true );
							*( int * ) ( Object.m_object + 0x3c8 ) = 1;
							*( int * ) ( Object.m_object + 0x3d0 ) = 2;
							*( GlowMode * ) ( Object.m_object + 0x2c4 ) = { 101,101,46,110 };
							*( float * ) ( Object.m_object + 0x1D0 ) = 15.f; // r
							*( float * ) ( Object.m_object + 0x1D4 ) = 0.f; // g
							*( float * ) ( Object.m_object + 0x1D8 ) = 0.f; // b
						}
					}

				}
			}

			if ( Classes == ( x( "CPlayerDecoy" ) ) )
			{
				if ( objectCfg::decoycheck )
				{
					D3DXVECTOR2 ScreenPosition;
					cWorld->WorldToScreen( Object.m_position, &ScreenPosition );
					*( int * ) ( Object.m_object + 0x3c8 ) = 1;
					*( int * ) ( Object.m_object + 0x3d0 ) = 2;
					*( GlowMode * ) ( Object.m_object + 0x2c4 ) = { 101,101,46,110 };
					*( float * ) ( Object.m_object + 0x1D0 ) = 15.f; // r
					*( float * ) ( Object.m_object + 0x1D4 ) = 0.f; // g
					*( float * ) ( Object.m_object + 0x1D8 ) = 0.f; // b
					if ( distance < objectCfg::renderDistance )
					{
						OutlinedText( m_pFont, x( "Decoy" ), ImVec2( ScreenPosition.x, ScreenPosition.y + 5 ), 10, { 255,223,0 , 255 }, true );
					}

				}
			}

			if ( Classes == ( x( "CPlayerVehicle" ) ) )
			{
				if ( objectCfg::vehicle )
				{
					D3DXVECTOR2 ScreenPosition;
					cWorld->WorldToScreen( Object.m_position, &ScreenPosition );
					*( int * ) ( Object.m_object + 0x3c8 ) = 1;
					*( int * ) ( Object.m_object + 0x3d0 ) = 2;
					*( GlowMode * ) ( Object.m_object + 0x2c4 ) = { 101,101,46,110 };
					*( float * ) ( Object.m_object + 0x1D0 ) = 15.f; // r
					*( float * ) ( Object.m_object + 0x1D4 ) = 0.f; // g
					*( float * ) ( Object.m_object + 0x1D8 ) = 0.f; // b
					if ( distance < objectCfg::renderDistance )
					{
						OutlinedText( m_pFont, x( "Vehicle" ), ImVec2( ScreenPosition.x, ScreenPosition.y + 5 ), 10, { 54, 176, 82 , 255 }, true );
					}

				}
			}

			if ( Classes == ( x( "CLootRoller" ) ) )
			{
				if ( objectCfg::vault_key_roller )
				{
					D3DXVECTOR2 ScreenPosition;
					cWorld->WorldToScreen( Object.m_position, &ScreenPosition );

					if ( distance < objectCfg::renderDistance )
					{
						int hasVaultKey = *( int * ) ( Object.m_object + 0x16f4 );

						*( int * ) ( Object.m_object + 0x3c8 ) = 1;
						*( int * ) ( Object.m_object + 0x3d0 ) = 2;
						*( GlowMode * ) ( Object.m_object + 0x2c4 ) = { 101,101,46,110 };
						*( float * ) ( Object.m_object + 0x1D0 ) = 15.f; // r
						*( float * ) ( Object.m_object + 0x1D4 ) = 0.f; // g
						*( float * ) ( Object.m_object + 0x1D8 ) = 0.f; // b

						if ( hasVaultKey == 1 )
						{
							OutlinedText( m_pFont, x( "Vault Key" ), ImVec2( ScreenPosition.x, ScreenPosition.y + 5 ), 10, { 255,0,0 , 255 }, true );
						}
					}

				}
			}
		}
	}
	return true;
}

auto cItemLoop() -> bool
{
	if ( !itemCfg::item_esp_enabled )
		return false;

	for ( int i = 0; i < ENTITY_MAX_COUNT; i++ )
	{
		Item.m_index = cObjects->m_GetObjectList( i );

		if ( !Item.m_index )
			continue;
		
		if ( cItem->m_isItem( Item.m_index ) )
		{
			Item.m_id = cItem->m_itemId( Item.m_index );
			Item.m_position = cPlayer->m_iGetPlayerOrigin( Item.m_index );

			itemCfg::heals = itemCfg::selectedTypes[0];
			itemCfg::guns = itemCfg::selectedTypes[1];
			itemCfg::attachment = itemCfg::selectedTypes[2];
			itemCfg::ammo = itemCfg::selectedTypes[3];
			itemCfg::scopes = itemCfg::selectedTypes[4];
			itemCfg::throwables = itemCfg::selectedTypes[5];
			itemCfg::armor = itemCfg::selectedTypes[6];
			itemCfg::evoarmor = itemCfg::selectedTypes[7];
			itemCfg::knockdownshield = itemCfg::selectedTypes[8];
			itemCfg::backpacks = itemCfg::selectedTypes[9];
			itemCfg::helmets = itemCfg::selectedTypes[10];

			itemCfg::rareCheck::common = itemCfg::selectedRarity[0];
			itemCfg::rareCheck::rare = itemCfg::selectedRarity[1];
			itemCfg::rareCheck::epic = itemCfg::selectedRarity[2];
			itemCfg::rareCheck::legendary = itemCfg::selectedRarity[3];
			itemCfg::rareCheck::evo = itemCfg::selectedRarity[4];
			itemCfg::rareCheck::Heirloom = itemCfg::selectedRarity[5];

			cItem->m_iUpdateItem();

			if ( Item.m_type == heal && itemCfg::heals != true or
				Item.m_type == gun && itemCfg::guns != true or
				Item.m_type == attachments && itemCfg::attachment != true or
				Item.m_type == ammo && itemCfg::ammo != true or
				Item.m_type == scopes && itemCfg::scopes != true or
				Item.m_type == throwables && itemCfg::throwables != true or
				Item.m_type == armor && itemCfg::armor != true or
				Item.m_type == evo_armor && itemCfg::evoarmor != true or
				Item.m_type == knockdown_shield && itemCfg::knockdownshield != true or
				Item.m_type == backpack && itemCfg::backpacks != true or
				Item.m_type == helmet && itemCfg::helmets != true)
				continue;

			if ( Item.m_rarity == common && itemCfg::rareCheck::common != true or
				Item.m_rarity == rare && itemCfg::rareCheck::rare != true or
				Item.m_rarity == epic && itemCfg::rareCheck::epic != true or
				Item.m_rarity == legendary && itemCfg::rareCheck::legendary != true or
				Item.m_rarity == evo && itemCfg::rareCheck::evo != true or
				Item.m_rarity == heirloom && itemCfg::rareCheck::Heirloom != true)
				continue;

			RGBA Color;
			Color = { 255, 255, 255, 255 };
			switch ( Item.m_rarity )
			{
				case common:
					Color = { 255, 255, 255, 255 };
					break;
				case rare:
					Color = { 25,25,112, 255 };
					break;
				case epic:
					Color = { 238,130,238, 255 };
					break;
				case legendary:
					Color = { 207,181,59, 255 };
					break;
				case evo:
					Color = { 255,99,71, 255 };
					break;
				case heirloom:
					Color = { 219,112,147, 255 };
					break;


			}
			float distance = ( int ) ( dist( LocalPlayer.m_position, Item.m_position ) / 39.62 );

			D3DXVECTOR2 ScreenPosition;
			if ( distance < itemCfg::renderDistance )
			{

				if ( cWorld->WorldToScreen( Item.m_position, &ScreenPosition ) )
				{
					OutlinedText( m_pFont, Item.m_name, ImVec2( ScreenPosition.x, ScreenPosition.y ), 15.0f, Color, true );
				}
			}
		}
	}
	return true;
}



auto cPlayerLoop() -> bool
{
	LocalPlayer.m_entity = cPlayer->m_GetLocalPlayer();

	float ofov = cfg::fov;
	float nfov = 0;

	for ( int i = 0; i < ENTITY_MAX_COUNT; i++ )
	{

		Player.m_entity = cObjects->m_GetObjectList( i );


		if ( !LocalPlayer.m_entity )
			continue;

		if ( !Player.m_entity )
			continue;

		if ( cPlayer->m_IsPlayer( Player.m_entity ) or cPlayer->m_IsDummy( Player.m_entity ) )
		{

			/* Update all player information */
			if ( Player.m_entity == LocalPlayer.m_entity )
				continue;

			

			Player.m_iHealth = cPlayer->m_iHealth( Player.m_entity );
			Player.m_iMaxHealth = cPlayer->m_iMaxHealth( Player.m_entity );
			Player.m_iShield = cPlayer->m_shieldHealth( Player.m_entity );
			Player.m_iMaxShield = cPlayer->m_shieldHealthMax( Player.m_entity );

			Player.m_isHologram = cPlayer->m_isHologram( Player.m_entity );
			Player.m_lifestate = cPlayer->m_lifeState( Player.m_entity );
			Player.m_position = cPlayer->m_iGetPlayerOrigin( Player.m_entity );
			Player.m_headposition = cPlayer->m_GetBonePositon( Player.m_entity, Player.m_position, 8 );
			Player.m_camera_position = cPlayer->m_iGetInGameCameraPosition( Player.m_entity );
			Player.m_team = cPlayer->m_iTeamNum( Player.m_entity );
			Player.m_view_angle = cPlayer->m_iGetPlayerViewAngle( Player.m_entity );

			LocalPlayer.m_iHealth = cPlayer->m_iHealth( LocalPlayer.m_entity );
			LocalPlayer.m_iMaxHealth = cPlayer->m_iMaxHealth( LocalPlayer.m_entity );
			LocalPlayer.m_iShield = cPlayer->m_shieldHealth( LocalPlayer.m_entity );
			LocalPlayer.m_iMaxShield = cPlayer->m_shieldHealthMax( LocalPlayer.m_entity );

			LocalPlayer.m_position = cPlayer->m_iGetPlayerOrigin( LocalPlayer.m_entity );
			LocalPlayer.m_camera_position = cPlayer->m_iGetInGameCameraPosition( LocalPlayer.m_entity );
			LocalPlayer.m_team = cPlayer->m_iTeamNum( LocalPlayer.m_entity );
			LocalPlayer.m_view_angle = cPlayer->m_iGetPlayerViewAngle( LocalPlayer.m_entity );
			LocalPlayer.m_headposition = cPlayer->m_GetBonePositon( LocalPlayer.m_entity, LocalPlayer.m_position, 8 );

			if ( Player.m_team == LocalPlayer.m_team )
				continue;

			index = i;

			float distance = ( int ) ( dist( LocalPlayer.m_position, Player.m_position ) / 39.62 );
			pkRadar( Player.m_position, LocalPlayer.m_position, LocalPlayer.m_view_angle.y, distance );


			if ( Player.m_entity && cPlayer->m_iHealth( Player.m_entity ) > 0 )
			{
				D3DXVECTOR3 OriginPosition = cPlayer->m_iGetPlayerOrigin( Player.m_entity );
				auto HeadPosition = cPlayer->m_GetBonePositon( Player.m_entity, OriginPosition, 8 );

				if ( HeadPosition != D3DXVECTOR3( 0, 0, 0 ) )
				{
					nfov = cWorld->ScreenToEnemy( HeadPosition );
					if ( nfov == 0 )
						continue;

					if ( nfov < ofov )
					{
						ofov = nfov;
						AimbotTarget = Player;

					}
				}
			}

			if ( LocalPlayer.m_entity && LocalPlayer.m_iHealth != 0 )
			{
				if ( cfg::skydivespeed )
				{
					bool isDiving = *( bool * ) ( LocalPlayer.m_entity + 0x4550 );
					if ( isDiving )
					{
						OutlinedText( esp_pFont, x( "Diving" ), ImVec2( Width / 2, 150 ), 20, { 255,0,0 , 255 }, true );

						Write<float>( LocalPlayer.m_entity + 0x4554, cfg::skydive_speed );
					}
				}

				if ( cfg::skin_changer )
				{
					if ( LocalPlayer.m_iHealth != 0 )
					{
						*( int * ) ( cPlayer->ActiveWeapon( LocalPlayer.m_entity ) + 0x0ea8 ) = cfg::weapon_skin;
						*( int * ) ( LocalPlayer.m_entity + 0x0ea8 ) = cfg::player_skin;
						*( int * ) ( LocalPlayer.m_entity + 0x0eb0 ) = cfg::player_body;
					}

				}

				if ( cfg::third_person )
				{
					*( int * ) ( BaseAddress + 0x01958bd0 + 0x6c ) = 2;

				}
				else
				{
					*( int * ) ( BaseAddress + 0x01958bd0 + 0x6c ) = -1;
				}
			}
			//*( float * ) ( 0x01238798 + 0xac0 ) = 120.0f;

			D3DXVECTOR2 ScreenPosition;
			D3DXVECTOR2 ScreenHeadPosition;


			if ( distance < cfg::esp_distance )
			{
				if ( cWorld->WorldToScreen( Player.m_position, &ScreenPosition ) )
				{
					if ( cWorld->WorldToScreen( Player.m_headposition, &ScreenHeadPosition ) )
					{
						float BoxHeight = ScreenHeadPosition.y - ScreenPosition.y;
						float BoxWidth = ( BoxHeight / 2 ) * 1.2f;
						D3DXVECTOR2 screened_left = ScreenPosition - D3DXVECTOR2( BoxWidth / 2, 0 );

						if ( cfg::esp_enabled )
						{
							if ( cfg::distance )
							{

								std::string Text = x( "[" ) + std::to_string( distance ) + x( "m]" );

								std::string s = x( ".000000" );

								std::string::size_type i = Text.find( s );

								if ( i != std::string::npos )
									Text.erase( i, s.length() );

								ImVec2 DistanceTextSize = ImGui::CalcTextSize( Text.c_str() );

								OutlinedText( m_pFont, Text, ImVec2( ScreenPosition.x, ScreenPosition.y + 5 ), 10, { 54, 175, 173 , 255 }, true );

							}



							if ( cfg::name )
							{
								std::string Name;

								//if ( Player.m_lifestate > 0 )
								//	Name = "Dead";
								//else
								//	Name = "Alive";

								if ( cPlayer->m_IsDummy( Player.m_entity ) )
									Name = x( "Dummy" );
								else
									Name = cPlayer->m_iuserName( Player.m_entity );

								ImVec2 PlayerTextSize = ImGui::CalcTextSize( Name.c_str() );


								OutlinedText( m_pFont, Name, ImVec2( ScreenHeadPosition.x, ScreenHeadPosition.y - 15 ), 10, { 255, 255, 255, 255 }, true );
							}


							if ( cfg::health )
							{
								HealthBar( Player.m_iHealth, screened_left.x + ( BoxHeight / 1.2 ), screened_left.y, BoxHeight );
							}

							if ( cfg::shield )
							{
								Shieldbar( Player.m_iShield, Player.m_iMaxShield, screened_left.x + ( BoxHeight / 1.1f ), screened_left.y, BoxHeight );
							}

							if ( cfg::chams )
							{
								*( int * ) ( Player.m_entity + 0x3c8 ) = cfg::chams;
								*( int * ) ( Player.m_entity + 0x3d0 ) = 2;
								*( GlowMode * ) ( Player.m_entity + 0x2c4 ) = { 101,101,46,110 };
								*( float * ) ( Player.m_entity + 0x1D0 ) = 0.f; // r
								*( float * ) ( Player.m_entity + 0x1D4 ) = 15.f; // g
								*( float * ) ( Player.m_entity + 0x1D8 ) = 15.f; // b
							}
							else
							{
								*( int * ) ( Player.m_entity + 0x3c8 ) = cfg::chams;
								*( int * ) ( Player.m_entity + 0x3d0 ) = 0;
								*( GlowMode * ) ( Player.m_entity + 0x2c4 ) = { 101,101,46,110 };
								*( float * ) ( Player.m_entity + 0x1D0 ) = 0.f; // r
								*( float * ) ( Player.m_entity + 0x1D4 ) = 0.f; // g
								*( float * ) ( Player.m_entity + 0x1D8 ) = 0.f; // b
							}


							if ( cfg::box )
							{
								if ( Player.m_lifestate == 0 )
								{
									RGBA Color;

									if ( ( cPlayer->lastVisTime( Player.m_entity ) > lastvis_aim[index] ) )
										Color = { 255, 255 , 255, 255 };
									else
										Color = { 54, 175, 173, 255 };

									CornerBox( ScreenPosition.x, ScreenPosition.y, BoxWidth, BoxHeight, 2, Color );
									lastvis_aim[index] = cPlayer->lastVisTime( Player.m_entity );
								}
							}
						}
					}
				}
			}
		}
	}
	if ( AimbotTarget.m_entity )
	{
		float distance = ( int ) ( dist( LocalPlayer.m_position, AimbotTarget.m_position ) / 39.62 );

		if ( distance < cfg::esp_distance )
		{
			CAimbot::Target( AimbotTarget );
		}
	}
	AimbotTarget.m_entity = 0;
	index = 0;
	return true;
}

D3DXVECTOR2 oldPunch = { 0.f, 0.f};


uint64_t CAimbot::Target( c_entity Player)
{
	D3DXVECTOR2 ScreenPosition;
	//uintptr_t Target = Aimbot.m_entity;

	if ( cfg::silentaim )
	{
		cfg::third_person = true;
	}

	if ( Player.m_entity)
	{

		if ( Player.m_team != LocalPlayer.m_team )
		{
			

			if ( cfg::aimbot_enabled )
			{
				srand( time( 0 ) );

				int random;
				random = rand() % 10 + 1;
				D3DXVECTOR3 HeadPosition = cPlayer->m_GetBonePositon( Player.m_entity, Player.m_position, random );

				int oldHealth = Player.m_iHealth;
				int oldShield = Player.m_iShield;

				float BulletSpeed = cPlayer->BulletSpeed( cPlayer->ActiveWeapon( LocalPlayer.m_entity ) );
				float BulletGravity = cPlayer->BulletGravity( cPlayer->ActiveWeapon( LocalPlayer.m_entity ) );


				D3DXVECTOR2 CalculatedAngles;


				float VerticalTime = Dist3D( HeadPosition, LocalPlayer.m_camera_position ) / BulletSpeed;
				HeadPosition.z += ( 750.f * cPlayer->BulletGravity( cPlayer->ActiveWeapon( LocalPlayer.m_entity ) ) * 0.5f ) * ( VerticalTime * VerticalTime );

				float HorizontalTime = Dist3D( HeadPosition, LocalPlayer.m_camera_position ) / BulletSpeed;
				HeadPosition += ( cPlayer->AbsVelocity( Player.m_entity ) * HorizontalTime );

				CalculatedAngles = cWorld->CalculateAngles( LocalPlayer.m_camera_position, HeadPosition );
				D3DXVECTOR2 ScreenPosition;

				cWorld->NormalizeAngles( CalculatedAngles );

				if ( cWorld->WorldToScreen( cPlayer->m_GetBonePositon( Player.m_entity, Player.m_position, 2 ), &ScreenPosition ) )
				{
					Line( Width - ( Width / 2 ), Height - Height + 540, ScreenPosition.x, ScreenPosition.y + 7, { 255, 223, 0, 255 }, 1 );
				}

				auto AimbotKey = VK_RBUTTON;

	/*			if ( cfg::silentaim )
				{
					AimbotKey = VK_LBUTTON;
				}*/
			
				if ( GetAsyncKeyState( AimbotKey ) & 0x8000 )
				{

					//if ( cfg::no_recoil )
					//{
					//	CalculatedAngles -= cPlayer->PunchAngle( LocalPlayer.m_entity );
					//	CalculatedAngles -= ( ( cPlayer->BreathAngles( LocalPlayer.m_entity ) - cPlayer->PunchAngle( LocalPlayer.m_entity ) ) - LocalPlayer.m_view_angle );
					//}
					D3DXVECTOR2 oldAngle = Read<D3DXVECTOR2>( LocalPlayer.m_entity + 0x2568 );
					D3DXVECTOR2 punchAngle = Read<D3DXVECTOR2>( LocalPlayer.m_entity + 0x2480 );
					D3DXVECTOR2 breathAngle = Read<D3DXVECTOR2>( LocalPlayer.m_entity + ( 0x2568 - 0x10 ) );

					CalculatedAngles -= breathAngle * ( cfg::rcsIntensity / 100.f );
					CalculatedAngles -= ( punchAngle * 0.05f ) * ( cfg::rcsIntensity / 100.f );
					CalculatedAngles += oldAngle * ( cfg::rcsIntensity / 100.f );
					oldPunch = punchAngle; // do this so the rcs doesnt jump down after unlocking from the enemy

					cWorld->NormalizeAngles( CalculatedAngles );

					D3DXVECTOR2 Delta = CalculatedAngles - LocalPlayer.m_view_angle;

					cWorld->NormalizeAngles( Delta );

					D3DXVECTOR2 SmoothedAngles = LocalPlayer.m_view_angle + Delta / ( cfg::smoothness );

					cWorld->NormalizeAngles( SmoothedAngles );

					if ( cfg::aimbotvischeck )
					{
						if ( ( cPlayer->lastVisTime( Player.m_entity ) > lastvis_aim[index] ) )
						{
							if ( SmoothedAngles != D3DXVECTOR2( 0, 0 ) )
							{
								*( D3DXVECTOR2 * ) ( LocalPlayer.m_entity + 0x2568 ) = SmoothedAngles;
							}
						}
					}
					else
					{
						if ( SmoothedAngles != D3DXVECTOR2( 0, 0 ) )
						{
							*( D3DXVECTOR2 * ) ( LocalPlayer.m_entity + 0x2568 ) = SmoothedAngles;
						}
					}
					lastvis_aim[index] = cPlayer->lastVisTime( Player.m_entity );

					return true;
				}
				
			}
		}
	}
	return false;
}

void  __stdcall CreateMoveHk( CInput *pInput, int sequence_number, float input_sample_frametime, bool active )
{
	utility *utilties {};
	CPlayer *c_player {};

	utilties->call( OLD_CreateMove, pInput, sequence_number, input_sample_frametime, active );
	auto getChecksum( ( __int64 *( __thiscall * )( void * ) )( checksum ) );


	if ( sequence_number == -1 ) return;

	//std::cout << "passed sequence number" << std::endl;
	CUserCmd *pCMD = reinterpret_cast< CUserCmd* >( ( reinterpret_cast< std::uintptr_t * >( pInput ) + 31 ) + 0x280 * ( sequence_number % 750 ) );

//	get cmd's
	if ( !pCMD || pCMD->command_number == NULL )
	{
		//std::cout << "cmd invalid" << std::endl;
		return;
	}
	//std::cout << "cmd is valid" << std::endl;
	CInput::CVerifiedUserCmd *VerefCmd = ( CInput::CVerifiedUserCmd * ) ( ( pInput + 31 ) + 0x280 * ( sequence_number % 750 ) );
	if ( !VerefCmd)
	{
		//std::cout << "cmd invalid" << std::endl;
		return;
	}

	std::cout << "X: " << pCMD->viewangles.x << "  Y: " << pCMD->viewangles.y << std::endl;

	VerefCmd->m_cmd = *pCMD;
	VerefCmd->m_crc = ( CRC32_t )utilties->call( getChecksum, ( void * ) pCMD );

	//CurCmd = ( UserCmd * ) ( *( DWORD64 * ) ( pInput + 0xF8 ) + 0x1E8 * ( sequence_number % 750 ) );



	//return utilties->call( OLD_CreateMove, pInput, sequence_number, input_sample_frametime, active );
}
