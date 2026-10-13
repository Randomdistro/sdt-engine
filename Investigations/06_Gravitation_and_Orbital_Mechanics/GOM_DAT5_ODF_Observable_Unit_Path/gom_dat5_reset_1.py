"""GOM_DAT5 C5: known-answer decode of the MESSENGER example record 6 from odf_unpack.pdf Table 3 (2026-10-12).
Registration: GOM_DAT5_RESET_ASSESSMENT_2026-10-12.md sections 0-2 (written before this file existed).
Run: python -I Investigations/06_Gravitation_and_Orbital_Mechanics/GOM_DAT5_ODF_Observable_Unit_Path/gom_dat5_reset_1.py
Author: J. C. Harvey, Melbourne."""
import struct


def bits(rec, start1, n):
    v = 0
    for i in range(n):
        k = start1 - 1 + i
        v = (v << 1) | ((rec[k // 8] >> (7 - k % 8)) & 1)
    return v


def put(buf, start1, n, value):
    for i in range(n):
        k = start1 - 1 + i
        if (value >> (n - 1 - i)) & 1:
            buf[k // 8] |= 0x80 >> (k % 8)


def decode(rec):
    q = rec[16:]
    t = struct.unpack('>I', rec[0:4])[0] + bits(rec[4:], 1, 10) / 1000.0
    delay = bits(rec[4:], 11, 22)
    obs = struct.unpack('>i', rec[8:12])[0] + struct.unpack('>i', rec[12:16])[0] / 1e9
    d = dict(t=t, delay=delay, obs=obs, fmt=bits(q, 1, 3), rx=bits(q, 4, 7), tx=bits(q, 11, 7), net=bits(q, 18, 2), typ=bits(q, 20, 6),
             dl=bits(q, 26, 2), ul=bits(q, 28, 2), refband=bits(q, 30, 2), valid=bits(q, 32, 1), i15=bits(q, 33, 7), i16=bits(q, 40, 10), i17=bits(q, 50, 1),
             i18=bits(q, 51, 22), i19=bits(q, 73, 24))
    w = rec[28:]
    d.update(i20=bits(w, 1, 20), i21=bits(w, 21, 22), i22=bits(w, 43, 22))
    d['fref_mHz'] = d['i18'] * 2 ** 24 + d['i19']
    return d


# --- validation: synthetic Cassini-layout record round trip (as GOM_DAT2) ---
syn = bytearray(36)
syn[0:4] = struct.pack('>I', 1654548090)
put(syn, 33, 10, 500)
put(syn, 129, 3, 2); put(syn, 132, 7, 25); put(syn, 139, 7, 25); put(syn, 148, 6, 12)
s = decode(bytes(syn))
okA = s['fmt'] == 2 and s['rx'] == 25 and s['tx'] == 25 and s['typ'] == 12 and s['t'] == 1654548090.5
print('[VA] synthetic record round trip:', 'met' if okA else 'NOT MET')

# --- the document's Table 3, record 6 (hex words and bit strings as listed there) ---
rec = bytearray(36)
rec[0:4] = bytes.fromhex('6c028048')      # record time tag, integer part (bits 1-32)
# bits 33-42 time fraction = 0 ; bits 43-64 downlink delay = 0
rec[8:12] = bytes.fromhex('fffa28ee')     # observable, integer part (bits 65-96)
rec[12:16] = bytes.fromhex('d86f2b24')    # observable, fractional part x 1e-9 (bits 97-128)
put(rec, 129, 3, 0b010)                   # format ID 2
put(rec, 132, 7, 0b0111111)               # primary receiving station 63
put(rec, 139, 7, 0b0000000)               # transmitting station 0
put(rec, 146, 2, 0b00)                    # network ID 0 (DSN)
put(rec, 148, 6, 0b001011)                # data type 11
put(rec, 154, 2, 0b10)                    # downlink band 2 (X)
put(rec, 156, 2, 0b00)                    # uplink band 0
put(rec, 158, 2, 0b10)                    # reference frequency band 2
put(rec, 160, 1, 0)                       # validity 0 (valid)  [table: bit 159/160]
put(rec, 161, 7, 0b0000001)               # item 15: receiver channel number 1
put(rec, 168, 10, 0b0011101100)           # item 16: spacecraft ID 236
put(rec, 178, 1, 1)                       # item 17: receiver/exciter independent flag
put(rec, 179, 22, 137079)                 # item 18: reference frequency, high part
put(rec, 201, 24, 8424936)                # item 19: reference frequency, low part
put(rec, 245, 22, 6000)                   # item 21: compression time (0.01 s)
d = decode(bytes(rec))
expect = dict(t=1812103240.0, obs=-382738.6638031, fmt=2, rx=63, tx=0, net=0, typ=11, dl=2, ul=0, refband=2, valid=0, i15=1, i16=236, i17=1, i18=137079, i19=8424936, i21=6000, i22=0, delay=0)
bad = 0
for k, v in expect.items():
    ok = abs(d[k] - v) < 1e-9 if isinstance(v, float) else d[k] == v
    print('  %-8s decoded %-22s document %-22s %s' % (k, d[k], v, 'ok' if ok else 'MISMATCH'))
    bad += 0 if ok else 1
print('reference frequency (I18 * 2^24 + I19) mHz = %d  (= %.3f Hz)' % (d['fref_mHz'], d['fref_mHz'] / 1000.0))
print('observable = %.9f Hz (document: -382738.663803100)' % d['obs'])
print('[VK] known-answer decode of the document record:', 'met (all fields)' if bad == 0 else 'NOT MET (%d fields)' % bad)
print('[C5] |observable| = %.2f Hz against the gate >= 1e3 Hz: %s (documented record only; the example file odf07155.dat was not fetched, so its other records, including type 12, are PENDING_DATA)' % (abs(d['obs']), 'met' if abs(d['obs']) >= 1e3 else 'NOT MET'))
