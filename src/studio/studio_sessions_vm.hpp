//
// Created by Jonathan Rothberg on 10/22/15.
//

#ifndef MX3_STUDIO_SESSIONS_VM_HPP
#define MX3_STUDIO_SESSIONS_VM_HPP


#include <optional/optional.hpp>
#include "studio_session_cell.hpp"
#import "studio_sessions_vm.hpp"
#include "http.hpp"
#include "studio_client.hpp"

class studio_sessions_vm : public mx3_gen::StudioSessionsVm,
                           public std::enable_shared_from_this<studio_sessions_vm>
{
public:
    studio_sessions_vm(const std::shared_ptr<studio_client>& pClient, const std::shared_ptr<mx3_gen::StudioSessionsObserver> & observer);
    virtual void getSessions();
    virtual std::experimental::optional<mx3_gen::StudioSessionCell> getSession(int32_t index);

    virtual int32_t getSessionCount();

private:
    std::weak_ptr<studio_client> _studioClient;
    std::vector<mx3_gen::SessionsDto> m_oSessions;
    const std::shared_ptr<mx3_gen::StudioSessionsObserver> _observer;
};


#endif //MX3_STUDIO_SESSIONS_VM_HPP
