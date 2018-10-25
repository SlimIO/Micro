declare namespace Micro {
    interface timeval {
        sec: number;
        usec: number;
    }

    interface timespec {
        sec: number;
        nsec: number;
    }

    export function gettimeofday(): timeval;
    export function now(): number;

    export namespace clock {
        export function now(): number;
        export function gettime(): timespec;
    }
}

export as namespace Micro;
export = Micro;
