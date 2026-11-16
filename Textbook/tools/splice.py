"""Replace or insert text in a UTF-8 file without shell escaping.
Usage: python splice.py FILE replace START_MARKER END_MARKER NEWFILE   (replaces [START, END) with NEWFILE's text)
       python splice.py FILE before MARKER NEWFILE                    (inserts NEWFILE's text before MARKER)
       python splice.py FILE sub OLDFILE NEWFILE                      (replaces the exact text of OLDFILE with NEWFILE's text, once)
Markers are matched as exact substrings; the first occurrence is used. Line endings are kept as LF.
"""
import sys

def rd(p):
    return open(p, "rb").read().decode("utf-8").replace("\r\n", "\n")

def main():
    a = sys.argv
    path, mode = a[1], a[2]
    s = rd(path)
    if mode == "replace":
        start, end, new = a[3], a[4], rd(a[5])
        i = s.index(start)
        j = s.index(end, i + len(start))
        s = s[:i] + new + s[j:]
    elif mode == "before":
        marker, new = a[3], rd(a[4])
        i = s.index(marker)
        s = s[:i] + new + s[i:]
    elif mode == "sub":
        old, new = rd(a[3]).rstrip("\n"), rd(a[4]).rstrip("\n")
        if old not in s:
            sys.exit("old text not found")
        s = s.replace(old, new, 1)
    else:
        sys.exit("unknown mode")
    open(path, "wb").write(s.encode("utf-8"))
    print("ok")

main()
