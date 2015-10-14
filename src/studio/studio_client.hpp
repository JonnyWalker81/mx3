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
#include "single_thread_task_runner.hpp"

class studio_client : public mx3_gen::Studio{
public:
    studio_client(const std::shared_ptr<mx3_gen::Http> &pHttp, const shared_ptr<mx3::SingleThreadTaskRunner>& bg_runner);
    virtual void login(const std::string &username, const std::string &password);

private:
    mx3::Http _http;
};


#endif //MX3_STUDIO_CLIENT_HPP
