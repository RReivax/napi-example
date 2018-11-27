#include "test_bind.h"


Napi::Object init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "double_it"), Napi::Function::New(env, double_it));

    return exports;
};

NODE_API_MODULE(NODE_GYP_MODULE_NAME, init);
