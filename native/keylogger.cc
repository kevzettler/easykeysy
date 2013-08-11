#include <node.h>
#include <v8.h>
#include <stdio.h>
#include <ApplicationServices/ApplicationServices.h> /* ApplicationServices.framework needed */

using namespace v8;
using namespace node;


struct Emitter: ObjectWrap {
  static Handle<Value> New(const Arguments& args);
  static CGEventRef myCGEventCallback (CGEventTapProxy, CGEventType, CGEventRef, void *);
};


Handle<Value> Emitter::New(const Arguments& args) {
  HandleScope scope;

  if (!args.IsConstructCall()) {
    return ThrowException(Exception::TypeError(
      String::New("Use the new operator to create instances of this object."))
    );
  }

  v8::Arguments wat = args;
  Emitter* self = new Emitter();
  self->Wrap(args.This());

  CGEventFlags oldFlags = CGEventSourceFlagsState(kCGEventSourceStateCombinedSessionState);
  CGEventMask eventMask = (CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventFlagsChanged));

  CFMachPortRef eventTap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 0, eventMask, self->myCGEventCallback, &wat);
  
  if (!eventTap) {
    return ThrowException(Exception::TypeError(
            String::New("failed to create event tap\nyou need to enable \"Enable access for assitive devices\" in Universal Access preference panel.")));
  }

  CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
  CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
  CGEventTapEnable(eventTap, true);
  CFRunLoopRun();

  return scope.Close(args.This());
}


CGEventRef Emitter::myCGEventCallback (CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
  HandleScope scope;

  if ((type != kCGEventKeyDown) && (type != kCGEventFlagsChanged)) {
    return event;
  }  
  CGKeyCode keyCode = (CGKeyCode) CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);  
  Handle<Value> neat[2] = {String::New("keypress"), String::New("lol")};


  v8::Arguments* args = static_cast<v8::Arguments *>(refcon);
  

  MakeCallback(args->This(), "emit", 2, neat);
  return event;
};

extern "C" void init(Handle<Object> target) {
  HandleScope scope;

  Local<FunctionTemplate> t = FunctionTemplate::New(Emitter::New);
  t->InstanceTemplate()->SetInternalFieldCount(1);
  t->SetClassName(String::New("Emitter"));


  target->Set(String::NewSymbol("Emitter"), t->GetFunction());
}

NODE_MODULE(keylogger, init);
