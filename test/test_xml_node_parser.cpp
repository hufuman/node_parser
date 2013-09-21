#include "test_node_parser.h"




#include <map>
#include <vector>
#include <iostream>


#include "../3rdlib/tinyxml/tinyxml.h"
#pragma comment(lib, "tinyxml.lib")


#include "../lib/node_parser.h"
#include "../lib/xml_node_parser.h"


#include "test_data_def.h"
#include "test_verifier.h"

namespace test_xml_details
{

//////////////////////////////////////////////////////////////////////////
// Test
bool testPlayer()
{
    const char* xml_player = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?><player id=\"23\" name=\"Jack\" leader=\"false\"></player>";

    test_data::CPlayer player;
    TiXmlDocument doc;
    doc.Parse(xml_player);
    TiXmlElement* root = doc.FirstChildElement("player");

    CHECK_VALUE("xml_test", NodeValueLoad<xml_node_parser>(player, *root));
    return test_verifier::verifyPlayer("xml_test", player);
}

bool testMatch()
{
    const char* xml_match = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?><match id=\"78\"><players><player id=\"23\" name=\"Rose\" leader=\"true\" /><player id=\"34\" name=\"Jack\" leader=\"false\" /></players></match>";

    test_data::CMatch match;
    TiXmlDocument doc;
    doc.Parse(xml_match);
    TiXmlElement* root = doc.FirstChildElement("match");

    CHECK_VALUE("xml_test", NodeValueLoad<xml_node_parser>(match, *root));
    return test_verifier::verifyMatch("xml_test", match);
}

bool testHistory()
{
    const char* xml_history = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?><history count=\"2\" remain=\"8\"><matches><match id=\"25\"><players><player id=\"23\" name=\"Rose2\" leader=\"true\" /><player id=\"34\" name=\"Jack2\" leader=\"false\" /></players></match><match id=\"89\"><players><player id=\"57\" name=\"Rose3\" leader=\"true\" /><player id=\"68\" name=\"Jack3\" leader=\"false\" /></players></match></matches></history>";

    test_data::CMatchHistory history;
    TiXmlDocument doc;
    doc.Parse(xml_history);
    TiXmlElement* root = doc.FirstChildElement("history");

    CHECK_VALUE("xml_test", NodeValueLoad<xml_node_parser>(history, *root));
    return test_verifier::verifyHistory("xml_test", history);
}

bool testResponse()
{
    const char* xml_response = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?><response test_id=\"76561198085675982\" ret_code=\"1\"></response>";

    test_data::CResponseInfo response;
    TiXmlDocument doc;
    doc.Parse(xml_response);
    TiXmlElement* root = doc.FirstChildElement("response");

    CHECK_VALUE("xml_test", NodeValueLoad<xml_node_parser>(response, *root));
    return test_verifier::verifyResponse("xml_test", response);
}

bool testResponseWithMessage()
{
    const char* xml_response = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?><response test_id=\"76561198085675982\" ret_code=\"42\" message=\"test message\"></response>";

    test_data::CResponseInfo response;
    TiXmlDocument doc;
    doc.Parse(xml_response);
    TiXmlElement* root = doc.FirstChildElement("response");

    CHECK_VALUE("xml_test", NodeValueLoad<xml_node_parser>(response, *root));
    return test_verifier::verifyResponseWithMsg("xml_test", response);

}

}

bool test_xml_node_parser()
{
    CHECK_VALUE("xml_test", test_xml_details::testPlayer());
    CHECK_VALUE("xml_test", test_xml_details::testMatch());
    CHECK_VALUE("xml_test", test_xml_details::testHistory());
    CHECK_VALUE("xml_test", test_xml_details::testResponse());
    CHECK_VALUE("xml_test", test_xml_details::testResponseWithMessage());

    return true;
}
