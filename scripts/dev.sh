#!/usr/bin/env bash
set -euo pipefail

make

gdbgui --remote --port 5000 --args "./$1" "$FILE" >/tmp/gdbgui.log 2>&1 &
gdbgui_pid=$!

for ((attempt = 0; attempt < 100; attempt++)); do
    if ! kill -0 "$gdbgui_pid" 2>/dev/null; then
        cat /tmp/gdbgui.log >&2
        exit 1
    fi

    if python3 -c 'from urllib.request import urlopen; urlopen("http://127.0.0.1:5000", timeout=0.5).close()' >/dev/null 2>&1; then
        printf 'gdbgui: http://localhost:%s\n' "$DEBUG_PORT"
        printf 'Log del debugger: /tmp/gdbgui.log\n'
        exec /bin/bash
    fi

    sleep 0.1
done

cat /tmp/gdbgui.log >&2
printf 'gdbgui non risponde sulla porta 5000.\n' >&2
exit 1
