// Require Third-party Dependencies
const avaTest = require("ava");
const is = require("@slimio/is");

// Require Micro
const Micro = require("..");

avaTest("Micro.now()", (assert) => {
    const ts = Micro.now();
    assert.true(is.number(ts));
    assert.true(ts.toString().length === 16);
});

avaTest("Micro.gettimeofday()", (assert) => {
    const timeval = Micro.gettimeofday();
    assert.true(is.plainObject(timeval));
    assert.true(Object.keys(timeval).length === 2);
    assert.true(is.number(timeval.sec));
    assert.true(is.number(timeval.usec));
    assert.true(timeval.sec.toString().length === 10);
    assert.true(timeval.usec.toString().length === 6);
});
