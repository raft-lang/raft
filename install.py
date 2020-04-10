#!/usr/bin/python3

import os, json, sys, platform

path = os.path.expanduser("~") + '/.raft/'

os.makedirs(path, exist_ok=True)
os.makedirs(path + 'bin', exist_ok=True)

with open(path + 'env', 'w') as file:
    file.write("export PATH=\"$PATH:${HOME}/.raft/bin\"")

os.system(f'chmod a+x {path}env')

env = {"CC":"clang", "PYV":"3.6m"}

for arg in sys.argv[1:]:
    arg = arg.split("=")
    env[arg[0]] = arg[1]

def run(a, b, c):
    print(end=f'\x1b[1;32m  {a[0]}\x1b[m {b}...')
    sys.stdout.flush()
    c()
    print(f'\r\x1b[K\x1b[1;32m  {a[1]}\x1b[m {b}.')

pip = lambda: os.system('pip3 install -r requirements.txt >/dev/null')
rfc = lambda: os.system(f'{env["CC"]} -O3 -lpython{env["PYV"]} -I/usr/include/python{env["PYV"]} -o {path}bin/rfc src/rfc/rfc.c')

def raftc_rfc():
    with open('src/raftc/src/grammar.lark') as file:
        grammar = file.read()
    with open('src/raftc/src/grammar.rf', 'w') as file:
        file.write(f'fn grammar() -> str {{ return {json.dumps(grammar)}; }}')
    os.system(f'{path}bin/rfc src/raftc/src -o {path}bin/raftc-rfc')

raftc = lambda: os.system(f'{path}bin/raftc-rfc src/raftc/src -o {path}bin/raftc')

def nuitka():
    p = platform.system()
    if p == "Linux":
        os.system("apt -y install nuitka 1>/dev/null 2>/dev/null")
    else:
        os.system("pip3 install nuitka >/dev/null")

run(('Installing', ' Installed'), 'nuitka', nuitka)
run(('Installing', ' Installed'), 'requirements', pip)
run((' Compiling', '  Compiled'), 'rfc', rfc)
run((' Compiling', '  Compiled'), 'raftc (by rfc)', raftc_rfc)
run((' Compiling', '  Compiled'), 'raftc (by raftc)', raftc)

os.remove(path + "bin/rfc")
os.remove(path + "bin/raftc-rfc")

print('To configure the current shell run:\n\x1b[1msource $HOME/.raft/env\x1b[m')
