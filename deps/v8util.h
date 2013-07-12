#ifndef V8_UTIL_H
#define V8_UTIL_H

#include <v8.h>

namespace v8util {


/**
 * Converts a `v8::String::Utf8Value` string to a c string
 *
 * @api public
 * @namespace v8util
 * @param {v8::String::Utf8Value} &str
 * @return {const char *}
 */

const char *
strtocstr (const v8::String::Utf8Value &str);


/**
 * Prints a `v8::String::Utf8Value` string to stdout
 *
 * @api public
 * @namespace `v8util`
 * @param {v8::String::Utf8Value} &str
 * @return {void}
 */

void
print (const v8::String::Utf8Value &str);


/**
 * Reads a JavaScript file into a a `v8::String` instance
 *
 * @api public
 * @namespace `v8util`
 * @param {const char} *file
 * @return {v8::Handle<v8::String>}
 */

v8::Handle<v8::String>
readjs (const char *file);


/**
 * Evaluates JavaScript from a given string
 *
 * @api public
 * @namespace `v8util`
 * @param {const char} *name
 * @param {const char} *source
 * @param {bool} report_exception (default: `true`)
 * @param {bool} print_result (default: `false`)
 * @return {v8::Handle<v8::Value>}
 */

v8::Handle<v8::Value>
evaljs (const char *name, const char *source, bool report_exception = true, bool print_result = false);


/**
 * Reports an exception to stdout
 *
 * @api public
 * @namespace `v8util`
 * @param {v8::TryCatch} *trycatch
 * @return {void}
 */

void
exception (v8::TryCatch *trycatch);


/**
 * Throws an `Error` exception with a message
 *
 * @api public
 * @namespace `v8util`
 * @param {const char} *message
 * @return {void}
 */

void
ThrowError (const char *message);


/**
 * Throws a `RangeError` exception with a message
 *
 * @api public
 * @namespace `v8util`
 * @param {const char} *message
 * @return {void}
 */

void
ThrowRangeError (const char *message);


/**
 * Throws a `ReferenceError` exception with a message
 *
 * @api public
 * @namespace `v8util`
 * @param {const char} *message
 * @return {void}
 */

void
ThrowReferenceError (const char *message);


/**
 * Throws a `SyntaxError` exception with a message
 *
 * @api public
 * @namespace `v8util`
 * @param {const char} *message
 * @return {void}
 */

void
ThrowSyntaxError (const char *message);


/**
 * Throws a `TypeError` exception with a message
 *
 * @api public
 * @namespace `v8util`
 * @param {const char} *message
 * @return {void}
 */

void
ThrowTypeError (const char *message);


}
#endif