

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

declare class StdSet<T> {
    size(): number;
    clear(): void;
    empty(): boolean;
    erase(item: T): number;
    count(item: T): number;
}
