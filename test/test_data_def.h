#pragma once


#include <map>
#include <vector>
#include <iostream>

#include "data_def.h"
#include "../lib/node_parser.h"

namespace test_data
{

//////////////////////////////////////////////////////////////////////////
// Test Class
class CPlayer
{
public:
    int             id;
    std::string     name;
    bool            leader;
};
typedef std::vector<CPlayer> PlayerList;

class CMatch
{
public:
    int         id;
    PlayerList  players;
};
typedef std::map<int, CMatch> MatchMap;

class CMatchHistory
{
public:
    int         count;
    int         remain;

    MatchMap    matches;
};

class CResponseInfo
{
public:
    uint64_t test_id;
    uint32_t ret_code;
    std::wstring message;
};


//////////////////////////////////////////////////////////////////////////
// Test Node Defination

DEF_NODE(CPlayer)
    DEF_VALUE(id,       "id")
    DEF_VALUE(name,     "name")
    DEF_VALUE(leader,   "leader")
END_NODE()

DEF_NODE(CMatch)
    DEF_VALUE(id,       "id")
    DEF_ARRAY(PlayerList, CPlayer,  players,    "players")
END_NODE()

DEF_NODE(CMatchHistory)
    DEF_VALUE(count,    "count")
    DEF_VALUE(remain,   "remain")

    DEF_MAP(MatchMap, CMatch,     matches,    "matches", id, int)

END_NODE()

DEF_NODE(CResponseInfo)
    DEF_VALUE(test_id, "test_id")
    DEF_VALUE(ret_code, "ret_code")
    DEF_VALUE_FALG(message, "message", VF_Optional)
END_NODE()

#define CHECK_VALUE(msg, expression) if(!(expression)) {std::cout << "Failed -- " << (msg) << "\r\n\t" << #expression <<  "\r\n\tLine: " << __LINE__ << "\r\n\tFile: " << __FILE__ << std::endl; return false;}


}