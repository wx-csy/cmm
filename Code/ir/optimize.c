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

__attribute__((unused))
static bool optimizer_remove_extra_label() {
    ir_foreach(iter) {
        if (iter->data.type == IRINSTR_LABEL) {
            ir_foreach(iter2)
                if ((iter2->data.type == IRINSTR_GOTO || iter2->data.type == IRINSTR_IF) &&
                        iter2->data.label == iter->data.label) goto fail;
            dlist_erase(iter);
            return true;
        }
        fail:;
    }
    return false;
};

static bool optimizer_remove_jump_next_instr() {
    ir_foreach(iter) {
        if (iter->data.type == IRINSTR_GOTO &&
            iter->next->data.type == IRINSTR_LABEL &&
            iter->data.label == iter->next->data.label) {
            dlist_erase(iter);
            return true;
        }
    }
    return false;
};


static bool (*ir_optimizer[256])() = {
    optimizer_del_adjacent_return,
    optimizer_remove_jump_next_instr,
    // optimizer_remove_extra_label,
};

void ir_optimize() {
    bool flag;

    do {
        flag = false;
        for (int i = 0; ir_optimizer[i]; i++)
            flag |= ir_optimizer[i]();
    } while (flag);
}