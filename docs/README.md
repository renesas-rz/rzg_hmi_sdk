# rzg_hmi_sdk/docs

This is a documentation sources for [rzg_hmi_sdk](https://renesas-rz.github.io/rzg_hmi_sdk) website (github.io).

## Prepare environment

Python3 and pip3 are required.

In some case you may need to make a `symlink` to pip (of python3).

### Setup from script

Working directory should be `rzg_hmi_sdk/docs/`.

```
. work/setup.sh
```

### Serve local server

Working directory should be `rzg_hmi_sdk/docs/`.

```
. serve.sh
```

## Test versioning with `mike`

Working directory should be `rzg_hmi_sdk/docs/`.

### Deploy

This will generate a static website into `local/gh-pages` branch.

`dev` will be used as version.

```
. mike/deploy.sh
```

### Serve

You must deploy first.

```
. mike/serve.sh
```

### Clean-up

This step is not mandatory.

After you complete checking your website, you may want to remove `local/gh-pages` branch.

```
. mike/remove.sh
```
