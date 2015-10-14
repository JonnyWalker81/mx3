//
// Created by Jonathan Rothberg on 10/13/15.
//

#include <iostream>
#include "studio_client.hpp"

std::shared_ptr<mx3_gen::Studio> mx3_gen::Studio::createStudioClient(const std::shared_ptr<Http> & http_impl, const std::shared_ptr<ThreadLauncher> & launcher)
{
    const auto bg_runner = make_shared<mx3::EventLoopCpp>(launcher);
    return std::make_shared<studio_client>(http_impl, bg_runner);
};

studio_client::studio_client(const std::shared_ptr<mx3_gen::Http> &pHttp, const std::shared_ptr<mx3::SingleThreadTaskRunner> &pLauncher)
    : _http{pHttp, pLauncher}
{

}

void studio_client::login(const std::string &username, const std::string &password) {
    std::cout << username << "  " << password;
}
