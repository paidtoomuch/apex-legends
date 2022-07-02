#pragma once
#include <impl/render/present.h>
#include <impl/hooking/memory_hook.h>
#include <cheat/internal/updater/updater.hpp>


memory_hook::memhook_context *present_hook;
memory_hook::memhook_context *clientmode_hook;



auto c_swapchain() -> bool
{
	utility *utility {};

	auto level = D3D_FEATURE_LEVEL_11_0;

	apex_output( x("c_swapchain: called") );

	DXGI_SWAP_CHAIN_DESC Description;
	IDXGISwapChain *swap_chain = nullptr;
	ID3D11Device *device = nullptr;
	ID3D11DeviceContext *context = nullptr;

	itemCfg::heals = false; //ectedTypes[0];
	itemCfg::guns = false; //ectedTypes[1];
	itemCfg::attachment = false; //ectedTypes[2];
	itemCfg::ammo = false; //ectedTypes[3];
	itemCfg::scopes = false; //ectedTypes[4];
	itemCfg::throwables = false; //ectedTypes[5];
	itemCfg::armor = false; //ectedTypes[6];
	itemCfg::evoarmor = false; //ectedTypes[7];
	itemCfg::knockdownshield = false; //ectedTypes[8];
	itemCfg::backpacks = false; //ectedTypes[9];
	itemCfg::helmets = false; //ectedTypes[10];

	HWND Window = utility->call( FindWindowA, ( "Respawn001" ), ( "Apex Legends" ) );

	if ( !Window )
	{
		apex_output( x("c_swapchain: can't find window") );
		return false;
	}

	NtGetAsyncKeyState = ( keyword ) lazy_import( GetProcAddress )( lazy_import( GetModuleHandleA )( xorstr( "win32u.dll" ) ), xorstr( "NtUserGetAsyncKeyState" ) );  //getasynckeystate hijacked on nt
	ZeroMemory( &Description, sizeof Description );

	Description.BufferCount = 1;
	Description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	Description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	Description.OutputWindow = Window;
	Description.SampleDesc.Count = 1;
	Description.Windowed = TRUE;
	Description.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	Description.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	Description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	apex_output( x( "c_swapchain: description toggled" ) );

	lazy_import( D3D11CreateDeviceAndSwapChain )( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &level, 1, D3D11_SDK_VERSION, &Description, &swap_chain, &device, nullptr, &context );
	
	//checksum = ( uint64_t ) scanner::find( x( "48 89 5C 24 ?? 55 48 8B EC 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 8B D9" ) );

	//GetChecksum = ( _GetChecksum ) ( checksum );

	//DWORD64 cm = ( uint64_t ) scanner::find(x( "48 8B C4 55 56 41 57 48 8D 68 A1 48 81 EC ? ? ? ? 48 89 58 18" ) );
	//_CreateMove tmpCreateMove = ( _CreateMove ) ( cm );

	//clientmode_hook = memory_hook::create_context( tmpCreateMove );
	//OLD_CreateMove = clientmode_hook->hook( CreateMoveHk );
	//clientmode_hook->enable_hook();

	uint64_t *swap_chain_vtable = *( uint64_t ** ) swap_chain;

	present_hook = memory_hook::create_context( swap_chain_vtable[8] );

	c_original = present_hook->hook( pkHook );

	present_hook->enable_hook();

	oriWndProc = ( WNDPROC ) utility->call( SetWindowLongPtr, Window, GWLP_WNDPROC, ( LONG_PTR ) WndProc );
	return true;
}

auto unloadCheat() -> bool
{
	utility *utility {};

	if ( unload )
	{
		cfg::chams = false;
		HWND Window = utility->call( FindWindowA, ( "Respawn001" ), ( "Apex Legends" ) );
		utility->call( SetWindowLongPtr, Window, GWLP_WNDPROC, ( LONG_PTR ) oriWndProc );
		//memory_hook::destroy_context( present_hook );
		present_hook->destroy_hook();

		return true;
	}
	return false;
}