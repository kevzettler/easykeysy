compile with

```shell
cd native
./node_modules/.bin/node-gyp configure
./node_modules/.bin/node-gyp build
```
test with
```shell
cd native node test.js
```

for rapid testing, build and run the test
```shell
./node_modules/.bin/node-gyp build; node test.j
```
