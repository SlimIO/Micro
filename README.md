# Micro

NodeJS C++ NAPI low level binding to get high resolution timestamp.

This API is synchronous.

## Getting Started

This package is available in the Node Package Repository and can be easily installed with [npm](https://docs.npmjs.com/getting-started/what-is-npm) or [yarn](https://yarnpkg.com).

```bash
$ npm i @slimio/micro
# or
$ yarn add @slimio/micro
```

## Usage example

```js
const { now, gettimeofday, clock } = require("@slimio/micro");

console.log(now()); // 1538484472718548
console.log(gettimeofday()); // { sec: 1538484493, usec: 222313 }
console.log(clock.now());
console.log(clock.gettime());
```

## API

### now(): number
Return the current timestamp as **microsecond**. You can achieve the same result with gettimeofday():
```js
const tv = micro.gettimeofday();
const now = (tv.sec * 1000000) + tv.usec;
console.log(now); // 1538484472718548
```

> Warning: Micro.now() suffers the effects of drift like Date.now()

### gettimeofday(): timeval
UNIX gettimeofday binding (polyfill has been added for Windows too). Return a **timeval** interface Object.
```ts
interface timeval {
    sec: number;
    usec: number;
}

export function gettimeofday(): timeval;
```

### clock.gettime(): timespec;
UNIX clock_gettime binding (polyfill has been added for Windows too). Return a **timespec** interface Object. This method work like NodeJS process.hrtime.

### clock.now(): number;
Return a millisecond no-drift timestamp. You can achieve the same with `clock.gettime()`:

```js
const { sec, usec } = micro.clock.gettime();
console.log(sec * 1e3 + usec / 1e6);

// same as:
console.log(micro.clock.now());
```

## How to build the project

Before building the project, be sure to get the following npm package installed:

- Install (or upgrade to) NodeJS v10+ and npm v6+
- [Windows build tools](https://www.npmjs.com/package/windows-build-tools)

Then, just run normal npm install command:

```bash
$ npm install
```

## Available commands

All projects commands are described here:

| command | description |
| --- | --- |
| npm run prebuild | Generate addon prebuild |
| npm run doc | Generate JSDoc .HTML documentation (in the /docs root directory) |
| npm run coverage | Generate coverage of tests |
| npm run report | Generate .HTML report of tests coverage |

> the report command have to be triggered after the coverage command.
