#include "test_bind.h"


class Worker_double_it: public Napi::AsyncWorker {
  public:
    Worker_double_it(int number, Napi::Function& callback)
      : Napi::AsyncWorker(callback), number_copy(number) {
    }

  private:
    void Execute() {
      number_copy *= 2;
    }

    void OnOK() {
      Napi::HandleScope scope(Env());       

      Callback().Call({
        Napi::Number::New(Env(), number_copy),
      });
    }

    int number_copy;
};

Napi::Value double_it(const Napi::CallbackInfo& info) {
  if (info.Length() < 2) {
     throw Napi::TypeError::New(info.Env(), "2 arguments expected");
  }

  int number = info[0].As<Napi::Number>().Int32Value();
  Napi::Function callback = info[1].As<Napi::Function>();

  Worker_double_it* worker = new Worker_double_it(number, callback);
  worker->Queue();
  return info.Env().Undefined();
}
