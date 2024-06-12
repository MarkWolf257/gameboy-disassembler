#ifndef IBLK0_H
#define IBLK0_H


static inline void
ld_r16_n16(register16_t * const r16, const char *name)
{
    r16->reg.lo = get_ro_mem(++pc.reg16);
    r16->reg.hi = get_ro_mem(++pc.reg16);
    cycle_count += 3;

#ifdef GENERATE_LOGS
    fprintf(log_file, "ld\t%s,\t%04X\n", name, r16->reg16);
#endif // GENERATE_LOGS
}


static inline void
ld_mr16_a(const register16_t r16, const char *name)
{
    *get_rw_memptr(r16.reg16) = af.reg.hi;
    cycle_count += 2;

#ifdef GENERATE_LOGS
    fprintf(log_file, "ld\t[%s],\ta", name);
    fprintf(log_file, "\t\t%s:\t%04X\t[%s]:\t%02X\n", name, r16.reg16, name, *get_rw_memptr(r16.reg16));
#endif // GENERATE_LOGS
}


static inline void
ld_a_mr16(const register16_t r16, const char *name)
{
    af.reg.hi = get_ro_mem(r16.reg16);
    cycle_count += 2;

#ifdef GENERATE_LOGS
    fprintf(log_file, "ld\ta,\t[%s]", name);
    fprintf(log_file, "\t\t%s:\t%04X\ta:\t%02X\n", name, r16.reg16, af.reg.hi);
#endif // GENERATE_LOGS
}


static inline void
inc_r16(register16_t * const r16, const char *name)
{
    r16->reg16++;
    cycle_count += 2;

#ifdef GENERATE_LOGS
    fprintf(log_file, "inc\t%s\t", name);
    fprintf(log_file, "\t\t%s:\t%04X\n", name, r16->reg16);
#endif // GENERATE_LOGS
}


static inline void
dec_r16(register16_t * const r16, const char *name)
{
    r16->reg16--;
    cycle_count += 2;

#ifdef GENERATE_LOGS
    fprintf(log_file, "dec\t%s\t", name);
    fprintf(log_file, "\t\t%s:\t%04X\n", name, r16->reg16);
#endif // GENERATE_LOGS
}


static inline void
add_hl_r16(const register16_t r16, const char *name)
{
    hl.reg16 += r16.reg16;
    hf = (hl.reg16 & 0x0fff) < (r16.reg16 & 0x0fff);
    nf = 0;
    cf = hl.reg16 < r16.reg16;
    cycle_count += 2;

#ifdef GENERATE_LOGS
    fprintf(log_file, "add\thl,\t%s", name);
    fprintf(log_file, "\t\thl:\t%04X\tznhc:\t%d%d%d%d\n", hl.reg16, zf, nf, hf, cf);
#endif // GENERATE_LOGS
}


static inline void
inc_r8(uint8_t * const r8, const char *name)
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
dec_r8(uint8_t * const r8, const char *name)
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
ld_r8_n8(uint8_t * const r8, const char *name)
{
    *r8 = get_ro_mem(++pc.reg16);
    cycle_count += 2;

#ifdef GENERATE_LOGS
    fprintf(log_file, "ld\t%s,\t%02X\n", name, *r8);
#endif // GENERATE_LOGS
}


static inline void
jr_cc_n8(const uint8_t cc, const char *name)
{
    const uint8_t n8 = get_ro_mem(++pc.reg16);
    if (cc)
    {
        pc.reg16 = (int16_t) pc.reg16 + (int8_t) n8;
        cycle_count += 1;
    }
    cycle_count += 2;

#ifdef GENERATE_LOGS
    fprintf(log_file, "jr%s\t%d\n", name, (int8_t) n8);
#endif // GENERATE_LOGS
}

#endif //IBLK0_H
