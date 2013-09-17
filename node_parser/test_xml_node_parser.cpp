#include "test_node_parser.h"




#include <map>
#include <vector>
#include <iostream>


#include "../tinyxml/tinyxml.h"
#pragma comment(lib, "tinyxml.lib")


#include "node_parser.h"
#include "xml_node_parser.h"


namespace test_xml_details
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

DEF_NODE(CPlayer, xml_node_parser)
    DEF_VALUE(id,       "id")
    DEF_VALUE(name,     "name")
    DEF_VALUE(leader,   "leader")
END_NODE()

DEF_NODE(CMatch, xml_node_parser)
    DEF_VALUE(id,       "id")
    DEF_ARRAY(PlayerList, CPlayer,  players,    "players")
END_NODE()

DEF_NODE(CMatchHistory, xml_node_parser)
    DEF_VALUE(count,    "count")
    DEF_VALUE(remain,   "remain")

    DEF_MAP(MatchMap, CMatch,     matches,    "matches", id, int)

END_NODE()

#define CHECK_VALUE(expression) if(!(expression)) {std::cout << "Failed -- XML\r\n\t" << #expression <<  "\r\n\tLine: " << __LINE__ << std::endl; return false;}


//////////////////////////////////////////////////////////////////////////
// Test
bool testPlayer()
{
    const char* xml_player = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?><player id=\"23\" name=\"Jack\" leader=\"false\"></player>";

    CPlayer player;
    TiXmlDocument doc;
    doc.Parse(xml_player);
    TiXmlElement* root = doc.FirstChildElement("player");

    CHECK_VALUE(NodeValueLoad(player, *root));
    CHECK_VALUE(player.id == 23);
    CHECK_VALUE(player.name == "Jack");
    CHECK_VALUE(player.leader == false);

    return true;
}

bool testMatch()
{
    const char* xml_match = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?><match id=\"78\"><players><player id=\"23\" name=\"Rose\" leader=\"true\" /><player id=\"34\" name=\"Jack\" leader=\"false\" /></players></match>";

    CMatch match;
    TiXmlDocument doc;
    doc.Parse(xml_match);
    TiXmlElement* root = doc.FirstChildElement("match");

    CHECK_VALUE(NodeValueLoad(match, *root));
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
    const char* xml_history = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?><history count=\"2\" remain=\"8\"><matches><match id=\"25\"><players><player id=\"23\" name=\"Rose2\" leader=\"true\" /><player id=\"34\" name=\"Jack2\" leader=\"false\" /></players></match><match id=\"89\"><players><player id=\"57\" name=\"Rose3\" leader=\"true\" /><player id=\"68\" name=\"Jack3\" leader=\"false\" /></players></match></matches></history>";

    CMatchHistory history;
    TiXmlDocument doc;
    doc.Parse(xml_history);
    TiXmlElement* root = doc.FirstChildElement("history");

    CHECK_VALUE(NodeValueLoad(history, *root));

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

bool test_xml_node_parser()
{
    CHECK_VALUE(test_xml_details::testPlayer());
    CHECK_VALUE(test_xml_details::testMatch());
    CHECK_VALUE(test_xml_details::testHistory());

    return true;
}
