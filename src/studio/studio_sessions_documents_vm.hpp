//
// Created by Jonathan Rothberg on 10/22/15.
//

#ifndef MX3_STUDIO_SESSIONS_DOCUMENTS_VM_HPP
#define MX3_STUDIO_SESSIONS_DOCUMENTS_VM_HPP


#include "studio_session_documents_vm.hpp"
#include "http.hpp"
#include "studio_client.hpp"
#include "SessionDocumentDto.hpp"

class studio_sessions_documents_vm : public mx3_gen::StudioSessionDocumentsVm,
                                     public std::enable_shared_from_this<studio_sessions_documents_vm>
{

public:
    studio_sessions_documents_vm(const std::shared_ptr<studio_client>& pClient, const std::shared_ptr<mx3_gen::StudioSessionsDocumentsObserver> & observer);
    virtual void getDocuments();

    virtual int32_t getDocumentCount();

    virtual std::experimental::optional<mx3_gen::StudioDocumentCell> getDocument(int32_t index);

private:
    std::weak_ptr<studio_client> _studioClient;
    std::vector<mx3_gen::SessionDocumentDto> _documents;
    const std::shared_ptr<mx3_gen::StudioSessionsDocumentsObserver> _observer;
};


#endif //MX3_STUDIO_SESSIONS_DOCUMENTS_VM_HPP
