#ifndef __OOP_H__
#define __OOP_H__

#define __maybe_unused __attribute__((unused))
#define __ref

#define __GET_VTABLE_TYPE(pname) _##pname##_vtable_t

#define __GET_VTABLE_NAME(cname) _##cname##_vtable

#define member(...) (void *_this, ##__VA_ARGS__)

#define member_of(cname) \
    struct cname *this __maybe_unused = _this; \
    typeof(this->base) *base __maybe__unused = &(this->base)

#define Interface(pname) \
    const struct __GET_VTABLE_TYPE(pname) {

#define End_Interface \
    } __ref *_vtable;

#define inherits(pname) \
  struct pname base

#define implementation(pname, cname) \
  const struct __GET_VTABLE_TYPE(pname) __GET_VTABLE_NAME(cname)

#define invoke(p_object, method, ...) \
  ((p_object)->_vtable->method((p_object), ##__VA_ARGS__))

#endif

