/****************************************************************************
Copyright (c) 2013 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

https://axmolengine.github.io/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "platform/winrt/InputEvent.h"
#include "platform/winrt/WinRTUtils.h"
#include "platform/winrt/GLViewImpl-winrt.h"
#include "base/EventAcceleration.h"
#include "base/Director.h"
#include "base/EventDispatcher.h"
#include "base/IMEDispatcher.h"

NS_AX_BEGIN

AccelerometerEvent::AccelerometerEvent(const Acceleration& event)
    : m_event(event)
{

}

void AccelerometerEvent::execute()
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    ax::EventAcceleration accEvent(m_event);
    dispatcher->dispatchEvent(&accEvent);
}


PointerEvent::PointerEvent(PointerEventType type, Windows::UI::Core::PointerEventArgs^ args)
    : m_type(type), m_args(args)
{

}

void PointerEvent::execute()
{
    switch(m_type)
    {
    case PointerEventType::PointerPressed:
        GLViewImpl::sharedOpenGLView()->OnPointerPressed(m_args.Get());
        break;
    case PointerEventType::PointerMoved:
        GLViewImpl::sharedOpenGLView()->OnPointerMoved(m_args.Get());
        break;           
    case PointerEventType::PointerReleased:
        GLViewImpl::sharedOpenGLView()->OnPointerReleased(m_args.Get());
        break;
    case ax::MousePressed:
        GLViewImpl::sharedOpenGLView()->OnMousePressed(m_args.Get());
        break;
    case ax::MouseMoved:
        GLViewImpl::sharedOpenGLView()->OnMouseMoved(m_args.Get());
        break;
    case ax::MouseReleased:
        GLViewImpl::sharedOpenGLView()->OnMouseReleased(m_args.Get());
        break;
    case ax::MouseWheelChanged:
        GLViewImpl::sharedOpenGLView()->OnMouseWheelChanged(m_args.Get());
        break;
    }
}

KeyboardEvent::KeyboardEvent(AxmolKeyEvent type)
    : m_type(type), m_text(nullptr)
{

}

KeyboardEvent::KeyboardEvent(AxmolKeyEvent type, Platform::String ^ text)
    : m_type(type), m_text(text)
{

}

void KeyboardEvent::execute()
{
    switch(m_type)
    {
    case AxmolKeyEvent::Text:
    {
        std::string utf8String = PlatformStringToString(m_text.Get());
        IMEDispatcher::sharedDispatcher()->dispatchInsertText(utf8String.c_str(), utf8String.size());
        break;
    }

    default:
        switch (m_type)
        {
        case AxmolKeyEvent::Escape:
            //Director::getInstance()()->getKeypadDispatcher()->dispatchKeypadMSG(kTypeBackClicked);
            break;
        case AxmolKeyEvent::Back:
            IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
            break;
        case AxmolKeyEvent::Enter:
            IMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
            break;
        default:
            break;
        }        
        break;
    }
}

WinRTKeyboardEvent::WinRTKeyboardEvent(WinRTKeyboardEventType type, Windows::UI::Core::KeyEventArgs^ args)
	: m_type(type), m_key(args)
{
}

void WinRTKeyboardEvent::execute()
{
	GLViewImpl::sharedOpenGLView()->OnWinRTKeyboardEvent(m_type, m_key.Get());
}

BackButtonEvent::BackButtonEvent()
{

}

void BackButtonEvent::execute()
{
    GLViewImpl::sharedOpenGLView()->OnBackKeyPress();
}

CustomInputEvent::CustomInputEvent(const std::function<void()>& fun)
: m_fun(fun)
{
}

void CustomInputEvent::execute()
{
    m_fun();
}

UIEditBoxEvent::UIEditBoxEvent(Platform::Object^ sender, Platform::String^ text, Windows::Foundation::EventHandler<Platform::String^>^ handle) 
    : m_sender(sender)
    , m_text(text)
    , m_handler(handle)
{

}

void UIEditBoxEvent::execute()
{
    if (m_handler.Get())
    {
        m_handler.Get()->Invoke(m_sender.Get(), m_text.Get());
    }
}

UIEditBoxEndEvent::UIEditBoxEndEvent(Platform::Object^ sender, Platform::String^ text, int action, Windows::Foundation::EventHandler<ax::EndEventArgs^>^ handle)
  : m_sender(sender)
  , m_text(text)
  , m_action(action)
  , m_handler(handle)
{

}

void UIEditBoxEndEvent::execute()
{
  if (m_handler.Get())
  {
    auto args = ref new EndEventArgs(m_action, m_text.Get());
    m_handler.Get()->Invoke(m_sender.Get(), args);
  }
}

NS_AX_END


