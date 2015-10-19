//
// Created by Jonathan Rothberg on 10/14/15.
//

#include "studio_dto.hpp"
#include <json11/json11.hpp>
#include <string>
#include <memory>
#include <iosfwd>
#include <bitset>
#include <iostream>

AuthorizeResponseDto::AuthorizeResponseDto() : _expiresIn{0}
{
}

AuthorizeResponseDto::AuthorizeResponseDto(const std::string &pAccessToken, const std::string &pTokenType,
        const int &pExpiresIn, const std::string &pScope, const std::string &pRefreshTokenExpiresIn)
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

SessionsDto::SessionsDto(): _version{0}
{
}

SessionsDto::SessionsDto(const std::string &pId, const std::string &pName, const bool &pIsRestricted,
        const std::string &pExpirationDate, const int pVersion, const std::string &pCreated,
        const std::string &pInviteUrl, const std::string &pOwnerEmail, const std::string &pStatus)
    : _id{pId}, _name{pName}, _restricted{pIsRestricted}, _expirationDate{pExpirationDate}, _version{pVersion},
      _created{pCreated}, _inviteUrl{pInviteUrl}, _ownerEmail{pOwnerEmail}, _status{pStatus}
{

}

std::string SessionsDto::getId()
{
    return _id;
}

std::string SessionsDto::getName()
{
    return _name;
}

bool SessionsDto::isRestricted() const
{
    return _restricted;
}

const std::string &SessionsDto::getExpirationDate() const
{
    return _expirationDate;
}

int SessionsDto::getVersion() const
{
    return _version;
}

const std::string &SessionsDto::getCreated() const
{
    return _created;
}

const std::string &SessionsDto::getInviteUrl() const
{
    return _inviteUrl;
}

const std::string &SessionsDto::getOwnerEmail() const
{
    return _ownerEmail;
}

const std::string &SessionsDto::getStatus() const
{
    return _status;
}

std::vector<mx3_gen::SessionsDto> SessionsDto::Parse(const std::string &json)
{
    std::string err;
    json11::Json result = json11::Json::parse(json, err);
    if(!err.empty())
    {
        std::cout << "Error Parsing SessionsDto" << std::endl;
    }

    auto jsonSessions = result["Sessions"].array_items();

    std::vector<mx3_gen::SessionsDto> sessions;

    for(const auto &jsonSession: jsonSessions)
    {
        auto id = jsonSession["Id"].string_value();
        auto name = jsonSession["Name"].string_value();
        /*auto isRestricted = jsonSession["Restricted"].bool_value();
        auto expirationDate = jsonSession["ExpirationDate"].string_value();
        auto version = jsonSession["Version"].int_value();
        auto created = jsonSession["Created"].string_value();
        auto inviteUrl = jsonSession["InviteUrl"].string_value();
        auto ownerEmail = jsonSession["OwnerEmail"].string_value();
        auto status = jsonSession["Status"].string_value();
         */

        //auto session = std::make_shared<SessionsDto>(id, name, isRestricted, expirationDate, version, created, inviteUrl, ownerEmail, status);
        sessions.push_back({name, id});
    }

    return std::move(sessions);
}

