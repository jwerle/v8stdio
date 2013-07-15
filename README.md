v8stdio
=====

utilities for v8 development

## install

Using a C package manager like [cpm](https://github.com/visionmedia/cpm) you can install v8stdio into the `deps/` directory of your project. It also installs to `/usr/local/include` and `/usr/local/lib` by default.

```sh
$ cpm install jwerle/v8stdio
```

Just link in your compilation

```sh
$ g++ -I/usr/local/include/v8 -lv8 -lv8stdio program.cc -o program
```

## building and linking to your project from source

Change to `v8stdio` root directory

```sh
$ cd v8stdio/
```

Install `libv8stdio` with `make`. ***requires g++***

You can set the `PREFIX` variable to be whatever you would like. Defaults to `/usr/local/`

```sh
$ make install
```

You can now link `v8stdio` to your project


```sh
$ g++ -I/usr/local/include/v8 -lv8 -lv8stdio program.cc -o program
```


### node-gyp

You can include `v8stdio` in your node.js addon by simply including it in the "sources" array in your `binding.gyp` file

```gyp
{
	"targets": [
		{
			"target_name": "myaddon",
			"sources": [
				"deps/v8stdio.h", "deps/v8stdio.cc",
				"src/myaddon.cc"
			]
		}
	]
}
```

## usage

To expose the `stdout` and `stderr` objects to your JavaScript environment in v8 you must attached it to an object like global object.

***Attaching to the global object***

```c++
v8stdio::AttachTo(v8stdio::Init(), v8::Context::GetCurrent()->Global());
```

***Attaching to a target object***

```c++
v8::Handle<v8::Object> target = v8::Object::New();
v8stdio::AttachTo(v8stdio::Init(), target);
```

## api

### v8::Handle\<v8::Object> v8stdio::Init ()

Initializes the `stdout` and `stderr` objects

***example***

```c++
v8::Handle<v8::Object> stdiov = v8stdio::Init();
```


### void v8stdio::AttachTo (v8::Handle\<v8::Object> stdio, v8::Handle\<v8::Object> target)

Attaches `stdio` object to a given object

***example***

```c++
v8stdio::AttachTo(stdiov, global);
```


### v8::Handle\<v8::Object> v8stdio::StdOut::Init (v8::Handle\<v8::Object> stdout_)

Initializes the `StdOut` object

***example***

```c++
v8::Local<v8::Object> stdout_ = v8stdio::StdOut::Init(v8::Object::New());
```


### v8::Handle\<v8::Value> v8stdio::StdOut::v8Write (const v8::Arguments &args)

Callback for JavaScript bindings to perform a write to stdout

**example***

```c++
target->Set(
	v8::String::New("write"),
	v8::FunctionTemplate::New((v8::FunctionCallback) v8stdio::StdOut::v8Write)->GetFunction()
);
```


### v8::Handle\<v8::Object> v8stdio::StdErr::Init (v8::Handle\<v8::Object> stdout_)

Initializes the `StdErr` object

***example***

```c++
v8::Local<v8::Object> stdout_ = v8stdio::StdErr::Init(v8::Object::New());
```


### v8::Handle\<v8::Value> v8stdio::StdErr::v8Write (const v8::Arguments &args)

Callback for JavaScript bindings to perform a write to stderr

**example***

```c++
target->Set(
	v8::String::New("write"),
	v8::FunctionTemplate::New((v8::FunctionCallback) v8stdio::StdErr::v8Write)->GetFunction()
);
```


## license

MIT