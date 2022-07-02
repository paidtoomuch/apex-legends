/*
                 _                   _          _     _      _
                / /\                /\ \       /\ \ /_/\    /\ \
               / /  \              /  \ \     /  \ \\ \ \   \ \_\
              / / /\ \            / /\ \ \   / /\ \ \\ \ \__/ / /
             / / /\ \ \          / / /\ \_\ / / /\ \_\\ \__ \/_/
            / / /  \ \ \        / / /_/ / // /_/_ \/_/ \/_/\__/\
           / / /___/ /\ \      / / /__\/ // /____/\     _/\/__\ \
          / / /_____/ /\ \    / / /_____// /\____\/    / _/_/\ \ \
         / /_________/\ \ \  / / /      / / /______   / / /   \ \ \
        / / /_       __\ \_\/ / /      / / /_______\ / / /    /_/ /
        \_\___\     /____/_/\/_/       \/__________/ \/_/     \_\/

                    apex-sdk - developed by NASM		
*/

#include <cheat/internal/core.hpp>

auto DllMain( void *, std::uint32_t call_reason, void * ) -> bool
{
    if ( call_reason != 1 )
        return false;

    if ( !c_swapchain() )
        return false;

    return true;
}
