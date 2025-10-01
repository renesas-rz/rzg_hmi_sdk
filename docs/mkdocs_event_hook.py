#!/usr/bin/python3

import os

pwd = os.getcwd()

def on_startup(**kwargs):
    base = pwd + '/docs/history/_components/changelogs'
    create_symlink(base)

def on_shutdown(**kwargs):
    base = pwd + '/docs/history/_components/changelogs'
    remove_symlink(base)

# ------------------------------------------------------------------------------

def create_symlink(base):
    files = os.listdir(base)
    files.sort()

    first = True
    counter = 0

    for name in reversed(files):
        if name.endswith(".md"):
            counter = counter + 1

            src = base + '/' + name

            if first:
                dst = base + '/latest'
                symlink_force(src, dst)
                first = False

            dst = base + '/sorted-' + "%09d" % counter + '-' + name
            symlink_force(src, dst)

def symlink_force(target, link_name):
    import errno

    try:
        os.symlink(target, link_name)
    except OSError as e:
        if e.errno == errno.EEXIST:
            os.remove(link_name)
            os.symlink(target, link_name)
        else:
            raise e

# ------------------------------------------------------------------------------

def remove_symlink(base):
    files = os.listdir(base)
    files.sort()

    for name in reversed(files):
        if name.startswith("sorted-"):
            dst = base + '/' + name
            os.remove(dst)

    dst = base + '/latest'
    os.remove(dst)
