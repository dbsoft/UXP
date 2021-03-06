/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef jit_x86_BaselineCompiler_x86_h
#define jit_x86_BaselineCompiler_x86_h

#include "jit/x86-shared/BaselineCompiler-x86-shared.h"

namespace js {
namespace jit {

class BaselineCompilerX86 : public BaselineCompilerX86Shared
{
  protected:
    BaselineCompilerX86(JSContext* cx, TempAllocator& alloc, JSScript* script);
};

typedef BaselineCompilerX86 BaselineCompilerSpecific;

} // namespace jit
} // namespace js

#endif /* jit_x86_BaselineCompiler_x86_h */
