
#include "third_party/WebKit/public/web/WebFrameClient.h"
#include "third_party/WebKit/Source/web/WebLocalFrameImpl.h"
#include "third_party/WebKit/Source/web/WebViewImpl.h"
#include "third_party/WebKit/public/web/WebDocument.h"
#include "content/browser/WebFrameClientImpl.h"
#include "content/browser/WebPage.h"
#include "content/web_impl_win/WebCookieJarCurlImpl.h"
#include "content/web_impl_win/WebMediaPlayerImpl.h"
#include "cef/include/capi/cef_base_capi.h"
#include "cef/include/capi/cef_browser_capi.h"
#include "cef/include/capi/cef_client_capi.h"
#include "cef/include/internal/cef_ptr.h"
#include "cef/include/internal/cef_export.h"
#include "cef/include/cef_app.h"
#include "cef/include/cef_client.h"
#include "cef/libcef/common/CommonBase.h"
#include "cef/libcef/common/CefRequestImpl.h"
#include "cef/libcef/common/CefContentClient.h"
#include "cef/libcef/common/StringUtil.h"
#include "cef/libcef/browser/CefFrameHostImpl.h"
#include "cef/libcef/browser/CefBrowserHostImpl.h"
#include "cef/libcef/renderer/CefV8Impl.h"
#include "third_party/WebKit/Source/platform/Language.h"
#include "third_party/WebKit/Source/core/frame/Settings.h"
#include "third_party/WebKit/Source/core/page/Page.h"
#include "net/RequestExtraData.h"
#include "wke/wkeWebView.h"
#include "wke/wkeJsBind.h"

namespace content {

WebFrameClientImpl::WebFrameClientImpl()
{
    m_loading = false;
    m_loadFailed = false;
    m_loaded = false;
    m_documentReady = false;
    m_webPage = nullptr;
}

WebFrameClientImpl::~WebFrameClientImpl()
{
    for (size_t i = 0; i < m_unusedFrames.size(); ++i) {
        WebFrame* frame = m_unusedFrames[i];
        frame->close();
    }
    m_unusedFrames.clear();
}

void WebFrameClientImpl::didAddMessageToConsole(const WebConsoleMessage& message,
    const WebString& sourceName, unsigned sourceLine, const WebString& stackTrace)
{
//     WTF::String outstr(L"console:");
// 
//     outstr.append((WTF::String)(message.text));
//     outstr.append(L" ;sourceName:");
//     outstr.append(sourceName);
// 
//     outstr.append(L" ;sourceLine:");
//     outstr.append(String::number(sourceLine));
//     outstr.append(L" \n");
//     OutputDebugStringW(outstr.charactersWithNullTermination().data());
}

void WebFrameClientImpl::setWebPage(WebPage* webPage)
{
    m_webPage = webPage;
}

WebPage* WebFrameClientImpl::webPage()
{
    return m_webPage;
}

WebFrame* WebFrameClientImpl::createChildFrame(WebLocalFrame* parent, WebTreeScopeType, const WebString& frameName, WebSandboxFlags sandboxFlags)
{
    WebLocalFrameImpl* webLocalFrameImpl = WebLocalFrameImpl::create(WebTreeScopeType::Document, this);
    parent->appendChild(webLocalFrameImpl);

	CefBrowserHostImpl* browser = m_webPage->browser();
	if (browser)
		browser->OnFrameIdentified(webLocalFrameImpl, parent);
	
    if (WTF::kNotFound == m_unusedFrames.find(webLocalFrameImpl))
        m_unusedFrames.append(webLocalFrameImpl);

    return webLocalFrameImpl; // TODO delete;
}

void WebFrameClientImpl::frameDetached(WebFrame* child, DetachType)
{
    if (WebFrame* parent = child->parent())
        parent->removeChild(child);
}

blink::WebPluginPlaceholder* WebFrameClientImpl::createPluginPlaceholder(WebLocalFrame*, const blink::WebPluginParams&) { return 0; }

blink::WebPlugin* WebFrameClientImpl::createPlugin(WebLocalFrame*, const WebPluginParams&) { return 0; }

blink::WebMediaPlayer* WebFrameClientImpl::createMediaPlayer(WebLocalFrame* frame, const WebURL& url , WebMediaPlayerClient* client, WebContentDecryptionModule*)
{
    return new WebMediaPlayerImpl(frame, url, client);
}

blink::WebMediaPlayer* WebFrameClientImpl::createMediaPlayer(WebLocalFrame* frame, const WebURL& url, WebMediaPlayerClient* client, WebMediaPlayerEncryptedMediaClient*, WebContentDecryptionModule*)
{
    return new WebMediaPlayerImpl(frame, url, client);
}

blink::WebApplicationCacheHost* WebFrameClientImpl::createApplicationCacheHost(WebLocalFrame*, WebApplicationCacheHostClient*) { return 0; }

blink::WebServiceWorkerProvider* WebFrameClientImpl::createServiceWorkerProvider(WebLocalFrame* frame) { return 0; }

blink::WebWorkerContentSettingsClientProxy* WebFrameClientImpl::createWorkerContentSettingsClientProxy(WebLocalFrame* frame) { return 0; }

// Create a new WebPopupMenu. In the "createExternalPopupMenu" form, the
// client is responsible for rendering the contents of the popup menu.
WebExternalPopupMenu* WebFrameClientImpl::createExternalPopupMenu(const WebPopupMenuInfo&, WebExternalPopupMenuClient*) {
    return 0;
}

WebCookieJar* WebFrameClientImpl::cookieJar(WebLocalFrame*)
{
    return WebCookieJarImpl::inst();
}

void WebFrameClientImpl::onLoadingStateChange(bool isLoading, bool toDifferentDocument)
{
    m_loading = isLoading;

    if (!m_webPage)
        return;
    CefBrowserHostImpl* browser = m_webPage->browser();
    if (!browser || !browser->client().get())
        return;

	browser->OnLoadingStateChange(isLoading, toDifferentDocument);

    WebViewImpl* webview = m_webPage->webViewImpl();
    if (!webview || !webview->client())
        return;

    bool canGoBack = webview->client()->historyForwardListCount() > 0;
    bool canGoForward = webview->client()->historyBackListCount() > 0;

    CefRefPtr<CefLoadHandler> handler = browser->client()->GetLoadHandler();
    if (handler.get())
        handler->OnLoadingStateChange(browser, isLoading, canGoBack, canGoForward);
}

void WebFrameClientImpl::didStartLoading(bool toDifferentDocument)
{
    onLoadingStateChange(true, toDifferentDocument);
}

void WebFrameClientImpl::didStopLoading()
{
    onLoadingStateChange(false, true);
}

void WebFrameClientImpl::didChangeLoadProgress(double loadProgress)
{
    onLoadingStateChange(loadProgress != 1.0, true);
}

void WebFrameClientImpl::willSendSubmitEvent(WebLocalFrame*, const WebFormElement&) { }
void WebFrameClientImpl::willSubmitForm(WebLocalFrame*, const WebFormElement&) { }

void WebFrameClientImpl::didCreateDataSource(WebLocalFrame*, WebDataSource*) { }

void WebFrameClientImpl::didStartProvisionalLoad(WebLocalFrame* localFrame, double triggeringEventTime)
{
	CefBrowserHostImpl* browser = m_webPage->browser();
	if (browser)
		browser->DidStartProvisionalLoad(localFrame, triggeringEventTime);
}

void WebFrameClientImpl::didReceiveServerRedirectForProvisionalLoad(WebLocalFrame*) { }

void WebFrameClientImpl::didFailProvisionalLoad(WebLocalFrame* frame, const WebURLError& error, WebHistoryCommitType type)
{
    m_loadFailed = true;

	CefBrowserHostImpl* browser = m_webPage->browser();
	if (browser)
		browser->DidFailProvisionalLoad(frame, error, type);

    wke::CWebViewHandler& handler = m_webPage->wkeHandler();
    if (handler.loadingFinishCallback) {
        wkeLoadingResult result = WKE_LOADING_FAILED;
        wke::CString failedReason(error.localizedDescription);
        wke::CString url(error.unreachableURL.string());

        if (error.isCancellation)
            result = WKE_LOADING_CANCELED;

        handler.loadingFinishCallback(m_webPage->wkeWebView(), handler.loadingFinishCallbackParam, &url, result, &failedReason);
    }
}

void WebFrameClientImpl::didCommitProvisionalLoad(WebLocalFrame* frame, const WebHistoryItem& history, WebHistoryCommitType type)
{
    CefBrowserHostImpl* browser = m_webPage->browser();
    if (!browser)
        return;
    browser->DidCommitProvisionalLoadForFrame(frame, history);
}

void WebFrameClientImpl::didCreateNewDocument(WebLocalFrame* frame) { }

void WebFrameClientImpl::didClearWindowObject(WebLocalFrame* frame) { }

void WebFrameClientImpl::didCreateDocumentElement(WebLocalFrame* frame) { }

void WebFrameClientImpl::didReceiveTitle(WebLocalFrame* frame, const WebString& title, WebTextDirection direction)
{
    if (frame == m_webPage->mainFrame()) {
        m_title = title;
        wke::CWebViewHandler& handler = m_webPage->wkeHandler();
        if (handler.titleChangedCallback) {
            wke::CString string(title);
            handler.titleChangedCallback(m_webPage->wkeWebView(), handler.titleChangedCallbackParam, &string);
        }
    }
}

void WebFrameClientImpl::didChangeIcon(WebLocalFrame*, WebIconURL::Type) { }

void WebFrameClientImpl::didFinishDocumentLoad(WebLocalFrame*)
{
    //     cef_load_handler_t* loadHandler = m_cefBrowserHostImpl->m_browserImpl->m_loadHandler;
    //     m_cefBrowserHostImpl->m_browserImpl->ref();
    //     loadHandler->on_loading_state_change(loadHandler, &m_cefBrowserHostImpl->m_browserImpl->m_baseClass, false, false, false);

    m_documentReady = true;

    wke::CWebViewHandler& handler = m_webPage->wkeHandler();
    if (handler.documentReadyCallback)
        handler.documentReadyCallback(m_webPage->wkeWebView(), handler.documentReadyCallbackParam);
}

void WebFrameClientImpl::didHandleOnloadEvents(WebLocalFrame*) { }

void WebFrameClientImpl::didFailLoad(WebLocalFrame* frame, const WebURLError& error, WebHistoryCommitType type)
{
    m_loadFailed = true;

	CefBrowserHostImpl* browser = m_webPage->browser();
	if (browser)
		browser->DidFailLoad(frame, error, type);

    wke::CWebViewHandler& handler = m_webPage->wkeHandler();
    if (handler.loadingFinishCallback) {
        wkeLoadingResult result = WKE_LOADING_FAILED;
        wke::CString failedReason(error.localizedDescription);
        wke::CString url(error.unreachableURL.string());

        if (error.isCancellation)
            result = WKE_LOADING_CANCELED;

        handler.loadingFinishCallback(m_webPage->wkeWebView(), handler.loadingFinishCallbackParam, &url, result, &failedReason);
    }
}

void WebFrameClientImpl::didFinishLoad(WebLocalFrame* frame)
{
    m_loaded = true;

    CefBrowserHostImpl* browser = m_webPage->browser();
    if (browser)
        browser->DidFinishLoad(frame);

    wke::CWebViewHandler& handler = m_webPage->wkeHandler();
    if (handler.loadingFinishCallback) {
        wkeLoadingResult result = WKE_LOADING_SUCCEEDED;
        blink::WebFrame* frame = m_webPage->mainFrame();
        wke::CString url(frame->document().url().string());
        handler.loadingFinishCallback(m_webPage->wkeWebView(), handler.loadingFinishCallbackParam, &url, result, NULL);
    }
}

void WebFrameClientImpl::didNavigateWithinPage(WebLocalFrame*, const WebHistoryItem&, WebHistoryCommitType)
{
    //     cef_load_handler_t* loadHandler = m_cefBrowserHostImpl->m_browserImpl->m_loadHandler;
    //     m_cefBrowserHostImpl->m_browserImpl->ref();
    //     loadHandler->on_loading_state_change(loadHandler, &m_cefBrowserHostImpl->m_browserImpl->m_baseClass, false, false, false);
}

void WebFrameClientImpl::didUpdateCurrentHistoryItem(WebLocalFrame*) { }

void WebFrameClientImpl::didChangeManifest(WebLocalFrame*) { }

void WebFrameClientImpl::didChangeDefaultPresentation(WebLocalFrame*) { }
void WebFrameClientImpl::didChangeThemeColor() { }

void WebFrameClientImpl::dispatchLoad() { }

WebNavigationPolicy WebFrameClientImpl::decidePolicyForNavigation(const NavigationPolicyInfo& info)
{
    if (!m_webPage || !m_webPage->browser() || !info.frame)
        return info.defaultPolicy;

    CefRefPtr<CefApp> application = CefContentClient::Get()->rendererApplication();
    if (!application.get())
        return info.defaultPolicy;

    CefRefPtr<CefRenderProcessHandler> handler = application->GetRenderProcessHandler();
    if (!handler.get())
        return info.defaultPolicy;

    CefStringUTF16 urlSpec;
    cef::WebStringToCefString(info.urlRequest.url().spec().utf16(), urlSpec);

    //CefRefPtr<CefFrameHostImpl> cefFrame = new CefFrameHostImpl(m_webPage->browser(), info.frame);
    CefRefPtr<CefFrame> cefFrame = m_webPage->browser()->GetOrCreateFrame(info.frame, content::WebPage::kUnspecifiedFrameId, blink::KURL());

    CefRefPtr<CefRequest> requestPtr(CefRequest::Create());
    CefRequestImpl* requestImpl = static_cast<CefRequestImpl*>(requestPtr.get());
    requestImpl->Set(info.urlRequest);
    requestImpl->SetReadOnly(true);

    cef_navigation_type_t navigation_type = NAVIGATION_OTHER;
    switch (info.navigationType) {
    case blink::WebNavigationTypeLinkClicked:
        navigation_type = NAVIGATION_LINK_CLICKED;
        break;
    case blink::WebNavigationTypeFormSubmitted:
        navigation_type = NAVIGATION_FORM_SUBMITTED;
        break;
    case blink::WebNavigationTypeBackForward:
        navigation_type = NAVIGATION_BACK_FORWARD;
        break;
    case blink::WebNavigationTypeReload:
        navigation_type = NAVIGATION_RELOAD;
        break;
    case blink::WebNavigationTypeFormResubmitted:
        navigation_type = NAVIGATION_FORM_RESUBMITTED;
        break;
    case blink::WebNavigationTypeOther:
        navigation_type = NAVIGATION_OTHER;
        break;
    }

    if (!handler->OnBeforeNavigation((CefBrowser*)m_webPage->browser(), cefFrame.get(),
        requestPtr.get(), navigation_type, info.isRedirect))
        return info.defaultPolicy;

    return WebNavigationPolicyIgnore;
}

void WebFrameClientImpl::willRequestResource(WebLocalFrame*, const WebCachedURLRequest&)
{

}

void WebFrameClientImpl::willSendRequest(WebLocalFrame* webFrame, unsigned identifier, WebURLRequest& request, const WebURLResponse& redirectResponse)
{
    net::RequestExtraData* requestExtraData = new net::RequestExtraData();
    requestExtraData->frame = webFrame;
    requestExtraData->browser = m_webPage->browser();
    request.setExtraData(requestExtraData);

//     String headerFieldValue = blink::defaultLanguage();
//     headerFieldValue.append(",en,*");
// 
//     CString value = headerFieldValue.latin1().data();
//     request.addHTTPHeaderField("Accept-Language", WebString::fromLatin1((const WebLChar*)value.data(), value.length()));
// 
//     WebViewImpl* viewImpl = m_webPage->webViewImpl();
//     if (!viewImpl)
//         return;
//     Page* page = viewImpl->page();
//     if (!page)
//         return;
// 
//     Settings& setting = page->settings();
//     headerFieldValue = "GBK"; // setting.defaultTextEncodingName();
//     headerFieldValue.append(",utf-8;q=0.7,*;q=0.3");
//     value = headerFieldValue.latin1().data();
//     request.addHTTPHeaderField("Accept-Charset", WebString::fromLatin1((const WebLChar*)value.data(), value.length()));
}

void WebFrameClientImpl::didReceiveResponse(WebLocalFrame*, unsigned identifier, const WebURLResponse&)
{

}

void WebFrameClientImpl::didChangeResourcePriority(
    WebLocalFrame* webFrame, unsigned identifier, const WebURLRequest::Priority& priority, int)
{
}

bool WebFrameClientImpl::runModalConfirmDialog(const WebString& message)
{
    return false;
}

void WebFrameClientImpl::didCreateScriptContext(WebLocalFrame* frame, v8::Local<v8::Context> context, int extensionGroup, int worldId)
{
    wke::onCreateGlobalObject(this, frame, context, extensionGroup, worldId);

    if (!CefContentClient::Get())
        return;

    CefRefPtr<CefApp> application = CefContentClient::Get()->rendererApplication();
    if (!application.get())
        return;

    CefRefPtr<CefRenderProcessHandler> handler = application->GetRenderProcessHandler();
    if (!handler.get())
        return;

    CefRefPtr<CefFrame> cefFrame = m_webPage->browser()->GetOrCreateFrame(frame, content::WebPage::kUnspecifiedFrameId, blink::KURL());
    CefRefPtr<CefV8Context> cefV8Context = new CefV8ContextImpl(context->GetIsolate(), context);
    handler->OnContextCreated((CefBrowser*)m_webPage->browser(), cefFrame.get(), cefV8Context);
}

void WebFrameClientImpl::willReleaseScriptContext(WebLocalFrame* frame, v8::Local<v8::Context> context, int worldId)
{
    wke::onReleaseGlobalObject(this, frame, context, worldId);

    if (!CefContentClient::Get())
        return;

    CefRefPtr<CefApp> application = CefContentClient::Get()->rendererApplication();
    if (!application.get())
        return;

    CefRefPtr<CefRenderProcessHandler> handler = application->GetRenderProcessHandler();
    if (!handler.get())
        return;

    CefRefPtr<CefFrame> cefFrame = m_webPage->browser()->GetOrCreateFrame(frame, content::WebPage::kUnspecifiedFrameId, blink::KURL());
    CefRefPtr<CefV8Context> cefV8Context = new CefV8ContextImpl(context->GetIsolate(), context);
    handler->OnContextReleased((CefBrowser*)m_webPage->browser(), cefFrame.get(), cefV8Context);
}

} // namespace blink