#include <stdarg.h>
#include <string.h>
#include "ir.h"
#include "memory.h"
#include "stdio.h"
#include "option.h"

IRList ir_list = {
    .data = { .type = IRINSTR_NULL },
    .prev = &ir_list,
    .next = &ir_list
};

void ir_gen_add(ir_instr instr) {
    dlist_insert(&ir_list, instr);
}

void ir_gen_add_with_comment(ir_instr instr, const char *fmt, ...) {
    ssize_t size = 0;
    char *comment = NULL;
    va_list ap;

    va_start(ap, fmt);
    size = vsnprintf(NULL, 0, fmt, ap) + 4;
    va_end(ap);
    if (size > 0) {
        comment = palloc((size_t)size);
        strcpy(comment, "\t; ");
        va_start(ap, fmt);
        vsnprintf(comment + strlen(comment), (size_t)size, fmt, ap);
    }
    instr.comment = comment;
    dlist_insert(&ir_list, instr);
}

static const char *_ir_valstr(ir_val val) {
    char *buf = palloc(32);
    switch (val.type) {
    case IRVAL_NULL: assert(!"unexpected ir_val type (IRVAL_NULL)");
    case IRVAL_IMMD: sprintf(buf, "#%d", val.immd); break;
    case IRVAL_VARIABLE: sprintf(buf, "v%zu", val.varid); break;
    case IRVAL_REF: sprintf(buf, "&v%zu", val.varid); break;
    case IRVAL_DEREF: sprintf(buf, "*v%zu", val.varid); break;
    }
    return buf;
}

static void _ir_write_function(FILE *stream, ir_instr instr) {
    fprintf(stream, "\nFUNCTION %s :", instr.func);
}

static void _ir_write_dec(FILE *stream, ir_instr instr) {
    fprintf(stream, "\tDEC %s %zu", _ir_valstr(instr.dest), instr.dec_size);
}

static void _ir_write_param(FILE *stream, ir_instr instr) {
    fprintf(stream, "\tPARAM %s", _ir_valstr(instr.dest));
}

static void _ir_write_label(FILE *stream, ir_instr instr) {
    fprintf(stream, "LABEL _L%zu :", instr.label);
}

static void _ir_write_assign(FILE *stream, ir_instr instr) {
    fprintf(stream, "\t%s := %s", _ir_valstr(instr.dest), _ir_valstr(instr.src1));
}

static void _ir_write_binary_op(FILE *stream, ir_instr instr) {
    static const char opstr[256][8] = {
        [IRBOP_ADD] = "+",
        [IRBOP_MINUS] = "-",
        [IRBOP_STAR] = "*",
        [IRBOP_DIV] = "/",
    };
    fprintf(stream, "\t%s := %s %s %s", _ir_valstr(instr.dest),
        _ir_valstr(instr.src1), opstr[instr.bop], _ir_valstr(instr.src2));
}

static void _ir_write_goto(FILE *stream, ir_instr instr) {
    fprintf(stream, "\tGOTO _L%zu", instr.label);
}

static void _ir_write_if(FILE *stream, ir_instr instr) {
    static const char opstr[256][8] = {
        [IRREL_GT] = ">",
        [IRREL_LT] = "<",
        [IRREL_GE] = ">=",
        [IRREL_LE] = "<=",
        [IRREL_EQU] = "==",
        [IRREL_NEQ] = "!=",
    };
    fprintf(stream, "\tIF %s %s %s GOTO _L%zu",
        _ir_valstr(instr.src1), opstr[instr.rop], _ir_valstr(instr.src2), instr.label);
}

static void _ir_write_return(FILE *stream, ir_instr instr) {
    fprintf(stream, "\tRETURN %s", _ir_valstr(instr.src1));
}

static void _ir_write_call(FILE *stream, ir_instr instr) {
    fprintf(stream, "\t%s := CALL %s", _ir_valstr(instr.dest), instr.func);
}

static void _ir_write_arg(FILE *stream, ir_instr instr) {
    fprintf(stream, "\tARG %s", _ir_valstr(instr.src1));
}

static void _ir_write_read(FILE *stream, ir_instr instr) {
    fprintf(stream, "\tREAD %s", _ir_valstr(instr.dest));
}

static void _ir_write_write(FILE *stream, ir_instr instr) {
    fprintf(stream, "\tWRITE %s", _ir_valstr(instr.src1));
}

static void (*ir_write_func[256])(FILE *, ir_instr) = {
    [IRINSTR_FUNCTION]  = _ir_write_function,
    [IRINSTR_DEC]       = _ir_write_dec,
    [IRINSTR_PARAM]     = _ir_write_param,
    [IRINSTR_LABEL]     = _ir_write_label,
    [IRINSTR_ASSIGN]    = _ir_write_assign,
    [IRINSTR_BINARY_OP] = _ir_write_binary_op,
    [IRINSTR_GOTO]      = _ir_write_goto,
    [IRINSTR_IF]        = _ir_write_if,
    [IRINSTR_RETURN]    = _ir_write_return,
    [IRINSTR_CALL]      = _ir_write_call,
    [IRINSTR_ARG]       = _ir_write_arg,
    [IRINSTR_READ]      = _ir_write_read,
    [IRINSTR_WRITE]     = _ir_write_write,
};

void ir_gen_output() {
    FILE *stream = opt_output_stream;
    dlist_foreach(&ir_list, iter) {
        ir_write_func[iter->data.type](stream, iter->data);
        if (opt_show_comment && iter->data.comment)
            fputs(iter->data.comment, stream);
        fputc('\n', stream);
    }
}

