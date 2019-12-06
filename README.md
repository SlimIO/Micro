# Micro
![version](https://img.shields.io/badge/dynamic/json.svg?url=https://raw.githubusercontent.com/SlimIO/Micro/master/package.json&query=$.version&label=Version)
[![Maintenance](https://img.shields.io/badge/Maintained%3F-yes-green.svg)](https://github.com/SlimIO/Micro/commit-activity)
[![mit](https://img.shields.io/github/license/Naereen/StrapDown.js.svg)](https://github.com/SlimIO/Micro/blob/master/LICENSE)
![dep](https://img.shields.io/david/SlimIO/Micro)
![size](https://img.shields.io/github/languages/code-size/SlimIO/Micro)
![known vulnerabilities](https://img.shields.io/snyk/vulnerabilities/github/SlimIO/Micro)
[![Build Status](https://travis-ci.com/SlimIO/Micro.svg?branch=master)](https://travis-ci.com/SlimIO/Micro)

NodeJS C++ NAPI low level binding to get high resolution timestamp.

This API is synchronous.

## Requirements
- [Node.js](https://nodejs.org/en/) v12 or higher

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

## Contribution Guidelines
To contribute to the project, please read the [code of conduct](https://github.com/SlimIO/Governance/blob/master/COC_POLICY.md) and the guide for [N-API compilation](https://github.com/SlimIO/Governance/blob/master/docs/native_addons.md).

## Dependencies

|Name|Refactoring|Security Risk|Usage|
|---|---|---|---|
|[node-addon-api](https://github.com/nodejs/node-addon-api)|⚠️Major|Low|Node.js C++ addon api|
|[node-gyp-build](https://github.com/prebuild/node-gyp-build)|⚠️Major|Low|Node-gyp builder|

## License
MIT
