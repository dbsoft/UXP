/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_dom_cache_CacheStorageParent_h
#define mozilla_dom_cache_CacheStorageParent_h

#include "mozilla/dom/cache/PCacheStorageParent.h"
#include "mozilla/dom/cache/PrincipalVerifier.h"
#include "mozilla/dom/cache/Types.h"

namespace mozilla {
namespace dom {
namespace cache {

class ManagerId;

class CacheStorageParent final : public PCacheStorageParent
                               , public PrincipalVerifier::Listener
{
public:
  CacheStorageParent(PBackgroundParent* aManagingActor, Namespace aNamespace,
                     const mozilla::ipc::PrincipalInfo& aPrincipalInfo);
  virtual ~CacheStorageParent();

private:
  // PCacheStorageParent methods
  virtual void
  ActorDestroy(ActorDestroyReason aReason) override;

  virtual PCacheOpParent*
  AllocPCacheOpParent(const CacheOpArgs& aOpArgs) override;

  virtual bool
  DeallocPCacheOpParent(PCacheOpParent* aActor) override;

  virtual bool
  RecvPCacheOpConstructor(PCacheOpParent* actor,
                          const CacheOpArgs& aOpArgs) override;

  virtual bool
  RecvTeardown() override;

  // PrincipalVerifier::Listener methods
  virtual void OnPrincipalVerified(nsresult aRv,
                                   ManagerId* aManagerId) override;

  const Namespace mNamespace;
  RefPtr<PrincipalVerifier> mVerifier;
  nsresult mVerifiedStatus;
  RefPtr<ManagerId> mManagerId;
};

} // namespace cache
} // namespace dom
} // namespace mozilla

#endif // mozilla_dom_cache_CacheStorageParent_h
