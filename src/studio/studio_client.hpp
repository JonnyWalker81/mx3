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

class studio_client : public mx3_gen::StudioVm,
                      public std::enable_shared_from_this<studio_client>{
public:
    studio_client(const std::shared_ptr<mx3_gen::Http> &pHttp, const shared_ptr<mx3::SingleThreadTaskRunner>& bg_runner, const std::shared_ptr<mx3_gen::StudioObserver> & studioObserver);
    virtual void login(const std::string &username, const std::string &password);
    virtual void getSessions();


private:
    mx3::Http _http;
    AuthorizeResponseDto _authDto;
    const std::shared_ptr<mx3_gen::StudioObserver> _observer;
};


#endif //MX3_STUDIO_CLIENT_HPP
