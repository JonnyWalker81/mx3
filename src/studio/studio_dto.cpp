//
// Created by Jonathan Rothberg on 10/14/15.
//

#include "studio_dto.hpp"
#include <json11/json11.hpp>
#include <string>
#include <memory>
#include <iosfwd>
#include <bitset>

AuthorizeResponseDto::AuthorizeResponseDto() : _expiresIn(0)
{
}

AuthorizeResponseDto::AuthorizeResponseDto(std::string &pAccessToken, std::string &pTokenType, int &pExpiresIn, std::string &pScope, std::string &pRefreshTokenExpiresIn)
    : _accessToken{pAccessToken}, _tokenType{pTokenType}, _expiresIn{pExpiresIn}, _scope{pScope}, _refreshTokenExpiresIn{pRefreshTokenExpiresIn}
{
}

int AuthorizeResponseDto::getExpiresIn() const
{
    return _expiresIn;
}

const std::string &AuthorizeResponseDto::getScope() const
{
    return _scope;
}

const std::string &AuthorizeResponseDto::getRefreshTokenExpiresIn() const
{
    return _refreshTokenExpiresIn;
}

const std::string &AuthorizeResponseDto::getTokenType() const
{
    return _tokenType;
}

const std::string &AuthorizeResponseDto::getAccessToken() const
{
    return _accessToken;
}

AuthorizeResponseDto AuthorizeResponseDto::Parse(const std::string &json)
{
    std::string err;
    json11::Json result = json11::Json::parse(json, err);
    auto accessToken = result["access_token"].string_value();
    auto tokenType = result["token_type"].string_value();
    auto expiresIn = result["expires_in"].int_value();
    auto scope = result["scope"].string_value();
    auto refreshTokenExpiresIn = result["refresh_token_expires_in"].string_value();
    return std::move(AuthorizeResponseDto{accessToken, tokenType, expiresIn, scope, refreshTokenExpiresIn});
}
