//------------------------------------------------------------------------------
// Author: Pavel Karneliuk
// Description: Struct represented tcp session.
// Copyright (c) 2013 EPAM Systems. All Rights Reserved.
//------------------------------------------------------------------------------
#ifndef SESSION_H
#define SESSION_H
//------------------------------------------------------------------------------
#include <ostream>
#include <sstream>

#include <stdint.h>
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
namespace NST
{
namespace auxiliary
{

struct Session
{
    struct Hash
    {
        std::size_t operator()(Session const &s) const;
    };

    enum Direction
    {
        Source      =0,
        Destination =1
    };

    enum IPType
    {
        v4=0,
        v6=1,
    } ip_type:16;    //16 bit for alignment following integers

    enum Type
    {
        TCP=0,
        UDP=1,
    } type:16;    //16 bit for alignment following integers

    union
    {
        struct
        {
            uint32_t addr[2];   // 2 IPv4 addresses in host byte order
        } v4;
        struct
        {
            uint8_t addr[2][16];// 2 IPv6 addresses in host byte order
        } v6;
    } ip;

    uint16_t port[2];           // 2 ports in host byte order

    bool operator==(const Session& obj) const;
    friend std::ostream& operator<<(std::ostream& out, const Session& session);
    static std::string session_addr(Session::Direction dir, const Session& session);
    static std::string ipv4_string(const uint32_t ip);
};

} // namespace auxiliary
} // namespace NST
//------------------------------------------------------------------------------
#endif //SESSION_H
//------------------------------------------------------------------------------