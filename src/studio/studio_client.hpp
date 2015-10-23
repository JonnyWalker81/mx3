//
// Created by Jonathan Rothberg on 10/13/15.
//

#ifndef MX3_STUDIO_CLIENT_HPP
#define MX3_STUDIO_CLIENT_HPP
#include "stl.hpp"
#include <json11/json11.hpp>
#include "event_loop.hpp"
#include "http.hpp"
#include "../interface/api.hpp"
#include "../interface/studio.hpp"
#include "../interface/SessionsDto.hpp"
#include "../interface/studio_observer.hpp"
#include "single_thread_task_runner.hpp"
#include "studio_dto.hpp"
#include "studio_vm.hpp"
#include "../interface/studio_session_cell.hpp"
#import "studio_sessions_vm.hpp"
#import "studio_sessions_documents_vm.hpp"
#import "studio_session_documents_vm.hpp"

class studio_client : public mx3_gen::StudioVm,
                      public std::enable_shared_from_this<studio_client>{
public:
    studio_client(const std::shared_ptr<mx3_gen::Http> &pHttp,
            const std::shared_ptr<mx3::SingleThreadTaskRunner>& ui_thread,
            const std::shared_ptr<mx3::SingleThreadTaskRunner>& bg_runner,
            const std::shared_ptr<mx3_gen::StudioObserver> & studioObserver);
    virtual void login(const std::string &username, const std::string &password);

    virtual void get(const std::string & url, const std::experimental::optional<std::unordered_map<std::string, std::string>> & headers, const std::shared_ptr<mx3_gen::HttpCallback> & callback);
    virtual void post(const std::string & url, const std::string & body, const std::experimental::optional<std::unordered_map<std::string, std::string>> & headers, const std::shared_ptr<mx3_gen::HttpCallback> & callback);

    virtual std::shared_ptr<mx3_gen::StudioSessionsVm> getSessionsVm(const std::shared_ptr<mx3_gen::StudioSessionsObserver> & observer);

    virtual std::shared_ptr<mx3_gen::StudioSessionDocumentsVm> getSessionDocumentsVm(const std::shared_ptr<mx3_gen::StudioSessionsDocumentsObserver> & observer);
    void executeOnMainThread(std::function<void()> pTask);

private:
    mx3::Http _http;
    AuthorizeResponseDto _authDto;
    const std::shared_ptr<mx3_gen::StudioObserver> _observer;
    const shared_ptr<mx3::SingleThreadTaskRunner> m_ui_thread;
    std::shared_ptr<mx3_gen::StudioSessionsVm> _sessionsVm;
    std::shared_ptr<mx3_gen::StudioSessionDocumentsVm> _sessionDocumentsVm;
};


#endif //MX3_STUDIO_CLIENT_HPP
