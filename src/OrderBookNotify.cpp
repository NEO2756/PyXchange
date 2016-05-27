/**
 * @brief This module implements simulator of exchange
 * @file NotifyLevels.cpp
 *
 */

#include "OrderBook.hpp"
#include "Client.hpp"
#include "Trader.hpp"
#include "Utils.hpp"


namespace pyxchange
{


/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
inline void OrderBook::notifyPriceLevels( const typename OrderContainer::type& orders, const typename OrderContainer::price_set& priceLevels,
                                          const MatcherConstPtr& matcher, const side_t side_ ) const
{
    for( const auto priceLevel : priceLevels )
    {
        notifyPriceLevel<OrderContainer>( orders, priceLevel, matcher, side_ );
    }
}


/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
inline void OrderBook::notifyPriceLevel( const typename OrderContainer::type& orders, const price_t priceLevel,
                                         const MatcherConstPtr& matcher, const side_t side_ ) const
{
    typename OrderContainer::type::template index<tags::idxPrice>::type const &idx                = orders.template get<tags::idxPrice>();
    typename OrderContainer::type::template index<tags::idxPrice>::type::const_iterator it        = idx.lower_bound( priceLevel );
    typename OrderContainer::type::template index<tags::idxPrice>::type::const_iterator const end = idx.upper_bound( priceLevel );

    quantity_t quantity = 0;

    while( it != end )
    {
        quantity += (*it)->quantity;

        ++it;
    }

    boost::python::dict response;

    response[ keys::message  ] = message::orderBook;
    response[ keys::side     ] = side::toBidAsk( side_ );
    response[ keys::price    ] = priceLevel;
    response[ keys::quantity ] = quantity;

    Client::writeAll( matcher, response );
}


template void OrderBook::notifyPriceLevels<BidOrderContainer>(
    const BidOrderContainer::type& orders,
    const BidOrderContainer::price_set& priceLevels,
    const MatcherConstPtr& matcher,
    const side_t side_
) const;

template void OrderBook::notifyPriceLevels<AskOrderContainer>(
    const AskOrderContainer::type& orders,
    const AskOrderContainer::price_set& priceLevels,
    const MatcherConstPtr& matcher,
    const side_t side_
) const;

template void OrderBook::notifyPriceLevel<BidOrderContainer>(
    const BidOrderContainer::type& orders,
    const price_t priceLevel,
    const MatcherConstPtr& matcher,
    const side_t side_
) const;

template void OrderBook::notifyPriceLevel<AskOrderContainer>(
    const AskOrderContainer::type& orders,
    const price_t priceLevel,
    const MatcherConstPtr& matcher,
    const side_t side_
) const;


} /* namespace pyxchange */


/* EOF */
