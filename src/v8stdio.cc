
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <v8.h>
#include <v8util.h>
#include "v8stdio.h"


v8::Handle<v8::Object>
v8stdio::Init () {
	v8::HandleScope scope(v8::Isolate::GetCurrent());
	v8::Local<v8::Object> stdio = v8::Object::New();
	v8::Local<v8::Object> stdout_ = v8stdio::StdOut::Init(v8::Object::New());
	v8::Local<v8::Object> stderr_ = v8stdio::StdErr::Init(v8::Object::New());
	stdio->Set(v8::String::New("stdout"), stdout_);
	stdio->Set(v8::String::New("stderr"), stderr_);
	return stdio->ToObject();
}


void
v8stdio::AttachTo (v8::Handle<v8::Object> stdio, v8::Handle<v8::Object> target) {
	target->Set(v8::String::New("stdio"), stdio);
}


v8::Handle<v8::Object>
v8stdio::StdOut::Init (v8::Handle<v8::Object> stdout_) {
	stdout_->Set(
		v8::String::New("write"), 
		v8::FunctionTemplate::New((v8::FunctionCallback) v8stdio::StdOut::v8Write)->GetFunction()
	);
	return stdout_;
}



v8::Handle<v8::Value>
v8stdio::StdOut::v8Write (const v8::Arguments &args) {
	v8::HandleScope scope(v8::Isolate::GetCurrent());
	// just return when there are no arguments present
	if (0 == args.Length()) return scope.Close(v8::Undefined());
	v8::String::Utf8Value str(args[0]->ToString());
	const char *cstr = v8util::strtocstr(str);
	printf("%s", cstr);
	return scope.Close(v8::Undefined());
}


v8::Handle<v8::Object>
v8stdio::StdErr::Init (v8::Handle<v8::Object> stderr_) {
	stderr_->Set(
		v8::String::New("write"), 
		v8::FunctionTemplate::New((v8::FunctionCallback) v8stdio::StdErr::v8Write)->GetFunction()
	);
	return stderr_;
}


v8::Handle<v8::Value>
v8stdio::StdErr::v8Write (const v8::Arguments &args) {
	v8::HandleScope scope(v8::Isolate::GetCurrent());
	// just return when there are no arguments present
	if (0 == args.Length()) return scope.Close(v8::Undefined());
	v8::String::Utf8Value str(args[0]->ToString());
	const char *cstr = v8util::strtocstr(str);
	fprintf(stderr, "%s", cstr);
	return scope.Close(v8::Undefined());
}
