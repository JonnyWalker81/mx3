//
// Created by Jonathan Rothberg on 10/14/15.
//

#ifndef MX3_STUDIO_DTO_HPP
#define MX3_STUDIO_DTO_HPP

#import <string>

class AuthorizeResponseDto
{
public:
    static AuthorizeResponseDto Parse(const std::string &json);

    AuthorizeResponseDto();
    AuthorizeResponseDto(std::string &pAccessToken, std::string &pTokenType, int &pExpiresIn, std::string &pScope, std::string &pRefreshTokenExpiresIn);

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


#endif //MX3_STUDIO_DTO_HPP
