#include "common.h"
#include "container/dlist.h"
#include "ir.h"

#define ir_foreach(iter) dlist_foreach(&ir_list, iter)

static bool optimizer_del_adjacent_return() {
    ir_foreach(iter) {
        if (iter->data.type == IRINSTR_RETURN && iter->next->data.type == IRINSTR_RETURN) {
            dlist_erase(iter->next);
            return true;
        }
    }
    return false;
};

static bool optimizer_remove_extra_dec() {
    ir_foreach(iter) {
        if (iter->data.type == IRINSTR_DEC && iter->data.dec_size == 4) {
            dlist_erase(iter);
            return true;
        }
    }
    return false;
};

static bool (*ir_optimizer[256])() = {
    optimizer_del_adjacent_return,
    optimizer_remove_extra_dec,
};

void ir_optimize() {
    bool flag;
    do {
        flag = false;
        for (int i = 0; ir_optimizer[i]; i++)
            flag |= ir_optimizer[i]();
    } while (flag);
}