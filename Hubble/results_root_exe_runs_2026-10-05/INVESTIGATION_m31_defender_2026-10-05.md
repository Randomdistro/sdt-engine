# Investigation — Defender `Trojan:Win64/Injector.NA!MTB` on rebuilt `zk2_m31` (2026-10-05)

Question (Operator): was something malicious loaded into the system for upload to GitHub, or is this a similarly-structured machine-learning false positive? Method: static inspection only; no flagged binary was executed after the first block.

## Where the detection occurred
`Get-MpThreatDetection`: three detections of ThreatID 2147954600 (10:44:45, 10:45:32, 10:54:14 on 2026-10-05), all on binaries I built from `Hubble/tools/zk2_m31_stars.cpp` in the session scratch folder under `AppData\Local\Temp\...\scratchpad\`. No file inside the repository was named. Nothing else (the 18 original root exes, the other 18 rebuilds, a tracked exe) was detected.

## Repository side
- `zk2_m31_stars.cpp`: one commit (cb89b1a, 2026-04-11), no uncommitted change; 254 lines; includes only iostream, cmath, string, vector, sstream, iomanip, algorithm; no process, memory, network, shell or assembly calls.
- Git: no active hooks (only `.sample` files); remote is `github.com/Randomdistro/sdt-engine`; no submodules or `.gitattributes`; the only workflow (`pages.yml`) runs the repo's own python and node checks and the Pages deploy actions.
- Executables ever committed in any branch: exactly one, `_archive/.../aps03_verify_2026-08-15.exe` (commit 45f0b19, 2026-08-15); a Defender custom scan finished with no detection (sha256 prefix CB896F1E476D83DF). `*.exe` is in `.gitignore`; none of the 18 root exes is tracked.
- Tracked `.ps1`/`.bat` files: no download-and-execute, encoded-command, certutil/bitsadmin/mshta/rundll32/regsvr32, scheduled-task or Defender-exclusion patterns. `scripts/run_all.ps1` starts the repo's own local python server.

## The original exe is a faithful build of the committed source
`zk2_m31.exe` (6 April, 328,704 bytes) versus a fresh unoptimised (`/Od`) rebuild of the current source: 8 bytes differ out of 328,704, in two places: the PE header timestamp (offset 0xf8) and the debug-directory timestamp (0x45594). Imports are identical: 89 functions, all from KERNEL32.dll, the standard set of a statically linked MSVC CRT (including GetProcAddress, LoadLibraryExW, VirtualProtect, WriteFile, which every such binary carries); none of OpenProcess, WriteProcessMemory, CreateRemoteThread, VirtualAlloc(Ex), socket or WinInet functions. No URLs or drive paths are embedded.

## Which builds are detected (Defender custom scan of each, not executed)
| Build of the same source | Size | Detected |
|---|---|---|
| default `cl /O2` (links the static CRT by default) | 291,328 | **yes** (×3, reproducible) |
| `/O2 /MT` (same as above) | 291,328 | **yes** |
| `/O1` | 286,720 | no |
| `/Od` (byte-equivalent to the April original) | 328,704 | no |
| control: 8-line program with the same headers | 264,192 | no |
The detection follows the optimised machine code of this program, not its source, its data table or its headers. The 17 other tools, also built `/O2`, were not flagged.

## Object-file check of the flagged variant
The flagged executable could not be dumped (held by Defender). Its object file (`/O2`, 54 undefined external symbols) and the clean one (`/Od`, 57) reference the same C++ runtime symbols; the differences are optimiser helper symbols (`__std_terminate`, `_dclass`, `_ldclass` in one; `__chkstk`, `_dtest`, `_ldtest`, `abs`, `fabs`, operator delete in the other). The only system-class external is the standard `std::_Facet_Register` of iostream locale setup. No process, memory, file or network API is referenced directly.

## Assessment
No evidence that anything malicious was loaded into the repository or the system: the source is unchanged since April, the April exe matches it to the timestamp, and the detection occurs only on freshly optimised builds that I created outside the repo. The pattern (detected on one optimised code layout of clean source, clean on `/O1`, `/Od` and a control) is that of a heuristic/ML false positive, but a false positive is inferred, not proven: the flagged executable itself could not be disassembled, and a classifier cannot be examined from outside. Defender removed the flagged files; the Operator's full scan was clean. Optional: submit the sample to Microsoft's false-positive channel (Defender security intelligence submission) if a formal answer is wanted.
