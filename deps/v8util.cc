
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <v8.h>
#include "v8util.h"


const char *
v8util::strtocstr (const v8::String::Utf8Value& str) {
	return *str ? *str : '\0';
}


void
v8util::Print (const v8::String::Utf8Value &str) {
	const char *cstr = v8util::strtocstr(str);
	printf("%s\n", cstr);
}


v8::Handle<v8::String> 
v8util::ReadJs (const char *file) {
	int size, read, i = 0;

	FILE *fh = fopen(file, "rb");
  
  // return an empty string if we had a `NULL` return
  if (NULL == fh) {
    char msg[255];
    sprintf(msg, "v8util.cc: error: Failed to open JavaScript source %s", file);
    perror(msg);
    return v8::Handle<v8::String>();
  }

 	// seek pointer to the end of the stream in the file handle
  fseek(fh, 0, SEEK_END);
  // capture size from stream position
  size = ftell(fh);
  // rewind pointer to beginning of the stream
  rewind(fh);

 	// chars array for characters; add `1` for `/0` character
  char *chars = new char[size + 1];

  // add null char to array
  chars[size] = '\0';
  
  for (;i < size;) {
  	// iterate and cast each `site_t` returned from `fread()` to an `int`
    read = static_cast<int>(fread(&chars[i], 1, size - i, fh));

    // add the size to the current index for an offset
    i += read;
  }

  // close file handle
  fclose(fh);

  // create result from chars array
  v8::Handle<v8::String> result = v8::String::New(chars, size);

  // delete the no longer needed chars
  delete[] chars;
  return result;
}


v8::Handle<v8::Value>
v8util::EvalJs (const char *name, const char *source, bool report_exception, bool print_result) {
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	v8::HandleScope scope(isolate);
	v8::Handle<v8::Value> empty_result;
	// capture exceptions
	v8::TryCatch trycatch;
	// compile source into a `v8::Script`
	v8::Handle<v8::Script> script = v8::Script::Compile(v8::String::New(source), v8::String::New(name));

	if (script.IsEmpty()) {
		if (report_exception) v8util::Exception(&trycatch);
		return empty_result;
	}

	// execute the script if there were no errors
	v8::Handle<v8::Value> result = script->Run();

	// check if we had good execution
	if (result.IsEmpty()) {
		// assert that we caught the exception before reporting it
		assert(trycatch.HasCaught());
		if (report_exception) v8util::Exception(&trycatch);
		return result;
	}

	// assert exceptions have not been caught
	assert(!trycatch.HasCaught());

	// if our result isn't undefined then lets print it
	if (!result->IsUndefined()) {
		v8::String::Utf8Value resultstr(result);
		if (print_result) printf("%s\n", v8util::strtocstr(resultstr));
	}

	return result;
}


void
v8util::Exception (v8::TryCatch *trycatch) {
	const char *string
		, *filename_str
		, *srcline_str
		, *strace_str;

	int linenum, start, end, i;
	
	//const char *string, *filenamestr
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	v8::HandleScope scope(isolate);
  v8::String::Utf8Value exception(trycatch->Exception());
  v8::Handle<v8::Message> message = trycatch->Message();

  string = v8util::strtocstr(exception);

  if (message.IsEmpty()) {
    fprintf(stderr, "%s\n", string);
    return;
  } 

  /**
   * borrowed from `shell.cc` from v8 source - thanks!
   * (filename):(line number): (message)
   */

  v8::String::Utf8Value filename(message->GetScriptResourceName());
  v8::String::Utf8Value sourceline(message->GetSourceLine());
  v8::String::Utf8Value strace(trycatch->StackTrace());

  filename_str = v8util::strtocstr(filename);
  linenum = message->GetLineNumber();
  srcline_str = v8util::strtocstr(sourceline);
  start = message->GetStartColumn();
  end = message->GetEndColumn();

  fprintf(stderr, "%s:%i: %s\n", filename_str, linenum, string);
  fprintf(stderr, "%s\n", srcline_str);
  
  for (i = 0; i < start; ++i) fprintf(stderr, " ");
  for (i = start; i < end; ++i) fprintf(stderr, "^");

  fprintf(stderr, "\n");

  if (strace.length() > 0) {
    strace_str = v8util::strtocstr(strace);
    fprintf(stderr, "%s\n", strace_str);
  }
}


v8::Handle<v8::Value>
v8util::Compile (const char *file, bool report_exception, bool print_result) {
  v8::HandleScope scope(v8::Isolate::GetCurrent());
  v8::Local<v8::String> source = v8util::ReadJs(file);
  if (source.IsEmpty()) return v8::Handle<v8::Value>();
  v8::String::Utf8Value jsstr(source);
  const char *cstr = v8util::strtocstr(jsstr);
  v8::Handle<v8::Value> result = v8util::EvalJs(file, cstr, true);
  return result;
}


void
v8util::ThrowError (const char *message) {
  v8::ThrowException(
    v8::Exception::Error(v8::String::New(message))
  );
}


void
v8util::ThrowRangeError (const char *message) {
  v8::ThrowException(
    v8::Exception::RangeError(v8::String::New(message))
  );
}


void
v8util::ThrowReferenceError (const char *message) {
  v8::ThrowException(
    v8::Exception::ReferenceError(v8::String::New(message))
  );
}


void
v8util::ThrowSyntaxError (const char *message) {
  v8::ThrowException(
    v8::Exception::SyntaxError(v8::String::New(message))
  );
}


void
v8util::ThrowTypeError (const char *message) {
  v8::ThrowException(
    v8::Exception::TypeError(v8::String::New(message))
  );
}