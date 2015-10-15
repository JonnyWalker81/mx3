//
// Created by Jonathan Rothberg on 10/13/15.
//

#include <iostream>
#include <json11/json11.hpp>
#include "studio_client.hpp"

std::shared_ptr<mx3_gen::Studio> mx3_gen::Studio::createStudioClient(const std::shared_ptr<Http> & http_impl, const std::shared_ptr<ThreadLauncher> & launcher)
{
    const auto bg_runner = make_shared<mx3::EventLoopCpp>(launcher);
    return std::make_shared<studio_client>(http_impl, bg_runner);
};

studio_client::studio_client(const std::shared_ptr<mx3_gen::Http> &pHttp, const std::shared_ptr<mx3::SingleThreadTaskRunner> &pLauncher)
    : _http{pHttp, pLauncher}, _authDto{}
{

}

void studio_client::login(const std::string &username, const std::string &password) {
    std::cout << username << "  " << password;

    std::ostringstream out;
    out << "grant_type=password&username=" << username << "&password=" << password;
    _http.post("https://authserver.bluebeam.com/auth/token", out.str(), nullopt, [this] (mx3::HttpResponse resp)
    {
        std::cout << "Login Response: " << resp.data << std::endl;
        std::string err;
        this->_authDto = AuthorizeResponseDto::Parse(resp.data);
    });
}

std::vector<std::shared_ptr<mx3_gen::SessionsDto>> studio_client::getSessions()
{
    std::unordered_map<std::string, std::string> headers;
    headers["Authorization"] = "Bearer " + _authDto.getAccessToken();
    for (const auto &p : headers) {
        std::cout << "m[" << p.first << "] = " << p.second << '\n';
    }
    _http.get("https://studioapi-dev.bluebeam.com/PublicAPI/v1/sessions", headers, [this] (mx3::HttpResponse resp)
    {
        std::cout << "Sessions Response: " << resp.data << std::endl;
    });

    return std::vector<std::shared_ptr<mx3_gen::SessionsDto>>();
}
