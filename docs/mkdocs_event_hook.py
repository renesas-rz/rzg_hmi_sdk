#!/usr/bin/python3

import os

pwd = os.getcwd()

def on_startup(**kwargs):
    base = pwd + '/docs/history/_components/changelogs'
    create_symlink(base)

def on_shutdown(**kwargs):
    base = pwd + '/docs/history/_components/changelogs'
    remove_symlink(base)

def on_config(config, **kwargs):
    target = pwd + '/docs/_announcements/announcements.md'
    update_announcements(config, target)

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

# ------------------------------------------------------------------------------

def update_announcements(config, target):
    import markdown
    from bs4 import BeautifulSoup

    with open(target, "r", encoding="utf-8") as input_file:
        text = input_file.read()

    html = markdown.markdown(text, extensions=[
        'tables', 'markdown_grid_tables', 'admonition',
        'pymdownx.highlight', 'pymdownx.inlinehilite', 'pymdownx.snippets',
        'pymdownx.superfences', 'attr_list'])
    soup = BeautifulSoup(html, features="lxml")

    announcements_list = []

    if len(soup) > 0:
        for el in soup.body:
            el = str(el).replace('\xa0', '&nbsp;')
            if el == "\n":
                continue
            elif "<p>" in el[:3]:
                announcements_list.append(el[3:-4])
            else:
                announcements_list.append(el)

    extra = config['extra']
    extra['announcements'] = announcements_list
