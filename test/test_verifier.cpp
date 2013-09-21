
#include "test_verifier.h"



namespace test_verifier
{
    bool verifyPlayer(const char* msg, const test_data::CPlayer& player)
    {
        CHECK_VALUE(msg, player.id == 23);
        CHECK_VALUE(msg, player.name.compare("Jack") == 0);
        CHECK_VALUE(msg, player.leader == false);

        return true;
    }

    bool verifyMatch(const char* msg, const test_data::CMatch& match)
    {
        CHECK_VALUE(msg, match.id == 78);
        CHECK_VALUE(msg, match.players.size() == 2);

        CHECK_VALUE(msg, match.players[0].id == 23);
        CHECK_VALUE(msg, match.players[0].name.compare("Rose") == 0);
        CHECK_VALUE(msg, match.players[0].leader == true);

        CHECK_VALUE(msg, match.players[1].id == 34);
        CHECK_VALUE(msg, match.players[1].name.compare("Jack") == 0);
        CHECK_VALUE(msg, match.players[1].leader == false);

        return true;
    }

    bool verifyHistory(const char* msg, const test_data::CMatchHistory& history)
    {

        CHECK_VALUE(msg, history.count == 2);
        CHECK_VALUE(msg, history.remain == 8);

        CHECK_VALUE(msg, history.matches.size() == 2);

        CHECK_VALUE(msg, history.matches.find(25) != history.matches.end());
        CHECK_VALUE(msg, history.matches.find(89) != history.matches.end());

        test_data::MatchMap::const_iterator ite = history.matches.find(25);
        CHECK_VALUE(msg, ite != history.matches.end());

        const test_data::CMatch& match1 = ite->second;

        ite = history.matches.find(89);
        CHECK_VALUE(msg, ite != history.matches.end());

        const test_data::CMatch& match2 = ite->second;

        CHECK_VALUE(msg, match1.id == 25);
        CHECK_VALUE(msg, match1.players.size() == 2);

        CHECK_VALUE(msg, match1.players[0].id == 23);
        CHECK_VALUE(msg, match1.players[0].name.compare("Rose2") == 0);
        CHECK_VALUE(msg, match1.players[0].leader == true);

        CHECK_VALUE(msg, match1.players[1].id == 34);
        CHECK_VALUE(msg, match1.players[1].name.compare("Jack2") == 0);
        CHECK_VALUE(msg, match1.players[1].leader == false);

        CHECK_VALUE(msg, match2.id == 89);
        CHECK_VALUE(msg, match2.players.size() == 2);

        CHECK_VALUE(msg, match2.players[0].id == 57);
        CHECK_VALUE(msg, match2.players[0].name.compare("Rose3") == 0);
        CHECK_VALUE(msg, match2.players[0].leader == true);

        CHECK_VALUE(msg, match2.players[1].id == 68);
        CHECK_VALUE(msg, match2.players[1].name.compare("Jack3") == 0);
        CHECK_VALUE(msg, match2.players[1].leader == false);

        return true;
    }

    bool verifyResponse(const char* msg, const test_data::CResponseInfo& response)
    {
        CHECK_VALUE(msg, response.test_id == 76561198085675982);
        CHECK_VALUE(msg, response.ret_code == 1);
        CHECK_VALUE(msg, response.message.empty());

        return true;
    }

    bool verifyResponseWithMsg(const char* msg, const test_data::CResponseInfo& response)
    {
        CHECK_VALUE(msg, response.test_id == 76561198085675982);
        CHECK_VALUE(msg, response.ret_code == 42);
        CHECK_VALUE(msg, response.message.compare(L"test message") == 0);

        return true;
    }
};

