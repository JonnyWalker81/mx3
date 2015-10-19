//
// Created by Jonathan Rothberg on 10/14/15.
//

#ifndef MX3_STUDIO_DTO_HPP
#define MX3_STUDIO_DTO_HPP

#import <string>
#include <vector>
#include "SessionsDto.hpp"

class AuthorizeResponseDto
{
public:
    static AuthorizeResponseDto Parse(const std::string &json);

    AuthorizeResponseDto();
    AuthorizeResponseDto(const std::string &pAccessToken, const std::string &pTokenType, const int &pExpiresIn, const std::string &pScope, const std::string &pRefreshTokenExpiresIn);

    const std::string & getAccessToken() const;

    const std::string & getTokenType() const;

    int getExpiresIn() const;

    const std::string & getScope() const;

    const std::string & getRefreshTokenExpiresIn() const;

private:
    std::string _accessToken;
    std::string _tokenType;
    int _expiresIn;
    std::string _scope;
    std::string _refreshTokenExpiresIn;
};

class SessionsDto
{
public:
    static std::vector<mx3_gen::SessionsDto> Parse(const std::string &json);

    SessionsDto();
    SessionsDto(const std::string &pId,
            const std::string &pName, const bool &pIsRestricted,
            const std::string &pExpirationDate, const int pVersion,
            const std::string &pCreated, const std::string &pInviteUrl,
            const std::string &pOwnerEmail, const std::string &pStatus);

    std::string getId();

    std::string getName();

    bool isRestricted() const;

    const std::string &getExpirationDate() const;

    int getVersion() const;

    const std::string &getCreated() const;

    const std::string &getInviteUrl() const;

    const std::string &getOwnerEmail() const;

    const std::string &getStatus() const;

private:
    std::string _id;
    std::string _name;
    bool _restricted;
    std::string _expirationDate;
    int _version;
    std::string _created;
    std::string _inviteUrl;
    std::string _ownerEmail;
    std::string _status;
};


#endif //MX3_STUDIO_DTO_HPP
