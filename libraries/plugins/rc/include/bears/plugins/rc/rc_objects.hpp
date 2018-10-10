#pragma once
#include <bears/chain/util/manabar.hpp>

#include <bears/plugins/rc/rc_utility.hpp>
#include <bears/plugins/rc/resource_count.hpp>

#include <bears/chain/bears_object_types.hpp>

#include <fc/int_array.hpp>

#include <boost/multi_index/composite_key.hpp>

namespace bears { namespace plugins { namespace rc {

using namespace std;
using namespace bears::chain;

#ifndef BEARS_RC_SPACE_ID
#define BEARS_RC_SPACE_ID 16
#endif

enum rc_object_types
{
   rc_resource_param_object_type   = ( BEARS_RC_SPACE_ID << 8 ),
   rc_pool_object_type             = ( BEARS_RC_SPACE_ID << 8 ) + 1,
   rc_account_object_type          = ( BEARS_RC_SPACE_ID << 8 ) + 2
};

class rc_resource_param_object : public object< rc_resource_param_object_type, rc_resource_param_object >
{
   public:
      template< typename Constructor, typename Allocator >
      rc_resource_param_object( Constructor&& c, allocator< Allocator > a )
      {
         c( *this );
      }

      id_type               id;
      fc::int_array< rc_resource_params, BEARS_NUM_RESOURCE_TYPES >
                            resource_param_array;
};

class rc_pool_object : public object< rc_pool_object_type, rc_pool_object >
{
   public:
      template< typename Constructor, typename Allocator >
      rc_pool_object( Constructor&& c, allocator< Allocator > a )
      {
         c( *this );
      }

      id_type               id;
      fc::int_array< int64_t, BEARS_NUM_RESOURCE_TYPES >
                            pool_array;
};

class rc_account_object : public object< rc_account_object_type, rc_account_object >
{
   public:
      template< typename Constructor, typename Allocator >
      rc_account_object( Constructor&& c, allocator< Allocator > a )
      {
         c( *this );
      }

      id_type               id;

      account_name_type     account;
      bears::chain::util::manabar   rc_manabar;
      asset                 max_rc_creation_adjustment = asset( 0, COINS_SYMBOL );

      // This is used for bug-catching, to match that the coining shares in a
      // pre-op are equal to what they were at the last post-op.
      int64_t               last_max_rc = 0;
};

int64_t get_maximum_rc( const bears::chain::account_object& account, const rc_account_object& rc_account );

using namespace boost::multi_index;

typedef multi_index_container<
   rc_resource_param_object,
   indexed_by<
      ordered_unique< tag< by_id >, member< rc_resource_param_object, rc_resource_param_object::id_type, &rc_resource_param_object::id > >
   >,
   allocator< rc_resource_param_object >
> rc_resource_param_index;

typedef multi_index_container<
   rc_pool_object,
   indexed_by<
      ordered_unique< tag< by_id >, member< rc_pool_object, rc_pool_object::id_type, &rc_pool_object::id > >
   >,
   allocator< rc_pool_object >
> rc_pool_index;

typedef multi_index_container<
   rc_account_object,
   indexed_by<
      ordered_unique< tag< by_id >, member< rc_account_object, rc_account_object::id_type, &rc_account_object::id > >,
      ordered_unique< tag< by_name >, member< rc_account_object, account_name_type, &rc_account_object::account > >
   >,
   allocator< rc_account_object >
> rc_account_index;

} } } // bears::plugins::rc

FC_REFLECT( bears::plugins::rc::rc_resource_param_object, (id)(resource_param_array) )
CHAINBASE_SET_INDEX_TYPE( bears::plugins::rc::rc_resource_param_object, bears::plugins::rc::rc_resource_param_index )

FC_REFLECT( bears::plugins::rc::rc_pool_object, (id)(pool_array) )
CHAINBASE_SET_INDEX_TYPE( bears::plugins::rc::rc_pool_object, bears::plugins::rc::rc_pool_index )

FC_REFLECT( bears::plugins::rc::rc_account_object,
   (id)
   (account)
   (rc_manabar)
   (max_rc_creation_adjustment)
   (last_max_rc)
   )
CHAINBASE_SET_INDEX_TYPE( bears::plugins::rc::rc_account_object, bears::plugins::rc::rc_account_index )
