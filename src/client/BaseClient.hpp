/**
 * @brief   Base class implementing shared functionality of Trader and Client
 * @file    BaseClient.hpp
 *
 */

#ifndef BASECLIENT_HPP
#define BASECLIENT_HPP

#include "PyXchange.hpp"


namespace pyxchange
{


class BaseClient
{
public:
                BaseClient( const std::string& name_,
                            const boost::python::object& transport_ );

                BaseClient( const Trader& ) = delete;
                BaseClient& operator=( const Trader& ) = delete;
    virtual     ~BaseClient();

    std::string toString( void ) const;

    void        disconnect( void );

    void        writeData( const boost::python::object& data );

private:
    const std::string name;
    const boost::python::object transport;
};


} /* namespace pyxchange */


#endif /* BASECLIENT_HPP */


/* EOF */

