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

    const len = ts.toString().length;
    assert.true(len === 12 || len === 13);
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

    const slen = timespec.sec.toString().length;
    assert.true(slen === 5 || slen === 6);

    const nlen = timespec.nsec.toString().length;
    assert.true(nlen === 8 || nlen === 9);
});
