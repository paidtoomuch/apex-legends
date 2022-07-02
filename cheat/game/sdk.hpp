#include <Windows.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <Psapi.h>
#include <d3d11.h>
#include <vector>
#include <Math.h>
#include <cheat/internal/updater/updater.hpp>
#include <map>

utility *utilities { };

D3DXMATRIX ViewMatrix;


uintptr_t client_render_targets = 0x1ef9430;
uintptr_t ibase_client_dll = 0x195a460;
uintptr_t iclient_entity_list = 0x1ef8c38;
uintptr_t cprediction = 0x1ef8c40;
uintptr_t iv_model_render = 0x1238660;
uintptr_t vgui_system = 0x1eb2f70;
uintptr_t iv_render_view = 0x7430230;
uintptr_t iv_debug_overlay = 0x74cb438;
uintptr_t iv_model_info_client = 0x7430240;
uintptr_t iv_engine_client = 0x0;
uintptr_t iv_engine_trace = 0x7430248;
uintptr_t inetwork_string_table = 0x7430258;
uintptr_t cnetwork_u64_table = 0x742da18;
uintptr_t cinput = 0x1d0c600;
uintptr_t cengine = 0x123f780;
uintptr_t iswapchain = 0xb84b068;
uintptr_t cl_entitylist = 0x1973ad8;
uintptr_t local_entity_handle = 0x123208c;
uintptr_t local_player = 0x1d233d8;
uintptr_t global_vars = 0x1308840;
uintptr_t name_list = 0xb9305d0;
uintptr_t view_render = 0x7430238;
uintptr_t view_matrix = 0x10e8d0;
uintptr_t client_state = 0x1308b30;
uintptr_t sign_on_state = 0x1308bc8;
uintptr_t level_name = 0x1308ce0;
uintptr_t glow_enable = 0x3c8;
uintptr_t glow_type = 0x2c0;
uintptr_t glow_color = 0x1d0;


namespace SDK
{

	/*
		Apex Legends SDK by NASM
	*/

	struct c_localplayer
	{
		uint64_t		m_entity;
		std::string		m_name;

		int				m_iHealth;
		int				m_iMaxHealth;

		int				m_iShield;
		int				m_iMaxShield;

		D3DXVECTOR3		m_position;
		D3DXVECTOR3		m_camera_position;
		D3DXVECTOR2		m_view_angle;
		D3DXVECTOR3		m_headposition;

		int				m_team;
	};



	enum rarity : int
	{
		empty,
		common,
		rare,
		epic,
		legendary,
		evo,
		heirloom
	};


	enum type : int
	{
		any,
		heal,
		gun,
		attachments,
		ammo,
		scopes,
		throwables,
		armor,
		evo_armor,
		knockdown_shield,
		backpack,
		helmet
	};

	struct c_object
	{

		uint64_t		m_object;
		int				m_id;
		std::string		m_name;
		float			m_distance;

		D3DXVECTOR3     m_position;
	}Object;

	struct c_item
	{

		uint64_t		m_index;
		int				m_id;
		std::string		m_name;
		float			m_distance;
		rarity			m_rarity;
		type			m_type;
		bool			m_isvalid;

		D3DXVECTOR3     m_position;
	}Item;



	struct c_entity
	{
		uint64_t		m_entity;
		std::string		m_name;

		int				m_iHealth;
		int				m_iMaxHealth;

		int				m_iShield;
		int				m_iMaxShield;

		bool			m_isVisible;

		int       		m_team;
		int				m_lifestate;
		int				m_isHologram;

		D3DXVECTOR3		m_position;
		D3DXVECTOR3		m_camera_position;
		D3DXVECTOR3		m_headposition;
		D3DXVECTOR2		m_view_angle;

		int				newHealth;
	};

	struct GlowMode
	{
		int8_t GeneralGlowMode, // 0x0
			BorderGlowMode, // 0x8
			BorderSize, // 0x10
			TransparentLevel; // 0x18
	};

	template <typename T>
	class CProp
	{
		std::string m_Name;
		rarity		m_Rarity;
		type		m_Type;
	};

	class CItems
	{
	public:
		auto m_isItem( uintptr_t object )
		{
			return *( int *) ( object + 0x2c0 ) >= 1358917120;
		}

		auto m_itemId( uintptr_t object )
		{
			return *( int * ) ( object + 0x1698 );
		}

		auto m_iUpdateItem()
		{
			/* Throwables */
			switch ( Item.m_id )
			{


				case 188:

					Item.m_name = ( "Thermite" );
					Item.m_rarity = common;
					Item.m_type = throwables;
					return; break;

				case  189:

					Item.m_name = ( "Grenade" );
					Item.m_rarity = common;
					Item.m_type = throwables;
					return; break;

				case  190:

					Item.m_name = ( "Arc Star" );
					Item.m_rarity = common;
					Item.m_type = throwables;
					return; break;

					/* Shotguns */
				case  84:

					Item.m_name = ( "Mozambique" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

				case  79:

					Item.m_name = ( "Peacekeeper" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

				case  74:

					Item.m_name = ( "EVA-8 Auto" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

				case  2:

					Item.m_name = ( "Mastelse iff" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

					/* Heirloom Guns */
				case  68:

					Item.m_name = ( "M600 Spitfire" );
					Item.m_rarity = heirloom;
					Item.m_type = gun;
					return; break;

				case  42:

					Item.m_name = ( "Alternator" );
					Item.m_rarity = heirloom;
					Item.m_type = gun;
					return; break;

				case  37:

					Item.m_name = ( "G7 Scout" );
					Item.m_rarity = heirloom;
					Item.m_type = gun;
					return; break;

				case  1:

					Item.m_name = ( "Kraber .50-Cal" );
					Item.m_rarity = heirloom;
					Item.m_type = gun;
					return; break;

					/* Bow */
				case  109:

					Item.m_name = ( "Bow" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

					/* Ammo */
				case  125:

					Item.m_name = ( "Arrows" );
					Item.m_rarity = common;
					Item.m_type = ammo;
					return; break;

				case  122:

					Item.m_name = ( "Shotgun Shells" );
					Item.m_rarity = common;
					Item.m_type = ammo;
					return; break;

				case  121:

					Item.m_name = ( "Energy" );
					Item.m_rarity = common;
					Item.m_type = ammo;
					return; break;

				case  123:

					Item.m_name = ( "Heavy" );
					Item.m_rarity = common;
					Item.m_type = ammo;
					return; break;

				case  120:

					Item.m_name = ( "Light" );
					Item.m_rarity = common;
					Item.m_type = ammo;
					return; break;

				case  124:

					Item.m_name = ( "Sniper Ammo" );
					Item.m_rarity = common;
					Item.m_type = ammo;
					return; break;

					/* Energy Guns */
				case  53:

					Item.m_name = ( "Volt SMG" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

				case  22:

					Item.m_name = ( "Triple Take" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

				case  17:

					Item.m_name = ( "Devotion" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

				case  12:

					Item.m_name = ( "Havoc" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

				case  7:

					Item.m_name = ( "L-STAR" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

					/* Knockdown Shield */
				case  183:

					Item.m_name = ( "Knockdown Shield" );
					Item.m_rarity = legendary;
					Item.m_type = knockdown_shield;
					return; break;

				case  182:

					Item.m_name = ( "Knockdown Shield" );
					Item.m_rarity = epic;
					Item.m_type = knockdown_shield;
					return; break;

				case  181:

					Item.m_name = ( "Knockdown Shield" );
					Item.m_rarity = rare;
					Item.m_type = knockdown_shield;
					return; break;

				case  180:

					Item.m_name = ( "Knockdown Shield" );
					Item.m_rarity = common;
					Item.m_type = knockdown_shield;
					return; break;

					/* backpacks */
				case  187:

					Item.m_name = ( "Backpack" );
					Item.m_rarity = legendary;
					Item.m_type = backpack;
					return; break;

				case  186:

					Item.m_name = ( "Backpack" );
					Item.m_rarity = epic;
					Item.m_type = backpack;
					return; break;

				case  185:

					Item.m_name = ( "Backpack" );
					Item.m_rarity = rare;
					Item.m_type = backpack;
					return; break;

				case  184:

					Item.m_name = ( "Backpack" );
					Item.m_rarity = common;
					Item.m_type = backpack;
					return; break;

					/* Helmet */
				case  169:

					Item.m_name = ( "Helmet" );
					Item.m_rarity = legendary;
					Item.m_type = helmet;
					return; break;

				case  168:

					Item.m_name = ( "Helmet" );
					Item.m_rarity = epic;
					Item.m_type = helmet;
					return; break;

				case  167:

					Item.m_name = ( "Helmet" );
					Item.m_rarity = rare;
					Item.m_type = helmet;
					return; break;

				case  166:

					Item.m_name = ( "Helmet" );
					Item.m_rarity = common;
					Item.m_type = helmet;
					return; break;

					/* Evo Armor */
				case  178:

					Item.m_name = ( "Evo Armor" );
					Item.m_rarity = evo;
					Item.m_type = evo_armor;
					return; break;

				case  177:

					Item.m_name = ( "Evo Armor" );
					Item.m_rarity = epic;
					Item.m_type = evo_armor;
					return; break;

				case  176:

					Item.m_name = ( "Evo Armor" );
					Item.m_rarity = rare;
					Item.m_type = evo_armor;
					return; break;

				case  175:

					Item.m_name = ( "Evo Armor" );
					Item.m_rarity = common;
					Item.m_type = evo_armor;
					return; break;

					/* Armor */

				case  173:

					Item.m_name = ( "Armor" );
					Item.m_rarity = legendary;
					Item.m_type = armor;
					return; break;

				case  172:

					Item.m_name = ( "Armor" );
					Item.m_rarity = epic;
					Item.m_type = armor;
					return; break;

				case  171:

					Item.m_name = ( "Armor" );
					Item.m_rarity = rare;
					Item.m_type = armor;
					return; break;

				case  170:

					Item.m_name = ( "Armor" );
					Item.m_rarity = common;
					Item.m_type = armor;
					return; break;

					/* Health */

				case  160:

					Item.m_name = ( "Ultimate Accelerant" );
					Item.m_rarity = rare;
					Item.m_type = heal;
					return; break;

				case  161:

					Item.m_name = ( "Phoenix Kit" );
					Item.m_rarity = epic;
					Item.m_type = heal;
					return; break;

				case  162:

					Item.m_name = ( "Medkit" );
					Item.m_rarity = rare;
					Item.m_type = heal;
					return; break;

				case  163:

					Item.m_name = ( "Syringe" );
					Item.m_rarity = common;
					Item.m_type = heal;
					return; break;

				case  164:

					Item.m_name = ( "Shield Battery" );
					Item.m_rarity = rare;
					Item.m_type = heal;
					return; break;

				case  165:

					Item.m_name = ( "Shield Cell" );
					Item.m_rarity = common;
					Item.m_type = heal;
					return; break;

					/* Heavy round guns */
				case  131:

					Item.m_name = ( "C.A.R SMG" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

				case  126:

					Item.m_name = ( "Rampage LMG" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

				case  114:

					Item.m_name = ( "30-30 Repeater" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

				case  89:

					Item.m_name = ( "Wingman" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

				case  48:

					Item.m_name = ( "Prowler Burst PDW" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

				case  32:

					Item.m_name = ( "Hemlok" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

				case  27:

					Item.m_name = ( "VK-47 Flatline" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

					/* Light Ammo guns */
				case  99:

					Item.m_name = ( "RE-45" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

				case  94:

					Item.m_name = ( "P2020" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

				case  69:

					Item.m_name = ( "R-301 Carbine" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

				case  43:

					Item.m_name = ( "R-99 SMG" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

					/* Sniper guns */
				case  104:

					Item.m_name = ( "Sentinel" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

				case  63:

					Item.m_name = ( "Charge Relse ifle" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

				case  58:

					Item.m_name = ( "Longbow DMR" );
					Item.m_rarity = common;
					Item.m_type = gun;
					return; break;

					/* Scopes */
				case  191:

					Item.m_name = ( "1 HCOG Classic" );
					Item.m_rarity = common;
					Item.m_type = scopes;
					return; break;

				case  192:

					Item.m_name = ( "2 HCOG Bruiser" );
					Item.m_rarity = rare;
					Item.m_type = scopes;
					return; break;

				case  193:

					Item.m_name = ( "1 Holo" );
					Item.m_rarity = common;
					Item.m_type = scopes;
					return; break;

				case  194:

					Item.m_name = ( "1-2 Variable Holo" );
					Item.m_rarity = rare;
					Item.m_type = scopes;
					return; break;

				case  195:

					Item.m_name = ( "1 Digital Thread" );
					Item.m_rarity = legendary;
					Item.m_type = scopes;
					return; break;

				case  196:

					Item.m_name = ( "3 HCOG Ranger" );
					Item.m_rarity = epic;
					Item.m_type = scopes;
					return; break;

				case  119:

					Item.m_name = ( "Dual Shell" );
					Item.m_rarity = epic;
					Item.m_type = attachments;
					return; break;

				case  241:

					Item.m_name = ( "Shatter Caps" );
					Item.m_rarity = epic;
					Item.m_type = attachments;
					return; break;

				case  239:

					Item.m_name = ( "Deadeye's Tempo" );
					Item.m_rarity = epic;
					Item.m_type = attachments;
					return; break;


				case -1:
					Item.m_rarity = empty;
					break;
			}

			Item.m_rarity = empty;
		}
	};
	__forceinline float Dist3D( const D3DXVECTOR3 &Src, const D3DXVECTOR3 &Dst )
	{
		return sqrtf( powf( Src.x - Dst.x, 2.f ) + powf( Src.y - Dst.y, 2.f ) + powf( Src.z - Dst.z, 2.f ) );
	}
	class CWorld
	{
	public:
		uintptr_t SetCameraMatrix()
		{
			uintptr_t ViewRender = *( uintptr_t * ) ( BaseAddress + view_render );

			if ( ViewRender )
			{
				uintptr_t Matrix = *( uintptr_t * ) ( ViewRender + view_matrix );
				if ( Matrix )
				{
					ViewMatrix = *( D3DMATRIX * ) ( Matrix );
				}
			}

			return 0;
		}


		bool WorldToScreen( D3DXVECTOR3 x_pos, D3DXVECTOR2 *x_out )
		{
			D3DXVECTOR3 vTransformed;

			///std::cout << "w: " << Width << " h: " << Height << std::endl;

			vTransformed.x = ( float ) ( x_pos.y * ViewMatrix.m[0][1] ) + ( float ) ( x_pos.x * ViewMatrix.m[0][0] ) + ( float ) ( x_pos.z * ViewMatrix.m[0][2] ) + ViewMatrix.m[0][3];
			vTransformed.y = ( float ) ( x_pos.y * ViewMatrix.m[1][1] ) + ( float ) ( x_pos.x * ViewMatrix.m[1][0] ) + ( float ) ( x_pos.z * ViewMatrix.m[1][2] ) + ViewMatrix.m[1][3];
			vTransformed.z = ( float ) ( x_pos.y * ViewMatrix.m[3][1] ) + ( float ) ( x_pos.x * ViewMatrix.m[3][0] ) + ( float ) ( x_pos.z * ViewMatrix.m[3][2] ) + ViewMatrix.m[3][3];

			if ( vTransformed.z < 0.001 )
			{
				//printf( "false\n" );
				return false;
			}

			vTransformed.x *= 1.0 / vTransformed.z;
			vTransformed.y *= 1.0 / vTransformed.z;

			*x_out = D3DXVECTOR2( Width / 2.0f + vTransformed.x * ( Width / 2.0f ), Height / 2.0f - vTransformed.y * ( Height / 2.0f ) );

			return true;
		}

		float ScreenToEnemy( D3DXVECTOR3 Position )
		{
			D3DXVECTOR2 Output;
			if ( WorldToScreen( Position, &Output ) )
			{
				return ( fabs( Output.x - ( Width / 2 ) ) + fabs( Output.y - ( Height / 2 ) ) );
			}
			return 0;
		}

		D3DXVECTOR2 CalculateAngles( const D3DXVECTOR3 &src, const D3DXVECTOR3 &dst )
		{
			D3DXVECTOR2 angle = D3DXVECTOR2();
			D3DXVECTOR3 delta = D3DXVECTOR3( ( src.x - dst.x ), ( src.y - dst.y ), ( src.z - dst.z ) );

			double hyp = sqrt( delta.x * delta.x + delta.y * delta.y );

			angle.x = atan( delta.z / hyp ) * ( 180.0f / M_PI );
			angle.y = atan( delta.y / delta.x ) * ( 180.0f / M_PI );
			if ( delta.x >= 0.0 ) angle.y += 180.0f;

			return angle;
		}

		void NormalizeAngles( D3DXVECTOR2 &angle )
		{
			while ( angle.x > 89.0f )
				angle.x -= 180.f;

			while ( angle.x < -89.0f )
				angle.x += 180.f;

			while ( angle.y > 180.f )
				angle.y -= 360.f;

			while ( angle.y < -180.f )
				angle.y += 360.f;
		}
	};

	struct visibleTime
	{
		float lastTime[100]; // last visible time in float
		bool lastState[100]; // last visibility state
		uintptr_t lastCheck[100]; // last visibility check time
	} lastVis;

	struct PredictCtx
	{
		//input data
		D3DXVECTOR3 StartPos;
		D3DXVECTOR3 TargetPos;
		D3DXVECTOR3 TargetVel;
		float BulletSpeed;
		float BulletGravity;

		//out data
		D3DXVECTOR2 AimAngles;
	};

	class CObjects
	{
	public:
		uintptr_t m_GetObjectList( int i )
		{
			return *( uintptr_t * ) ( BaseAddress + cl_entitylist + (i * 0x20));
		}
	};

	class CPlayer
	{
		utility *Utility { };
	public:

		class GlobalVars
		{
		public:
			float realtime; //0x0000
			int32_t framecount; //0x0004
			float absoluteframetime; //0x0008
			float curtime; //0x000C
			float frametime; //0x0010
			int32_t tickcount; //0x0014
			float Unk1; //0x0018
			float interval_per_tick; //0x001C
			float interpolation_amount; //0x0020
			int32_t simTicksThisFrame; //0x0024
			int32_t network_protocol; //0x0028
		}; //Size: 0x002C

		class UserCmd
		{
		public:
			int command_number;
			int tick_count;
			float command_time;
			D3DXVECTOR3 viewangles;
			BYTE pad1[0xC];
			float forwardmove;
			float sidemove;
			float upmove;
			int buttons;
			BYTE pad2[0x24C];
		};

		struct kbutton_t
		{
			int down[2];
			int state;
		};



		class Ray
		{
		public:
			BYTE RayRaw[0x68];
			/*__forceinline Ray(const Vector3& Start, const Vector3& End) {
				SpoofCall(Fn::RayInit, RayRaw, &Start, &End);
			}*/
		};

		struct surface_t
		{
			const char *name;				//0x0000
			int				surfaceProp;		//0x0008
			unsigned short	flags;				//0x000C
		};

		struct plane_t
		{
			D3DXVECTOR3	surfaceNormal;	//0x0000
			float	dist;			//0x000C
		};

		struct TraceData
		{
			D3DXVECTOR3 startpos;
			int unk0;
			D3DXVECTOR3 endpos;
			int unk01;
			plane_t plane;
			float fraction;
			int contents;
			unsigned short dispFlags;
			bool allsolid;
			bool startsolid;
			int unk02;
			float fractionLeftSolid;
			int unk03;
			surface_t surface;
			int hitgroup;
			short physicsBone;
			unsigned short m_nWorldSurfaceIndex;
			void *m_pEnt;
			int hitbox;
			char pad[0x114];
		};

	#define M_PI 3.14159265358979323846f
	#define M_RADPI	57.295779513082f
	#define M_PI_F ((float)(M_PI))
	#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))

		__forceinline D3DXVECTOR3 ExtrapolatePos( const PredictCtx &Ctx, float Time )
		{
			return Ctx.TargetPos + ( Ctx.TargetVel * Time );
		}

		bool OptimalPitch( const PredictCtx &Ctx, const D3DXVECTOR2 &Dir2D, float *OutPitch )
		{
			float Vel = Ctx.BulletSpeed, Grav = Ctx.BulletGravity, DirX = Dir2D.x, DirY = Dir2D.y;
			float Root = Vel * Vel * Vel * Vel - Grav * ( Grav * DirX * DirX + 2.f * DirY * Vel * Vel );
			if ( Root >= 0.f )
			{
				*OutPitch = atanf( ( Vel * Vel - sqrt( Root ) ) / ( Grav * DirX ) );
				
					return true;
			}

			return false;
		}

		bool SolveTrajectory( PredictCtx &Ctx, const D3DXVECTOR3 &ExtrPos, float *TravelTime )
		{
			
				D3DXVECTOR3 Dir = ExtrPos - Ctx.StartPos;
			D3DXVECTOR2 Dir2D = { sqrtf( Dir.x * Dir.x + Dir.y * Dir.y ), Dir.z };

			float CurPitch;
			if ( !OptimalPitch( Ctx, Dir2D, &CurPitch ) )
			{
				return false;
			}

			*TravelTime = Dir2D.x / ( cosf( CurPitch ) * Ctx.BulletSpeed );
			Ctx.AimAngles.y = atan2f( Dir.y, Dir.x );
			Ctx.AimAngles.x = CurPitch;

			
				return true;
		}

		bool BulletPredict( PredictCtx &Ctx )
		{
			const float MAX_TIME = 1.f, TIME_STEP = ( 1.f / 128.f/*256.f*/ );
			for ( float CurrentTime = 0.f; CurrentTime <= MAX_TIME; CurrentTime += TIME_STEP )
			{
				float TravelTime;
				D3DXVECTOR3 ExtrPos = ExtrapolatePos( Ctx, CurrentTime );
				if ( !SolveTrajectory( Ctx, ExtrPos, &TravelTime ) )
				{
					return false;
				}

				if ( TravelTime < CurrentTime )
				{
					Ctx.AimAngles = { -RAD2DEG( Ctx.AimAngles.x ), RAD2DEG( Ctx.AimAngles.y ) };
					return true;
				}
			}
		}
		
		D3DXVECTOR2 BreathAngles( uintptr_t ent )
		{
			return *( D3DXVECTOR2 * ) ( ent + (0x257c - 0x10));
		}

		D3DXVECTOR2 PunchAngle( uintptr_t ent )
		{
			return *( D3DXVECTOR2 * ) ( ent + 0x2480 );
		}

		D3DXVECTOR3 AbsVelocity(uintptr_t ent)
		{
			return *( D3DXVECTOR3 * ) ( ent + 0x0140 );
		}

		float BulletSpeed(DWORD64 ActiveWeapon)
		{
			if ( !ActiveWeapon )
			{
				return 0.f;
			}

			return *( float * ) ( ActiveWeapon + 0x1f18 );
		}

		float BulletGravity( DWORD64 ActiveWeapon )
		{
			if ( !ActiveWeapon )
			{
				return 0.f;
			}
			return *( float * ) ( ActiveWeapon + ( 0x1f18 + 0x8 ) );
		}

		D3DXVECTOR3 m_GetBonePositon( uintptr_t ent, D3DXVECTOR3 BasePos, int bone )
		{
			D3DXVECTOR3 headpos;
			uintptr_t bArray = *( uintptr_t * ) ( ent + 0x0F38 );
			headpos.x = *( float * ) ( bArray + 0xCC + ( bone * 0x30 ) ) + BasePos.x;
			headpos.y = *( float * ) ( bArray + 0xDC + ( bone * 0x30 ) ) + BasePos.y;
			headpos.z = *( float * ) ( bArray + 0xEC + ( bone * 0x30 ) ) + BasePos.z;

			return headpos;
		}

		uintptr_t m_iTeamNum( uint64_t entity )
		{
			return *( uint64_t * ) ( entity + 0x0448 );
		}

		uintptr_t m_iName(uint64_t entity)
		{
			return *( uint64_t * ) ( entity + 0x589);
		}

		bool m_IsPlayer(uintptr_t entity)
		{
			return ( m_iName(entity) == 125780153691248 );
		}

		bool m_IsDummy( uintptr_t entity )
		{
			if ( m_iTeamNum( entity ) == 97 )
				return true;
			else
				return false;
		}


		struct ClientClass
		{
			uint64_t pCreateFn;
			uint64_t pCreateEventFn;
			uint64_t pNetworkName;
			uint64_t pRecvTable;
			uint64_t pNext;
			uint32_t ClassID;
			uint32_t ClassSize;
		};

		bool getClassNameX( uintptr_t ent, std::string &className )
		{
			uintptr_t clientNetworkableVTable = *(uintptr_t*)( ent + 8 * 3 );
			if ( !clientNetworkableVTable )
				return false;

			uintptr_t getClientClass = *(uintptr_t*)( clientNetworkableVTable + 8 * 3 );
			if ( !getClientClass )
				return false;

			uint32_t disp = *(uint32_t*)( getClientClass + 3 );
			if ( !disp )
			{
				return false;
			}
			const uint64_t client_class_ptr = getClientClass + disp + 7;
			// Get the ClientClass instance itself.
			ClientClass clientClass = *(ClientClass*)( client_class_ptr );

			 //Finally grab some bytes to be interpreted as a nul terminated c-string.
			className = ReadASCII128( clientClass.pNetworkName );
			if ( className.length() == 128 )
				className = "Unknown";
			return true;
		}

		uintptr_t m_GetLocalPlayer( )
		{
			return *( uintptr_t * ) ( BaseAddress + local_player );
		}

		int m_iHealth( uintptr_t entity )
		{
			return *( int * ) ((uint64_t)entity + 0x438 );
		}

		std::string m_iuserName(uintptr_t entity)
		{
			int32_t name_index = *( int32_t * ) ( entity + 0x38 );
			std::string Textt;
			if ( name_index != -1 )
			{ //Don't really know if this check is needed
				uint64_t name_list_ptr = ( BaseAddress + name_list );
				uint64_t name_offset = ( 2 * ( uint64_t ) name_index - 2 ) * 8;

				uint64_t name_ptr = *( uint64_t * ) ( name_list_ptr + name_offset );

				//Read null terminated string at name_ptr
				char works[64];
				auto yeah = ReadASCII( name_ptr ); //I just try to read 64 bytes... :/ 

				Textt += yeah;
			}
			return Textt;
		}

		D3DXVECTOR2 m_iGetPlayerViewAngle( uintptr_t entity )
		{
			return *( D3DXVECTOR2 * ) ( entity + 0x257c );
		}

		D3DXVECTOR3 m_iGetPlayerOrigin( uintptr_t entity )
		{
			return *( D3DXVECTOR3 * ) ( entity + 0x014C );
		}

		D3DXVECTOR3 m_iGetInGameCameraPosition( uintptr_t entity )
		{
			return *( D3DXVECTOR3 * ) ( entity + 0x1f20 );
		}

		int m_iMaxHealth( uintptr_t entity )
		{
			return *( int * ) ( ( uint64_t ) entity + 0x578 );
		}

		DWORD64 ActiveWeapon( uintptr_t ent )
		{
			uint64_t entitylist = BaseAddress + cl_entitylist;
			uint64_t wephandle = *(uint64_t*)( ent + 0x1a8c /*active weapon*/ );

			wephandle &= 0xffff;

			uint64_t wep_entity = *( uint64_t * ) ( entitylist + ( wephandle << 5 ) );

			return wep_entity;
		}

		int m_shieldHealth( uintptr_t entity )
		{
			return *( int * ) ( ( uint64_t ) entity + 0x170 );
		}

		int m_shieldHealthMax( uintptr_t entity )
		{
			return *( int * ) ( ( uint64_t ) entity + 0x174 );
		}

		int m_lifeState( uintptr_t entity )
		{
			return *( int * ) ( ( uint64_t ) entity + 0x0798);
		}

		bool isDown( uintptr_t entity )
		{
			int lifestate = *( int * ) ( entity + 0x2718 );
			if ( lifestate > 0 )
				return true;
			else
				return false;
		}

		int m_aiSprinting( uintptr_t entity )
		{
			return *( int * ) ( ( uint64_t ) entity + 0x1d9a );
		}

		int m_isHologram( uintptr_t entity )
		{
			return *( int * ) ( ( uint64_t ) entity + 0x1dc0 );
		}

		int m_hGroundEntity( uintptr_t entity )
		{
			return *( int * ) ( ( uint64_t ) entity + 0x434 );
		}

		float last_vis_time( uintptr_t entity )
		{
			return *(float*)( entity + 0x1af4 );
		}

		float lastVisTime(uintptr_t ent)
		{
			return *( float * ) ( ent + 0x1af4 );
		}
	};
}