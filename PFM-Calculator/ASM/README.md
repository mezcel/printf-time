## asm example

Assembly code based on main.c (gcc generated)

```bash
gcc -S -o mainasm simple-easter.c -lm
```

*Note:* The ASM is a demo illustration for observational curiosity. Just for jollies.

---

## Enclosed ASM is from an ancient AMD cpu running Arch. ( a "burner" device )

Assembly architecture (AMD):

```bash
## cpu specs
lscpu

## Cli Return

Architecture: x86_64
CPU op-mode(s): 32-bit, 64-bit
Byte Order: Little Endian
Address sizes: 40 bits physical, 48 bits virtual
CPU(s): 2
On-line CPU(s) list: 0,1
Thread(s) per core: 1
Core(s) per socket: 2 Socket(s): 1
NUMA node(s): 1
Vendor ID: AuthenticAMD
CPU family: 15
Model: 72
Model name: AMD Turion(tm) 64 X2 Mobile Technology TL-52
Stepping: 2
CPU MHz: 800.000
CPU max MHz: 1600.0000
CPU min MHz: 800.0000
BogoMIPS: 1596.55
Virtualization: AMD-V
L1d cache: 64K
L1i cache: 64K
L2 cache: 512K
NUMA node0 CPU(s): 0,1
Flags: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ht syscall nx mmxext fxsr_opt rdtscp lm 3dnowext 3dnow rep_good nopl cpuid extd_apicid pni cx16 lahf_lm cmp_legacy svm extapic cr8_legacy 3dnowprefetch vmmcall
```

Assembly generator (gcc):

```bash
## gcc version
gcc -v

## Cli Return

Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-pc-linux-gnu/8.2.1/lto-wrapper
Target: x86_64-pc-linux-gnu
Configured with: /build/gcc/src/gcc/configure --prefix=/usr --libdir=/usr/lib --libexecdir=/usr/lib --mandir=/usr/share/man --infodir=/usr/share/info --with-bugurl=https://bugs.archlinux.org/ --enable-languages=c,c++,ada,fortran,go,lto,objc,obj-c++ --enable-shared --enable-threads=posix --enable-libmpx --with-system-zlib --with-isl --enable-__cxa_atexit --disable-libunwind-exceptions --enable-clocale=gnu --disable-libstdcxx-pch --disable-libssp --enable-gnu-unique-object --enable-linker-build-id --enable-lto --enable-plugin --enable-install-libiberty --with-linker-hash-style=gnu --enable-gnu-indirect-function --enable-multilib --disable-werror --enable-checking=release --enable-default-pie --enable-default-ssp --enable-cet=auto
Thread model: posix
gcc version 8.2.1 20181127 (GCC)

```
