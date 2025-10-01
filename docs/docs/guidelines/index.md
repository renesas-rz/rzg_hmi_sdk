# Welcome to MkDocs

For full documentation visit [mkdocs.org](https://www.mkdocs.org).

## Commands

* `mkdocs new [dir-name]` - Create a new project.
* `mkdocs serve` - Start the live-reloading docs server.
* `mkdocs build` - Build the documentation site.
* `mkdocs -h` - Print help message and exit.

## Project layout

    mkdocs.yml    # The configuration file.
    docs/
        index.md  # The documentation homepage.
        ...       # Other markdown pages, images and other files.

## Test admonitions

!!! note "Note"
    Test admonition.

!!! abstract "Abstract"
    Test admonition.

!!! info "Info"
    Test admonition.

!!! tip "Tip"
    Test admonition.

!!! success "Success"
    Test admonition.

!!! question "Question"
    Test admonition.

!!! warning "Warning"
    Test admonition.

!!! failure "Failure"
    Test admonition.

!!! danger "Danger"
    Test admonition.

!!! bug "Bug"
    Test admonition.

!!! example "Example"
    Test admonition.

!!! quote "Quote"
    Test admonition.

### Without title

!!! note ""
    Test admonition.

## Test code blocks

``` py
import tensorflow as tf
```

### Adding a title

``` py title="bubble_sort.py"
def bubble_sort(items):
    for i in range(len(items)):
        for j in range(len(items) - 1 - i):
            if items[j] > items[j + 1]:
                items[j], items[j + 1] = items[j + 1], items[j]
```

### Adding annotations

``` yaml
theme:
  features:
    - content.code.annotate # (1)
```

1.  :man_raising_hand: I'm a code annotation! I can contain `code`, __formatted
    text__, images, ... basically anything that can be written in Markdown.

#### Stripping comments

``` yaml
# (1)!
```

1.  Look ma, less line noise!

### Adding line numbers

``` py linenums="1"
def bubble_sort(items):
    for i in range(len(items)):
        for j in range(len(items) - 1 - i):
            if items[j] > items[j + 1]:
                items[j], items[j + 1] = items[j + 1], items[j]
```

### Highlighting specific lines

``` py linenums="1" hl_lines="2 3"
def bubble_sort(items):
    for i in range(len(items)):
        for j in range(len(items) - 1 - i):
            if items[j] > items[j + 1]:
                items[j], items[j + 1] = items[j + 1], items[j]
```

### Highlighting inline code blocks

The `#!python range()` function is used to generate a sequence of numbers.

### Embedding external files

``` bash title="serve.sh" linenums="1"
--8<-- "serve.sh"
```

## Test (sortable) tables

### Column alignment

#### Center

| Method      | Description                          |
| :---------: | :----------------------------------: |
| `GET`       | :material-check:     Fetch resource  |
| `PUT`       | :material-check-all: Update resource |
| `DELETE`    | :material-close:     Delete resource |

#### Right

| Method      | Description                          |
| ----------: | -----------------------------------: |
| `GET`       | :material-check:     Fetch resource  |
| `PUT`       | :material-check-all: Update resource |
| `DELETE`    | :material-close:     Delete resource |

### Grid table (inside admonitions)

!!! note "Note"
    +-------------------+--------------------------------------------+-------------------+
    | Name              | Description                                | Example           |
    +===================+============================================+===================+
    | Server Version    | The version of the server                  | 0.20.0            |
    +-------------------+--------------------------------------------+-------------------+
    | Protocol Version  | The version of the protocol                | 0.1.0             |
    |                   | (different servers can have same protocol) |                   |
    +-------------------+--------------------------------------------+-------------------+
    | Capabilities      | What features the server has implemented   | "search"          |
    +-------------------+--------------------------------------------+-------------------+

### Import table from file (.csv)

{{ read_csv('./_tables/basic_table.csv') }}

### Table with footnote (table area)

!!! content-wrapper no-indent ""

    | Month                             | Savings |
    | --------------------------------- | ------- |
    | January ^[1](#tf:1)^{: #tfref:1 } | $250    |
    | February                          | $80     |
    | March ^[2](#tf:2)^{: #tfref:2 }   | $420    |

    1. This is a footnote inside table area. [↩](#tfref:1){: .tf-backref }
    {: #tf:1 }

    2. This is another footnote inside table area. [↩](#tfref:2){: .tf-backref }
    {: #tf:2 }

#### Indented

!!! danger
    As each page elements must have unique id,
    please increase referred and referrer ids of `content-wrapper`, as:

    * `#tf:X`
    * `#tfref:X`

    Where `X=1,2,3,...`

!!! content-wrapper ""

    | Month                             | Savings |
    | --------------------------------- | ------- |
    | January ^[1](#tf:3)^{: #tfref:3 } | $250    |
    | February                          | $80     |
    | March ^[2](#tf:4)^{: #tfref:4 }   | $420    |

    1. This is a footnote inside table area. [↩](#tfref:3){: .tf-backref }
    {: #tf:3 }

    2. This is another footnote inside table area. [↩](#tfref:4){: .tf-backref }
    {: #tf:4 }

#### Indented without footnote

!!! content-wrapper ""

    | Month    | Savings |
    | -------- | ------- |
    | January  | $250    |
    | February | $80     |
    | March    | $420    |

## Test buttons

[Subscribe to our newsletter](#){ .md-button .md-button--primary }

[Subscribe to our newsletter](#){ .md-button .md-button--primary .btn-grey }

### Rounded

[Subscribe to our newsletter](#){ .md-button .md-button--primary .btn-yellow .btn-round }

### Right

[Subscribe to our newsletter](#){ .md-button .md-button--primary .btn-right }

### Grouped

[Subscribe to our newsletter](#){ .md-button .md-button--primary .btn-grey }
[Subscribe to our newsletter](#){ .md-button .md-button--primary .btn-yellow .btn-round }

#### Grouped right

[Subscribe to our newsletter](#){ .md-button .md-button--primary .btn-right }
[Subscribe to our newsletter](#){ .md-button .md-button--primary .btn-yellow .btn-round .btn-right }

### Sub-text

[Subscribe to our newsletter<br><span class="btn-subtext">Sub-text</span>](#){ .md-button .md-button--primary }

### Indented

[Subscribe to our newsletter](#){ .md-button .md-button--primary .btn-grey .btn-indent }

#### Grouped

[Subscribe to our newsletter](#){ .md-button .md-button--primary .btn-grey .btn-indent }
[Subscribe to our newsletter](#){ .md-button .md-button--primary .btn-yellow .btn-round }

#### Small

[Subscribe to our newsletter](#){ .md-button .md-button--primary .btn-grey .btn-indent .btn-small }

## Test include page

{% include "./_components/image.md" %}

## Test text formatting

### Highlighting changes

Text can be {--deleted--} and replacement text {++added++}. This can also be
combined into {~~one~>a single~~} operation. {==Highlighting==} is also
possible {>>and comments can be added inline<<}.

{==

Formatting can also be applied to blocks by putting the opening and closing
tags on separate lines and adding new lines between the tags and the content.

==}

### Highlighting text

- ==This was marked (highlight)==
- ^^This was inserted (underline)^^
- ~~This was deleted (strikethrough)~~

### Sub- and superscripts

- H~2~O
- A^T^A

### Adding keyboard keys

++ctrl+alt+del++

## Test footnotes

!!! warning
    Footnotes always placed at last of page, regardless referrer place.

Lorem ipsum[^1] dolor sit amet, consectetur adipiscing elit.[^2]

[^1]: Lorem ipsum dolor sit amet, consectetur adipiscing elit.

[^2]:
    Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla et euismod
    nulla. Curabitur feugiat, tortor non consequat finibus, justo purus auctor
    massa, nec semper lorem quam in massa.
