/// <reference path = "index.d.ts"/>

declare var convertCPPType: (cppType: any, instance: any) => any;
declare var getCppTypeName: (cppType: any) => string;
declare var $isValidCppObject: (obj: any) => boolean;

type HWND__ = number;
type DWORD = number;

type char = number;
type wchar = number;
type wchar_t = number;
type unsigned_char = number;
type short = number;
type unsigned_short = number;
type int = number;
type unsigned_int = number;
type long = number;
type unsigned_long = number;
type long_long = number;
type unsigned_long_long = number;
type float = number;
type double = number;
type long_double = number;
type uint8 = number;
type uint32 = number;
type int32 = number;
type uint64 = number;

type entt_entity = number;

type EventTypeExt = number;
type CustomEventType = number;

// temp
declare class IGameplayCueInterface {}

declare class StdVector<T> {
    push_back(item: T): void;
    pop_back(): void;
    size(): number;
    clear(): void;
    empty(): boolean;
    at(index: number): T;
}

declare class StdMap<K, V> {
    size(): number;
    clear(): void;
    empty(): boolean;
    at(key: K): V;
    erase(key: K): number;
    count(key: K): number;
}
