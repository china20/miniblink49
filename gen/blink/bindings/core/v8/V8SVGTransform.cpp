// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#include "config.h"
#include "V8SVGTransform.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/V8DOMConfiguration.h"
#include "bindings/core/v8/V8ObjectConstructor.h"
#include "bindings/core/v8/V8SVGElement.h"
#include "bindings/core/v8/V8SVGMatrix.h"
#include "core/dom/ContextFeatures.h"
#include "core/dom/Document.h"
#include "core/frame/UseCounter.h"
#include "platform/RuntimeEnabledFeatures.h"
#include "platform/TraceEvent.h"
#include "wtf/GetPtr.h"
#include "wtf/RefPtr.h"

namespace blink {

// Suppress warning: global constructors, because struct WrapperTypeInfo is trivial
// and does not depend on another global objects.
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
const WrapperTypeInfo V8SVGTransform::wrapperTypeInfo = { gin::kEmbedderBlink, V8SVGTransform::domTemplate, V8SVGTransform::refObject, V8SVGTransform::derefObject, V8SVGTransform::trace, 0, V8SVGTransform::visitDOMWrapper, V8SVGTransform::preparePrototypeObject, V8SVGTransform::installConditionallyEnabledProperties, "SVGTransform", 0, WrapperTypeInfo::WrapperTypeObjectPrototype, WrapperTypeInfo::ObjectClassId, WrapperTypeInfo::NotInheritFromEventTarget, WrapperTypeInfo::Dependent, WrapperTypeInfo::WillBeGarbageCollectedObject };
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic pop
#endif

// This static member must be declared by DEFINE_WRAPPERTYPEINFO in SVGTransformTearOff.h.
// For details, see the comment of DEFINE_WRAPPERTYPEINFO in
// bindings/core/v8/ScriptWrappable.h.
const WrapperTypeInfo& SVGTransformTearOff::s_wrapperTypeInfo = V8SVGTransform::wrapperTypeInfo;

namespace SVGTransformTearOffV8Internal {

static void typeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    v8::Local<v8::Object> holder = info.Holder();
    SVGTransformTearOff* impl = V8SVGTransform::toImpl(holder);
    v8SetReturnValueUnsigned(info, impl->transformType());
}

static void typeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMGetter");
    SVGTransformTearOffV8Internal::typeAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void matrixAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    v8::Local<v8::Object> holder = info.Holder();
    SVGTransformTearOff* impl = V8SVGTransform::toImpl(holder);
    v8SetReturnValueFast(info, WTF::getPtr(impl->matrix()), impl);
}

static void matrixAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMGetter");
    SVGTransformTearOffV8Internal::matrixAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void angleAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    v8::Local<v8::Object> holder = info.Holder();
    SVGTransformTearOff* impl = V8SVGTransform::toImpl(holder);
    v8SetReturnValue(info, impl->angle());
}

static void angleAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMGetter");
    SVGTransformTearOffV8Internal::angleAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void setMatrixMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "setMatrix", "SVGTransform", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        setMinimumArityTypeError(exceptionState, 1, info.Length());
        exceptionState.throwIfNeeded();
        return;
    }
    SVGTransformTearOff* impl = V8SVGTransform::toImpl(info.Holder());
    SVGMatrixTearOff* matrix;
    {
        matrix = V8SVGMatrix::toImplWithTypeCheck(info.GetIsolate(), info[0]);
        if (!matrix) {
            exceptionState.throwTypeError("parameter 1 is not of type 'SVGMatrix'.");
            exceptionState.throwIfNeeded();
            return;
        }
    }
    impl->setMatrix(matrix, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void setMatrixMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    SVGTransformTearOffV8Internal::setMatrixMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void setTranslateMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "setTranslate", "SVGTransform", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 2)) {
        setMinimumArityTypeError(exceptionState, 2, info.Length());
        exceptionState.throwIfNeeded();
        return;
    }
    SVGTransformTearOff* impl = V8SVGTransform::toImpl(info.Holder());
    float tx;
    float ty;
    {
        tx = toRestrictedFloat(info.GetIsolate(), info[0], exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        ty = toRestrictedFloat(info.GetIsolate(), info[1], exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
    }
    impl->setTranslate(tx, ty, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void setTranslateMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    SVGTransformTearOffV8Internal::setTranslateMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void setScaleMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "setScale", "SVGTransform", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 2)) {
        setMinimumArityTypeError(exceptionState, 2, info.Length());
        exceptionState.throwIfNeeded();
        return;
    }
    SVGTransformTearOff* impl = V8SVGTransform::toImpl(info.Holder());
    float sx;
    float sy;
    {
        sx = toRestrictedFloat(info.GetIsolate(), info[0], exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        sy = toRestrictedFloat(info.GetIsolate(), info[1], exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
    }
    impl->setScale(sx, sy, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void setScaleMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    SVGTransformTearOffV8Internal::setScaleMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void setRotateMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "setRotate", "SVGTransform", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 3)) {
        setMinimumArityTypeError(exceptionState, 3, info.Length());
        exceptionState.throwIfNeeded();
        return;
    }
    SVGTransformTearOff* impl = V8SVGTransform::toImpl(info.Holder());
    float angle;
    float cx;
    float cy;
    {
        angle = toRestrictedFloat(info.GetIsolate(), info[0], exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        cx = toRestrictedFloat(info.GetIsolate(), info[1], exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
        cy = toRestrictedFloat(info.GetIsolate(), info[2], exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
    }
    impl->setRotate(angle, cx, cy, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void setRotateMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    SVGTransformTearOffV8Internal::setRotateMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void setSkewXMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "setSkewX", "SVGTransform", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        setMinimumArityTypeError(exceptionState, 1, info.Length());
        exceptionState.throwIfNeeded();
        return;
    }
    SVGTransformTearOff* impl = V8SVGTransform::toImpl(info.Holder());
    float angle;
    {
        angle = toRestrictedFloat(info.GetIsolate(), info[0], exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
    }
    impl->setSkewX(angle, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void setSkewXMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    SVGTransformTearOffV8Internal::setSkewXMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void setSkewYMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "setSkewY", "SVGTransform", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        setMinimumArityTypeError(exceptionState, 1, info.Length());
        exceptionState.throwIfNeeded();
        return;
    }
    SVGTransformTearOff* impl = V8SVGTransform::toImpl(info.Holder());
    float angle;
    {
        angle = toRestrictedFloat(info.GetIsolate(), info[0], exceptionState);
        if (exceptionState.throwIfNeeded())
            return;
    }
    impl->setSkewY(angle, exceptionState);
    if (exceptionState.hadException()) {
        exceptionState.throwIfNeeded();
        return;
    }
}

static void setSkewYMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    SVGTransformTearOffV8Internal::setSkewYMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

} // namespace SVGTransformTearOffV8Internal

void V8SVGTransform::visitDOMWrapper(v8::Isolate* isolate, ScriptWrappable* scriptWrappable, const v8::Persistent<v8::Object>& wrapper)
{
    SVGTransformTearOff* impl = scriptWrappable->toImpl<SVGTransformTearOff>();
    v8::Local<v8::Object> creationContext = v8::Local<v8::Object>::New(isolate, wrapper);
    V8WrapperInstantiationScope scope(creationContext, isolate);
    SVGElement* contextElement = impl->contextElement();
    if (contextElement) {
        if (DOMDataStore::containsWrapper(contextElement, isolate))
            DOMDataStore::setWrapperReference(wrapper, contextElement, isolate);
    }
}

static const V8DOMConfiguration::AccessorConfiguration V8SVGTransformAccessors[] = {
    {"type", SVGTransformTearOffV8Internal::typeAttributeGetterCallback, 0, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::ExposedToAllScripts, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder},
    {"matrix", SVGTransformTearOffV8Internal::matrixAttributeGetterCallback, 0, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::ExposedToAllScripts, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder},
    {"angle", SVGTransformTearOffV8Internal::angleAttributeGetterCallback, 0, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::ExposedToAllScripts, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder},
};

static const V8DOMConfiguration::MethodConfiguration V8SVGTransformMethods[] = {
    {"setMatrix", SVGTransformTearOffV8Internal::setMatrixMethodCallback, 0, 1, V8DOMConfiguration::ExposedToAllScripts},
    {"setTranslate", SVGTransformTearOffV8Internal::setTranslateMethodCallback, 0, 2, V8DOMConfiguration::ExposedToAllScripts},
    {"setScale", SVGTransformTearOffV8Internal::setScaleMethodCallback, 0, 2, V8DOMConfiguration::ExposedToAllScripts},
    {"setRotate", SVGTransformTearOffV8Internal::setRotateMethodCallback, 0, 3, V8DOMConfiguration::ExposedToAllScripts},
    {"setSkewX", SVGTransformTearOffV8Internal::setSkewXMethodCallback, 0, 1, V8DOMConfiguration::ExposedToAllScripts},
    {"setSkewY", SVGTransformTearOffV8Internal::setSkewYMethodCallback, 0, 1, V8DOMConfiguration::ExposedToAllScripts},
};

static void installV8SVGTransformTemplate(v8::Local<v8::FunctionTemplate> functionTemplate, v8::Isolate* isolate)
{
    functionTemplate->ReadOnlyPrototype();

    v8::Local<v8::Signature> defaultSignature;
    if (!RuntimeEnabledFeatures::svg1DOMEnabled())
        defaultSignature = V8DOMConfiguration::installDOMClassTemplate(isolate, functionTemplate, "SVGTransform", v8::Local<v8::FunctionTemplate>(), V8SVGTransform::internalFieldCount, 0, 0, 0, 0, 0, 0);
    else
        defaultSignature = V8DOMConfiguration::installDOMClassTemplate(isolate, functionTemplate, "SVGTransform", v8::Local<v8::FunctionTemplate>(), V8SVGTransform::internalFieldCount,
            0, 0,
            V8SVGTransformAccessors, WTF_ARRAY_LENGTH(V8SVGTransformAccessors),
            V8SVGTransformMethods, WTF_ARRAY_LENGTH(V8SVGTransformMethods));
    v8::Local<v8::ObjectTemplate> instanceTemplate = functionTemplate->InstanceTemplate();
    ALLOW_UNUSED_LOCAL(instanceTemplate);
    v8::Local<v8::ObjectTemplate> prototypeTemplate = functionTemplate->PrototypeTemplate();
    ALLOW_UNUSED_LOCAL(prototypeTemplate);
    static const V8DOMConfiguration::ConstantConfiguration V8SVGTransformConstants[] = {
        {"SVG_TRANSFORM_UNKNOWN", 0, 0, 0, V8DOMConfiguration::ConstantTypeUnsignedShort},
        {"SVG_TRANSFORM_MATRIX", 1, 0, 0, V8DOMConfiguration::ConstantTypeUnsignedShort},
        {"SVG_TRANSFORM_TRANSLATE", 2, 0, 0, V8DOMConfiguration::ConstantTypeUnsignedShort},
        {"SVG_TRANSFORM_SCALE", 3, 0, 0, V8DOMConfiguration::ConstantTypeUnsignedShort},
        {"SVG_TRANSFORM_ROTATE", 4, 0, 0, V8DOMConfiguration::ConstantTypeUnsignedShort},
        {"SVG_TRANSFORM_SKEWX", 5, 0, 0, V8DOMConfiguration::ConstantTypeUnsignedShort},
        {"SVG_TRANSFORM_SKEWY", 6, 0, 0, V8DOMConfiguration::ConstantTypeUnsignedShort},
    };
    V8DOMConfiguration::installConstants(isolate, functionTemplate, prototypeTemplate, V8SVGTransformConstants, WTF_ARRAY_LENGTH(V8SVGTransformConstants));
    static_assert(0 == SVGTransformTearOff::SVG_TRANSFORM_UNKNOWN, "the value of SVGTransformTearOff_SVG_TRANSFORM_UNKNOWN does not match with implementation");
    static_assert(1 == SVGTransformTearOff::SVG_TRANSFORM_MATRIX, "the value of SVGTransformTearOff_SVG_TRANSFORM_MATRIX does not match with implementation");
    static_assert(2 == SVGTransformTearOff::SVG_TRANSFORM_TRANSLATE, "the value of SVGTransformTearOff_SVG_TRANSFORM_TRANSLATE does not match with implementation");
    static_assert(3 == SVGTransformTearOff::SVG_TRANSFORM_SCALE, "the value of SVGTransformTearOff_SVG_TRANSFORM_SCALE does not match with implementation");
    static_assert(4 == SVGTransformTearOff::SVG_TRANSFORM_ROTATE, "the value of SVGTransformTearOff_SVG_TRANSFORM_ROTATE does not match with implementation");
    static_assert(5 == SVGTransformTearOff::SVG_TRANSFORM_SKEWX, "the value of SVGTransformTearOff_SVG_TRANSFORM_SKEWX does not match with implementation");
    static_assert(6 == SVGTransformTearOff::SVG_TRANSFORM_SKEWY, "the value of SVGTransformTearOff_SVG_TRANSFORM_SKEWY does not match with implementation");

    // Custom toString template
    functionTemplate->Set(v8AtomicString(isolate, "toString"), V8PerIsolateData::from(isolate)->toStringTemplate());
}

v8::Local<v8::FunctionTemplate> V8SVGTransform::domTemplate(v8::Isolate* isolate)
{
    return V8DOMConfiguration::domClassTemplate(isolate, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), installV8SVGTransformTemplate);
}

bool V8SVGTransform::hasInstance(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Local<v8::Object> V8SVGTransform::findInstanceInPrototypeChain(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

SVGTransformTearOff* V8SVGTransform::toImplWithTypeCheck(v8::Isolate* isolate, v8::Local<v8::Value> value)
{
    return hasInstance(value, isolate) ? toImpl(v8::Local<v8::Object>::Cast(value)) : 0;
}

void V8SVGTransform::refObject(ScriptWrappable* scriptWrappable)
{
#if !ENABLE(OILPAN)
    scriptWrappable->toImpl<SVGTransformTearOff>()->ref();
#endif
}

void V8SVGTransform::derefObject(ScriptWrappable* scriptWrappable)
{
#if !ENABLE(OILPAN)
    scriptWrappable->toImpl<SVGTransformTearOff>()->deref();
#endif
}

} // namespace blink