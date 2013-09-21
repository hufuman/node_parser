#pragma once



#include "test_data_def.h"


namespace test_verifier
{
    bool verifyPlayer(const char* msg, const test_data::CPlayer& player);
    bool verifyMatch(const char* msg, const test_data::CMatch& match);
    bool verifyHistory(const char* msg, const test_data::CMatchHistory& history);
    bool verifyResponse(const char* msg, const test_data::CResponseInfo& response);
    bool verifyResponseWithMsg(const char* msg, const test_data::CResponseInfo& response);
};
