#include "test_node_parser.h"




#include "../3rdlib/json/json/json.h"
#pragma comment(lib, "json.lib")


#include "../lib/node_parser.h"
#include "../lib/json_node_parser.h"

#include "test_data_def.h"
#include "test_verifier.h"


namespace test_json_details
{

//////////////////////////////////////////////////////////////////////////
// Test
bool testPlayer()
{
    const char* json_player = "{\"id\":23,\"name\":\"Jack\",\"leader\":false}";
    const char* json_player_end = json_player + strlen(json_player);

    test_data::CPlayer player;
    Json::Reader reader;
    Json::Value playerValue;
    reader.parse(json_player, json_player_end, playerValue);

    CHECK_VALUE("json_test", NodeValueLoad<json_node_parser>(player, playerValue));
    return test_verifier::verifyPlayer("json_test", player);
}

bool testMatch()
{
    const char* json_match = "{\"id\":78,\"players\":[{\"id\":23,\"name\":\"Rose\",\"leader\":true},{\"id\":34,\"name\":\"Jack\",\"leader\":false}]}";
    const char* json_match_end = json_match + strlen(json_match);

    test_data::CMatch match;
    Json::Reader reader;
    Json::Value matchValue;

    reader.parse(json_match, json_match_end, matchValue);

    CHECK_VALUE("json_test", NodeValueLoad<json_node_parser>(match, matchValue));
    return test_verifier::verifyMatch("json_test", match);
}

bool testHistory()
{
    const char* json_history = "{\"count\":2,\"remain\":8,\"matches\":[{\"id\":25,\"players\":[{\"id\":23,\"name\":\"Rose2\",\"leader\":true},{\"id\":34,\"name\":\"Jack2\",\"leader\":false}]},{\"id\":89,\"players\":[{\"id\":57,\"name\":\"Rose3\",\"leader\":true},{\"id\":68,\"name\":\"Jack3\",\"leader\":false}]}]}";
    const char* json_history_end = json_history + strlen(json_history);

    Json::Reader reader;
    test_data::CMatchHistory history;
    Json::Value historyValue;

    reader.parse(json_history, json_history_end, historyValue);

    CHECK_VALUE("json_test", NodeValueLoad<json_node_parser>(history, historyValue));
    return test_verifier::verifyHistory("json_test", history);
}

bool testResponse()
{
    const char* json_response = "{\"response\": {\"test_id\": \"76561198085675982\",\"ret_code\": 1}}";
    const char* json_response_end = json_response + strlen(json_response);

    Json::Reader reader;
    test_data::CResponseInfo response;
    Json::Value responseValue;

    reader.parse(json_response, json_response_end, responseValue);

    const Json::Value& v = responseValue["response"];

    CHECK_VALUE("json_test", NodeValueLoad<json_node_parser>(response, v));
    return test_verifier::verifyResponse("json_test", response);
}

bool testResponseWithMessage()
{
    const char* json_response = "{\"response\": {\"test_id\": \"76561198085675982\",\"ret_code\": 42, \"message\": \"test message\"}}";
    const char* json_response_end = json_response + strlen(json_response);

    Json::Reader reader;
    test_data::CResponseInfo response;
    Json::Value responseValue;

    reader.parse(json_response, json_response_end, responseValue);

    const Json::Value& v = responseValue["response"];

    CHECK_VALUE("json_test", NodeValueLoad<json_node_parser>(response, v));
    return test_verifier::verifyResponseWithMsg("json_test", response);
}

}


bool test_json_node_parser()
{
    CHECK_VALUE("json_test", test_json_details::testPlayer());
    CHECK_VALUE("json_test", test_json_details::testMatch());
    CHECK_VALUE("json_test", test_json_details::testHistory());
    CHECK_VALUE("json_test", test_json_details::testResponse());
    CHECK_VALUE("json_test", test_json_details::testResponseWithMessage());

    return true;
}
