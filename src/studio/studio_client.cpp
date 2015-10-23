//
// Created by Jonathan Rothberg on 10/13/15.
//

#include <iostream>
#include <json11/json11.hpp>
#include "studio_client.hpp"

std::shared_ptr<mx3_gen::StudioVm> mx3_gen::StudioVm::createStudioClient(const std::shared_ptr<Http> & http_impl,
        const std::shared_ptr<mx3_gen::EventLoop>& ui_thread,
        const std::shared_ptr<ThreadLauncher> & launcher,
        const std::shared_ptr<StudioObserver> & studioObserver)
{
    const auto bg_runner = std::make_shared<mx3::EventLoopCpp>(launcher);
    const auto ui_runner = std::make_shared<mx3::EventLoopRef>(ui_thread);
    return std::make_shared<studio_client>(http_impl, ui_runner, bg_runner, studioObserver);
};

studio_client::studio_client(const std::shared_ptr<mx3_gen::Http> &pHttp,
        const std::shared_ptr<mx3::SingleThreadTaskRunner>& ui_thread,
        const std::shared_ptr<mx3::SingleThreadTaskRunner> &pLauncher,
        const std::shared_ptr<mx3_gen::StudioObserver> & studioObserver)
    : _http{pHttp, pLauncher}, _authDto{}, _observer{studioObserver}, m_ui_thread{ui_thread}
{

}

void studio_client::login(const std::string &username, const std::string &password) {
    std::cout << username << "  " << password;

    std::ostringstream out;
    out << "grant_type=password&username=" << username << "&password=" << password;
    const auto self = shared_from_this();
    _http.post("https://authserverdev.bluebeam.com/auth/token", out.str(), nullopt, [self] (mx3::HttpResponse resp)
    {
        std::cout << "Login Response: " << resp.data << std::endl;
        std::string err;
        self->_authDto = AuthorizeResponseDto::Parse(resp.data);
        self->m_ui_thread->post([self](){
            self->_observer->OnLogin();
        });
    });
}

std::shared_ptr<mx3_gen::StudioSessionsVm> studio_client::getSessionsVm(const std::shared_ptr<mx3_gen::StudioSessionsObserver> &observer)
{
    if(!_sessionsVm)
        _sessionsVm = std::make_shared<studio_sessions_vm>(shared_from_this());

    return _sessionsVm;
}

std::shared_ptr<mx3_gen::StudioSessionDocumentsVm> studio_client::getSessionDocumentsVm(const std::shared_ptr<mx3_gen::StudioSessionsDocumentsObserver> &observer)
{
    if(!_sessionDocumentsVm)
        _sessionDocumentsVm = std::make_shared<studio_sessions_documents_vm>(shared_from_this());

    return _sessionDocumentsVm;
}

void studio_client::get(const std::string &url, const std::experimental::optional<std::unordered_map<std::string, std::string>> &headers, const std::shared_ptr<mx3_gen::HttpCallback> &callback)
{
    _http.get(url, headers, callback);
}

void studio_client::post(const std::string &url, const std::string &body, const std::experimental::optional<std::unordered_map<std::string, std::string>> &headers, const std::shared_ptr<mx3_gen::HttpCallback> &callback)
{
    _http.post(url, body, headers, callback);
}

void studio_client::executeOnMainThread(std::function<void()> pTask)
{
    m_ui_thread->post(pTask);f
}
