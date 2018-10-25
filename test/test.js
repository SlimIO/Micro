// Require Third-party Dependencies
const avaTest = require("ava");
const is = require("@slimio/is");

// Require Micro
const Micro = require("..");

avaTest("Micro.now()", (assert) => {
    const ts = Micro.now();
    assert.true(is.number(ts));
    assert.is(ts.toString().length, 16);
});

avaTest("Micro.clock.now()", (assert) => {
    const ts = Micro.clock.now();
    assert.true(is.number(ts));
    assert.is(ts.toString().length, 16);
});

avaTest("Micro.gettimeofday()", (assert) => {
    const timeval = Micro.gettimeofday();
    assert.true(is.plainObject(timeval));
    assert.is(Object.keys(timeval).length, 2);
    assert.true(is.number(timeval.sec));
    assert.true(is.number(timeval.usec));
    assert.is(timeval.sec.toString().length, 10);
    assert.is(timeval.usec.toString().length, 6);
});

avaTest("Micro.clock.gettime()", (assert) => {
    const timespec = Micro.clock.gettime();
    assert.true(is.plainObject(timespec));
    assert.is(Object.keys(timespec).length, 2);
    assert.true(is.number(timespec.sec));
    assert.true(is.number(timespec.nsec));
    assert.is(timespec.sec.toString().length, 6);
    assert.is(timespec.nsec.toString().length, 9);
});
