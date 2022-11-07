#include <iostream>
#include <cstdlib>
#include <thread>

static std::mutex g_cout_lock;

extern "C" {

typedef void(*js_callback)(void);

void run_thread(js_callback* resolve) {
  for (int i = 0; i < 20; ++i) {
    {
      std::lock_guard<std::mutex> guard(g_cout_lock);
      std::cout << "here! " << i << "\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  {
    std::lock_guard<std::mutex> guard(g_cout_lock);
    (*resolve)();
  }
}


void cbtest(void* fn) {
  auto* resolve = reinterpret_cast<js_callback>(fn);
  std::thread t(run_thread, &resolve);
  t.detach();
}

}
