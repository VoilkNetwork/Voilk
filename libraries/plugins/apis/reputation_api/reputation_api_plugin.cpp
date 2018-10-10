#include <bears/plugins/reputation_api/reputation_api_plugin.hpp>
#include <bears/plugins/reputation_api/reputation_api.hpp>


namespace bears { namespace plugins { namespace reputation {

reputation_api_plugin::reputation_api_plugin() {}
reputation_api_plugin::~reputation_api_plugin() {}

void reputation_api_plugin::set_program_options( options_description& cli, options_description& cfg ) {}

void reputation_api_plugin::plugin_initialize( const variables_map& options )
{
   api = std::make_shared< reputation_api >();
}

void reputation_api_plugin::plugin_startup() {}
void reputation_api_plugin::plugin_shutdown() {}

} } } // bears::plugins::reputation
