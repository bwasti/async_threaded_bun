import { dlopen, JSCallback, ptr, CString } from "bun:ffi";

const {
  symbols: { cbtest }
} = dlopen("libcb.dylib", {
  cbtest: {
    args: ["callback"],
  },
});

function ff() {
  return new Promise((resolve) => {
    const finished = new JSCallback((arg) => {
      resolve()
    }, {
      args: [],
      threadsafe: true
    })
    cbtest(finished.ptr)
  })
}

//const c = await ff()
// This runs in parallel, but crashes silently
const c = await Promise.all([ff(), ff()])
console.log('here')
