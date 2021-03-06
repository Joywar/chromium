/*
 * Copyright (C) 2009 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WebKitClient_h
#define WebKitClient_h

#include "WebCommon.h"

namespace WebKit {
    class WebClipboard;
    class WebData;
    class WebMimeRegistry;
    class WebPluginListBuilder;
    class WebSandboxSupport;
    class WebString;
    class WebThemeEngine;
    class WebURL;
    class WebURLLoader;
    struct WebPluginInfo;
    template <typename T> class WebVector;

    class WebKitClient {
    public:
        // Must return non-null.
        virtual WebClipboard* clipboard() = 0;

        // Must return non-null.
        virtual WebMimeRegistry* mimeRegistry() = 0;

        // May return null if sandbox support is not necessary
        virtual WebSandboxSupport* sandboxSupport() = 0;

        // May return null on some platforms.
        virtual WebThemeEngine* themeEngine() = 0;


        // History -------------------------------------------------------------

        // Returns the hash for the given canonicalized URL for use in visited
        // link coloring.
        virtual unsigned long long visitedLinkHash(
            const char* canonicalURL, size_t length) = 0;

        // Returns whether the given link hash is in the user's history.  The
        // hash must have been generated by calling VisitedLinkHash().
        virtual bool isLinkVisited(unsigned long long linkHash) = 0;


        // Network -------------------------------------------------------------

        virtual void setCookies(
            const WebURL& url, const WebURL& policyURL, const WebString& cookies) = 0;
        virtual WebString cookies(const WebURL& url, const WebURL& policyURL) = 0;

        // A suggestion to prefetch IP information for the given hostname.
        virtual void prefetchHostName(const WebString&) = 0;

        // File ----------------------------------------------------------------

        virtual bool getFileSize(const WebString& path, long long& result) = 0;

        // Returns a new WebURLLoader instance.
        virtual WebURLLoader* createURLLoader() = 0;


        // Plugins -------------------------------------------------------------

        // If refresh is true, then cached information should not be used to
        // satisfy this call.
        virtual void getPluginList(bool refresh, WebPluginListBuilder*) = 0;


        // Profiling -----------------------------------------------------------

        virtual void decrementStatsCounter(const char* name) = 0;
        virtual void incrementStatsCounter(const char* name) = 0;

        // An event is identified by the pair (name, id).  The extra parameter
        // specifies additional data to log with the event.
        virtual void traceEventBegin(const char* name, void* id, const char* extra) = 0;
        virtual void traceEventEnd(const char* name, void* id, const char* extra) = 0;


        // Resources -----------------------------------------------------------

        // Returns a blob of data corresponding to the named resource.
        virtual WebData loadResource(const char* name) = 0;


        // Sudden Termination --------------------------------------------------

        // Disable/Enable sudden termination.
        virtual void suddenTerminationChanged(bool enabled) = 0;


        // System --------------------------------------------------------------

        // Returns a value such as "en-US".
        virtual WebString defaultLocale() = 0;

        // Wall clock time in seconds since the epoch.
        virtual double currentTime() = 0;

        // Delayed work is driven by a shared timer.
        virtual void setSharedTimerFiredFunction(void (*func)()) = 0;
        virtual void setSharedTimerFireTime(double fireTime) = 0;
        virtual void stopSharedTimer() = 0;

        // Callable from a background WebKit thread.
        virtual void callOnMainThread(void (*func)()) = 0;
    };

} // namespace WebKit

#endif
