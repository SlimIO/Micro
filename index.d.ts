declare namespace Micro {
    interface timeval {
        sec: number;
        usec: number;
    }

    export function gettimeofday(): timeval;
    export function now(): number;
}

export as namespace Micro;
export = Micro;
