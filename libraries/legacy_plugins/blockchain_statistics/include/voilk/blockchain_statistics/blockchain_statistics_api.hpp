#pragma once

#include <voilk/blockchain_statistics/blockchain_statistics_plugin.hpp>

#include <fc/api.hpp>

namespace voilk { namespace app {
   struct api_context;
} }

namespace voilk { namespace blockchain_statistics {

namespace detail
{
   class blockchain_statistics_api_impl;
}

struct statistics
{
   uint32_t             blocks = 0;                                  ///< Blocks produced
   uint32_t             bandwidth = 0;                               ///< Bandwidth in bytes
   uint32_t             operations = 0;                              ///< Operations evaluated
   uint32_t             transactions = 0;                            ///< Transactions processed
   uint32_t             transfers = 0;                               ///< Account to account transfers
   share_type           voilk_transferred = 0;                       ///< VOILK transferred from account to account
   share_type           vsd_transferred = 0;                         ///< VSD transferred from account to account
   share_type           vsd_paid_as_interest = 0;                    ///< VSD paid as interest
   uint32_t             accounts_created = 0;                        ///< Total accounts created
   uint32_t             paid_accounts_created = 0;                   ///< Accounts created with fee
   uint32_t             mined_accounts_created = 0;                  ///< Accounts mined for free
   uint32_t             total_comments= 0;                           ///< Total comments
   uint32_t             total_comment_edits = 0;                     ///< Edits to comments
   uint32_t             total_comments_deleted = 0;                  ///< Comments deleted
   uint32_t             root_comments = 0;                           ///< Top level root comments
   uint32_t             root_comment_edits = 0;                      ///< Edits to root comments
   uint32_t             root_comments_deleted = 0;                   ///< Root comments deleted
   uint32_t             replies = 0;                                 ///< Replies to comments
   uint32_t             reply_edits = 0;                             ///< Edits to replies
   uint32_t             replies_deleted = 0;                         ///< Replies deleted
   uint32_t             total_votes = 0;                             ///< Total votes on all comments
   uint32_t             new_votes = 0;                               ///< New votes on comments
   uint32_t             changed_votes = 0;                           ///< Changed votes on comments
   uint32_t             total_root_votes = 0;                        ///< Total votes on root comments
   uint32_t             new_root_votes = 0;                          ///< New votes on root comments
   uint32_t             changed_root_votes = 0;                      ///< Changed votes on root comments
   uint32_t             total_reply_votes = 0;                       ///< Total votes on replies
   uint32_t             new_reply_votes = 0;                         ///< New votes on replies
   uint32_t             changed_reply_votes = 0;                     ///< Changed votes on replies
   uint32_t             payouts = 0;                                 ///< Number of comment payouts
   share_type           vsd_paid_to_authors = 0;                     ///< Ammount of VSD paid to authors
   share_type           coins_paid_to_authors = 0;                   ///< Ammount of VESS paid to authors
   share_type           coins_paid_to_curators = 0;                  ///< Ammount of COINS paid to curators
   share_type           liquidity_rewards_paid = 0;                  ///< Ammount of VOILK paid to market makers
   uint32_t             transfers_to_coining = 0;                    ///< Transfers of VOILK into COINS
   share_type           voilk_coined = 0;                            ///< Ammount of VOILK coined
   uint32_t             new_coining_withdrawal_requests = 0;         ///< New coining withdrawal requests
   uint32_t             modified_coining_withdrawal_requests = 0;    ///< Changes to coining withdrawal requests
   share_type           coining_withdraw_rate_delta = 0;
   uint32_t             coining_withdrawals_processed = 0;           ///< Number of coining withdrawals
   uint32_t             finished_coining_withdrawals = 0;            ///< Processed coining withdrawals that are now finished
   share_type           coins_withdrawn = 0;                         ///< Ammount of COINS withdrawn to VOILK
   share_type           coins_transferred = 0;                       ///< Ammount of COINS transferred to another account
   uint32_t             vsd_conversion_requests_created = 0;         ///< VSD conversion requests created
   share_type           vsd_to_be_converted = 0;                     ///< Amount of VSD to be converted
   uint32_t             vsd_conversion_requests_filled = 0;          ///< VSD conversion requests filled
   share_type           voilk_converted = 0;                         ///< Amount of VOILK that was converted
   uint32_t             limit_orders_created = 0;                    ///< Limit orders created
   uint32_t             limit_orders_filled = 0;                     ///< Limit orders filled
   uint32_t             limit_orders_cancelled = 0;                  ///< Limit orders cancelled
   uint32_t             total_pow = 0;                               ///< POW submitted
   uint128_t            estimated_hashpower = 0;                     ///< Estimated average hashpower over interval

   statistics& operator += ( const bucket_object& b );
};

class blockchain_statistics_api
{
   public:
      blockchain_statistics_api( const voilk::app::api_context& ctx );

      void on_api_startup();

      /**
      * @brief Gets statistics over the time window length, interval, that contains time, open.
      * @param open The opening time, or a time contained within the window.
      * @param interval The size of the window for which statistics were aggregated.
      * @returns Statistics for the window.
      */
      statistics get_stats_for_time( fc::time_point_sec open, uint32_t interval )const;

      /**
      * @brief Aggregates statistics over a time interval.
      * @param start The beginning time of the window.
      * @param stop The end time of the window. stop must take place after start.
      * @returns Aggregated statistics over the interval.
      */
      statistics get_stats_for_interval( fc::time_point_sec start, fc::time_point_sec end )const;

      /**
       * @brief Returns lifetime statistics.
       */
      statistics get_lifetime_stats()const;

   private:
      std::shared_ptr< detail::blockchain_statistics_api_impl > my;
};

} } // voilk::blockchain_statistics

FC_REFLECT( voilk::blockchain_statistics::statistics,
   (blocks)
   (bandwidth)
   (operations)
   (transactions)
   (transfers)
   (voilk_transferred)
   (vsd_transferred)
   (vsd_paid_as_interest)
   (accounts_created)
   (paid_accounts_created)
   (mined_accounts_created)
   (total_comments)
   (total_comment_edits)
   (total_comments_deleted)
   (root_comments)
   (root_comment_edits)
   (root_comments_deleted)
   (replies)
   (reply_edits)
   (replies_deleted)
   (total_votes)
   (new_votes)
   (changed_votes)
   (total_root_votes)
   (new_root_votes)
   (changed_root_votes)
   (total_reply_votes)
   (new_reply_votes)
   (changed_reply_votes)
   (payouts)
   (vsd_paid_to_authors)
   (coins_paid_to_authors)
   (coins_paid_to_curators)
   (liquidity_rewards_paid)
   (transfers_to_coining)
   (voilk_coined)
   (new_coining_withdrawal_requests)
   (modified_coining_withdrawal_requests)
   (coining_withdraw_rate_delta)
   (coining_withdrawals_processed)
   (finished_coining_withdrawals)
   (coins_withdrawn)
   (coins_transferred)
   (vsd_conversion_requests_created)
   (vsd_to_be_converted)
   (vsd_conversion_requests_filled)
   (voilk_converted)
   (limit_orders_created)
   (limit_orders_filled)
   (limit_orders_cancelled)
   (total_pow)
   (estimated_hashpower) )


FC_API( voilk::blockchain_statistics::blockchain_statistics_api,
   (get_stats_for_time)
   (get_stats_for_interval)
   (get_lifetime_stats)
)
