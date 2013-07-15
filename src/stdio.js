(function (global) {


	var __native_stdio = global.__native_stdio;


	/**
	 * @namespace `stdio`
	 */

	var stdio = {}


	stdio.stdout = {
		write: function (chunk) {
			__native_stdio.stdout.write(chunk);
		}
	};


	stdio.stderr = {
		write: function (chunk){
			__native_stdio.stderr.write(chunk);
		}
	}

	// remove binding reference from global context 
	delete global.__native_stdio;
	return stdio;
})(this);