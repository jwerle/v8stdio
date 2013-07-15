
#include <assert.h>
#include <iostream>
#include <v8.h>
#include <v8util.h>
#include "v8stdio.h"


v8::Handle<v8::Context>
createContext (v8::Isolate *isolate);


int
main (int argc, char *argv[]) {
	v8::V8::SetFlagsFromCommandLine(&argc, argv, true);
	v8::Isolate *isolate = v8::Isolate::GetCurrent();

	{
		v8::HandleScope scope(isolate);
		v8::Handle<v8::Context> context = createContext(isolate);
		v8::Local<v8::Object> global = context->Global();

		if (context.IsEmpty()) {
			fprintf(stderr, "error creating context\n");
			return 1;
		}

		context->Enter();

		{
			v8stdio::AttachTo(v8stdio::Init(), global);

			{
				v8util::Compile("./test.js");
			}
		}

		context->Exit();
	}

	v8::V8::Dispose();
	return 0;
}


v8::Handle<v8::Context>
createContext (v8::Isolate *isolate) {
	v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();	
	return v8::Context::New(isolate, NULL, global);
}