//
// Created by Jonathan Rothberg on 10/22/15.
//

#include "studio_sessions_documents_vm.hpp"

studio_sessions_documents_vm::studio_sessions_documents_vm(const std::shared_ptr<studio_client>& pClient, const std::shared_ptr<mx3_gen::StudioSessionsDocumentsObserver> & observer)
    : _studioClient{pClient}, _observer{observer}
{

}

int32_t studio_sessions_documents_vm::getDocumentCount()
{
    return 0;
}

std::experimental::optional<mx3_gen::StudioDocumentCell> studio_sessions_documents_vm::getDocument(int32_t index)
{
    return std::experimental::optional<mx3_gen::StudioDocumentCell>();
}
