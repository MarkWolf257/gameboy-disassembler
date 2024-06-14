#ifndef IBLK0_H
#define IBLK0_H


static inline void
ld_r16_n16(uint8_t *hi, uint8_t *lo, const char *name)
{
    *lo = get_ro_mem(++pc);
    *hi = get_ro_mem(++pc);
    cycle_count += 3;

#ifdef GENERATE_LOGS
    fprintf(log_file, "ld\t%s,\t%02X%02X\n", name, *hi, *lo);
#endif // GENERATE_LOGS
}


static inline void
ld_mr16_a(const uint8_t hi, const uint8_t lo, const char *name)
{
    const uint16_t r16 = hi << 8 | lo;
    *get_rw_memptr(r16) = a;
    cycle_count += 2;

#ifdef GENERATE_LOGS
    fprintf(log_file, "ld\t[%s],\ta", name);
    fprintf(log_file, "\t\t%s:\t%04X\t[%s]:\t%02X\n", name, r16, name, *get_rw_memptr(r16));
#endif // GENERATE_LOGS
}


static inline void
ld_a_mr16(const uint8_t hi, const uint8_t lo, const char *name)
{
    const uint16_t r16 = hi << 8 | lo;
    a = get_ro_mem(r16);
    cycle_count += 2;

#ifdef GENERATE_LOGS
    fprintf(log_file, "ld\ta,\t[%s]", name);
    fprintf(log_file, "\t\t%s:\t%04X\ta:\t%02X\n", name, r16, a);
#endif // GENERATE_LOGS
}


static inline void
inc_r16(uint8_t *hi, uint8_t *lo, const char *name)
{
    *lo += 1;
    *hi += !(*lo);
    cycle_count += 2;

#ifdef GENERATE_LOGS
    fprintf(log_file, "inc\t%s\t", name);
    fprintf(log_file, "\t\t%s:\t%02X%02X\n", name, *hi, *lo);
#endif // GENERATE_LOGS
}


static inline void
dec_r16(uint8_t *hi, uint8_t *lo, const char *name)
{
    *hi -= !(*lo);
    *lo -= 1;
    cycle_count += 2;

#ifdef GENERATE_LOGS
    fprintf(log_file, "dec\t%s\t", name);
    fprintf(log_file, "\t\t%s:\t%02X%02X\n", name, *hi, *lo);
#endif // GENERATE_LOGS
}


static inline void
add_hl_r16(const uint8_t hi, const uint8_t lo, const char *name)
{
    l += lo;
    hf = l < lo;
    h += hi + hf;
    nf = 0;
    cf = h < hi;

    cycle_count += 2;

#ifdef GENERATE_LOGS
    fprintf(log_file, "add\thl,\t%s", name);
    fprintf(log_file, "\t\thl:\t%04X\tznhc:\t%d%d%d%d\n", h << 8 | l, zf, nf, hf, cf);
#endif // GENERATE_LOGS
}


static inline void
inc_r8(uint8_t *r8, const char *name)
{
    (*r8)++;
    zf = !(*r8);
    nf = 0;
    hf = !((*r8) & 0xf);
    cycle_count += 1;

#ifdef GENERATE_LOGS
    fprintf(log_file, "inc\t%s\t", name);
    fprintf(log_file, "\t\t%s:\t%02X\tznhc:\t%d%d%d%d\n", name, *r8, zf, nf, hf, cf);
#endif // GENERATE_LOGS
}


static inline void
dec_r8(uint8_t *r8, const char *name)
{
    hf = !((*r8) & 0xf);
    (*r8)--;
    zf = !(*r8);
    nf = 1;
    cycle_count += 1;

#ifdef GENERATE_LOGS
    fprintf(log_file, "dec\t%s\t", name);
    fprintf(log_file, "\t\t%s:\t%02X\tznhc:\t%d%d%d%d\n", name, *r8, zf, nf, hf, cf);
#endif // GENERATE_LOGS
}


static inline void
ld_r8_n8(uint8_t *r8, const char *name)
{
    *r8 = get_ro_mem(++pc);
    cycle_count += 2;

#ifdef GENERATE_LOGS
    fprintf(log_file, "ld\t%s,\t%02X\n", name, *r8);
#endif // GENERATE_LOGS
}


static inline void
jr_cc_n8(const uint8_t cc, const char *name)
{
    const uint8_t n8 = get_ro_mem(++pc);
    if (cc)
    {
        pc = (int16_t) pc + (int8_t) n8;
        cycle_count += 1;
    }
    cycle_count += 2;

#ifdef GENERATE_LOGS
    fprintf(log_file, "jr%s\t%d\n", name, (int8_t) n8);
#endif // GENERATE_LOGS
}

#endif //IBLK0_H
