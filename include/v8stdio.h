#ifndef V8_STDIO_H
#define V8_STDIO_H

#include <v8.h>

namespace v8stdio {


/**
 * `v8stdio::file`
 */

namespace file {


/**
 * removes a file
 */
 
v8::Handle<v8::Value>
remove (const v8::Arguments &args);

}


}

#endif	