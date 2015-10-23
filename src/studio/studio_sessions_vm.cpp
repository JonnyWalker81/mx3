//
// Created by Jonathan Rothberg on 10/22/15.
//

#include <iostream>
#include "studio_sessions_vm.hpp"

studio_sessions_vm::studio_sessions_vm(const std::shared_ptr<studio_client>& pClient, const std::shared_ptr<mx3_gen::StudioSessionsDocumentsObserver> & observer)
    : _studioClient{pClient}, _observer{observer}
{

}

std::experimental::optional<mx3_gen::StudioSessionCell> studio_sessions_vm::getSession(int32_t index)
{
    if(index < getSessionCount() && index >= 0)
    {
        return mx3_gen::StudioSessionCell{m_oSessions[index].id, m_oSessions[index].name};
    }

    return nullopt;
}

int32_t studio_sessions_vm::getSessionCount()
{
    return static_cast<int32_t>(m_oSessions.size());
}

void studio_sessions_vm::getSessions()
{
    /*std::unordered_map<std::string, std::string> headers;
    headers["Authorization"] = "Bearer " + _authDto.getAccessToken();
    for (const auto &p : headers) {
        std::cout << "m[" << p.first << "] = " << p.second << '\n';
    }
     */

    const auto self = shared_from_this();
    _studioClient.lock().get("https://studioapi-dev.bluebeam.com/PublicAPI/v1/sessions", nullopt, [self] (mx3::HttpResponse resp)
    {
        std::cout << "Sessions Response: " << resp.data << std::endl;

        const auto sessions = SessionsDto::Parse(resp.data);

        self->m_oSessions = sessions;
        self->_studioClient.lock().post([self, sessions](){
            self->_observer->OnSessionsRetrieved(sessions);
        });
    });
}
