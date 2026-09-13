#pragma once

// Editor-only stand-ins for CUDA's lower-level pipeline intrinsics.
// These allow clangd to understand code that uses the manual API.

#ifndef __pipeline_memcpy_async
#define __pipeline_memcpy_async(destination, source, bytes) \
    ((void)(destination), (void)(source), (void)(bytes))
#endif

#ifndef __pipeline_commit
#define __pipeline_commit() ((void)0)
#endif

#ifndef __pipeline_wait_prior
#define __pipeline_wait_prior(stages) ((void)(stages))
#endif
