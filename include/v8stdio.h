#ifndef V8_STDIO_H
#define V8_STDIO_H

#include <v8.h>

namespace v8stdio {


/**
 * Initializes the `stdout` and `stderr` objects
 *
 * @api public
 * @namespace `v8stdio`
 * @return {v8::Handle<v8::Object>}
 */

v8::Handle<v8::Object>
Init ();


/**
 * Attaches `stdio` object to a given object
 *
 * @api public
 * @namespace `v8stdio`
 * @return {void}
 */

void
AttachTo (v8::Handle<v8::Object> stdio, v8::Handle<v8::Object> target);



namespace StdOut {


/**
 * Initializes the `stdout` object
 *
 * @api public
 * @namespace `v8stdio::StdOut`
 * @return {v8::Handle<v8::Object>}
 */

v8::Handle<v8::Object>
Init (v8::Handle<v8::Object> stdout_);


/**
 * Callback for JavaScript bindings to perform a write to stdout
 *
 * @api public
 * @namespace `v8stdio::StdOut`
 * @return {v8::Handle<v8::Object>}
 */

v8::Handle<v8::Value>
v8Write (const v8::Arguments &args);


} // end `v8stdio::StdOut`



namespace StdErr {


/**
 * Initializes the `stderr` object
 *
 * @api public
 * @namespace `v8stdio::StdErr`
 * @return {v8::Handle<v8::Object>}
 */

v8::Handle<v8::Object>
Init (v8::Handle<v8::Object> stderr_);


/**
 * Callback for JavaScript bindings to perform a write to stderr
 *
 * @api public
 * @namespace `v8stdio::StdErr`
 * @return {v8::Handle<v8::Object>}
 */

v8::Handle<v8::Value>
v8Write (const v8::Arguments &args);


} // end `v8stdio::StdErr`


} // end `v8stdio`

#endif	