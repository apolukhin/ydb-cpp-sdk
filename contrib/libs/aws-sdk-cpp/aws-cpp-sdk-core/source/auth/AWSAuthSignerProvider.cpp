/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */
 
#include <aws/core/utils/logging/LogMacros.h> 
#include <aws/core/auth/AWSAuthSignerProvider.h> 
#include <aws/core/auth/AWSAuthSigner.h> 
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/core/utils/memory/stl/AWSAllocator.h>
 
const char CLASS_TAG[] = "AuthSignerProvider"; 
 
using namespace Aws::Auth; 

DefaultAuthSignerProvider::DefaultAuthSignerProvider(const std::shared_ptr<AWSCredentialsProvider>& credentialsProvider,
        const Aws::String& serviceName, const Aws::String& region)
{
    m_signers.emplace_back(Aws::MakeShared<Aws::Client::AWSAuthV4Signer>(CLASS_TAG, credentialsProvider, serviceName.c_str(), region));
    m_signers.emplace_back(Aws::MakeShared<Aws::Client::AWSAuthEventStreamV4Signer>(CLASS_TAG, credentialsProvider, serviceName.c_str(), region));
    m_signers.emplace_back(Aws::MakeShared<Aws::Client::AWSNullSigner>(CLASS_TAG));
}

DefaultAuthSignerProvider::DefaultAuthSignerProvider(const std::shared_ptr<Aws::Client::AWSAuthSigner>& signer) 
{ 
    m_signers.emplace_back(Aws::MakeShared<Aws::Client::AWSNullSigner>(CLASS_TAG)); 
    if(signer) 
    { 
        m_signers.emplace_back(signer); 
    } 
} 
 
std::shared_ptr<Aws::Client::AWSAuthSigner> DefaultAuthSignerProvider::GetSigner(const Aws::String& signerName) const 
{ 
    for(const auto& signer : m_signers) 
    { 
        if(signer->GetName() == signerName) 
        { 
            return signer; 
        } 
    } 
    AWS_LOGSTREAM_ERROR(CLASS_TAG, "Request's signer: '" << signerName << "' is not found in the signer's map."); 
    assert(false); 
    return nullptr; 
} 

void DefaultAuthSignerProvider::AddSigner(std::shared_ptr<Aws::Client::AWSAuthSigner>& signer)
{
    assert(signer);
    m_signers.emplace_back(signer);
}
