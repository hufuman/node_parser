#include "test_node_parser.h"




#include <map>
#include <vector>
#include <iostream>


#include "../3rdlib/json/json/json.h"
#pragma comment(lib, "json.lib")


#include "../lib/node_parser.h"
#include "../lib/json_node_parser.h"

namespace test_json_details
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

//////////////////////////////////////////////////////////////////////////
// Test Node Defination

DEF_NODE(CPlayer, json_node_parser)
    DEF_VALUE(id,       "id")
    DEF_VALUE(name,     "name")
    DEF_VALUE(leader,   "leader")
END_NODE()

DEF_NODE(CMatch, json_node_parser)
    DEF_VALUE(id,       "id")
    DEF_ARRAY(PlayerList, CPlayer,  players,    "players")
END_NODE()

DEF_NODE(CMatchHistory, json_node_parser)
    DEF_VALUE(count,    "count")
    DEF_VALUE(remain,   "remain")

    DEF_MAP(MatchMap, CMatch,     matches,    "matches", id, int)

END_NODE()

#define CHECK_VALUE(expression) if(!(expression)) {std::cout << "Failed -- JSON\r\n\t" << #expression <<  "\r\n\tLine: " << __LINE__ << std::endl; return false;}


//////////////////////////////////////////////////////////////////////////
// Test
bool testPlayer()
{
    const char* json_player = "{\"id\":23,\"name\":\"Jack\",\"leader\":false}";
    const char* json_player_end = json_player + strlen(json_player);

    CPlayer player;
    Json::Reader reader;
    Json::Value playerValue;
    reader.parse(json_player, json_player_end, playerValue);

    CHECK_VALUE(NodeValueLoad(player, playerValue));
    CHECK_VALUE(player.id == 23);
    CHECK_VALUE(player.name == "Jack");
    CHECK_VALUE(player.leader == false);

    return true;
}

bool testMatch()
{
    const char* json_match = "{\"id\":78,\"players\":[{\"id\":23,\"name\":\"Rose\",\"leader\":true},{\"id\":34,\"name\":\"Jack\",\"leader\":false}]}";
    const char* json_match_end = json_match + strlen(json_match);

    CMatch match;
    Json::Reader reader;
    Json::Value matchValue;

    reader.parse(json_match, json_match_end, matchValue);

    CHECK_VALUE(NodeValueLoad(match, matchValue));
    CHECK_VALUE(match.id == 78);
    CHECK_VALUE(match.players.size() == 2);

    CHECK_VALUE(match.players[0].id == 23);
    CHECK_VALUE(match.players[0].name == "Rose");
    CHECK_VALUE(match.players[0].leader == true);

    CHECK_VALUE(match.players[1].id == 34);
    CHECK_VALUE(match.players[1].name == "Jack");
    CHECK_VALUE(match.players[1].leader == false);

    return true;
}

bool testHistory()
{
    const char* json_history = "{\"count\":2,\"remain\":8,\"matches\":[{\"id\":25,\"players\":[{\"id\":23,\"name\":\"Rose2\",\"leader\":true},{\"id\":34,\"name\":\"Jack2\",\"leader\":false}]},{\"id\":89,\"players\":[{\"id\":57,\"name\":\"Rose3\",\"leader\":true},{\"id\":68,\"name\":\"Jack3\",\"leader\":false}]}]}";
    const char* json_history_end = json_history + strlen(json_history);

    Json::Reader reader;
    CMatchHistory history;
    Json::Value historyValue;

    reader.parse(json_history, json_history_end, historyValue);

    CHECK_VALUE(NodeValueLoad(history, historyValue));

    CHECK_VALUE(history.count == 2);
    CHECK_VALUE(history.remain == 8);

    CHECK_VALUE(history.matches.size() == 2);

    CHECK_VALUE(history.matches.find(25) != history.matches.end());
    CHECK_VALUE(history.matches.find(89) != history.matches.end());

    CMatch& match1 = history.matches[25];
    CMatch& match2 = history.matches[89];

    CHECK_VALUE(match1.id == 25);
    CHECK_VALUE(match1.players.size() == 2);

    CHECK_VALUE(match1.players[0].id == 23);
    CHECK_VALUE(match1.players[0].name == "Rose2");
    CHECK_VALUE(match1.players[0].leader == true);

    CHECK_VALUE(match1.players[1].id == 34);
    CHECK_VALUE(match1.players[1].name == "Jack2");
    CHECK_VALUE(match1.players[1].leader == false);

    CHECK_VALUE(match2.id == 89);
    CHECK_VALUE(match2.players.size() == 2);

    CHECK_VALUE(match2.players[0].id == 57);
    CHECK_VALUE(match2.players[0].name == "Rose3");
    CHECK_VALUE(match2.players[0].leader == true);

    CHECK_VALUE(match2.players[1].id == 68);
    CHECK_VALUE(match2.players[1].name == "Jack3");
    CHECK_VALUE(match2.players[1].leader == false);

    return true;
}
}


bool test_json_node_parser()
{
    CHECK_VALUE(test_json_details::testPlayer());
    CHECK_VALUE(test_json_details::testMatch());
    CHECK_VALUE(test_json_details::testHistory());

    return true;
}
